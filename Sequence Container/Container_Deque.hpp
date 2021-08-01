/* deque implementation
 *
 * Copyright(c) 2021 Mashiro -1262159823@qq.com
 *
 * This File is part of CONTAINER LIBRARY project.
 *
 * version : 1.0.0
 *
 * author : Mashiro
 *
 * File name : Container_Deque.hpp -a kind of sequence container.
 *
 * This library is free software;you can redistribute is and/or modify it
 * under the APACHE LICENSE 2.0 as published by the Free Software Foundation.
 * ------------------------------------------------------------------------
 *
 *-------------------------------README------------------------------------
 *
 * template<typename Ty,_alloc = _default_allocator>
 * class deque
 * {
 *		//iterator : deque_iterator
 *		//const_iterator : const_deque_iterator
 *
 *      //ctor
 *
 *      deque()
 *      deque(size_t size)-------------------------------initialized with size.
 *      deque(size_t size,Ty elem)-----------------------initializer with size and fill with elem.
 *      deque(const initializer_list<Ty>& list)
 *      deque(const deque<Ty,_alloc>& obj)
 *
 *      //operations
 *
 *		void insert(Ty elem)-----------------------------call push_back().
 *      void push_back(Ty elem)--------------------------insert at end.
 *      void push_front(Ty elem)-------------------------insert at head.
 *      void pop_back()----------------------------------pop last elem.
 *      void pop_front()---------------------------------pop first elem.
 *      iterator erase(iterator ptr)---------------------erase elem at iterator position.
 *      const_iterator erase(const_iterator ptr)
 *      void erase(iterator p_begin,iterator p_end)------erase elem in iterator range.
 *      void clear()-------------------------------------erase all elem.
 *      Ty front()---------------------------------------return first elem.
 *      Ty back()----------------------------------------return last elem.
 *		bool search(Ty elem)
 *		iterator find(Ty elem)
 *		const_iterator cfind(Ty elem)
 *      void resize(size_t resize)-----------------------resize container.
 *      int size()---------------------------------------return number of elems.
 *		size_t buffers()
 *		size_t bodys()
 *      size_t max_size()--------------------------------return size of container.
 *		bool empty()-------------------------------------return true if container is empty.
 *      void swap(self& obj)------------------------make swap operation.
 *
 *      //iterator
 *
 *      iterator begin()
 *      iterator end()
 *      const_iterator cbegin() const
 *      const_iterator cend() const
 *
 *      //operator overload
 *
 *      decltype(auto) operator[](int n)
 *      self& operator=(const self& obj)
 *      bool operator==(const coll& obj)
 *      bool operator!=(const coll& obj)
 *      bool operator>(const coll& obj)
 *      bool operator<(const coll& obj)
 *      bool operator>=(const coll& obj)
 *      bool operator<=(const coll& obj)
 *
 *      //private functions
 *
 *      void MemoryExpand(size_t resize)----------------------resize and expand size of container.
 *      void alloc()------------------------------------------allocation memory
 *		void ptr_alloc(Ty** &ptr,int size)
 *		void destroy()
 * }
 * ----------------------------------------------------------------------------------------------
*/

#pragma once
#include<initializer_list>
#include"memory.hpp"
#include"iterator.hpp"
#include"errors.hpp"
#include"memory_allocator.hpp"


#if _LIB_DEBUG_LEVEL == 1

#include<assert.h>

#endif // _LIB_DEBUG_LEVEL == 1

using std::initializer_list;


template<typename Ty , typename _alloc = _default_allocator>
class deque
{
	private:
		Ty** map_ptr = nullptr;

		size_t body_size = 10;
		size_t buffer_size = 8;

		int last_flag = 0;						//last buffer flag
		int head_flag = 0;						//head buffer flag
		int last_insert = 0;					//last insert flag
		int head_insert = (int)body_size - 1;   //head insert flag

		int elem_count = 0;
		int buffer_distance = 1;

