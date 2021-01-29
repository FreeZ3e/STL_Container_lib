#pragma once
#include<initializer_list>
#include<typeinfo>
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
		using TypeValue = Ty;
		using iterator = Random_iterator<Ty>;

		//initializer_list ctor
		array(const initializer_list<Ty>& list)
		{
			int count = 0;
			for (auto p = list.begin(); p != list.end(); ++p)
			{
				if (count < size)
				{
					arr[count] = (*p);
					++count;

					elem_count++;
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

		//copy ctor
		array(const array<Ty , size>& obj)
		{
			for (int i = 0; i < size; ++i)
			{
				Ty temp = obj.arr[i];
				arr[i] = temp;

				elem_count++;
			}
		}

		explicit array(Ty num)
		{
			for (int i = 0;i<size;++i)
			{
				arr[i] = num;
			}

			elem_count = size;
		}

		//default ctor
		array()
		{
			for (int i = 0; i < size; ++i)
				arr[i] = 0;
		}

		~array()
		{
			delete[] arr;
			arr = nullptr;
		}

		//check array empty or not;
		bool empty()
		{
			if (elem_count == 0)
				return true;

			return false;
		}

		//return elem_count
		int array_size()
		{
			return elem_count;
		}

		//return size
		size_t max_size()
		{
			return size;
		}

		//return first elem
		Ty back()
		{
			return arr[size - 1];
		}

		//return last elem
		Ty front()
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
			//swap elem

			//keep obj arr
			Ty* obj_arr = new Ty[size];
			for (int n = 0; n < size; ++n)
			{
				obj_arr[n] = obj.arr[n];
			}
			
			//swap obj arr
			int count = 0;
			for (auto& p : obj)
			{
				p = this->arr[count];
				count++;
			}

			//swap this->arr
			for (int n = 0; n < size; ++n)
			{
				Ty temp = obj_arr[n];
				arr[n] = temp;
			}

			//swap elem_count
			int temp = elem_count;

			elem_count = obj.elem_count;
			obj.elem_count = elem_count;

			delete obj_arr;
			obj_arr = nullptr;
		}


		//iterator
		iterator begin()
		{
			return iterator(arr,(int)size);
		}

		iterator end()
		{
			return iterator(arr+elem_count,(int)size);
		}

		iterator cbegin() const
		{
			return iterator(arr , (int)size);
		}

		iterator cend() const
		{
			return iterator(arr + elem_count , (int)size);
		}


		//operator overload

		decltype(auto) operator[](int n)
		{
			return this->arr[n];
		}

		void operator=(const array<Ty , size>& obj)
		{
			for (int n = 0; n < obj.elem_count; ++n)
			{	
				Ty temp = obj.arr[n];
				this->arr[n] = temp;
			}

			this->elem_count = obj.elem_count;
		}

		bool operator==(const array<Ty , size>& obj)
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

		bool operator!=(const array<Ty , size>& obj)
		{
			return !((*this) == obj);
		}

		bool operator>(const array<Ty , size>& obj)
		{
			if (size > obj.size)
				return true;

			return false;
		}

		bool operator<(const array<Ty , size>& obj)
		{
			if (size < obj.size)
				return true;

			return false;
		}

		bool operator<=(const array<Ty , size>& obj)
		{
			if (size <= obj.size)
				return true;

			return false;
		}

		bool operator>=(const array<Ty , size>& obj)
		{
			if (size >= obj.size)
				return true;

			return false;
		}
};