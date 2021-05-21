/* stack implementation
 *
 * Copyright(c) 2021 Mashiro -1262159823@qq.com
 *
 * This File is part of CONTAINER LIBRARY project.
 *
 * version : 1.2.1-alpha
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
#include<initializer_list>
#include"iterator.hpp"
#include"Container_Deque.hpp"

using std::initializer_list;


template<typename Ty>
class stack
{
	private:
		deque<Ty>* arr = nullptr;
	public:
		using self = stack<Ty>;
		using TypeValue = Ty;
		using iterator = Random_iterator<Ty>;
		using const_iterator = const_Random_iterator<Ty>;

	public:
		stack() noexcept
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

		~stack() noexcept
		{
			arr->~deque();
			delete arr;
			arr = nullptr;
		}


		//operations 

		[[noreturn]] void push(const Ty& elem) noexcept
		{
			arr->push_back(elem);
		}

		[[noreturn]] void pop() noexcept
		{
			arr->pop_back();
		}

		[[noreturn]] void clear() noexcept
		{
			arr->clear();
		}

		_NODISCARD Ty top() const noexcept
		{
			return arr->back();
		}

		_NODISCARD bool empty() const noexcept
		{
			if (arr->empty())
				return true;

			return false;
		}

		_NODISCARD int size() const noexcept
		{
			return arr->size();
		}

		_NODISCARD size_t max_size() const noexcept
		{
			return arr->max_size();
		}

		[[noreturn]] void swap(stack<Ty>& obj) noexcept
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
		_NODISCARD iterator begin() noexcept
		{
			return arr->begin();
		}

		_NODISCARD iterator end() noexcept
		{
			return arr->end();
		}

		_NODISCARD iterator begin() const noexcept
		{
			return arr->begin();
		}

		_NODISCARD iterator end() const noexcept
		{
			return arr->end();
		}

		_NODISCARD const_iterator cbegin() const noexcept
		{
			return arr->cbegin();
		}

		_NODISCARD const_iterator cend() const noexcept
		{
			return arr->cend();
		}


		//operator overload

		stack<Ty>& operator=(const stack<Ty>& obj) noexcept
		{
			this->clear();

			auto p = obj.cbegin();
			for (; p != obj.cend(); ++p)
			{
				arr->push_back((*p));
			}

			return *this;
		}

		_NODISCARD bool operator==(const stack<Ty>& obj) const noexcept
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

		_NODISCARD bool operator!=(const stack<Ty>& obj) const noexcept
		{
			return !((*this) == obj);
		}
};