	public:
		using self = deque<Ty , _alloc>;
		using TypeValue = Ty;
		using iterator = deque_iterator<Ty>;
		using const_iterator = const_deque_iterator<Ty>;

	public:
		deque() noexcept
		{
			alloc();
		}

		explicit deque(const size_t& size)
		{
		#if _LIB_DEBUG_LEVEL == 1

			_BUG_VERIFY((size > 0) , "container size error");
			assert(size > 0);

		#endif // _LIB_DEBUG_LEVEL == 1

			buffer_size = size;
			alloc();
		}

		deque(const size_t& size , const Ty& elem)
		{
		#if _LIB_DEBUG_LEVEL == 1

			_BUG_VERIFY((size > 0) , "container size error");
			assert(size > 0);

		#endif // _LIB_DEBUG_LEVEL == 1

			buffer_size = size;
			alloc();

			for (int n = 0; n < body_size; ++n)
			{
				map_ptr[last_flag][n] = elem;
			}

			elem_count = body_size;
			last_insert = body_size;
		}

		explicit deque(const initializer_list<Ty>& list) noexcept
		{
			body_size = list.size();
			head_insert = (int)body_size - 1;

			alloc();

			for (auto p : list)
			{
				map_ptr[last_flag][elem_count++] = p;
			}

			last_insert = (int)body_size;
		}

		deque(const deque<Ty , _alloc>& obj) noexcept
		{
			elem_count = obj.elem_count;
			buffer_distance = obj.buffer_distance;
			buffer_size = obj.buffer_size;
			body_size = obj.body_size;
			last_flag = obj.last_flag;
			head_flag = obj.head_flag;


			alloc();

			last_insert = obj.last_insert;
			head_insert = obj.head_insert;

			for (int n = head_flag; n <= last_flag; ++n)
			{
				if (obj.map_ptr[n] != nullptr)
				{
					if (map_ptr[n] == nullptr)
						map_ptr[n] = simple_allocator(_alloc , Ty)::allocate((int)body_size);

					for (int i = 0; i < body_size; ++i)
					{
						map_ptr[n][i] = obj.map_ptr[n][i];
					}
				}
			}
		}

		~deque() noexcept
		{
			destory();
		}


		//push and pop operation

		[[noreturn]] void insert(const Ty& elem) noexcept
		{
			push_back(elem);
		}

		[[noreturn]] void push_back(const Ty& elem) noexcept
		{
			if (last_insert == body_size)
			{
				if (last_flag == buffer_size - 1)
				{
					buffer_size = buffer_size * 2;
					MemoryExpand(buffer_size);
				}

				map_ptr[++last_flag] = simple_allocator(_alloc , Ty)::allocate((int)body_size);
				last_insert = 0;
				buffer_distance++;
			}

			map_ptr[last_flag][last_insert++] = elem;
			elem_count++;
		}

		[[noreturn]] void push_front(const Ty& elem) noexcept
		{
			if (head_insert == -1)
			{
				if (head_flag == 0)
				{
					buffer_size = buffer_size * 2;
					MemoryExpand(buffer_size);
				}

				map_ptr[--head_flag] = simple_allocator(_alloc , Ty)::allocate((int)body_size);
				head_insert = body_size - 1;
				buffer_distance++;
			}

			map_ptr[head_flag][head_insert--] = elem;
			elem_count++;
		}

		[[noreturn]] void pop_back() noexcept
		{
			if (elem_count > 0)
			{
				memory::elem_destory(back());

				if (last_insert == 0)
				{
					last_flag--;
					last_insert = (int)body_size - 1;

					buffer_distance--;
				}
				else
				{
					last_insert--;
				}

				elem_count--;
			}
		}

		[[noreturn]] void pop_front() noexcept
		{
			if (elem_count > 0)
			{
				memory::elem_destory(front());

				if (head_insert == body_size - 1)
				{
					head_flag++;
					head_insert = 0;

					buffer_distance--;
				}
				else
				{
					head_insert++;
				}

				elem_count--;
			}
		}


