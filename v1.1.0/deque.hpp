/* deque implementation
 *
 * Copyright(c) 2021 Mashiro -1262159823@qq.com
 *
 * This File is part of CONTAINER LIBRARY project.
 *
 * version : 1.1.0
 *
 * author : Mashiro
 *
 * File name : deque.hpp -a kind of sequence container.
 *
 * This library is free software;you can redistribute is and/or modify it
 * under the APACHE LICENSE 2.0 as published by the Free Software Foundation.
 *-------------------------------------------------------------------------
 */

#pragma once
#include"errors.hpp"

#if _LIB_DEBUG_LEVEL == 1

#include<assert.h>

#endif //_LIB_DEBUG_LEVEL

#include<initializer_list>
#include"memory.hpp"
#include"iterator.hpp"
#include"memory_allocator.hpp"

using std::initializer_list;


template<typename Ty , typename _alloc = _default_allocator>
class deque
{
	public:
		using value_type = Ty;
		using reference = Ty&;
		using const_reference = const Ty&;
		using pointer = Ty*;
		using const_pointer = const Ty*;
		using iterator = deque_iterator<Ty>;
		using const_iterator = const_deque_iterator<Ty>;
		using const_reverse_iterator = reverse_iterator<const_iterator>;
		using reverse_iterator = reverse_iterator<iterator>;
		using size_type = size_t;
		using self = deque<Ty , _alloc>;

	private:
		pointer* map_ptr = nullptr;

		size_t body_size = 10;
		size_t buffer_size = 8;

		int last_flag = 0;						//last buffer flag
		int head_flag = 0;						//head buffer flag
		int last_insert = 0;					//last insert flag
		int head_insert = (int)body_size - 1;   //head insert flag

		int elem_count = 0;
		int buffer_distance = 1;

	public:
		deque()
		{
			alloc();
		}

		explicit deque(size_type size)
		{
		#if _LIB_DEBUG_LEVEL == 1

			_BUG_VERIFY((size > 0) , "container size error");
			assert(size > 0);

		#endif // _LIB_DEBUG_LEVEL == 1

			body_size = size;
			head_insert = (int)body_size - 1;

			alloc();
		}

		deque(size_type size , const_reference elem)
		{
		#if _LIB_DEBUG_LEVEL == 1

			_BUG_VERIFY((size > 0) , "container size error");
			assert(size > 0);

		#endif // _LIB_DEBUG_LEVEL == 1

			body_size = size;
			head_insert = (int)body_size - 1;
			alloc();

			for (int n = 0; n < body_size; ++n)
			{
				map_ptr[last_flag][n] = elem;
			}

			elem_count = body_size;
			last_insert = body_size;
		}

		explicit deque(const initializer_list<value_type>& list)
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

		template<typename iter>
		deque(iter beg , iter end)
		{
			body_size = ((size_type)end.step() - beg.step());
			head_insert = (int)body_size - 1;

			alloc();

			while (beg != end)
			{
				map_ptr[last_flag][elem_count++] = *beg;
				++beg;
			}

			last_insert = (int)body_size;
		}

		deque(const self& obj)
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

		deque(self&& obj)
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

			//destory obj map pointer
			for (int n = 0; n < obj.buffer_size; ++n)
			{
				if (obj.map_ptr[n] != nullptr)
					simple_allocator(_alloc , Ty)::deallocate(obj.map_ptr[n] , obj.body_size * sizeof(Ty));
			}

