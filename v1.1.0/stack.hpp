/* stack implementation
 *
 * Copyright(c) 2021 Mashiro -1262159823@qq.com
 *
 * This File is part of CONTAINER LIBRARY project.
 *
 * version : 1.1.0
 *
 * author : Mashiro
 *
 * File name : stack.hpp -a kind of containers.
 *
 * This library is free software;you can redistribute is and/or modify it
 * under the APACHE LICENSE 2.0 as published by the Free Software Foundation.
 * ------------------------------------------------------------------------
 */


#pragma once
#include"deque.hpp"


template<typename Ty , template <typename type> typename container = deque>
class stack
{
	private:
		container<Ty>* arr = nullptr;
	public:
		using self = stack<Ty , container>;
		using value_type = Ty;
		using iterator = typename container<Ty>::iterator;
		using const_iterator = typename container<Ty>::const_iterator;

	public:
		stack()
		{
			arr = new container<Ty>;
		}

		stack(const initializer_list<Ty>& list) :stack()
		{
			for (auto p : list)
			{
				arr->push_back(p);
			}
		}

		stack(const self& obj)
		{
			arr = new container<Ty>(4);

			for (auto p : obj)
				push(p);
		}

		stack(self&& obj)
		{
			arr = new container<Ty>(obj.size());

			for (auto p : obj)
				push(p);

			obj.arr->~container<Ty>();
			obj.arr = nullptr;
		}

		~stack()
		{
			delete arr;
			arr = nullptr;
		}


		//operations 

		template<typename... value>
		[[noreturn]] void emplace(value&&... args)
		{
			arr->emplace_back(args...);
		}

		[[noreturn]] void push(value_type elem)
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

		_NODISCARD const value_type& top() const noexcept
		{
			return arr->back();
		}

		_NODISCARD value_type& top() noexcept
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

		[[noreturn]] void swap(self& obj)
		{
			container<Ty>* temp = new container<Ty>(obj.size());

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

		self& operator=(const self& obj)
		{
			if (*this != obj)
			{
				this->clear();

				auto p = obj.cbegin();
				for (; p != obj.cend(); ++p)
				{
					arr->push_back((*p));
				}
			}

			return *this;
		}

		_NODISCARD bool operator==(const self& obj) const noexcept
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

		_NODISCARD bool operator!=(const self& obj) const noexcept
		{
			return !((*this) == obj);
		}
};