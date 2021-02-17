/* stack implementation
 *
 * Copyright(c) 2021 Mashiro -1262159823@qq.com
 *
 * This File is part of CONTAINER LIBRARY project.
 *
 * version : 1.1.1-alpha
 *
 * author : Mashiro
 *
 * File name : Container_Stack.hpp -a kind of containers.
 *
 * This library is free software;you can redistribute is and/or modify it
 * under the APACHE LICENSE 2.0 as published by the Free Software Foundation.
 * ------------------------------------------------------------------------
 *
 * -----------------------------README-------------------------------------
 *
 * class stack
 * {
 *      //bottom container : deque
 *      //iterator : random_iterator
 *      //const_iterator : const_random_iterator
 *
 *      //ctor
 *
 *      stack()
 *      stack(const initializer_list<Ty>& list)
 *
 *
 *      //operations
 *
 *      void push(Ty elem)---------------------------insert elem at last.
 *      void pop()-----------------------------------pop elem by pop_back().
 *      void clear()
 *      Ty top()-------------------------------------return last elem.
 *      bool empty()
 *      int size()
 *      size_t max_size()
 *      void swap(stack<Ty>& obj)
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
 *      stack<Ty>& operator=(const stack<Ty>& obj)
 *      bool operator==(const stack<Ty>& obj)
 *      bool operator!=(const stack<Ty>& obj)
 * };
 */


#pragma once
#include"iterator.hpp"
#include"Container_Deque.hpp"
#include<initializer_list>

using std::initializer_list;


template<typename Ty>
class stack
{
	private:
		deque<Ty>* arr = nullptr;
	public:
		using value = Ty;
		using iterator = Random_iterator<Ty>;
		using const_iterator = const_Random_iterator<Ty>;

	public:
		stack()
		{
			arr = new deque<Ty>;
		}

		stack(const initializer_list<Ty>& list) :stack()
		{
			for (auto p : list)
			{
				arr->push_back(p);
			}
		}

		~stack()
		{
			delete arr;
			arr = nullptr;
		}


		//operations 

		void push(Ty elem)
		{
			arr->push_back(elem);
		}

		void pop()
		{
			arr->pop_back();
		}

		void clear()
		{
			arr->clear();
		}

		Ty top()
		{
			return arr->back();
		}

		bool empty()
		{
			if (arr->empty())
				return true;

			return false;
		}

		int size()
		{
			return arr->size();
		}

		size_t max_size()
		{
			return arr->max_size();
		}

		void swap(stack<Ty>& obj)
		{
			deque<Ty>* temp = new deque<Ty>(obj.size());

			for (auto p : obj)
			{
				temp->push_back(p);
			}


			obj.clear();
			for (auto p = begin(); p != end(); ++p)
			{
				obj.push((*p));
			}


			this->clear();
			for (auto p = temp->begin(); p != temp->end(); ++p)
			{
				this->push((*p));
			}
		}


		//iterator
		iterator begin()
		{
			return arr->begin();
		}

		iterator end()
		{
			return arr->end();
		}

		const_iterator cbegin() const
		{
			return arr->cbegin();
		}

		const_iterator cend() const
		{
			return arr->cend();
		}


		//operator overload

		stack<Ty>& operator=(const stack<Ty>& obj)
		{
			this->clear();

			auto p = obj.cbegin();
			for (; p != obj.cend(); ++p)
			{
				arr->push_back((*p));
			}

			return *this;
		}

		bool operator==(const stack<Ty>& obj)
		{
			if (this->size() != obj.size())
				return false;

			auto p1 = cbegin();
			auto p2 = obj.cbegin();

			for (; p1 != cend() , p2 != obj.cend(); ++p1 , ++p2)
			{
				if ((*p1) != (*p2))
					return false;
			}

			return true;
		}

		bool operator!=(const stack<Ty>& obj)
		{
			return !((*this) == obj);
		}
};