		//erase and clear operation

		_NODISCARD iterator erase(iterator ptr) noexcept
		{
			Ty next_val;

			if (ptr.step() == end().step() - 1)
				next_val = *(end() - 1);
			else
				next_val = *(ptr + 1);

			memory::elem_destory(*ptr);

			//save data
			Ty* arr = new Ty[elem_count];
			int count = 0;

			auto p = begin();
			for (; p != end(); ++p)
			{
				if (*p != *ptr)
					arr[count++] = *p;
			}

			//clear
			clear();


			//move data
			int temp = count;
			count = 0;
			for (int n = 0; n < temp; ++n)
			{
				push_back(arr[count++]);
			}

			return find(next_val);
		}

		_NODISCARD const_iterator erase(const_iterator ptr) noexcept
		{
			Ty next_val;

			if (ptr.step() == end().step() - 1)
				next_val = *(end() - 1);
			else
				next_val = *(ptr + 1);

			memory::elem_destory(*ptr);

			//save data
			Ty* arr = new Ty[elem_count];
			int count = 0;

			auto p = begin();
			for (; p != end(); ++p)
			{
				if (*p != *ptr)
					arr[count++] = *p;
			}


			//clear
			clear();


			//move data
			int temp = count;
			count = 0;
			for (int n = 0; n < temp; ++n)
			{
				push_back(arr[count++]);
			}

			return cfind(next_val);
		}

		[[noreturn]] void erase(iterator p_begin , iterator p_end) noexcept
		{
			int begin = p_begin.step();
			int end = p_end.step();

			for (int n = begin; n < end; ++n)
			{
				p_begin = erase(p_begin);
			}
		}

		[[noreturn]] void clear() noexcept
		{
			destory();
			alloc();

			elem_count = 0;
			last_insert = 0;
			head_insert = body_size - 1;
			buffer_distance = 1;
		}


		//other

		_NODISCARD Ty& front() noexcept
		{
			if (head_insert == body_size - 1)
				return map_ptr[last_flag][0];
			else
				return map_ptr[head_flag][head_insert + 1];
		}

		_NODISCARD const Ty& front() const noexcept
		{
			if (head_insert == body_size - 1)
				return map_ptr[last_flag][0];
			else
				return map_ptr[head_flag][head_insert + 1];
		}

		_NODISCARD Ty& back() noexcept
		{
			return map_ptr[last_flag][last_insert - 1];
		}

		_NODISCARD const Ty& back() const noexcept
		{
			return map_ptr[last_flag][last_insert - 1];
		}

		_NODISCARD bool search(const Ty& elem) const noexcept
		{
			auto p = begin();
			for (; p != end(); ++p)
			{
				if (*p == elem)
					return true;
			}

			return false;
		}

		_NODISCARD iterator find(const Ty& elem) noexcept
		{
			auto p = begin();
			for (; p != end(); ++p)
			{
				if (*p == elem)
					return p;
			}

			return end();
		}

		_NODISCARD const_iterator cfind(const Ty& elem) const noexcept
		{
			auto p = cbegin();
			for (; p != cend(); ++p)
			{
				if (*p == elem)
					return p;
			}

			return cend();
		}

		void resize(size_t size)
		{
		#if _LIB_DEBUG_LEVEL == 1

			_BUG_VERIFY((size > 0) , "container size error");
			assert(size > 0);

		#endif // _LIB_DEBUG_LEVEL == 1

			if ((int)(size * body_size) == elem_count)
				return;

			if ((int)(size * body_size) < elem_count)	//smaller
			{
				while (size * body_size < elem_count)
				{
					pop_back();
				}
			}
			else                                        //bigger
			{
				MemoryExpand(size);
			}

			buffer_size = size;
		}

		_NODISCARD int size() const noexcept
		{
			return elem_count;
		}

