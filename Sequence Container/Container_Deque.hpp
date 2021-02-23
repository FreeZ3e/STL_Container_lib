/* deque implementation
 *
 * Copyright(c) 2021 Mashiro -1262159823@qq.com
 *
 * This File is part of CONTAINER LIBRARY project.
 *
 * version : 1.1.1-alpha
 *
 * author : Mashiro
 *
 * File name : Container_Deque.hpp -a kind of sequence container.
 *
 * This library is free software;you can redistribute is and/or modify it
 * under the APACHE LICENSE 2.0 as published by the Free Software Foundation.
 * ------------------------------------------------------------------------
 *
 *-------------------------------README------------------------------------
 *
 * template<typename Ty>
 * class deque
 * {
 *		//iterator : random_iterator
 *		//const_iterator : const_random_iterator
 * 
 *      //ctor
 *
 *      deque()
 *      deque(size_t size)-------------------------------initialized with size.
 *      deque(size_t size,Ty elem)-----------------------initializer with size and fill with elem.
 *      deque(const initializer_list<Ty>& list)
 *      deque(const deque<Ty>& obj)
 *
 *      //operations
 *
 *		void insert(Ty elem)-----------------------------call push_back().
 *      void push_back(Ty elem)--------------------------insert at end.
 *      void push_front(Ty elem)-------------------------insert at head.
 *      void pop_back()----------------------------------pop last elem.
 *      void pop_front()---------------------------------pop first elem.
 *      iterator erase(iterator ptr)---------------------erase elem at iterator position.
 *      const_iterator erase(const_iterator ptr)
 *      void erase(iterator p_begin,iterator p_end)------erase elem in iterator range.
 *      void clear()-------------------------------------erase all elem.
 *      Ty front()---------------------------------------return first elem.
 *      Ty back()----------------------------------------return last elem.
 *      void resize(size_t resize)-----------------------resize container.
 *      int size()---------------------------------------return number of elems.
 *      size_t max_size()--------------------------------return size of container.
 *		bool empty()-------------------------------------return true if container is empty.
 *      void swap(deque<Ty>& obj)------------------------make swap operation.
 *
 *      //iterator
 *
 *      iterator begin()
 *      iterator end()
 *      const_iterator cbegin() const
 *      const_iterator cend() const
 *
 *      //operator overload
 *
 *      decltype(auto) operator[](int n)
 *      self& operator=(const deque<Ty>& obj)
 *      self& operator=(Ty elem)
 *      bool operator==(const deque<Ty>& obj)
 *      bool operator!=(const deque<Ty>& obj)
 *      bool operator>(const deque<Ty>& obj)
 *      bool operator<(const deque<Ty>& obj)
 *      bool operator>=(const deque<Ty>& obj)
 *      bool operator<=(const deque<Ty>& obj)
 *
 *      //private functions
 *
 *      void MemoryExpand(size_t resize)----------------------resize and expand size of container.
 *      void ComplexArr(Ty head)------------------------------when function:push_front call,connect
 *                                                            first elem with deque.
 * }
 * ----------------------------------------------------------------------------------------------
*/

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
		using self = deque<Ty>;
		using TypeValue = Ty;
		using iterator = Random_iterator<Ty>;
		using const_iterator = const_Random_iterator<Ty>;

	public:
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


		//push and pop operation

		void insert(Ty elem)
		{
			push_back(elem);
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


		//erase and clear operation

		iterator erase(iterator ptr)
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

			delete[] body;
			body = new Ty[body_size];

			for (int n = 0; n < elem_count - 1; ++n)
			{
				body[n] = temp[n];
			}

			delete[] temp;
			temp = nullptr;

			elem_count--;

			return iterator(&body[del]);
		}

		const_iterator erase(const_iterator ptr)
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

			delete[] body;
			body = new Ty[body_size];

			for (int n = 0; n < elem_count - 1; ++n)
			{
				body[n] = temp[n];
			}

			delete[] temp;
			temp = nullptr;

			elem_count--;

			return const_iterator(&body[del]);
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
			delete[] body;
			body = new Ty[body_size];

			elem_count = 0;
		}


		//other

		Ty front() const
		{
			return body[0];
		}

		Ty back() const
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

		int size() const
		{
			return elem_count;
		}

		size_t max_size() const
		{
			return body_size;
		}

		bool empty() const
		{
			if (elem_count == 0)
				return true;

			return false;
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
			return iterator(body,0);
		}

		iterator end()
		{
			return iterator(body + elem_count, elem_count);
		}

		const_iterator cbegin() const
		{
			return const_iterator(body,0);
		}

		const_iterator cend() const
		{
			return const_iterator(body + elem_count, elem_count);
		}


		//operator overload

		decltype(auto) operator[](int n)
		{
			return body[n];
		}

		self& operator=(const deque<Ty>& obj)
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

			return *this;
		}

		self& operator=(Ty elem)
		{
			for (int n = 0; n < body_size; ++n)
				body[n] = elem;

			elem_count = body_size;

			return *this;
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