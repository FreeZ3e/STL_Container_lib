/* array implementation
 *
 * Copyright(c) 2021 Mashiro -1262159823@qq.com
 *
 * This File is part of CONTAINER LIBRARY project.
 *
 * version : 1.2.0-alpha
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
 * template<typename Ty,size_t size = 10>
 * class array
 * {
 *		//iterator : random_iterator
 *		//const_iterator : const_random_iterator
 * 
 *      //ctor
 *
 *      array(const initializer_list<Ty>& list)
 *      array(const array<Ty,size>& obj)
 *      array(Ty num)--------------------------------initialized with num.
 *      array()
 *
 *      //operations
 *
 *      bool empty()---------------------------------if array is empty,return true.
 *      int array_size()-----------------------------return number of elem in array.
 *      size_t max_size()----------------------------return size of array.
 *      Ty back()------------------------------------return last elem of array without check.
 *      Ty front()-----------------------------------return first elem of array without check.
 *      void fill(Ty elem)---------------------------fill array with elem.
 *      void swap(array<Ty,size>& obj)---------------make swap operation.
 *
 *      //iterator
 *
 *      iterator begin()-----------------------------return the position of beginning.
 *      iterator end()-------------------------------return the position of ending.
 *      const_iterator cbegin()----------------------return const_iterator(begining).
 *      const_iterator cend()------------------------return const_iterator(ending).
 *
 *      //operator overload
 *
 *      decltype(auto) operator[](int n)
 *      self& operator=(const array<Ty,size>& obj)
 *      bool operator==(const array<Ty,size>& obj)
 *      bool operator!=(const array<Ty,size>& obj)
 *      bool operator>(const array<Ty,size>& obj)
 *      bool operator<(const array<Ty,size>& obj)
 *      bool operator>=(const array<Ty,size>& obj)
 *      bool operator<=(const array<Ty,size>& obj)
 * }
 * ----------------------------------------------------------------------------------------------
*/


#pragma once
#include<initializer_list>
#include<typeinfo>
#include<string>
#include"iterator.hpp"

using std::initializer_list;
using std::string;


template<typename Ty , size_t size = 10>
class array
{
	private:
		Ty* arr = new Ty[size];
		int elem_count = 0;

	public:
		using self = array<Ty , size>;
		using TypeValue = Ty;
		using iterator = Random_iterator<Ty>;
		using const_iterator = const_Random_iterator<Ty>;

	public:
		explicit array(const initializer_list<Ty>& list)
		{
			for (auto p : list)
			{
				if (elem_count < size)
				{
					arr[elem_count] = p;
					++elem_count;
				}
				else
					break;
			}

			if (typeid(Ty) != typeid(string))
			{
				if (list.size() < size)
				{
					for (int n = list.size(); n < size; ++n)
						arr[n] = (Ty)0;
				}
			}
		}

		explicit array(const array<Ty , size>& obj)
		{
			for (int i = 0; i < obj.elem_count; ++i)
			{
				arr[i] = obj.arr[i];
			}

			elem_count = obj.elem_count;
		}

		array(Ty num)
		{
			for (int i = 0;i<size;++i)
			{
				arr[i] = num;
			}

			elem_count = size;
		}

		array()
		{
			for (int i = 0; i < size; ++i)
				arr[i] = (Ty)0;
		}

		~array()
		{
			if(arr != nullptr)
				delete[] arr;

			arr = nullptr;
		}



		bool empty() const
		{
			if (elem_count == 0)
				return true;

			return false;
		}

		int array_size() const
		{
			return elem_count;
		}

		size_t max_size() const
		{
			return size;
		}

		Ty back() const
		{
			return arr[elem_count-1];
		}

		Ty front() const
		{
			return arr[0];
		}

		void fill(Ty elem)
		{
			for (int i = 0; i < size; ++i)
			{
				arr[i] = elem;
			}

			elem_count = size;
		}

		void swap(array<Ty , size>& obj)
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
		iterator begin()
		{
			return iterator(arr,0);
		}

		iterator end()
		{
			return iterator(arr+elem_count,elem_count);
		}

		const_iterator cbegin() const
		{
			return const_iterator(arr,0);
		}

		const_iterator cend() const
		{
			return const_iterator(arr + elem_count,elem_count);
		}


		//operator overload

		decltype(auto) operator[](int n)
		{
			return this->arr[n];
		}

		self& operator=(const array<Ty , size>& obj)
		{
			for (int n = 0; n < obj.elem_count; ++n)
			{
				this->arr[n] = obj.arr[n];
			}

			this->elem_count = obj.elem_count;

			return *this;
		}

		bool operator==(const array<Ty , size>& obj) const
		{
			if (this->elem_count != obj.elem_count)
				return false;

			for (int n = 0; n < obj.elem_count; ++n)
			{
				if (this->arr[n] != obj.arr[n])
					return false;
			}

			return true;
		}

		bool operator!=(const array<Ty , size>& obj) const
		{
			return !((*this) == obj);
		}

		bool operator>(const array<Ty , size>& obj) const
		{
			if (size > obj.size)
				return true;

			return false;
		}

		bool operator<(const array<Ty , size>& obj) const
		{
			if (size < obj.size)
				return true;

			return false;
		}

		bool operator<=(const array<Ty , size>& obj) const
		{
			if (size <= obj.size)
				return true;

			return false;
		}

		bool operator>=(const array<Ty , size>& obj) const
		{
			if (size >= obj.size)
				return true;

			return false;
		}
};