		_NODISCARD size_t buffers() const noexcept
		{
			return buffer_size;
		}

		_NODISCARD size_t bodys() const noexcept
		{
			return body_size;
		}

		_NODISCARD size_t max_size() const noexcept
		{
			return (buffer_size * body_size);
		}

		_NODISCARD bool empty() const noexcept
		{
			return (elem_count == 0);
		}

		[[noreturn]] void swap(self& obj) noexcept
		{
			Ty** temp_arr = map_ptr;
			Ty** obj_arr = obj.map_ptr;

			//map_ptr swap
			map_ptr = obj_arr;
			obj.map_ptr = temp_arr;


			//flags swap

			size_t size_temp = body_size;
			body_size = obj.body_size;
			obj.body_size = size_temp;

			size_temp = buffer_size;
			buffer_size = obj.buffer_size;
			obj.buffer_size = size_temp;

			int int_temp = last_flag;
			last_flag = obj.last_flag;
			obj.last_flag = int_temp;

			int_temp = head_flag;
			head_flag = obj.head_flag;
			obj.head_flag = int_temp;

			int_temp = last_insert;
			last_insert = obj.last_insert;
			obj.last_insert = int_temp;

			int_temp = head_insert;
			head_insert = obj.head_insert;
			obj.head_insert = int_temp;

			int_temp = elem_count;
			elem_count = obj.elem_count;
			obj.elem_count = int_temp;

			int_temp = buffer_distance;
			buffer_distance = obj.buffer_distance;
			obj.buffer_distance = int_temp;
		}



		//iterator

		_NODISCARD iterator begin() noexcept
		{
			if (head_insert == body_size - 1)
				return iterator(map_ptr , 0 , head_flag + 1 , (int)body_size , 0);
			else
				return iterator(map_ptr , head_insert + 1 , head_flag , (int)body_size , 0);
		}

		_NODISCARD iterator begin() const noexcept
		{
			if (head_insert == body_size - 1)
				return iterator(map_ptr , 0 , head_flag + 1 , (int)body_size , 0);
			else
				return iterator(map_ptr , head_insert + 1 , head_flag , (int)body_size , 0);
		}

		_NODISCARD iterator end() noexcept
		{
			return iterator(map_ptr , last_insert , last_flag , (int)body_size , elem_count);
		}

		_NODISCARD iterator end() const noexcept
		{
			return iterator(map_ptr , last_insert , last_flag , (int)body_size , elem_count);
		}

		_NODISCARD const_iterator cbegin() const noexcept
		{
			if (head_insert == body_size - 1)
				return const_iterator(map_ptr , 0 , head_flag + 1 , (int)body_size , 0);
			else
				return const_iterator(map_ptr , head_insert + 1 , head_flag , (int)body_size , 0);
		}

		_NODISCARD const_iterator cend() const noexcept
		{
			return const_iterator(map_ptr , last_insert , last_flag , (int)body_size , elem_count);
		}



		//opeartor overload

		_NODISCARD const Ty*& operator[](int n) const
		{
		#if _LIB_DEBUG_LEVEL == 1

			_BUG_VERIFY(((n < elem_count) && (n >= 0)) , "out of range");
			assert(n < elem_count&& n >= 0);

		#endif // _LIB_DEBUG_LEVEL == 1

			return map_ptr[n];
		}

		_NODISCARD Ty*& operator[](int n)
		{
		#if _LIB_DEBUG_LEVEL == 1

			_BUG_VERIFY(((n < elem_count) && (n >= 0)) , "out of range");
			assert(n < elem_count&& n >= 0);

		#endif // _LIB_DEBUG_LEVEL == 1

			return map_ptr[n];
		}

		self& operator=(const self& obj) noexcept
		{
			clear();

			auto p = obj.cbegin();
			for (; p != obj.cend(); ++p)
			{
				push_back(*p);
			}

			return *this;
		}

