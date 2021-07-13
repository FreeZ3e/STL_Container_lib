/* vector implementation
 *
 * Copyright(c) 2021 Mashiro -1262159823@qq.com
 *
 * This File is part of CONTAINER LIBRARY project.
 *
 * version : 1.3.0-alpha
 *
 * author : Mashiro
 *
 * File name : Container_Vector.hpp -a kind of sequence container.
 *
 * This library is free software;you can redistribute is and/or modify it
 * under the APACHE LICENSE 2.0 as published by the Free Software Foundation.
 * ------------------------------------------------------------------------
 *
 *-------------------------------README------------------------------------
 *
 * template<typename Ty,typename alloc = _default_allocator>
 * class vector
 * {
 *		//iterator : random_iterator
 *		//const_iterator : const_random_iterator
 * 
 *      //ctor
 *
 *      vector()
 *      vector(size_t size)
 *      vector(size_t size,Ty elem)
 *      vector(const initializer_list<Ty>& list)
 *      vector(const vector<Ty,alloc>& obj)
 *
 *      //operations
 *
 *		void insert(Ty elem)--------------------------------call push_back().
 *      void insert(iterator pos,Ty elem)------------------------insert elem before pos position.
 *      void push_back(Ty elem)
 *      void emplace_back(Ty elem)--------------------------insert elem without copy.
 *      void pop_back()
 *      iterator erase(iterator ptr)
 *      const_iterator erase(const_iterator ptr)
 *      void erase(iterator p_begin,iterator p_end)
 *      void clear()
 *      Ty back()
 *      Ty front()
 *      void resize(size_t resize)
 *      size_t max_size()
 *      int size()
 *		bool empty()
 *      int capacity()--------------------------------------return max_size-size.
 *      void swap(self& obj)
 *
 *      //iterator
 *
 *      iterator begin()
 *      iterator end()
 *      const_iterator cbegin()
 *      const_iterator cend()
 *
 *      //operator overload
 *
 *      decltype(auto) operator[](int n)
 *      self& operator=(const self& obj)
 *      bool operator==(const coll& obj)
 *      bool operator!=(const coll& obj)
 *      bool operator<(const coll& obj)
 *      bool operator>(const coll& obj)
 *      bool operator<=(const coll& obj)
 *      bool operator>=(const coll& obj)
 *
 *      //private function
 *
 *      void MemoryExpand(size_t resize)----------------expand and resize memory for container.
 *                                                      when container full,expand memory as 2xsize.
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

#endif  // _LIB_DEBUG_LEVEL == 1

using std::initializer_list;
//using allocator::simple_alloc;

template<typename Ty , typename alloc = _default_allocator>
class vector
{
	private:
		Ty* arr = nullptr;

		size_t arr_size = 10;
		int elem_count = 0;

	public:
		using self = vector<Ty , alloc>;
		using TypeValue = Ty;
		using iterator = Random_iterator<Ty>;
		using const_iterator = const_Random_iterator<Ty>;

	public:

		vector() noexcept
		{
			arr = simple_allocator(alloc , Ty)::allocate((int)arr_size);
		}

		vector(const size_t& size)
		{
		#if _LIB_DEBUG_LEVEL == 1

			_BUG_VERIFY( (size > 0), "container size error");
			assert(size > 0);

		#endif // _LIB_DEBUG_LEVEL == 1

			arr_size = size;
			arr = simple_allocator(alloc , Ty)::allocate((int)arr_size);
		}

		vector(const size_t& size , const Ty& elem):vector(size)
		{
		#if _LIB_DEBUG_LEVEL == 1

			_BUG_VERIFY( (size > 0) , "container size error");
			assert(size > 0);

		#endif // _LIB_DEBUG_LEVEL == 1

			for (int n = 0; n < arr_size; ++n)
			{
				arr[n] = elem;
			}

			elem_count = arr_size;
		}

		explicit vector(const initializer_list<Ty>& list) noexcept
		{
			arr_size = list.size();
			arr = simple_allocator(alloc , Ty)::allocate((int)arr_size);

			for (auto p = list.begin(); p != list.end(); ++p)
			{
				arr[elem_count] = (*p);
				elem_count++;
			}
		}

		explicit vector(const vector<Ty , alloc>& obj) noexcept
		{
			arr_size = obj.arr_size;
			arr = simple_allocator(alloc , Ty)::allocate((int)arr_size);

			for (int n = 0; n < obj.elem_count; ++n)
			{
				arr[n] = obj.arr[n];
			}

			elem_count = obj.elem_count;
		}

		~vector() noexcept
		{
			if (arr != nullptr)
			{
				simple_allocator(alloc , Ty)::deallocate(arr , arr_size * sizeof(Ty));
				arr = nullptr;
			}
		}


		//push and pop operation

		[[noreturn]] void insert(const Ty& elem) noexcept
		{
			push_back(elem);
		}

		[[noreturn]] void insert(const iterator& pos , const Ty& elem) noexcept
		{
			if (pos > begin())
			{
				*(pos-1) = elem;
			}
		}

		[[noreturn]] void push_back(const Ty elem) noexcept
		{
			if (elem_count == arr_size)
			{
				MemoryExpand(arr_size*2);
				arr_size = arr_size * 2;
			}

			arr[elem_count] = elem;
			elem_count++;
		}

		[[noreturn]] void emplace_back(const Ty& elem) noexcept
		{
			if (elem_count == arr_size)
			{   
				MemoryExpand(arr_size*2);
				arr_size = arr_size * 2;
			}

			arr[elem_count] = elem;
			elem_count++;
		}

		[[noreturn]] void pop_back() noexcept
		{
			if (elem_count > 0)
			{
				memory::elem_destory(back());

				elem_count--;

				Ty* Temp = new Ty[elem_count];

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

				delete[] Temp;
				Temp = nullptr;
			}
		}


		//erase and clear operation

		_NODISCARD iterator erase(iterator ptr) noexcept
		{
			Ty* temp = new Ty[(size_t)elem_count];

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

			delete[] temp;
			temp = nullptr;

			elem_count = count;

			return iterator(&arr[del] , del);
		}

		_NODISCARD const_iterator erase(const_iterator ptr) noexcept
		{
			Ty* temp = new Ty[(size_t)elem_count];

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

			delete[] temp;
			temp = nullptr;

			elem_count = count;

			return const_iterator(&arr[del] , del);

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
			simple_allocator(alloc , Ty)::deallocate(arr , arr_size * sizeof(Ty));
			arr = simple_allocator(alloc , Ty)::allocate(arr_size);

			elem_count = 0;
		}


		//other

		_NODISCARD const Ty& back() const noexcept
		{
			return arr[elem_count - 1];
		}

		_NODISCARD Ty& back() noexcept
		{
			return arr[elem_count - 1];
		}

		_NODISCARD const Ty& front() const noexcept
		{
			return arr[0];
		}

		_NODISCARD Ty& front() noexcept
		{
			return arr[0];
		}

		[[noreturn]] void resize(size_t resize)
		{
		#if _LIB_DEBUG_LEVEL == 1

			_BUG_VERIFY( (resize > 0) , "container size error");
			assert(resize > 0);

		#endif // _LIB_DEBUG_LEVEL == 1

			MemoryExpand(resize);

			if (elem_count > resize)
				elem_count = (int)resize;

			arr_size = resize;
		}

		_NODISCARD size_t max_size() const noexcept
		{
			return this->arr_size;
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

		[[noreturn]] void swap(self& obj) noexcept
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



		//iterator
		_NODISCARD iterator begin() noexcept
		{
			return iterator(arr,0);
		}

		_NODISCARD iterator end() noexcept
		{
			return iterator(arr + elem_count, elem_count);
		}

		_NODISCARD iterator begin() const noexcept
		{
			return iterator(arr , 0);
		}

		_NODISCARD iterator end() const noexcept
		{
			return iterator(arr + elem_count , elem_count);
		}

		_NODISCARD const_iterator cbegin() const noexcept
		{
			return const_iterator(arr,0);
		}

		_NODISCARD const_iterator cend() const noexcept
		{
			return const_iterator(arr + elem_count, elem_count);
		}
			

		//operator overload

		_NODISCARD const Ty& operator[](int n) const
		{
		#if _LIB_DEBUG_LEVEL == 1

			_BUG_VERIFY(((n < elem_count) && (n >= 0)) , "out of range");
			assert(n < elem_count && n >= 0);

		#endif // _LIB_DEBUG_LEVEL == 1

			return arr[n];
		}

		_NODISCARD Ty& operator[](int n)
		{
		#if _LIB_DEBUG_LEVEL == 1

			_BUG_VERIFY(((n < elem_count) && (n >= 0)) , "out of range");
			assert(n < elem_count && n >= 0);

		#endif // _LIB_DEBUG_LEVEL == 1

			return arr[n];
		}

		self& operator=(const self& obj) noexcept
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

			return *this;
		}

		template<typename coll>
		_NODISCARD bool operator==(const coll& obj) const noexcept
		{
			if (elem_count != obj.size())
				return false;

			auto p = obj.begin();
			for (int n = 0; n < elem_count; ++n,++p)
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
		[[noreturn]] void MemoryExpand(size_t resize)
		{
		#if _LIB_DEBUG_LEVEL == 1

			_BUG_VERIFY( (resize > 0) , "container size error");
			assert(resize > 0);

		#endif // _LIB_DEBUG_LEVEL == 1

			if (elem_count != 0)
			{
				Ty* TempArr = new Ty[elem_count];

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

				delete[] TempArr;
				TempArr = nullptr;
			}
			else
			{
				simple_allocator(alloc , Ty)::deallocate(arr , arr_size * sizeof(Ty));
				arr = simple_allocator(alloc , Ty)::allocate((int)resize);
			}
		}
};