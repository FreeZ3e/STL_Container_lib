/*implementation of memory alloctor
* 
* Copyright(c) 2021 Mashiro -1262159823@qq.com
* 
* This File is part of CONTAINER LIBRARY project.
* 
* version : 1.3.0-alpha
* 
* author : Mashiro
* 
* File name : memory_allocator.hpp -memory allocator.
* 
* This library is free software;you can redistribute is and/or modify it
* under the APACHE LICENSE 2.0 as published by the Free Software Foundation.
* ---------------------------------------------------------------------------
*/

#pragma once
#include"errors.hpp"

#if _LIB_DEBUG_LEVEL == 1

#include<assert.h>

#endif //_LIB_DEBUG_LEVEL == 1


//marco define------------------------------------------------------------

#define default_alloc _default_allocator
#define buddy_alloc _buddy_allocator
#define malloc_alloc _malloc_allocator

#define simple_malloc(classname) simple_alloc<classname , malloc_alloc>
#define simple_default_alloc(classname) simple_alloc<classname , default_alloc>
#define simple_buddy_alloc(classname) simple_alloc<classname , buddy_alloc>
#define simple_allocator(allocator,classname) simple_alloc<classname , allocator>

//allocator wrappers-------------------------------------------------------

//check for allocator
class alloc_count
{
	template<typename Ty , typename alloc>
	friend class simple_alloc;

	private:
		//alloc count
		static int count;

	public:
		~alloc_count()
		{
			check();
		}

		void check() const
		{
			if (count != 0)
				_MEMORY_FREE_CHECK;
		}
};
int alloc_count::count = 0;

//simple_alloc
template<typename Ty,typename alloc>
class simple_alloc
{
	public:
		static Ty* allocate(int num)
		{
		#if _LIB_DEBUG_LEVEL == 1

			_BUG_VERIFY((num > 0) , "num must bigger than 0");
			assert(num > 0);

		#endif //_LIB_DEBUG_LEVEL == 1

			alloc_count::count++;
			return (Ty*)alloc::allocate(num * sizeof(Ty));
		}

		static void deallocate(Ty* ptr,size_t size)
		{
			if (ptr != nullptr)
			{
				alloc::deallocate(ptr , size);
 				alloc_count::count--;
			}
		}
};

//----------------------------------------------------------------------------------


//alloc call malloc and free
class _malloc_allocator
{
	using handler = void (*)(void);

	private:
		static handler handler_func;

	public:
		//alloc
		static void* allocate(size_t size)
		{
		#if _LIB_DEBUG_LEVEL == 1

			_BUG_VERIFY((size > 0) , "size must bigger than 0");
			assert(size > 0);

		#endif //_LIB_DEBUG_LEVEL == 1

			void* ptr = malloc(size);

			if (ptr == nullptr)
			{
				ptr = oom_handler(size);
			}

			return ptr;
		}

		//dealloc
		static void deallocate(void* ptr , size_t size)
		{
			if (ptr != nullptr)
				free(ptr);
		}

		//set_handler
		static void set_new_handler(handler new_handler)
		{
			handler_func = new_handler;
		}

	private:
		//out-of-memort handler
		static void* oom_handler(size_t size)
		{
			void* result = nullptr;

			while (1)
			{
				if (handler_func == nullptr)
					_BAD_ALLOC_THROW;

				handler_func();//handle out

				result = malloc(size);
				if (result != nullptr)
					return result;
			}
		}
};

typename _malloc_allocator::handler _malloc_allocator::handler_func = nullptr;



//default_allocator
class _default_allocator
{
	enum {ALIGN = 8};			//round up align
	enum {MAX_BYTES = 128 };	//block max size
	enum {NFREELISTS = 16};		//free-list number

	//memory node
	struct node
	{
		node* next = nullptr;
	};

	//free list block
	struct block
	{
		node* next = nullptr;
		char empty = 0;
	};

	private:
		//free list
		static block free_list[NFREELISTS];

		//memory pool position tag
		static char* start_free;
		static char* end_free;

		//total size
		static size_t heap_size;


	public:
		static void* allocate(size_t size)
		{
		#if _LIB_DEBUG_LEVEL == 1

			_BUG_VERIFY((size > 0) , "size must bigger than 0");
			assert(size > 0);

		#endif //_LIB_DEBUG_LEVEL == 1



			block* my_list = nullptr;
			node* result = nullptr;

			//if size bigger than MAX_BYTES
			//call _malloc_allocator
			if (size > (size_t)MAX_BYTES)
			{
				return _malloc_allocator::allocate(size);
			}

			//location free list position
			my_list = free_list + FREELIST_INDEX(size);
			result = (*my_list).next;

			//list empty
			if (result == nullptr)
			{
				//refill from memory pool
				void* ptr = refill(ROUND_UP(size));
				(*my_list).empty++;
				return ptr;
			}

			(*my_list).next = result->next;
			(*my_list).empty++;
			return result;
		}