		template<typename coll>
		_NODISCARD bool operator==(const coll& obj) const noexcept
		{
			if (elem_count != obj.size())
				return false;

			auto p1 = cbegin();
			auto p2 = obj.cbegin();

			for (; p1 != cend() , p2 != obj.cend(); ++p1 , ++p2)
			{
				if (*p1 != *p2)
					return false;
			}

			return true;
		}

		template<typename coll>
		_NODISCARD bool operator!=(const coll& obj) const noexcept
		{
			return !((*this) == obj);
		}

		template<typename coll>
		_NODISCARD bool operator>(const coll& obj) const noexcept
		{
			return (elem_count > obj.size());
		}

		template<typename coll>
		_NODISCARD bool operator>=(const coll& obj) const noexcept
		{
			return (elem_count >= obj.size());
		}

		template<typename coll>
		_NODISCARD bool operator<(const coll& obj) const noexcept
		{
			return (elem_count < obj.size());
		}

		template<typename coll>
		_NODISCARD bool operator<=(const coll& obj) const noexcept
		{
			return (elem_count <= obj.size());
		}

	private:
		[[noreturn]] void alloc() noexcept
		{
			map_ptr = simple_allocator(_alloc , Ty*)::allocate((int)buffer_size);

			for (int n = 0; n < buffer_size; ++n)
			{
				map_ptr[n] = nullptr;
			}

			last_flag = (int)buffer_size / 2;
			head_flag = last_flag - 1;

			map_ptr[last_flag] = simple_allocator(_alloc , Ty)::allocate((int)body_size);
			map_ptr[head_flag] = simple_allocator(_alloc , Ty)::allocate((int)body_size);
		}

		[[noreturn]] void ptr_alloc(Ty**& ptr , int size) noexcept
		{
			for (int n = 0; n < size; ++n)
			{
				ptr[n] = nullptr;
			}
		}

		[[noreturn]] void destory() noexcept
		{
			if (map_ptr != nullptr)
			{
				for (int n = 0; n < buffer_size; ++n)
				{
					if (map_ptr[n] != nullptr)
						simple_allocator(_alloc , Ty)::deallocate(map_ptr[n],body_size * sizeof(Ty));
				}

				map_ptr = nullptr;
			}
		}

		[[noreturn]] void MemoryExpand(size_t size)
		{
		#if _LIB_DEBUG_LEVEL == 1

			_BUG_VERIFY((size > 0) , "container size error");
			assert(size > 0);

		#endif // _LIB_DEBUG_LEVEL == 1

			if (elem_count != 0) //deque not empty
			{
				Ty** temp_arr = new Ty * [size];
				ptr_alloc(temp_arr , (int)size);

				int count = 0;
				for (int n = head_flag; n <= last_flag; ++n) // save data
				{
					temp_arr[count] = new Ty[body_size];

					for (int i = 0; i < body_size; ++i)
					{
						temp_arr[count][i] = map_ptr[n][i];
					}

					count++;
				}

				simple_allocator(_alloc , Ty*)::deallocate(map_ptr , buffer_size * sizeof(Ty*));
				map_ptr = simple_allocator(_alloc , Ty*)::allocate((int)size);
				ptr_alloc(map_ptr , (int)size);

				int map_count = (int)size / 2 - 1;
				for (int n = 0; n < size; ++n)				       //copy
				{
					if (temp_arr[n] != nullptr)
					{
						map_ptr[map_count] = simple_allocator(_alloc , Ty)::allocate((int)body_size);

						for (int i = 0; i < body_size; ++i)
						{
							map_ptr[map_count][i] = temp_arr[n][i];
						}

						map_count++;
					}
				}


				//reset flags;
				head_flag = (int)size / 2 - 1;
				last_flag = (int)(head_flag + buffer_distance);

				delete[] temp_arr;
				temp_arr = nullptr;
			}
			else               //deque is empty
			{
				buffer_size = size;
				alloc();
			}
		}
};