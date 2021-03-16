/* vector implementation
 *
 * Copyright(c) 2021 Mashiro -1262159823@qq.com
 *
 * This File is part of CONTAINER LIBRARY project.
 *
 * version : 1.1.1-alpha
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
 * template<typename Ty>
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
 *      vector(const vector<Ty>& obj)
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
 *      void swap(vector<Ty& obj)
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
 *      self& operator=(const vector<Ty>& obj)
 *      bool operator==(const vector<Ty>& obj)
 *      bool operator!=(const vector<Ty>& obj)
 *      bool operator<(const vector<Ty>& obj)
 *      bool operator>(const vector<Ty>& obj)
 *      bool operator<=(const vector<Ty>& obj)
 *      bool operator>=(const vector<Ty& obj)
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
#include"iterator.hpp"

using std::initializer_list;

template<typename Ty>
class vector
{
	private:
		Ty* arr = nullptr;

		size_t arr_size = 10;
		int elem_count = 0;

	public:
		using self = vector<Ty>;
		using TypeValue = Ty;
		using iterator = Random_iterator<Ty>;
		using const_iterator = const_Random_iterator<Ty>;

	public:
		vector()
		{
			arr = new Ty[arr_size];
		}

		vector(size_t size)
		{
			arr_size = size;
			arr = new Ty[arr_size];
		}

		vector(size_t size , Ty elem):vector(size)
		{
			for (int n = 0; n < arr_size; ++n)
			{
				arr[n] = elem;
			}

			elem_count = arr_size;
		}

		explicit vector(const initializer_list<Ty>& list)
		{
			arr_size = list.size();
			arr = new Ty[arr_size];

			for (auto p = list.begin(); p != list.end(); ++p)
			{
				arr[elem_count] = (*p);
				elem_count++;

				if (elem_count == arr_size)
					break;
			}
		}

		explicit vector(const vector<Ty>& obj)
		{
			arr_size = obj.arr_size;
			arr = new Ty[arr_size];

			for (int n = 0; n < obj.elem_count; ++n)
			{
				arr[n] = obj.arr[n];
			}

			elem_count = obj.elem_count;
		}

		~vector()
		{
			delete[] arr;
			arr = nullptr;
		}


		//push and pop operation

		void insert(Ty elem)
		{
			push_back(elem);
		}

		void insert(iterator pos , Ty elem)
		{
			if (pos != begin())
			{
				*(pos-1) = elem;
			}
		}

		void push_back(Ty elem)
		{
			if (elem_count == arr_size)
			{
				MemoryExpand(arr_size*2);
				arr_size = arr_size * 2;
			}

			arr[elem_count] = elem;
			elem_count++;
		}

		void emplace_back(const Ty &elem)
		{
			if (elem_count == arr_size)
			{   
				MemoryExpand(arr_size*2);
				arr_size = arr_size * 2;
			}

			arr[elem_count] = elem;
			elem_count++;
		}

		void pop_back()
		{
			elem_count--;

			Ty* Temp = new Ty[elem_count];

			for (int n = 0; n < elem_count; ++n)
			{
				Temp[n] = arr[n];
			}

			delete[] arr;
			arr = new Ty[arr_size];

			for (int n = 0; n < elem_count; ++n)
			{
				arr[n] = Temp[n];
			}

			delete[] Temp;
			Temp = nullptr;
		}


		//erase and clear operation

		iterator erase(iterator ptr)
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

			delete[] arr;
			arr = new Ty[arr_size];

			for (int n = 0; n < elem_count - 1; ++n)
			{
				arr[n] = temp[n];
			}

			delete[] temp;
			temp = nullptr;

			elem_count--;

			return iterator(&arr[del]);
		}

		const_iterator erase(const_iterator ptr)
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

			delete[] arr;
			arr = new Ty[arr_size];

			for (int n = 0; n < elem_count - 1; ++n)
			{
				arr[n] = temp[n];
			}

			delete[] temp;
			temp = nullptr;

			elem_count--;

			return const_iterator(&arr[del]);

		}

		void erase(iterator p_begin , iterator p_end)
		{
			int begin = p_begin.step();
			int end = p_end.step();

			for (int n = begin; n < end; ++n)
			{
				p_begin = erase(p_begin);
			}
		}

		void clear()
		{
			delete[] arr;
			arr = new Ty[arr_size];

			elem_count = 0;
		}


		//other

		Ty back() const
		{
			return arr[elem_count-1];
		}

		Ty front() const
		{
			return arr[0];
		}

		void resize(size_t resize)
		{
			MemoryExpand(resize);

			if (elem_count > resize)
				elem_count = (int)resize;

			arr_size = resize;
		}

		size_t max_size() const
		{
			return this->arr_size;
		}

		int size() const
		{
			return elem_count;
		}

		bool empty() const
		{
			if (elem_count == 0)
				return true;

			return false;
		}

		int capacity() const
		{
			return (int)arr_size - elem_count;
		}

		void swap(vector<Ty>& obj)
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
		iterator begin()
		{
			return iterator(arr,0);
		}

		iterator end()
		{
			return iterator(arr + elem_count, elem_count);
		}

		const_iterator cbegin() const
		{
			return const_iterator(arr,0);
		}

		const_iterator cend() const
		{
			return const_iterator(arr + elem_count, elem_count);
		}
			

		//operator overload

		decltype(auto) operator[](int n)
		{
			return arr[n];
		}

		self& operator=(const vector<Ty>& obj)
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

		bool operator==(const vector<Ty>& obj)
		{
			if (elem_count != obj.elem_count)
				return false;

			for (int n = 0; n < elem_count; ++n)
			{
				if (arr[n] != obj.arr[n])
					return false;
			}

			return true;
		}

		bool operator!=(const vector<Ty>& obj)
		{
			return !((*this) == obj);
		}

		bool operator>(const vector<Ty>& obj)
		{
			if (arr_size > obj.arr_size)
				return true;
			
			return false;
		}

		bool operator<(const vector<Ty>& obj)
		{
			if (arr_size < obj.arr_size)
				return true;

			return false;
		}

		bool operator<=(const vector<Ty>& obj)
		{
			if (arr_size <= obj.arr_size)
				return true;

			return false;
		}

		bool operator>=(const vector<Ty>& obj)
		{
			if (arr_size >= obj.arr_size)
				return true;

			return false;
		}

	private:
		void MemoryExpand(size_t resize)
		{

			if (elem_count != 0)
			{
				Ty* TempArr = new Ty[elem_count];

				for (int n = 0; n < elem_count; n++)
				{
					TempArr[n] = arr[n];
				}

				delete[] arr;
				arr = new Ty[resize];

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
				delete[] arr;
				arr = new Ty[resize];
			}
		}
};