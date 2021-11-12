/* array implementation
 *
 * Copyright(c) 2021 Mashiro -1262159823@qq.com
 *
 * This File is part of CONTAINER LIBRARY project.
 *
 * version : 1.1.0
 *
 * author : Mashiro
 *
 * File name : array.hpp -a kind of sequence container.
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
#include"iterator.hpp"
#include"memory_allocator.hpp"


using std::initializer_list;

template<typename Ty , size_t _size = 8 , typename alloc = _default_allocator>
class array
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
		using self = array<Ty , _size , alloc>;

	private:
		pointer arr = simple_allocator(alloc , Ty)::allocate(_size);
		int elem_count = 0;

	public:
		static_assert(_size > 0 , "array size must bigger than 0");


		explicit array(const initializer_list<value_type>& list)
		{
			for (auto p : list)
			{
				if (elem_count < _size)
				{
					arr[elem_count++] = p;
				}
				else
					break;
			}
		}

		array(const self& obj)
		{
			for (int n = 0; n < obj.elem_count; ++n)
			{
				arr[n] = obj.arr[n];
			}

			elem_count = obj.elem_count;
		}

		array(self&& obj)
		{
			for (int n = 0; n < obj.elem_count; ++n)
			{
				arr[n] = obj.arr[n];
			}

			elem_count = obj.elem_count;

			simple_allocator(alloc , value_type)::deallocate(obj.arr , _size * sizeof(value_type));
			obj.elem_count = 0;
			obj.arr = nullptr;
		}

		explicit array(const_reference num)
		{
			for (int n = 0; n < _size; ++n)
			{
				arr[n] = num;
			}

			elem_count = _size;
		}

		array() = default;

		~array()
		{
			if (arr != nullptr)
				simple_allocator(alloc , value_type)::deallocate(arr , _size * sizeof(value_type));
			arr = nullptr;
		}


		_NODISCARD bool empty() const noexcept
		{
			return elem_count == 0;
		}

		_NODISCARD int size() const noexcept
		{
			return elem_count;
		}

		_NODISCARD size_type max_size() const noexcept
		{
			return _size;
		}

		_NODISCARD reference front() noexcept
		{
			return arr[0];
		}

		_NODISCARD const_reference front() const noexcept
		{
			return arr[0];
		}

		_NODISCARD reference back() noexcept
		{
			return arr[elem_count - 1];
		}

		_NODISCARD const_reference back() const noexcept
		{
			return arr[elem_count - 1];
		}

		_NODISCARD reference at(int pos)
		{
			return arr[pos];
		}

		_NODISCARD const_reference at(int pos) const
		{
			return arr[pos];
		}

		_NODISCARD pointer data() noexcept
		{
			return arr;
		}

		_NODISCARD const_pointer data() const noexcept
		{
			return arr;
		}

		[[noreturn]] void fill(const_reference elem)
		{
			for (int n = 0; n < _size; ++n)
			{
				arr[n] = elem;
			}

			elem_count = _size;
		}

		[[noreturn]] void swap(self& obj)
		{
			pointer temp_ptr = obj.arr;
			obj.arr = this->arr;
			this->arr = temp_ptr;

			int temp = elem_count;
			elem_count = obj.elem_count;
			obj.elem_count = temp;
		}



		_NODISCARD iterator begin() noexcept
		{
			return iterator(arr , 0 , elem_count);
		}

		_NODISCARD iterator end() noexcept
		{
			return iterator(arr + elem_count , elem_count , elem_count);
		}

		_NODISCARD iterator begin() const noexcept
		{
			return iterator(arr , 0 , elem_count);
		}

		_NODISCARD iterator end() const noexcept
		{
			return iterator(arr + elem_count , elem_count , elem_count);
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

			return this->arr[n];
		}

		_NODISCARD reference operator[](int n)
		{
		#if _LIB_DEBUG_LEVEL == 1

			_BUG_VERIFY(((n < elem_count) && (n >= 0)) , "out of range");
			assert(n < elem_count&& n >= 0);

		#endif // _LIB_DEBUG_LEVEL == 1

			return this->arr[n];
		}

		self& operator=(const self& obj)
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
			for (int n = 0; n < elem_count; ++n , ++p)
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