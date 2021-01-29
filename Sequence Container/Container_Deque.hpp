#pragma once
#include<initializer_list>
#include"iterator.hpp"

using std::initializer_list;


template<typename Ty>
class deque
{
	private:
		Ty* body = nullptr;

		size_t body_size = 10;
		int elem_count = 0;

	public:
		using TypeValue = Ty;
		using iterator = Random_iterator<Ty>;


		deque()
		{
			body = new Ty[body_size];
		}

		deque(size_t size)
		{
			body_size = size;
			body = new Ty[body_size];
		}

		deque(size_t size , Ty elem) :deque(size)
		{
			for (int n = 0; n < body_size; ++n)
			{
				body[n] = elem;
			}

			elem_count = body_size;
		}

		deque(const initializer_list<Ty>& list)
		{
			body_size = list.size() * 2;
			body = new Ty[body_size];

			for (auto p = list.begin(); p != list.end(); ++p)
			{
				body[elem_count] = (*p);
				elem_count++;
			}
		}

		deque(const deque<Ty>& obj)
		{
			body = new Ty[obj.body_size];

			for (int n=0; n < obj.elem_count; ++n)
			{
				Ty temp = obj.body[n];
				body[elem_count] = temp;

				elem_count++;
			}
		}

		~deque()
		{
			delete[] body;
			body = nullptr;
		}


		void push_back(Ty elem)
		{
			if (elem_count == body_size)
			{
				body_size = body_size * 2;
				MemoryExpand(body_size);
			}

			body[elem_count] = elem;
			elem_count++;
		}

		void push_front(Ty elem)
		{
			if (elem_count == body_size)
			{
				body_size = body_size * 2;
				MemoryExpand(body_size);
			}

			Ty head = elem;
			elem_count++;

			ComplexArr(head);
		}

		void pop_back()
		{   
			Ty* temp = new Ty[(size_t)elem_count - 1];

			for (int n = 0; n < elem_count - 1; ++n)
				temp[n] = body[n];

			delete[] body;
			body = new Ty[body_size];

			for (int n = 0; n < elem_count - 1; ++n)
				body[n] = temp[n];

			delete[] temp;
			temp = nullptr;
			elem_count--;
		}

		void pop_front()
		{
			Ty* temp = new Ty[(size_t)elem_count - 1];

			for (int n = 1; n < elem_count; ++n)
			{
				temp[n-1] = body[n];
			}

			delete[] body;
			body = new Ty[body_size];

			for (int n = 0; n < elem_count - 1; ++n)
			{
				body[n] = temp[n];
			}

			delete[] temp;
			temp = nullptr;
			elem_count--;
		}

		iterator erase(iterator& ptr)
		{
			Ty* temp = new Ty[(size_t)elem_count];

			int count = 0;
			int del = 0;
			for (int n = 0; n < elem_count; ++n)
			{
				if ((*ptr) != body[n])
				{
					temp[count] = body[n];
					count++;
				}
				else
					del = n;
			}

			delete body;
			body = new Ty[(size_t)elem_count - 1];

			for (int n = 0; n < elem_count - 1; ++n)
			{
				body[n] = temp[n];
			}

			delete[] temp;
			temp = nullptr;

			elem_count--;

			return iterator(&body[del] , elem_count);
		}

		void clear()
		{
			delete[] body;
			body = new Ty[body_size];

			elem_count = 0;
		}

		Ty front()
		{
			return body[0];
		}

		Ty back()
		{
			return body[elem_count-1];
		}

		void resize(size_t resize)
		{
			MemoryExpand(resize);

			if (elem_count > resize)
				elem_count = (int)resize;

			body_size = resize;
		}

		int size()
		{
			return elem_count;
		}

		size_t max_size()
		{
			return body_size;
		}

		void swap(deque<Ty>& obj)
		{
			//check size
			if (body_size > obj.body_size)
				obj.resize(body_size);
			else if (body_size < obj.body_size)
				resize(obj.body_size);

			//keep elem
			Ty* ptr = new Ty[obj.elem_count];

			for (int n = 0; n < obj.elem_count; ++n)
			{
				ptr[n] = obj.body[n];
			}

			//swap elem

			for (int n = 0; n < elem_count; ++n)
			{
				obj.body[n] = this->body[n];
			}

			for (int n = 0; n < obj.elem_count; ++n)
				body[n] = ptr[n];

			//swap count & size

			int temp_count = elem_count;
			elem_count = obj.elem_count;
			obj.elem_count = temp_count;

			size_t temp_size = body_size;
			body_size = obj.body_size;
			obj.body_size = temp_size;


			//free ptr
			delete[] ptr;
			ptr = nullptr;
		}


		//iterator
		iterator begin()
		{
			return iterator(body, (int)body_size);
		}

		iterator end()
		{
			return iterator(body + elem_count, (int)body_size);
		}

		iterator cbegin() const
		{
			return iterator(body , (int)body_size);
		}

		iterator cend() const
		{
			return iterator(body + elem_count , (int)body_size);
		}


		//operator overload

		decltype(auto) operator[](int n)
		{
			return body[n];
		}

		void operator=(const deque<Ty>& obj)
		{
			if (body_size < obj.body_size)
			{
				body_size = obj.body_size;
				MemoryExpand(body_size);
			}

			for (int n = 0; n < obj.elem_count; ++n)
			{
				Ty temp = obj.body[n];
				body[n] = temp;
			}

			elem_count = obj.elem_count;
		}

		void operator=(Ty elem)
		{
			for (int n = 0; n < body_size; ++n)
				body[n] = elem;

			elem_count = body_size;
		}

		bool operator==(const deque<Ty>& obj)
		{
			if (elem_count != obj.elem_count)
				return false;

			for (int n = 0; n < elem_count; ++n)
			{
				if (body[n] != obj.body[n])
					return false;
			}

			return true;
		}

		bool operator!=(const deque<Ty>& obj)
		{
			return !((*this) == obj);
		}

		bool operator>(const deque<Ty>& obj)
		{
			if (body_size > obj.body_size)
				return true;

			return false;
		}

		bool operator<(const deque<Ty>& obj)
		{
			if (body_size < obj.body_size)
				return true;

			return false;
		}

		bool operator<=(const deque<Ty>& obj)
		{
			if (body_size <= obj.body_size)
				return true;

			return false;
		}

		bool operator>=(const deque<Ty>& obj)
		{
			if (body_size >= obj.body_size)
				return true;

			return false;
		}

	private:
		void MemoryExpand(size_t resize)
		{
			if (elem_count != 0)
			{
				Ty* temp = new Ty[elem_count];

				for (int n = 0; n < elem_count; ++n)
					temp[n] = body[n];

				delete[] body;
				body = new Ty[resize];

				if (resize > body_size)
				{
					for (int n = 0; n < elem_count; ++n)
						body[n] = temp[n];
				}
				else
				{
					for (int n = 0; n < resize; ++n)
						body[n] = temp[n];
				}

				delete[] temp;
				temp = nullptr;
			}
			else
			{
				delete[] body;
				body = new Ty[resize];
			}
		}
		   	   
		void ComplexArr(Ty head)
		{
			Ty* temp = new Ty[elem_count];

			for (int n = 0; n < elem_count; ++n)
			{
				if (n == 0)
					temp[n] = head;
				else
					temp[n] = body[n - 1];
			}

			delete[] body;
			body = new Ty[body_size];

			for (int n = 0; n < elem_count; ++n)
				body[n] = temp[n];

			delete[] temp;
			temp = nullptr;
		}
};