			obj.map_ptr = nullptr;
			obj.elem_count = 0;
		}

		~deque()
		{
			destory();
		}



		[[noreturn]] void assgin(int size , const_reference elem)
		{
			if (size > elem_count)
			{
				iterator beg = begin();

				while (beg != end())
				{
					*beg = elem;
					++beg;
					--size;
				}

				while (size > 0)
				{
					push_back(elem);
					--size;
				}
			}
			else
			{
				iterator beg = begin();
				int step = elem_count - size;

				while (size > 0)
				{
					*beg = elem;
					++beg;
					--size;
				}

				for (int n = 0; n < step; ++n)
				{
					pop_back();
				}
			}
		}

		template<typename iter>
		[[noreturn]] void assgin(iter beg , iter p_end)
		{
			int size = p_end.step() - beg.step();

			if (size > elem_count)
			{
				auto temp = begin();
				while (temp.step() != end().step())
				{
					*temp = (*beg++);
					++temp;
					--size;
				}

				while (size > 0)
				{
					push_back((*beg++));
					--size;
				}
			}
			else
			{
				auto temp = begin();
				int step = elem_count - size;

				while (size > 0)
				{
					*temp = (*beg++);
					++temp;
					--size;
				}

				for (int n = 0; n < step; ++n)
				{
					pop_back();
				}
			}
		}

		[[noreturn]] void assgin(const initializer_list<value_type>& list)
		{
			int size = list.size();

			if (size > elem_count)
			{
				auto temp = begin();
				auto pos = list.begin();

				while (temp != end())
				{
					*temp = (*pos++);
					++temp;
					--size;
				}

				while (size > 0)
				{
					push_back((*pos++));
					--size;
				}
			}
			else
			{
				auto temp = begin();
				auto pos = list.begin();
				int step = elem_count - size;

				while (size > 0)
				{
					*temp = (*pos++);
					++temp;
					--size;
				}

				for (int n = 0; n < step; ++n)
				{
					pop_back();
				}
			}
		}

		[[noreturn]] void insert(const iterator pos , const_reference elem)
		{
			if (pos >= end())
			{
				push_back(elem);
				return;
			}

			push_back(*(end() - 1));
			iterator iter = end() - 2;

			while (iter != pos)
			{
				*iter = *(iter - 1);
				--iter;
			}

			*iter = elem;
		}

		[[noreturn]] void insert(const iterator pos , value_type&& elem)
		{
			if (pos >= end())
			{
				push_back(elem);
				return;
			}

			push_back(*(end() - 1));
			iterator iter = end() - 2;

			while (iter != pos)
			{
				*iter = *(iter - 1);
				--iter;
			}

			*iter = elem;
		}

		template<typename iter>
		[[noreturn]] void insert(const iterator pos , iter beg , iter end)
		{
			while (end >= beg)
			{
				insert(pos , *(end--));
			}
		}

		[[noreturn]] void insert(const iterator pos , const initializer_list<value_type>& list)
		{
			auto temp = list.end() - 1;
			while (temp >= list.begin())
			{
				insert(pos , *(temp--));
			}
		}

		[[noreturn]] void insert(const_reference elem)
		{
			push_back(elem);
		}

		[[noreturn]] void insert(value_type&& elem)
		{
			push_back(elem);
		}

		[[noreturn]] void push_back(const_reference elem)
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

		[[noreturn]] void push_back(value_type&& elem)
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

		[[noreturn]] void push_front(const_reference elem)
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

		[[noreturn]] void push_front(value_type&& elem)
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

		[[noreturn]] void pop_back()
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

		[[noreturn]] void pop_front()
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

		template<typename... value>
		_NODISCARD iterator emplace(const iterator pos , value&&... arg)
		{
			if (pos >= end())
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

				pointer temp = map_ptr[last_flag] + last_insert++;
				new(temp) value_type(arg...);

				elem_count++;
				return begin()+pos.step();
			}

			push_back(*(end() - 1));
			iterator iter = end() - 2;

			while (iter != pos)
			{
				*iter = *(iter - 1);
				--iter;
			}

			pointer temp = map_ptr[iter.buffer()] + iter.insert_flag();
			new(temp) value_type(arg...);
			

			return (begin() + pos.step());
		}

		template<typename... value>
		[[noreturn]] void emplace_back(value&&... arg)
		{
			emplace(end() , arg...);
		}

		template<typename... value>
		[[noreturn]] void emplace_front(value&&... arg)
		{
			emplace(begin() , arg...);
		}



		_NODISCARD iterator erase(iterator ptr)
		{
			Ty next_val;

			if (ptr.step() == end().step() - 1)
				next_val = *(end() - 1);
			else
				next_val = *(ptr + 1);

			memory::elem_destory(*ptr);

			//save data
			Ty* arr = simple_allocator(_alloc , Ty)::allocate((int)elem_count);
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

		_NODISCARD const_iterator erase(const_iterator ptr)
		{
			Ty next_val;

			if (ptr.step() == end().step() - 1)
				next_val = *(end() - 1);
			else
				next_val = *(ptr + 1);

			memory::elem_destory(*ptr);

			//save data
			Ty* arr = simple_allocator(_alloc , Ty)::allocate((int)elem_count);
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

		[[noreturn]] void erase(iterator p_begin , iterator p_end)
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



		_NODISCARD reference front() noexcept
		{
			if (head_insert == body_size - 1)
				return map_ptr[last_flag][0];
			else
				return map_ptr[head_flag][head_insert + 1];
		}

		_NODISCARD const_reference front() const noexcept
		{
			if (head_insert == body_size - 1)
				return map_ptr[last_flag][0];
			else
				return map_ptr[head_flag][head_insert + 1];
		}

		_NODISCARD reference back() noexcept
		{
			return map_ptr[last_flag][last_insert - 1];
		}

		_NODISCARD const_reference back() const noexcept
		{
			return map_ptr[last_flag][last_insert - 1];
		}

		_NODISCARD reference at(size_type n)
		{
			return *(begin() + n);
		}

		_NODISCARD const_reference at(size_type n) const
		{
			return *(begin() + n);
		}

		_NODISCARD bool search(const_reference elem) const
		{
			auto p = begin();
			for (; p != end(); ++p)
			{
				if (*p == elem)
					return true;
			}

			return false;
		}

		_NODISCARD iterator find(const_reference elem)
		{
			auto p = begin();
			for (; p != end(); ++p)
			{
				if (*p == elem)
					return p;
			}

			return end();
		}

		_NODISCARD const_iterator find(const_reference elem) const
		{
			auto p = cbegin();
			for (; p != cend(); ++p)
			{
				if (*p == elem)
					return p;
			}

			return cend();
		}

		[[noreturn]] void resize(size_type size)
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

		[[noreturn]] void shrink_to_fit()
		{
			if ((body_size * buffer_distance) - elem_count > 10)
			{
				resize((size_type)elem_count + 10);
			}
		}

		_NODISCARD int size() const noexcept
		{
			return elem_count;
		}

		_NODISCARD size_type max_size() const noexcept
		{
			return size_type(-1) / sizeof(value_type);
		}

		_NODISCARD size_type buffers() const noexcept
		{
			return buffer_size;
		}

		_NODISCARD size_type bodys() const noexcept
		{
			return body_size;
		}

		_NODISCARD bool empty() const noexcept
		{
			return (elem_count == 0);
		}

		[[noreturn]] void swap(self& obj)
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




		_NODISCARD iterator begin() noexcept
		{
			if (head_insert == body_size - 1)
				return iterator(map_ptr , 0 , head_flag + 1 , (int)body_size , 0 , elem_count);
			else
				return iterator(map_ptr , head_insert + 1 , head_flag , (int)body_size , 0 , elem_count);
		}

		_NODISCARD iterator begin() const noexcept
		{
			if (head_insert == body_size - 1)
				return iterator(map_ptr , 0 , head_flag + 1 , (int)body_size , 0 , elem_count);
			else
				return iterator(map_ptr , head_insert + 1 , head_flag , (int)body_size , 0 , elem_count);
		}

		_NODISCARD iterator end() noexcept
		{
			return iterator(map_ptr , last_insert , last_flag , (int)body_size , elem_count , elem_count);
		}

		_NODISCARD iterator end() const noexcept
		{
			return iterator(map_ptr , last_insert , last_flag , (int)body_size , elem_count , elem_count);
		}

		_NODISCARD const_iterator cbegin() const noexcept
		{
			if (head_insert == body_size - 1)
				return const_iterator(map_ptr , 0 , head_flag + 1 , (int)body_size , 0 , elem_count);
			else
				return const_iterator(map_ptr , head_insert + 1 , head_flag , (int)body_size , 0 , elem_count);
		}

		_NODISCARD const_iterator cend() const noexcept
		{
			return const_iterator(map_ptr , last_insert , last_flag , (int)body_size , elem_count , elem_count);
		}

		_NODISCARD reverse_iterator rbegin() noexcept
		{
			return reverse_iterator(end());
		}

		_NODISCARD reverse_iterator rend() noexcept
		{
			return reverse_iterator(begin());
		}

		_NODISCARD const_reverse_iterator crbegin() const noexcept
		{
			return const_reverse_iterator(cend());
		}

		_NODISCARD const_reverse_iterator crend() const noexcept
		{
			return const_reverse_iterator(cbegin());
		}




		_NODISCARD const_reference operator[](int n) const
		{
		#if _LIB_DEBUG_LEVEL == 1

			_BUG_VERIFY(((n < elem_count) && (n >= 0)) , "out of range");
			assert(n < elem_count&& n >= 0);

		#endif // _LIB_DEBUG_LEVEL == 1

			return *(begin() + n);
		}

		_NODISCARD reference operator[](int n)
		{
		#if _LIB_DEBUG_LEVEL == 1

			_BUG_VERIFY(((n < elem_count) && (n >= 0)) , "out of range");
			assert(n < elem_count&& n >= 0);

		#endif // _LIB_DEBUG_LEVEL == 1

			return *(begin() + n);
		}

		self& operator=(const self& obj)
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

		[[noreturn]] void ptr_alloc(pointer*& ptr , int size)
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
						simple_allocator(_alloc , Ty)::deallocate(map_ptr[n] , body_size * sizeof(Ty));
				}

				map_ptr = nullptr;
			}
		}

		[[noreturn]] void MemoryExpand(size_type size)
		{
		#if _LIB_DEBUG_LEVEL == 1

			_BUG_VERIFY((size > 0) , "container size error");
			assert(size > 0);

		#endif // _LIB_DEBUG_LEVEL == 1

			if (elem_count != 0) //deque not empty
			{
				Ty** temp_arr = simple_allocator(_alloc , pointer)::allocate((int)size);
				ptr_alloc(temp_arr , (int)size);

				int count = 0;
				for (int n = head_flag; n <= last_flag; ++n) // save data
				{
					temp_arr[count] = simple_allocator(_alloc , Ty)::allocate((int)body_size);

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