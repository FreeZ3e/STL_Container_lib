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
		//class type
		using TypeValue = Ty;
		//iterator type
		using iterator = Random_iterator<Ty>;

		//default ctor
		vector()
		{
			arr = new Ty[arr_size];
		}

		//initialize with size
		vector(size_t size)
		{
			arr_size = size;
			arr = new Ty[arr_size];
		}

		//initizlize with size & elem
		vector(size_t size , Ty elem):vector(size)
		{
			for (int n = 0; n < arr_size; ++n)
			{
				arr[n] = elem;
			}

			elem_count = arr_size;
		}

		//initializer_list ctor
		vector(const initializer_list<Ty>& list)
		{
			arr_size = list.size();
			arr = new Ty[(size_t)arr_size];

			for (auto p = list.begin(); p != list.end(); ++p)
			{
				arr[elem_count] = (*p);
				elem_count++;

				if (elem_count == arr_size)
					break;
			}
		}

		//copy ctor
		vector(const vector<Ty>& obj)
		{
			arr_size = obj.arr_size;
			arr = new Ty[arr_size];

			for (int n = 0; n < obj.elem_count; ++n)
			{
				Ty temp = obj.arr[n];
				arr[n] = temp;
			}

			elem_count = obj.elem_count;
		}

		//dtor
		~vector()
		{
			delete[] arr;
			arr = nullptr;
		}



		void insert(int pos , Ty elem)
		{
			arr[pos] = elem;
			elem_count++;
		}

		void push_back(Ty elem)
		{
			if (elem_count == arr_size)
			{
				arr_size = arr_size * 2;
				MemoryExpand(arr_size);
			}

			Ty insert_elem = elem;

			arr[elem_count] = insert_elem;
			elem_count++;
		}

		void emplace_back(const Ty &elem)
		{
			if (elem_count == arr_size)
			{   
				arr_size = arr_size * 2;
				MemoryExpand(arr_size);
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

		void clear()
		{
			delete[] arr;
			arr = new Ty[arr_size];

			elem_count = 0;
		}

		Ty back()
		{
			return arr[elem_count-1];
		}

		void resize(size_t resize)
		{
			MemoryExpand(resize);

			if (elem_count > resize)
				elem_count = (int)resize;

			arr_size = resize;
		}

		size_t max_size()
		{
			return this->arr_size;
		}

		int size()
		{
			return elem_count;
		}

		int capacity()
		{
			return (int)arr_size - elem_count;
		}

		void swap(vector<Ty>& obj)
		{
			if (arr_size > obj.arr_size)
				obj.resize(arr_size);
			else if (arr_size < obj.arr_size)
				resize(obj.arr_size);

			Ty* ptr = new Ty[obj.elem_count];

			for (int n = 0; n < obj.elem_count; ++n)
			{
				ptr[n] = obj.arr[n];
			}

			for (int n = 0; n < elem_count; ++n)
			{
				obj.arr[n] = this->arr[n];
			}

			for (int n = 0; n < obj.elem_count; ++n)
			{
				this->arr[n] = ptr[n];
			}

			int temp_count = elem_count;
			elem_count = obj.elem_count;
			obj.elem_count = temp_count;

			size_t temp_size = arr_size;
			arr_size = obj.arr_size;
			obj.arr_size = temp_size;

			delete[] ptr;
			ptr = nullptr;
		}


		//iterator
		iterator begin()
		{
			return iterator(arr,elem_count);
		}

		iterator end()
		{
			return iterator(arr + elem_count , elem_count);
		}

		iterator cbegin() const
		{
			return iterator(arr , elem_count);
		}

		iterator cend() const
		{
			return iterator(arr + elem_count , elem_count);
		}
			

		//operator overload

		decltype(auto) operator[](int n)
		{
			return arr[n];
		}

		void operator=(const vector<Ty>& obj)
		{
			if (arr_size < obj.arr_size)
			{
				arr_size = obj.arr_size;
				MemoryExpand(arr_size);
			}

			for (int n = 0; n < obj.elem_count; ++n)
			{
				Ty temp = obj.arr[n];
				this->arr[n] = temp;
			}

			this->elem_count = obj.elem_count;
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