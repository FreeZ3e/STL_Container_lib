/* vector implementation
 *
 * Copyright(c) 2021 Mashiro -1262159823@qq.com
 *
 * This File is part of CONTAINER LIBRARY project.
 *
 * version : 1.1.0
 *
 * author : Mashiro
 *
 * File name : vector.hpp -a kind of sequence container.
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


template<typename Ty,typename alloc = _default_allocator>
class vector
{
	public:
		using value_type = Ty;
		using reference = Ty&;
		using const_reference = const Ty&;
		using pointer = Ty*;
		using const_pointer = const Ty*;
		using iterator = Random_iterator<Ty>;
		using const_iterator = const_Random_iterator<Ty>;
		using const_reverse_iterator = reverse_iterator<const_iterator>;
		using reverse_iterator = reverse_iterator<iterator>;
		using size_type = size_t;
		using self = vector<Ty , alloc>;

	private:
		pointer arr = nullptr;

		size_type arr_size = 10;
		int elem_count = 0;

	public:
		
		vector()
		{
			arr = simple_allocator(alloc , Ty)::allocate((int)arr_size);
		}

		explicit vector(size_type size)
		{
		#if _LIB_DEBUG_LEVEL == 1

			_BUG_VERIFY((size > 0) , "container size error");
			assert(size > 0);

		#endif // _LIB_DEBUG_LEVEL == 1

			arr_size = size;
			arr = simple_allocator(alloc , Ty)::allocate((int)arr_size);
		}

		vector(size_type size , const_reference elem) :vector(size)
		{
			for (int n = 0; n < arr_size; ++n)
			{
				arr[n] = elem;
			}

			elem_count = arr_size;
		}

		explicit vector(const initializer_list<value_type>& list) :vector(list.size())
		{
			for (auto p = list.begin(); p != list.end(); ++p)
			{
				arr[elem_count] = (*p);
				elem_count++;
			}
		}

		template<typename iter>
		vector(iter begin , iter end) :vector()
		{
			while (begin != end)
			{
				push_back((*begin));
				++begin;
			}
		}

		vector(const self& obj) :vector(obj.arr_size)
		{
			for (int n = 0; n < obj.elem_count; ++n)
			{
				arr[n] = obj.arr[n];
			}

			elem_count = obj.elem_count;
		}

		vector(self&& obj) :vector(obj.arr_size)
		{
			for (int n = 0; n < obj.elem_count; ++n)
			{
				arr[n] = obj.arr[n];
			}

			elem_count = obj.elem_count;

			simple_allocator(alloc , value_type)::deallocate(obj.arr , obj.arr_size * sizeof(Ty));
			obj.arr = nullptr;
			obj.elem_count = 0;
		}

		~vector()
		{
			if (arr != nullptr)
			{
				simple_allocator(alloc , Ty)::deallocate(arr , arr_size * sizeof(Ty));
				arr = nullptr;
			}
		}



		[[noreturn]] void insert(const_reference elem)
		{
			push_back(elem);
		}

		[[noreturn]] void insert(const iterator pos , value_type&& elem)
		{
			if (elem_count == arr_size)
			{
				MemoryExpand(arr_size * 2);
				arr_size = arr_size * 2;
			}

			iterator temp = iterator(arr + elem_count , elem_count , (size_t)elem_count+1);

			while (temp > pos && temp > begin())
			{
				*temp = *(temp - 1);
				--temp;
			}

			*temp = elem;
			elem_count++;
		}

		[[noreturn]] void insert(const iterator pos , const_reference elem)
		{
			if (elem_count == arr_size)
			{
				MemoryExpand(arr_size * 2);
				arr_size = arr_size * 2;
			}

			iterator temp = iterator(arr + elem_count , elem_count , (size_t)elem_count + 1);

			while (temp > pos && temp > begin())
			{
				*temp = *(temp - 1);
				--temp;
			}

			*temp = elem;
			elem_count++;
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

		[[noreturn]] void assgin(int size , const_reference elem)
		{
			while (size >= arr_size)
			{
				MemoryExpand(arr_size * 2);
				arr_size = arr_size * 2;
			}

			for (int n = 0; n < size; ++n)
			{
				arr[n] = elem;
			}

			while (size < elem_count)
				pop_back();
			elem_count = size;
		}

		template<typename iter>
		[[noreturn]] void assgin(iter beg , iter end)
		{
			int step = end.step() - beg.step();
			while (step >= arr_size)
			{
				MemoryExpand(arr_size * 2);
				arr_size = arr_size * 2;
			}

			for (int n = 0; n < step; ++n)
			{
				arr[n] = (*beg++);
			}

			while (step < elem_count)
				pop_back();
			elem_count = step;
		}

		[[noreturn]] void assgin(const initializer_list<value_type>& list)
		{
			while (list.size() >= arr_size)
			{
				MemoryExpand(arr_size * 2);
				arr_size = arr_size * 2;
			}

			auto temp = list.begin();
			for (int n = 0; n < list.size(); ++n)
			{
				arr[n] = (*temp++);
			}

			while (list.size() < elem_count)
				pop_back();
			elem_count = list.size();
		}

		[[noreturn]] void push_back(const_reference elem)
		{
			if (elem_count == arr_size)
			{
				MemoryExpand(arr_size * 2);
				arr_size = arr_size * 2;
			}

			arr[elem_count] = elem;
			elem_count++;
		}

		[[noreturn]] void push_back(value_type&& elem)
		{
			if (elem_count == arr_size)
			{
				MemoryExpand(arr_size * 2);
				arr_size = arr_size * 2;
			}

			arr[elem_count] = elem;
			elem_count++;
		}

		template<typename... value>
		_NODISCARD iterator emplace(const iterator pos , value&&... arg)
		{
			if (pos >= end())
			{
				if (elem_count == arr_size)
				{
					MemoryExpand(arr_size * 2);
					arr_size = arr_size * 2;
				}

				pointer iter = arr + elem_count;
				new(iter) value_type(arg...);

				elem_count++;
				return begin()+pos.step();
			}

			push_back(*(end() - 1));
			iterator temp = end()-2;

			while (temp.step() > pos.step())
			{
				*temp = *(temp - 1);
				--temp;
			}

			pointer iter = arr + temp.step();
			new(iter) value_type(arg...);


			return iterator(arr + pos.step() , pos.step() , elem_count);
		}

		template<typename... value>
		[[noreturn]] void emplace_back(value&&... arg)
		{
			emplace(end() , arg...);
		}

		[[noreturn]] void pop_back()
		{
			if (elem_count > 0)
			{
				memory::elem_destory(back());

				elem_count--;

				//Ty* Temp = new Ty[elem_count];
				Ty* Temp = simple_allocator(alloc , Ty)::allocate(elem_count);

				for (int n = 0; n < elem_count; ++n)
				{
					Temp[n] = arr[n];
				}

				simple_allocator(alloc , Ty)::deallocate(arr , arr_size * sizeof(Ty));
				arr = simple_allocator(alloc , Ty)::allocate(arr_size);

				for (int n = 0; n < elem_count; ++n)
				{
					arr[n] = Temp[n];
				}

				simple_allocator(alloc , Ty)::deallocate(Temp , elem_count * sizeof(Ty));
				Temp = nullptr;
			}
		}



		_NODISCARD iterator erase(iterator ptr)
		{
			Ty* temp = simple_allocator(alloc , Ty)::allocate(elem_count);

			int count = 0;
			int del = 0;
			for (int n = 0; n < elem_count; ++n)	//save data
			{
				if ((*ptr) != arr[n])
				{
					temp[count] = arr[n];
					count++;
				}
				else
					del = n;
			}

			simple_allocator(alloc , Ty)::deallocate(arr , arr_size * sizeof(Ty));
			arr = simple_allocator(alloc , Ty)::allocate(arr_size);
			memory::elem_destory(*ptr);

			for (int n = 0; n < count; ++n)	//reset data
			{
				arr[n] = temp[n];
			}

			simple_allocator(alloc , Ty)::deallocate(temp , elem_count * sizeof(Ty));
			temp = nullptr;

			elem_count = count;

			return iterator(&arr[del] , del , elem_count);
		}

		_NODISCARD const_iterator erase(const_iterator ptr)
		{
			Ty* temp = simple_allocator(alloc , Ty)::allocate(elem_count);

			int count = 0;
			int del = 0;
			for (int n = 0; n < elem_count; ++n)
			{
				if ((*ptr) != arr[n])
				{
					temp[count] = arr[n];
					count++;
				}
				else
					del = n;
			}

			simple_allocator(alloc , Ty)::deallocate(arr , arr_size * sizeof(Ty));
			arr = simple_allocator(alloc , Ty)::allocate(arr_size);
			memory::elem_destory(*ptr);

			for (int n = 0; n < count; ++n)
			{
				arr[n] = temp[n];
			}

			simple_allocator(alloc , Ty)::deallocate(temp , elem_count * sizeof(Ty));
			temp = nullptr;

			elem_count = count;

			return const_iterator(&arr[del] , del , elem_count);

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
			simple_allocator(alloc , Ty)::deallocate(arr , arr_size * sizeof(Ty));
			arr = simple_allocator(alloc , Ty)::allocate(arr_size);

			elem_count = 0;
		}



		_NODISCARD const_reference back() const noexcept
		{
			return arr[elem_count - 1];
		}

		_NODISCARD reference back() noexcept
		{
			return arr[elem_count - 1];
		}

		_NODISCARD const_reference front() const noexcept
		{
			return arr[0];
		}

		_NODISCARD reference front() noexcept
		{
			return arr[0];
		}

		_NODISCARD reference at(size_type n)
		{
			return arr[n];
		}

		_NODISCARD const_reference at(size_type n) const
		{
			return arr[n];
		}

		_NODISCARD pointer data() noexcept
		{
			return arr;
		}

		_NODISCARD const_pointer data() const noexcept
		{
			return arr;
		}



		[[noreturn]] void resize(size_type resize)
		{
		#if _LIB_DEBUG_LEVEL == 1

			_BUG_VERIFY((resize > 0) , "container size error");
			assert(resize > 0);

		#endif // _LIB_DEBUG_LEVEL == 1

			MemoryExpand(resize);

			if (elem_count > resize)
				elem_count = (int)resize;

			arr_size = resize;
		}

		[[noreturn]] void shrink_to_fit()
		{
			if (arr_size - elem_count > 10)
			{
				resize((size_type)elem_count + 10);
			}
		}

		_NODISCARD size_type max_size() const noexcept
		{
			return size_type(-1) / sizeof(value_type);
		}

		_NODISCARD int size() const noexcept
		{
			return elem_count;
		}

		_NODISCARD bool empty() const noexcept
		{
			if (elem_count == 0)
				return true;

			return false;
		}

		_NODISCARD int capacity() const noexcept
		{
			return (int)arr_size - elem_count;
		}

		[[noreturn]] void swap(self& obj)
		{
			Ty* temp_ptr = arr;
			Ty* obj_ptr = obj.arr;

			arr = obj_ptr;
			obj.arr = temp_ptr;

			int temp_count = elem_count;
			elem_count = obj.elem_count;
			obj.elem_count = temp_count;

			size_t temp_size = arr_size;
			arr_size = obj.arr_size;
			obj.arr_size = temp_size;
		}


		_NODISCARD iterator begin() noexcept
		{
			return iterator(arr , 0 , elem_count);
		}

		_NODISCARD iterator end() noexcept
		{
			return iterator(arr + elem_count , elem_count , elem_count);
		}

		_NODISCARD const_iterator begin() const noexcept
		{
			return const_iterator(arr , 0 , elem_count);
		}

		_NODISCARD const_iterator end() const noexcept
		{
			return const_iterator(arr + elem_count , elem_count , elem_count);
		}

		_NODISCARD const_iterator cbegin() const noexcept
		{
			return const_iterator(arr , 0 , elem_count);
		}

		_NODISCARD const_iterator cend() const noexcept
		{
			return const_iterator(arr + elem_count , elem_count , elem_count);
		}

		_NODISCARD reverse_iterator rbegin() noexcept
		{
			return reverse_iterator(iterator(arr + elem_count , elem_count , elem_count));
		}

		_NODISCARD reverse_iterator rend() noexcept
		{
			return reverse_iterator(iterator(arr , 0 , elem_count));
		}

		_NODISCARD const_reverse_iterator crbegin() const noexcept
		{
			return const_reverse_iterator(const_iterator(arr + elem_count , elem_count , elem_count));
		}

		_NODISCARD const_reverse_iterator crend() const noexcept
		{
			return const_reverse_iterator(const_iterator(arr , 0 , elem_count));
		}




		_NODISCARD const_reference operator[](int n) const
		{
		#if _LIB_DEBUG_LEVEL == 1

			_BUG_VERIFY(((n < elem_count) && (n >= 0)) , "out of range");
			assert(n < elem_count&& n >= 0);

		#endif // _LIB_DEBUG_LEVEL == 1

			return arr[n];
		}

		_NODISCARD reference operator[](int n)
		{
		#if _LIB_DEBUG_LEVEL == 1

			_BUG_VERIFY(((n < elem_count) && (n >= 0)) , "out of range");
			assert(n < elem_count&& n >= 0);

		#endif // _LIB_DEBUG_LEVEL == 1

			return arr[n];
		}

		self& operator=(const self& obj)
		{
			if (*this != obj)
			{
				if (arr_size < obj.arr_size)
				{
					arr_size = obj.arr_size;
					MemoryExpand(arr_size);
				}

				for (int n = 0; n < obj.elem_count; ++n)
				{
					this->arr[n] = obj.arr[n];
				}

				this->elem_count = obj.elem_count;
			}

			return *this;
		}

		template<typename coll>
		_NODISCARD bool operator==(const coll& obj) const noexcept
		{
			if (elem_count != obj.size())
				return false;

			auto p = obj.begin();
			for (int n = 0; n < elem_count; ++n , ++p)
			{
				if (arr[n] != *p)
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
			if (elem_count > obj.size())
				return true;

			return false;
		}

		template<typename coll>
		_NODISCARD bool operator<(const coll& obj) const noexcept
		{
			if (elem_count < obj.size())
				return true;

			return false;
		}

		template<typename coll>
		_NODISCARD bool operator<=(const coll& obj) const noexcept
		{
			if (elem_count <= obj.size())
				return true;

			return false;
		}

		template<typename coll>
		_NODISCARD bool operator>=(const coll& obj) const noexcept
		{
			if (elem_count >= obj.size())
				return true;

			return false;
		}

	private:
		[[noreturn]] void MemoryExpand(size_type resize)
			{
			#if _LIB_DEBUG_LEVEL == 1

				_BUG_VERIFY((resize > 0) , "container size error");
				assert(resize > 0);

			#endif // _LIB_DEBUG_LEVEL == 1

				if (elem_count != 0)
				{
					Ty* TempArr = simple_allocator(alloc , Ty)::allocate((int)elem_count);

					for (int n = 0; n < elem_count; n++)
					{
						TempArr[n] = arr[n];
					}

					simple_allocator(alloc , Ty)::deallocate(arr , arr_size * sizeof(Ty));
					arr = simple_allocator(alloc , Ty)::allocate((int)resize);

					if (resize > arr_size)
					{
						for (int n = 0; n < elem_count; ++n)
							arr[n] = TempArr[n];
					}
					else
					{
						for (int n = 0; n < resize; ++n)
							arr[n] = TempArr[n];
					}

					//delete[] TempArr;
					simple_allocator(alloc , Ty)::deallocate(TempArr , elem_count * sizeof(Ty));
					TempArr = nullptr;
				}
				else
				{
					simple_allocator(alloc , Ty)::deallocate(arr , arr_size * sizeof(Ty));
					arr = simple_allocator(alloc , Ty)::allocate((int)resize);
				}
			}
};