		static void deallocate(void* ptr , size_t size)
		{
		#if _LIB_DEBUG_LEVEL == 1

			_BUG_VERIFY((ptr != nullptr) , "empty pointer");
			assert(ptr != nullptr);

		#endif //_LIB_DEBUG_LEVEL == 1

			node* temp = (node*)ptr;
			block* my_list = nullptr;

			//deallocate by free
			if (size > (size_t)MAX_BYTES)
			{
				_malloc_allocator::deallocate(ptr , size);
				return;
			}

			my_list = free_list + FREELIST_INDEX(size);

			temp->next = (*my_list).next;
			(*my_list).next = temp;
			(*my_list).empty--;
		}

	private:
		//round up to align
		static size_t ROUND_UP(size_t size)
		{
			return ((size)+ALIGN - 1 & ~(ALIGN - 1));
		}

		//location index in freelist
		static size_t FREELIST_INDEX(size_t size)
		{
			return (((size)+ALIGN - 1) / ALIGN - 1);
		}

		//count list
		static int LIST_COUNT()
		{
			int count = 0;
			for (int n = 0; n < 16; ++n)
			{
				if (free_list[n].next != nullptr)
					++count;
			}

			return count;
		}

		static void* refill(size_t size)
		{
			//refill blocks number
			int nobjs = 20;

			//get new blocks
			char* chunk = chunk_alloc(size , nobjs);

			block* my_list = nullptr;
			node* result = nullptr;
			node* next_node = nullptr;
			
			if (nobjs == 1)
				return (chunk);

			
			my_list = free_list + FREELIST_INDEX(size);

			result = (node*)chunk;

			//set new block
			(*my_list).next = next_node = (node*)(chunk + size);

			//link blocks
			node* cur_node = nullptr;
			for (int n = 1; ;++n)
			{
				cur_node = next_node;
				next_node = (node*)((char*)next_node + size);

				if (nobjs - 1 == n)
				{
					cur_node->next = nullptr;
					break;
				}
				else
				{
					cur_node->next = next_node;
				}
			}

			return result;
		}

		static char* chunk_alloc(size_t size , int& nobjs)
		{
			char* result = nullptr;
			size_t total_bytes = size * (size_t)nobjs;
			size_t bytes_left = end_free - start_free;

			if (bytes_left >= total_bytes)
			{
				result = start_free;
				start_free += total_bytes;

				return result;
			}
			else if (bytes_left >= size)
			{
				nobjs = (int)(bytes_left / size);
				total_bytes = size * (size_t)nobjs;

				result = start_free;
				start_free += total_bytes;

				return result;
			}
			else
			{
				//new block size
				size_t bytes_to_get = 2 * total_bytes + ROUND_UP(heap_size >> 4);

				//have rest block in memory pool
				//fill to free list
				if (bytes_left > 0)
				{
					block* my_list = free_list + FREELIST_INDEX(bytes_left);

					((node*)start_free)->next = (*my_list).next;
					(*my_list).next = (node*)start_free;
				}

				//to fill memory pool
				start_free = (char*)malloc(bytes_to_get);

				if (start_free == nullptr)	//fail to malloc
				{
					block* my_list = nullptr;
					node* ptr = nullptr;

					//try to find free blocks in free_list 
					for (int n = (int)size; n <= MAX_BYTES; n += ALIGN)
					{
						my_list = free_list + FREELIST_INDEX(n);
						ptr = (*my_list).next;

						if (ptr != nullptr)
						{
							//reset pool tag
							(*my_list).next = ptr->next;
							start_free = (char*)ptr;
							end_free = start_free + n;

							return chunk_alloc(size , nobjs);
						}
					}

					end_free = nullptr;

					//call malloc_allocator
					start_free = (char*)_malloc_allocator::allocate(bytes_to_get);
				}

				//reset memory pool position
				heap_size += bytes_to_get;
				end_free = start_free + bytes_to_get;

				return chunk_alloc(size , nobjs);
			}
		}
};

char* _default_allocator::start_free = nullptr;
char* _default_allocator::end_free = nullptr;
size_t _default_allocator::heap_size = 0;
_default_allocator::block _default_allocator::free_list[_default_allocator::NFREELISTS];


//buddy_allocator
class _buddy_allocator
{
	//min size of pool
	enum{MIN_POOL_SIZE = 1024};
	//min size of block
	enum{MIN_BLOCK_SIZE = 16};
	//min level slot size
	enum{MIN_LEVEL = 4};

	//freelist node
	struct node
	{
		node* next = nullptr;
	};

	//buddy block
	struct block
	{
		unsigned char* pool = nullptr;	//memory pool
		unsigned char* base = nullptr;	//memory free block's base address
		node** freelist = nullptr;		//free-list,each slot is power of 2

		int max_level = 0;	//max level slot
		int min_level = 0;	//min level slot
	};

	private:
		//block header
		static block* header;

		//block initialization tag
		static char is_init;

