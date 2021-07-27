/* array implementation
 *
 * Copyright(c) 2021 Mashiro -1262159823@qq.com
 *
 * This File is part of CONTAINER LIBRARY project.
 *
 * version : 1.3.0-alpha
 *
 * author : Mashiro
 *
 * File name : Container_Array.hpp -a kind of sequence container.
 *
 * This library is free software;you can redistribute is and/or modify it
 * under the APACHE LICENSE 2.0 as published by the Free Software Foundation.
 * ------------------------------------------------------------------------
 *
 *-------------------------------README------------------------------------
 *
 * template<typename Ty,size_t _size = 10,alloc = _default_allocator>
 * class array
 * {
 *		//iterator : random_iterator
 *		//const_iterator : const_random_iterator
 * 
 *      //ctor
 *
 *      array(const initializer_list<Ty>& list)
 *      array(const array<Ty,_size,alloc>& obj)
 *      array(Ty num)--------------------------------initialized with num.
 *      array()
 *
 *      //operations
 *
 *      bool empty()---------------------------------if array is empty,return true.
 *		int size()-----------------------------------call array_size.
 *      int array_size()-----------------------------return number of elem in array.
 *      size_t max_size()----------------------------return _size of array.
 *      Ty back()------------------------------------return last elem of array without check.
 *      Ty front()-----------------------------------return first elem of array without check.
 *      void fill(Ty elem)---------------------------fill array with elem.
 *      void swap(self& obj)---------------make swap operation.
 *
 *      //iterator
 *
 *      iterator begin()-----------------------------return the position of beginning.
 *      iterator end()-------------------------------return the position of ending.
 *      const_iterator cbegin()----------------------return const_iterator(beginning).
 *      const_iterator cend()------------------------return const_iterator(ending).
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
 * }
 * ----------------------------------------------------------------------------------------------
*/


#pragma once
#include<initializer_list>
#include<typeinfo>
#include<string>
#include"iterator.hpp"
#include"errors.hpp"
#include"memory_allocator.hpp"

#if _LIB_DEBUG_LEVEL == 1

#include<assert.h>

#endif // _LIB_DEBUG_LEVEL == 1


using std::initializer_list;
using std::string;

template<typename Ty , size_t _size = 8,
		typename alloc = _default_allocator>
class array
{
	private:
		Ty* arr = simple_allocator(alloc , Ty)::allocate(_size);
		int elem_count = 0;

	public:
		using self = array<Ty , _size , alloc>;
		using TypeValue = Ty;
		using iterator = Random_iterator<Ty>;
		using const_iterator = const_Random_iterator<Ty>;

	public:
		//array _size check
		static_assert(_size > 0,"_size must bigger than 0");

		
		explicit array(const initializer_list<Ty>& list) noexcept
		{
			for (auto p : list)
			{
				if (elem_count < _size)
				{
					arr[elem_count] = p;
					++elem_count;
				}
				else
					break;
			}

			if (typeid(Ty) != typeid(string))
			{
				if (list.size() < _size)
				{
					for (int n = (int)list.size(); n < _size; ++n)
						arr[n] = (Ty)0;
				}
			}
		}

		explicit array(const array<Ty , _size , alloc>& obj) noexcept
		{
			for (int i = 0; i < obj.elem_count; ++i)
			{
				arr[i] = obj.arr[i];
			}

			elem_count = obj.elem_count;
		}

		explicit array(const Ty& num) noexcept
		{
			for (int i = 0;i<_size;++i)
			{
				arr[i] = num;
			}

			elem_count = _size;
		}

		array() noexcept
		{
			for (int i = 0; i < _size; ++i)
				arr[i] = (Ty)0;
		}

		~array() noexcept
		{
			if (arr != nullptr)
				simple_allocator(alloc , Ty)::deallocate(arr , _size * sizeof(Ty));

			arr = nullptr;
		}



		_NODISCARD bool empty() const noexcept
		{
			if (elem_count == 0)
				return true;

			return false;
		}

		_NODISCARD int size() const noexcept
		{
			return array_size();
		}

		_NODISCARD int array_size() const noexcept
		{
			return elem_count;
		}

		_NODISCARD size_t max_size() const noexcept
		{
			return _size;
		}

		_NODISCARD Ty& back() noexcept
		{
			return arr[elem_count - 1];
		}

		_NODISCARD const Ty& back() const noexcept
		{
			return arr[elem_count - 1];
		}

		_NODISCARD Ty& front() noexcept
		{
			return arr[0];
		}

		_NODISCARD const Ty& front() const noexcept
		{
			return arr[0];
		}

		[[noreturn]] void fill(const Ty& elem) noexcept
		{
			for (int i = 0; i < _size; ++i)
			{
				arr[i] = elem;
			}

			elem_count = _size;
		}

		[[noreturn]] void swap(self& obj) noexcept
		{
			Ty* self_ptr = this->arr;
			Ty* obj_ptr = obj.arr;

			obj.arr = self_ptr;
			this->arr = obj_ptr;

			int temp = elem_count;
			elem_count = obj.elem_count;
			obj.elem_count = temp;
		}


		//iterator
		_NODISCARD iterator begin() noexcept
		{
			return iterator(arr , 0);
		}

		_NODISCARD iterator end() noexcept
		{
			return iterator(arr + elem_count , elem_count);
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
			return const_iterator(arr + elem_count,elem_count);
		}


		//operator overload

		_NODISCARD const Ty& operator[](int n) const noexcept
		{
		#if _LIB_DEBUG_LEVEL == 1

			_BUG_VERIFY(((n < elem_count) && (n >= 0)) , "out of range");
			assert(n < elem_count&& n >= 0);

		#endif // _LIB_DEBUG_LEVEL == 1

			return this->arr[n];
		}

		_NODISCARD Ty& operator[](int n) noexcept
		{
		#if _LIB_DEBUG_LEVEL == 1

			_BUG_VERIFY(((n < elem_count) && (n >= 0)) , "out of range");
			assert(n < elem_count&& n >= 0);

		#endif // _LIB_DEBUG_LEVEL == 1

			return this->arr[n];
		}

		self& operator=(const self& obj) noexcept
		{
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
			if (this->elem_count != obj.size())
				return false;

			auto p = obj.begin();
			for (int n = 0; n < elem_count; ++n,++p)
			{
				if (this->arr[n] != *p)
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
};