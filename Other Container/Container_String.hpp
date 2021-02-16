/* self_string implementation
 *
 * Copyright(c) 2021 Mashiro -1262159823@qq.com
 *
 * This File is part of CONTAINER LIBRARY project.
 *
 * version : 1.1.1-alpha
 *
 * author : Mashiro
 *
 * File name : Container_String.hpp -a kind of containers.
 *
 * This library is free software;you can redistribute is and/or modify it
 * under the APACHE LICENSE 2.0 as published by the Free Software Foundation.
 * ------------------------------------------------------------------------
 *
 * -----------------------------README-------------------------------------
 *
 * class self_string
 * {
 *      //iterator : Random_iterator
 *      //const_iterator : const_Random_iterator
 *
 *      //ctor
 *
 *      self_string()
 *      self_string(const initializer_list<char>& list)
 *      self_string(const char ptr[])
 *      self_string(const self_string& obj)
 *
 *
 *      //operations
 *
 *      void erase(char c)
 *      iterator erase(iterator ptr)
 *      const_iterator erase(const_iterator ptr)
 *      void erase(iterator p_begin,iterator p_end)
 *      void clear()
 *      char back()
 *      char* find(char elem)-----------------------------------------------if elem exist,return the position ptr.
 *      size_t max_size()
 *      bool empty()
 *      void swap(self_string& obj)
 *
 *
 *      //iterator
 *
 *      iterator begin()
 *      iterator end()
 *      const_iterator cbegin() const
 *      const_iterator cend() const
 *
 *
 *      //operator overload
 *
 *      char& operator[](int n)
 *      friend ostream& operator<<(ostream& out,const self_string& obj)-----output by ostream.
 *      friend istream& operator>>(istream& input,self_string& obj)---------input by istream.
 *      self_string& operator+(const char ptr[])
 *      self_string& operator+=(const char ptr[])
 *      self_string& operator=(const self_string& obj)
 *      bool operator==(const self_string& obj)
 *      bool operator!=(const self_string& obj)
 *
 *
 *      //private function
 *
 *      void MemoryExpand(size_t resize)------------------------------------resize and expand memory.
 * };
 */


#pragma once
#include<initializer_list>
#include<ostream>
#include<istream>
#include"iterator.hpp"

using std::ostream;
using std::istream;
using std::initializer_list;


class self_string
{
	private:
		char* arr = nullptr;

		size_t arr_size = 10;
		int elem_count = 0;

	public:
		using value = char*;
		using iterator = Random_iterator<char>;
		using const_iterator = const_Random_iterator<char>;

	public:
		self_string()
		{
			arr = new char[arr_size];
		}

		self_string(const initializer_list<char>& list)
		{
			arr_size = list.size();
			arr = new char[arr_size];

			for (auto p : list)
			{
				arr[elem_count++] = p;
			}
		}

		self_string(const char ptr[])
		{
			int count = 0;
			while (ptr[count])
			{
				count++;
			}

			arr_size = (size_t)count;
			arr = new char[arr_size];

			for (int n = 0; n < arr_size; ++n)
			{
				arr[elem_count++] = ptr[n];
			}
		}

		self_string(const self_string& obj)
		{
			arr_size = obj.arr_size;
			arr = new char[arr_size];

			for (int n = 0; n < obj.elem_count; ++n)
			{
				arr[elem_count++] = obj.arr[n];
			}
		}

		~self_string()
		{
			delete[] arr;
			arr = nullptr;
		}



		//operations

		void erase(char c)
		{
			for (int n = 0; n < elem_count; ++n)
			{
				if (arr[n] == c)
				{
					char* temp = new char[(size_t)elem_count];

					int count = 0;
					for (int i = 0; i < elem_count; ++i)
					{
						if (arr[i] != c)
							temp[count++] = arr[i];
					}

					delete[] arr;
					arr = new char[arr_size];

					for (int i = 0; i < elem_count - 1; ++i)
					{
						arr[i] = temp[i];
					}

					elem_count--;
					break;
				}
			}
		}

		iterator erase(iterator ptr)
		{
			char* temp = new char[(size_t)elem_count];

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
			arr = new char[arr_size];

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
			char* temp = new char[(size_t)elem_count];

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
			arr = new char[arr_size];

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
			arr = new char[arr_size];

			elem_count = 0;
		}

