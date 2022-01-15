/* self_string implementation
 *
 * Copyright(c) 2021 Mashiro -1262159823@qq.com
 *
 * This File is part of CONTAINER LIBRARY project.
 *
 * version : 1.1.0
 *
 * author : Mashiro
 *
 * File name : string.hpp -a kind of containers.
 *
 * This library is free software;you can redistribute is and/or modify it
 * under the APACHE LICENSE 2.0 as published by the Free Software Foundation.
 * ------------------------------------------------------------------------
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
		using value_type = char*;
		using iterator = Random_iterator<char>;
		using const_iterator = const_Random_iterator<char>;
		using const_reverse_iterator = reverse_iterator<const_iterator>;
		using reverse_iterator = reverse_iterator<iterator>;

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

		self_string(const char* ptr)
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

		self_string(const char* ptr , size_t n)
		{
			arr_size = n;
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

		self_string(const self_string& obj , size_t pos , size_t len = -1)
		{
			size_t p_end;
			len == -1 ? p_end = obj.size() : p_end = pos + len;

			arr_size = p_end - pos;
			arr = new char[arr_size];

			for (int n = pos; n < p_end; ++n)
			{
				arr[elem_count++] = obj.arr[n];
			}
		}

		self_string(size_t n , char c)
		{
			arr_size = n;
			arr = new char[arr_size];
			
			for (int i = 0; i < n; ++i)
			{
				arr[elem_count++] = c;
			}
		}

		template<typename iter>
		self_string(iter beg , iter end):self_string()
		{
			while (beg < end)
			{
				push_back(*beg);
				++beg;
			}
		}

		self_string(self_string&& robj)
		{
			arr_size = robj.arr_size;
			arr = new char[arr_size];

			for (int n = 0; n < robj.elem_count; ++n)
			{
				arr[elem_count++] = robj.arr[n];
			}

			delete[] robj.arr;
			robj.arr = nullptr;

			robj.elem_count = 0;
		}

		~self_string()
		{
			delete[] arr;
			arr = nullptr;
		}



		//operations
		[[noreturn]] void push_back(char&& c)
		{
			if (elem_count >= arr_size-1)
			{
				arr_size = arr_size * 2;
				MemoryExpand(arr_size);
			}

			arr[elem_count++] = c;
		}

		[[noreturn]] void push_back(char& c)
		{
			if (elem_count >= arr_size - 1)
			{
				arr_size = arr_size * 2;
				MemoryExpand(arr_size);
			}

			arr[elem_count++] = c;
		}

		[[noreturn]] void pop_back() noexcept
		{
			erase(back());
		}

		_NODISCARD self_string& append(const self_string& obj)
		{
			while (elem_count + obj.elem_count >= (int)arr_size)
			{
				arr_size = arr_size * 2;
				MemoryExpand(arr_size);
			}

			for (int n = 0; n < obj.elem_count; ++n)
			{
				arr[elem_count++] = obj[n];
			}

			return *this;
		}

		_NODISCARD self_string& append(const self_string& obj , size_t pos , size_t len = -1)
		{
			size_t p_end;
			len == -1 ? p_end = obj.size() : p_end = pos + len;

			while (elem_count + (p_end - pos) >= (int)arr_size)
			{
				arr_size = arr_size * 2;
				MemoryExpand(arr_size);
			}

			for (int n = pos; n < p_end; ++n)
			{
				arr[elem_count++] = obj[n];
			}

			return *this;
		}

		_NODISCARD self_string& append(const char* ptr)
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

		_NODISCARD self_string& append(const char* ptr , size_t n)
		{
			while (elem_count + n >= (int)arr_size)
			{
				arr_size = arr_size * 2;
				MemoryExpand(arr_size);
			}

			for (int i = 0; i < n; ++i)
			{
				arr[elem_count++] = ptr[i];
			}

			return *this;
		}

		_NODISCARD self_string& append(size_t n , char c)
		{
			while (elem_count + n >= (int)arr_size)
			{
				arr_size = arr_size * 2;
				MemoryExpand(arr_size);
			}

			for (int i = 0; i < n; ++i)
			{
				arr[elem_count++] = c;
			}

			return *this;
		}

		template<typename iter>
		_NODISCARD self_string& append(iter beg , iter end)
		{
			while (beg < end)
			{
				push_back(*beg);
				++beg;
			}

			return *this;
		}

		_NODISCARD self_string& append(const initializer_list<char>& list)
		{
			for (auto p : list)
			{
				push_back(p);
			}

			return *this;
		}

		_NODISCARD self_string& assgin(const self_string& obj)
		{
			while (obj.elem_count > arr_size)
			{
				arr_size = arr_size * 2;
				MemoryExpand(arr_size);
			}

			for (int n = 0; n < obj.elem_count; ++n)
			{
				arr[n] = obj[n];
			}

			while (obj.elem_count < elem_count)
				pop_back();

			elem_count = obj.elem_count;
			return *this;
		}

		_NODISCARD self_string& assgin(const self_string& obj , size_t pos , size_t len = -1)
		{
			size_t p_end;
			len == -1 ? p_end = obj.size() : p_end = pos + len;

			while ((size_t)p_end - pos > arr_size)
			{
				arr_size = arr_size * 2;
				MemoryExpand(arr_size);
			}

			int index = pos;
			for (int n = 0; n < p_end - pos; ++n)
			{
				arr[n] = obj[index++];
			}

			while (p_end - pos < elem_count)
				pop_back();

			elem_count = p_end - pos;
			return *this;
		}

		_NODISCARD self_string& assgin(const char* ptr)
		{
			int count = 0;
			while (ptr[count])
			{
				count++;
			}

			while (count > (int)arr_size)
			{
				arr_size = arr_size * 2;
				MemoryExpand(arr_size);
			}

			for (int n = 0; n < count; ++n)
			{
				arr[n] = ptr[n];
			}

			while (count < elem_count)
				pop_back();

			elem_count = count;
			return *this;
		}

		_NODISCARD self_string& assgin(const char* ptr , size_t n)
		{
			while (n > arr_size)
			{
				arr_size = arr_size * 2;
				MemoryExpand(arr_size);
			}

			for (int i = 0; i < n; ++i)
			{
				arr[i] = ptr[i];
			}

			while (n < elem_count)
				pop_back();

			elem_count = n;
			return *this;
		}

		_NODISCARD self_string& assgin(size_t n , char c)
		{
			while (n > arr_size)
			{
				arr_size = arr_size * 2;
				MemoryExpand(arr_size);
			}

			for (int i = 0; i < n; ++i)
			{
				arr[i] = c;
			}

			while (n < elem_count)
				pop_back();

			elem_count = n;
			return *this;
		}

		template<typename iter>
		_NODISCARD self_string& assgin(iter beg , iter end)
		{
			int count = end.step() - beg.step();
			while (count > arr_size)
			{
				arr_size = arr_size * 2;
				MemoryExpand(arr_size);
			}

			for (int n = 0; n < count; ++n)
			{
				arr[n] = (*beg++);
			}

			while (count < elem_count)
				pop_back();

			elem_count = count;
			return *this;
		}

		_NODISCARD self_string& assgin(const initializer_list<char>& list)
		{
			while (list.size() > arr_size)
			{
				arr_size = arr_size * 2;
				MemoryExpand(arr_size);
			}

			auto it = list.begin();
			for (int n = 0; n < list.size(); ++n)
			{
				arr[n] = (*it++);
			}

			while (list.size() < elem_count)
				pop_back();

			elem_count = list.size();
			return *this;
		}

		_NODISCARD self_string& assgin(self_string&& obj)
		{
			while (obj.elem_count > arr_size)
			{
				arr_size = arr_size * 2;
				MemoryExpand(arr_size);
			}

			for (int n = 0; n < obj.elem_count; ++n)
			{
				arr[n] = obj[n];
			}

			while (obj.elem_count < elem_count)
				pop_back();

			elem_count = obj.elem_count;
			return *this;
		}

		_NODISCARD self_string& insert(size_t pos , const char c)
		{
			if (elem_count == arr_size)
			{
				arr_size = arr_size * 2;
				MemoryExpand(arr_size * 2);
			}

			int p_end = elem_count;
			while (p_end > pos && p_end > 0)
			{
				arr[p_end] = arr[p_end - 1];
				--p_end;
			}

			arr[p_end] = c;
			elem_count++;

			return *this;
		}

		_NODISCARD self_string& insert(size_t pos , const char* s)
		{
			int count = 0;
			while (s[count])
			{
				count++;
			}

			for (int n = count - 1; n > 0; --n)
			{
				insert(pos , s[n]);
			}

			return insert(pos , s[0]);
		}

		_NODISCARD self_string& insert(size_t pos , const char* s , size_t n)
		{
			for (int i = n - 1; i > 0; --i)
			{
				insert(pos , s[i]);
			}

			return insert(pos , s[0]);
		}

		_NODISCARD self_string& insert(size_t pos , size_t n , char c)
		{
			for (int i = 0; i < n-1; ++i)
			{
				insert(pos , c);
			}

			return insert(pos , c);
		}
		
		_NODISCARD self_string& insert(size_t pos , const self_string& obj)
		{
			for (int n = obj.elem_count - 1; n > 0; --n)
			{
				insert(pos , obj[n]);
			}

			return insert(pos , obj[0]);
		}

		_NODISCARD self_string& insert(size_t pos , const self_string& obj ,
									   size_t subpos , size_t len = -1)
		{
			size_t p_end;
			len == -1 ? p_end = obj.size() : p_end = subpos + len;

			for (int n = p_end - 1; n > subpos; --n)
			{
				insert(pos , obj[n]);
			}

			return insert(pos , obj[subpos]);
		}

		_NODISCARD iterator insert(iterator p , char c)
		{
			if (elem_count == arr_size)
			{
				arr_size = arr_size * 2;
				MemoryExpand(arr_size);
			}

			iterator temp = iterator(arr + elem_count , elem_count , (size_t)elem_count + 1);

			while (temp > p && temp > begin())
			{
				*temp = *(temp - 1);
				--temp;
			}

			*temp = c;
			elem_count++;

			return temp;
		}

		_NODISCARD iterator insert(iterator p , size_t n , char c)
		{
			for (int i = 0; i < n-1; ++i)
			{
				insert(p , c);
			}

			return insert(p , c) + n-1;
		}

		template<typename input_iter>
		_NODISCARD iterator insert(iterator p , input_iter beg , input_iter end)
		{
			int step = end.step() - beg.step();
			while (end > beg)
			{
				insert(p , *(end--));
			}

			return insert(p , *end) + step;
		}

		_NODISCARD self_string& insert(iterator p , const initializer_list<char>& list)
		{
			auto it = list.end() - 1;
			for (; it >= list.begin(); --it)
			{
				insert(p , *it);
			}

			return *this;
		}

		_NODISCARD self_string& replace(size_t pos , size_t len , const self_string& obj)
		{
			while ((size_t)elem_count + obj.elem_count > arr_size)
			{
				arr_size = arr_size * 2;
				MemoryExpand(arr_size);
			}

			int index = 0;
			int n = pos;
			for (; n < len + pos; ++n)
			{
				arr[n] = obj[index++];
				if (index >= obj.elem_count)
					break;
			}

			int last = obj.elem_count - 1;
			while (index <= last)
			{
				insert(pos + len , obj[last--]);
			}

			int del = n + 1;
			while (n < len + pos-1)
			{
				erase(arr[del]);
				n++;
			}

			return *this;
		}

		_NODISCARD self_string& replace(iterator beg , iterator end , const self_string& obj)
		{
			while ((size_t)elem_count + obj.elem_count > arr_size)
			{
				arr_size = arr_size * 2;
				MemoryExpand(arr_size);
			}
			
			size_t left = beg.step();
			size_t right = end.step();

			int index = 0;
			int n = left;
			for (; n <= right; ++n)
			{
				arr[n] = obj[index++];
				if (index >= obj.elem_count)
					break;
			}

			int last = obj.elem_count - 1;
			while (index <= last)
			{
				insert(right , obj[last--]);
			}

			int del = n+1;
			while (n < right)
			{
				erase(arr[del]);
				n++;
			}

			return *this;
		}

		_NODISCARD self_string& replace(size_t pos , size_t len , const self_string& obj,
							 size_t subpos , size_t sublen = -1)
		{
			size_t p_end;
			sublen == -1 ? p_end = obj.size() : p_end = subpos + sublen;

			while ((size_t)elem_count + p_end - subpos > arr_size)
			{
				arr_size = arr_size * 2;
				MemoryExpand(arr_size);
			}

			int index = subpos;
			int n = pos;
			for (; n < len + pos; ++n)
			{
				arr[n] = obj[index++];
				if (index >= p_end)
					break;
			}

			while (index < p_end)
			{
				insert(pos + len , obj[p_end--]);
			}

			int del = n+1;
			while (n < len + pos - 1)
			{
				erase(arr[del]);
				n++;
			}

			return *this;
		}

		_NODISCARD self_string& replace(size_t pos , size_t len , const char* s)
		{
			int count = 0;
			while (s[count])
			{
				count++;
			}

			while ((size_t)elem_count + count > arr_size)
			{
				arr_size = arr_size * 2;
				MemoryExpand(arr_size);
			}

			int index = 0;
			int n = pos;
			for (; n < len + pos; ++n)
			{
				arr[n] = s[index++];
				if (index >= count)
					break;
			}

			int last = count - 1;
			while (index <= last)
			{
				insert(pos + len , s[last--]);
			}

			int del = n + 1;
			while (n < len + pos - 1)
			{
				erase(arr[del]);
				n++;
			}

			return *this;
		}

		_NODISCARD self_string& replace(iterator beg , iterator end , const char* s)
		{
			int count = 0;
			while (s[count])
			{
				count++;
			}

			while ((size_t)elem_count + count > arr_size)
			{
				arr_size = arr_size * 2;
				MemoryExpand(arr_size);
			}

			size_t left = beg.step();
			size_t right = end.step();

			int index = 0;
			int n = left;
			for (; n <= right; ++n)
			{
				arr[n] = s[index++];
				if (index >= count)
					break;
			}

			int last = count - 1;
			while (index <= last)
			{
				insert(right , s[last--]);
			}

			int del = n + 1;
			while (n < right)
			{
				erase(arr[del]);
				n++;
			}

			return *this;
		}

		_NODISCARD self_string& replace(size_t pos , size_t len , const char* s , size_t n)
		{
			while ((size_t)elem_count + n > arr_size)
			{
				arr_size = arr_size * 2;
				MemoryExpand(arr_size);
			}


			int index = 0;
			int i = pos;
			for (; i < pos + len; ++i)
			{
				arr[i] = s[index++];
				if (index >= n)
					break;
			}

			int last = n - 1;
			while (index <= last)
			{
				insert(pos + len , s[last--]);
			}

			int del = i + 1;
			while (i < pos + len - 1)
			{
				erase(arr[del]);
				i++;
			}

			return *this;
		}

		_NODISCARD self_string& replace(iterator beg , iterator end , const char* s , size_t n)
		{
			while ((size_t)elem_count + n > arr_size)
			{
				arr_size = arr_size * 2;
				MemoryExpand(arr_size);
			}

			size_t left = beg.step();
			size_t right = end.step();

			int index = 0;
			int i = left;
			for (; i <= right; ++i)
			{
				arr[i] = s[index++];
				if (index >= n)
					break;
			}

			int last = n - 1;
			while (index <= last)
			{
				insert(right , s[last--]);
			}

			int del = i + 1;
			while (i < right)
			{
				erase(arr[del]);
				i++;
			}

			return *this;
		}

		_NODISCARD self_string& replace(size_t pos , size_t len , size_t n , char c)
		{
			while ((size_t)elem_count + n > arr_size)
			{
				arr_size = arr_size * 2;
				MemoryExpand(arr_size);
			}

			int index = 0;
			int i = pos;
			for ( ; i < pos + len; ++i)
			{
				arr[i] = c;
				index++;
				if (index >= n)
					break;
			}

			while (index < n)
			{
				insert(pos + len , c);
				index++;
			}

			int del = i + 1;
			while (i < pos + len - 1)
			{
				erase(arr[del]);
				++i;
			}

			return *this;
		}

		_NODISCARD self_string& replace(iterator beg , iterator end , size_t n , char c)
		{
			while ((size_t)elem_count + n > arr_size)
			{
				arr_size = arr_size * 2;
				MemoryExpand(arr_size);
			}

			size_t left = beg.step();
			size_t right = end.step();

			int index = 0;
			int i = left;
			for (; i <= right; ++i)
			{
				arr[i] = c;
				index++;
				if (index >= n)
					break;
			}

			while (index < n)
			{
				insert(right , c);
				index++;
			}

			int del = i + 1;
			while (i < right)
			{
				erase(arr[del]);
				++i;
			}

			return *this;
		}

		template<typename iter,typename input_iter>
		_NODISCARD self_string& replace(iter beg , iter end , input_iter p_beg , input_iter p_end)
		{
			int count = p_end.step() - p_beg.step();
			while ((size_t)elem_count + count > arr_size)
			{
				arr_size = arr_size * 2;
				MemoryExpand(arr_size);
			}

			size_t left = beg.step();
			size_t right = end.step();

			int index = 0;
			int n = left;
			for (; n <= right; ++n)
			{
				arr[n] = *p_beg;
				p_beg++;
				index++;
				if (index > count)
					break;
			}

			while (index <= count)
			{
				insert(right , *p_end--);
				index++;
			}

			int del = n + 1;
			while (n < right)
			{
				erase(arr[del]);
				++n;
			}

			return *this;
		}

		template<typename iter>
		_NODISCARD self_string& replace(iter beg , iter end , const initializer_list<char>& list)
		{
			while((size_t)elem_count + list.size() > arr_size)
			{
				arr_size = arr_size * 2;
				MemoryExpand(arr_size);
			}

			size_t left = beg.step();
			size_t right = end.step();

			auto it = list.begin();
			int n = left;
			for (; n <= right; ++n)
			{
				arr[n] = *it++;
				if (it == list.end())
					break;
			}

			auto last = list.end()-1;
			while (it <= last)
			{
				insert(right , *last--);
			}

			int del = n + 1;
			while (n < right)
			{
				erase(arr[del]);
				++n;
			}

			return *this;
		}


		[[noreturn]] void erase(const char& c)
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

		_NODISCARD iterator erase(iterator ptr)
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

			return iterator(&arr[del] , del , elem_count);
		}

		_NODISCARD const_iterator erase(const_iterator ptr)
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
			delete[] arr;
			arr = new char[arr_size];

			elem_count = 0;
		}

		_NODISCARD const char& back() const noexcept
		{
			return arr[elem_count - 1];
		}

		_NODISCARD char& back() noexcept
		{
			return arr[elem_count - 1];
		}

		_NODISCARD const char& front() const noexcept
		{
			return arr[0];
		}

		_NODISCARD char& front() noexcept
		{
			return arr[0];
		}

		_NODISCARD const char& at(size_t n) const
		{
			return arr[n];
		}

		_NODISCARD char& at(size_t n)
		{
			return arr[n];
		}

		_NODISCARD const char* data() const noexcept
		{
			return arr;
		}

		_NODISCARD char* data() noexcept
		{
			return arr;
		}

		_NODISCARD iterator find(char elem)
		{
			iterator temp = begin();

			for (;temp != end();++temp)
			{
				if ((*temp) == elem)
					return temp;
			}

			return temp;
		}

		_NODISCARD const_iterator find(char elem) const
		{
			const_iterator temp = cbegin();

			for (; temp != cend(); ++temp)
			{
				if ((*temp) == elem)
					return temp;
			}

			return temp;
		}

		_NODISCARD size_t size() const noexcept
		{
			return this->elem_count;
		}

		_NODISCARD size_t length() const noexcept
		{
			return this->elem_count;
		}

		_NODISCARD size_t max_size() const noexcept
		{
			return size_t(-1) / sizeof(char);
		}

		_NODISCARD size_t capacity() const noexcept
		{
			return arr_size - elem_count;
		}

		_NODISCARD bool empty() const noexcept
		{
			if (elem_count == 0)
				return true;

			return false;
		}

		[[noreturn]] void swap(self_string& obj)
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

		_NODISCARD self_string substr(size_t pos , size_t len = -1) const
		{
			self_string str(*this , pos , len);
			return str;
		}

		_NODISCARD char* c_str() const noexcept
		{
			char* str = (char*)malloc(sizeof(char) * elem_count);
			assert(str != nullptr);

			for (int n = 0; n < elem_count; ++n)
			{
				str[n] = arr[n];
			}

			return str;
		}

		//iterator

		_NODISCARD iterator begin() noexcept
		{
			return iterator(arr , 0, elem_count);
		}

		_NODISCARD iterator end() noexcept
		{
			return iterator(arr + elem_count , elem_count, elem_count);
		}

		_NODISCARD iterator begin() const noexcept
		{
			return iterator(arr , 0, elem_count);
		}

		_NODISCARD iterator end() const noexcept
		{
			return iterator(arr + elem_count , elem_count, elem_count);
		}

		_NODISCARD const_iterator cbegin() const noexcept
		{
			return const_iterator(arr , 0, elem_count);
		}

		_NODISCARD const_iterator cend() const noexcept
		{
			return const_iterator(arr + elem_count , elem_count, elem_count);
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


		//operator overload

		_NODISCARD char& operator[](int n)
		{
			return arr[n];
		}

		_NODISCARD const char& operator[](int n) const
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
			if (*this != obj)
			{
				delete[] arr;
				arr = new char[obj.arr_size];

				elem_count = 0;
				arr_size = obj.arr_size;

				for (int n = 0; n < obj.elem_count; ++n)
				{
					arr[elem_count++] = obj.arr[n];
				}
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
		[[noreturn]] void MemoryExpand(size_t resize)
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