	public:
		static void* allocate(size_t size)
		{
		#if _LIB_DEBUG_LEVEL == 1

			_BUG_VERIFY((size > 0) , "size must bigger than 0");
			assert(size > 0);

		#endif //_LIB_DEBUG_LEVEL == 1

			size += 1;
			int level = FREELIST_INDEX(size);
			if (level > header->max_level)
			{
				//out of level range
				//call malloc
				return malloc(size);
			}


			//initialization
			if (is_init == 0)
			{
				if (size > MIN_BLOCK_SIZE)
					buddy_init(size * 2);
				else
					buddy_init();

				is_init = 1;
			}

			//find free block
			int n = level;
			for (;; ++n)
			{
				if (n > header->max_level)
				{
					return nullptr;
				}
				if (header->freelist[n] != nullptr)
					break;
			}

			node* ptr = header->freelist[n];
			header->freelist[n] = header->freelist[n]->next;

			//devide blocks to each slots
			node* buddy_ptr = nullptr;
			while (n-- > level)
			{
				buddy_ptr = GET_BUDDY(ptr , n);
				header->freelist[n] = buddy_ptr;
			}


			//recond level tag on block ptr
			//at first byte
			GET_LEVEL(ptr) = level;
			return ptr;
		}

		static void deallocate(void* ptr , size_t size)
		{
		#if _LIB_DEBUG_LEVEL == 1

			_BUG_VERIFY((ptr != nullptr) , "empty pointer");
			assert(ptr != nullptr);

		#endif //_LIB_DEBUG_LEVEL == 1

			int level = FREELIST_INDEX(size);
			if (level > header->max_level)
			{
				free(ptr);
				return;
			}

			node* node_ptr = (node*)ptr;
			int n = GET_LEVEL(node_ptr);

			node* buddy = nullptr;
			node** list = nullptr;

			for (;; ++n)
			{
				buddy = GET_BUDDY(node_ptr , n);

				//find buddy in freelist
				list = &header->freelist[n];

				while (((*list) != nullptr) && ((*list) != buddy))
					list = &(*list)->next;

				//non-exist
				if ((*list) != buddy)
				{
					//insert block to freelist
					node_ptr->next = header->freelist[n];
					header->freelist[n] = node_ptr;
					return;
				}
				else if((*list) != nullptr)
				{
					//link block & buddy
					node_ptr = node_ptr < buddy ? node_ptr : buddy;
					*list = (*list)->next;
				}
			}
		}

		static void destory()
		{
			free(header->freelist);
			free(header->pool);

			is_init = 0;
		}

		static void buddy_init(size_t pool_size = 0 , size_t min_size = 0)
		{
			pool_size = pool_size > MIN_POOL_SIZE ? pool_size : MIN_POOL_SIZE;
			min_size = min_size > MIN_BLOCK_SIZE ? min_size : MIN_BLOCK_SIZE;

			assert(min_size < pool_size);

			pool_size = (size_t)ROUND_UP(pool_size);
			min_size = (size_t)ROUND_UP(min_size);
			header->max_level = FREELIST_INDEX(pool_size);
			header->min_level = FREELIST_INDEX(min_size);

			header->pool = (unsigned char*)calloc(pool_size + sizeof(void*) , 1);
			header->base = header->pool + sizeof(void*);

			header->freelist = (node**)calloc((size_t)header->max_level + 1 , sizeof(node*));

			if(header->freelist != nullptr)
				header->freelist[header->max_level] = (node*)header->base;
			else
			{
			#if _LIB_DEBUG_LEVEL == 1

				_BUG_VERIFY((header->freelist != nullptr) , "init fail");
				assert(header->freelist != nullptr);

			#endif //_LIB_DEBUG_LEVEL == 1
			}
		}

	private:
		//round up to pow of 2
		static inline __int64 ROUND_UP(__int64 n)
		{
			n--;
			n |= n >> 1;
			n |= n >> 2;
			n |= n >> 4;
			n |= n >> 8;
			n |= n >> 16;
			n |= n >> 32;

			return ++n;
		}

		static inline int FREELIST_INDEX(size_t size)
		{
			int level = MIN_LEVEL;
			size_t sz = (size_t)1 << level;

			while (size > sz)
			{
				sz <<= 1;
				level++;
			}

			return level;
		}

		//get address offset
		static inline uintptr_t GET_OFFSET(node* ptr)
		{
			return ((uintptr_t)(ptr)-(uintptr_t)(header)->base);
		}

		//get size of slot
		static inline unsigned char& GET_LEVEL(node* ptr)
		{
			return (*((unsigned char*)ptr-1));
		}

		//get buddy node
		static inline node* GET_BUDDY(node* ptr , int level)
		{
			uintptr_t offset_addr = GET_OFFSET(ptr);
			uintptr_t buddy_addr = offset_addr ^ ((uintptr_t)1 << (uintptr_t)level);

			return (node*)((uintptr_t)header->base + buddy_addr);
		}
};

_buddy_allocator::block* _buddy_allocator::header = new _buddy_allocator::block();
char _buddy_allocator::is_init = 0;