		char back()
		{
			return arr[elem_count - 1];
		}

		char* find(char elem)
		{
			char* temp = arr;

			for (int n = 0; n < elem_count; ++n)
			{
				if ((*temp) == elem)
					return temp;
				else
					temp++;
			}

			return nullptr;
		}

		int size()
		{
			return this->elem_count;
		}

		size_t max_size()
		{
			return this->arr_size;
		}

		bool empty()
		{
			if (elem_count == 0)
				return true;

			return false;
		}

		void swap(self_string& obj)
		{
			char* temp = new char[(size_t)obj.elem_count];

			for (int n = 0; n < obj.elem_count; ++n)
			{
				temp[n] = obj.arr[n];
			}


			delete[] obj.arr;
			obj.arr = new char[this->arr_size];

			for (int n = 0; n < this->elem_count; ++n)
			{
				obj.arr[n] = this->arr[n];
			}

			delete[] this->arr;
			this->arr = new char[obj.arr_size];

			for (int n = 0; n < obj.elem_count; ++n)
			{
				this->arr[n] = temp[n];
			}


			size_t size_temp = obj.arr_size;
			obj.arr_size = this->arr_size;
			this->arr_size = size_temp;

			int count = obj.elem_count;
			obj.elem_count = this->elem_count;
			this->elem_count = count;

			delete[] temp;
			temp = nullptr;
		}




		//iterator

		iterator begin()
		{
			return iterator(arr , 0);
		}

		iterator end()
		{
			return iterator(arr + elem_count , elem_count);
		}

		const_iterator cbegin() const
		{
			return const_iterator(arr , 0);
		}

		const_iterator cend() const
		{
			return const_iterator(arr + elem_count , elem_count);
		}




		//operator overload

		char& operator[](int n)
		{
			return arr[n];
		}

		friend ostream& operator<<(ostream& out,const self_string& obj)
		{	
			auto p = obj.cbegin();
			for (; p != obj.cend(); ++p)
			{
				out << (*p);
			}

			return out;
		}

		friend istream& operator>>(istream& input , self_string& obj)
		{
			char* p = new char;
			input >> p;

			int count = 0;
			while (p[count])
			{
				count++;
			}

			while (obj.elem_count+count >= obj.arr_size)
			{
				obj.arr_size = obj.arr_size * 2;
				obj.MemoryExpand(obj.arr_size);
			}

			for (int n = 0; n < count; ++n)
			{
				obj.arr[obj.elem_count++] = p[n];
			}

			return input;
		}

		self_string& operator+(const char ptr[])
		{
			int count = 0;
			while (ptr[count])
			{
				count++;
			}

			while (elem_count + count >= arr_size)
			{
				arr_size = arr_size * 2;
				MemoryExpand(arr_size);
			}

			for (int n = 0; n < count; ++n)
			{
				arr[elem_count++] = ptr[n];
			}

			return *this;
		}

		self_string& operator+=(const char ptr[])
		{
			int count = 0;
			while (ptr[count])
			{
				count++;
			}

			while (elem_count + count >= arr_size)
			{
				arr_size = arr_size * 2;
				MemoryExpand(arr_size);
			}

			for (int n = 0; n < count; ++n)
			{
				arr[elem_count++] = ptr[n];
			}

			return *this;
		}

		self_string& operator=(const self_string& obj)
		{
			delete[] arr;
			arr = new char[obj.arr_size];

			elem_count = 0;
			arr_size = obj.arr_size;

			for (int n = 0; n < obj.elem_count; ++n)
			{
				arr[elem_count++] = obj.arr[n];
			}

			return *this;
		}

		bool operator==(const self_string& obj)
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

		bool operator!=(const self_string& obj)
		{
			return !((*this) == obj);
		}

	private:
		void MemoryExpand(size_t resize)
		{
			char* temp = new char[elem_count];

			for (int n = 0; n < elem_count; ++n)
			{
				temp[n] = arr[n];
			}

			delete[] arr;
			arr = new char[resize];

			for (int n = 0; n < elem_count; ++n)
			{
				arr[n] = temp[n];
			}

			delete[] temp;
			temp = nullptr;
		}
};