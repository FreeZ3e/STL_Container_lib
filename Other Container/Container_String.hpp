/* self_string implementation
 *
 * Copyright(c) 2021 Mashiro -1262159823@qq.com
 *
 * This File is part of CONTAINER LIBRARY project.
 *
 * version : 1.3.0-alpha
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

#pragma warning(disable : 6386) //warning disable


class self_string
{
	private:
		char* arr = nullptr;

		size_t arr_size = 10;
		int elem_count = 0;

	public:
		using self = self_string;
		using TypeValue = char*;
		using iterator = Random_iterator<char>;
		using const_iterator = const_Random_iterator<char>;

	public:
		self_string() noexcept
		{
			arr = new char[arr_size];
		}

		self_string(const initializer_list<char>& list) noexcept
		{
			arr_size = list.size();
			arr = new char[arr_size];

			for (auto p : list)
			{
				arr[elem_count++] = p;
			}
		}

		self_string(const char ptr[]) noexcept
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

		self_string(const self_string& obj) noexcept
		{
			arr_size = obj.arr_size;
			arr = new char[arr_size];

			for (int n = 0; n < obj.elem_count; ++n)
			{
				arr[elem_count++] = obj.arr[n];
			}
		}

		~self_string() noexcept
		{
			delete[] arr;
			arr = nullptr;
		}



		//operations

		[[noreturn]] void erase(const char& c) noexcept
		{
			if (elem_count > 0)
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
		}

		_NODISCARD iterator erase(iterator ptr) noexcept
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

			for (int n = 0; n < count; ++n)
			{
				arr[n] = temp[n];
			}

			delete[] temp;
			temp = nullptr;

			elem_count = count;

			return iterator(&arr[del]);
		}

		_NODISCARD const_iterator erase(const_iterator ptr) noexcept
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

			for (int n = 0; n < count; ++n)
			{
				arr[n] = temp[n];
			}

			delete[] temp;
			temp = nullptr;

			elem_count = count;

			return const_iterator(&arr[del]);
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
			delete[] arr;
			arr = new char[arr_size];

			elem_count = 0;
		}

		_NODISCARD char back() const noexcept
		{
			return arr[elem_count - 1];
		}

		_NODISCARD char find(const char& elem) const noexcept
		{
			char* temp = arr;

			for (int n = 0; n < elem_count; ++n)
			{
				if ((*temp) == elem)
					return *temp;
				else
					temp++;
			}

			return *temp;
		}

		_NODISCARD int size() const noexcept
		{
			return this->elem_count;
		}

		_NODISCARD size_t max_size() const noexcept
		{
			return this->arr_size;
		}

		_NODISCARD bool empty() const noexcept
		{
			if (elem_count == 0)
				return true;

			return false;
		}

		[[noreturn]] void swap(self_string& obj) noexcept
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
			return const_iterator(arr , 0);
		}

		_NODISCARD const_iterator cend() const noexcept
		{
			return const_iterator(arr + elem_count , elem_count);
		}




		//operator overload

		_NODISCARD char& operator[](int n) noexcept
		{
			return arr[n];
		}

		_NODISCARD const char& operator[](int n) const noexcept
		{
			return arr[n];
		}

		friend ostream& operator<<(ostream& out,const self_string& obj) noexcept
		{	
			auto p = obj.cbegin();
			for (; p != obj.cend(); ++p)
			{
				out << (*p);
			}

			return out;
		}

		friend istream& operator>>(istream& input , self_string& obj) noexcept
		{
			char* p = new char;
			input.getline(p,100);
			p += '\0';

			int count = 0;
			while (p[count] != '\0')
			{
				count++;
			}

			while (obj.elem_count+count >= (int)obj.arr_size)
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

		self_string& operator+(const char ptr[]) noexcept
		{
			int count = 0;
			while (ptr[count])
			{
				count++;
			}

			while (elem_count + count >= (int)arr_size)
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

		self_string& operator+=(const char ptr[]) noexcept
		{
			int count = 0;
			while (ptr[count])
			{
				count++;
			}

			while (elem_count + count >= (int)arr_size)
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

		self_string& operator=(const self_string& obj) noexcept
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

		_NODISCARD bool operator==(const self_string& obj) const noexcept
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

		_NODISCARD bool operator!=(const self_string& obj) const noexcept
		{
			return !((*this) == obj);
		}

	private:
		[[noreturn]] void MemoryExpand(size_t resize) noexcept
		{
			if (elem_count > 0)
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
			else
			{
				delete[] arr;
				arr = new char[resize];
			}
		}
};