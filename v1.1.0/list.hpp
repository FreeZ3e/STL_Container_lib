/* list implementation
 *
 * Copyright(c) 2021 Mashiro -1262159823@qq.com
 *
 * This File is part of CONTAINER LIBRARY project.
 *
 * version : 1.1.0
 *
 * author : Mashiro
 *
 * File name : list.hpp -a kind of sequence container.
 *
 * This library is free software;you can redistribute is and/or modify it
 * under the APACHE LICENSE 2.0 as published by the Free Software Foundation.
 *-------------------------------------------------------------------------
 */


#pragma once
#include"errors.hpp"

#if _LIB_DEBUG_LEVEL == 1

#include<assert.h> 

#endif //_LIB_DEBUG_LEVEL == 1

#include<initializer_list>
#include"memory.hpp"
#include"iterator.hpp"
#include"memory_allocator.hpp"

using std::initializer_list;


template<typename Ty,size_t default_size = 8,
					 typename _alloc = _default_allocator>
class list
{
	private:
		struct node
		{
			using value_type = Ty;

			node* next = nullptr;
			node* last = nullptr;
			value_type data;

			node() = default;

			node(value_type elem , node* n_ptr = nullptr , node* l_ptr = nullptr) :next(n_ptr) , last(l_ptr) , data(elem)
			{
			}

			void* operator new(size_t size)
			{
				return simple_allocator(_alloc , node)::allocate(1);
			}

			void operator delete(void* ptr , size_t size)
			{
				simple_allocator(_alloc , node)::deallocate((node*)ptr , sizeof(node));
			}
		};


	public:
		using value_type = Ty;
		using reference = Ty&;
		using const_reference = const Ty&;
		using pointer = Ty*;
		using const_pointer = const Ty*;
		using iterator = List_iterator<node>;
		using const_iterator = const_List_iterator<node>;
		using const_reverse_iterator = reverse_iterator<const_iterator>;
		using reverse_iterator = reverse_iterator<iterator>;
		using size_type = size_t;
		using self = list<Ty , default_size , _alloc>;

	private:
		node* Head = nullptr;
		node* CurPtr = nullptr;

		size_t list_size = default_size;
		int elem_count = 0;

	public:
		static_assert(default_size > 0 , "default size must bigger than 0");



		list()
		{
			alloc(list_size);
		}

		explicit list(size_type size)
		{
		#if _LIB_DEBUG_LEVEL == 1

			_BUG_VERIFY((size > 0) , "container size error");
			assert(size > 0);

		#endif // _LIB_DEBUG_LEVEL == 1

			list_size = size;
			alloc(list_size);
		}

		list(size_type size , const_reference elem) :list(size)
		{
		#if _LIB_DEBUG_LEVEL == 1

			_BUG_VERIFY((size > 0) , "container size error");
			assert(size > 0);

		#endif // _LIB_DEBUG_LEVEL == 1

			for (int n = 0; n < size; ++n)
				push_back(elem);
		}

		explicit list(const initializer_list<value_type>& list) :list(list.size())
		{
			for (auto p = list.begin(); p != list.end(); ++p)
			{
				CurPtr->data = (*p);

				if (CurPtr->next)
					CurPtr = CurPtr->next;

				elem_count++;
			}
		}

		template<typename iter>
		list(iter beg , iter end) :list((size_type)end.step() - beg.step())
		{
			while (beg != end)
			{
				push_back(*beg);
				++beg;
			}
		}

		list(const self& obj)
		{
			list_size = obj.list_size;
			alloc(list_size);

			//get head ptr
			auto ptr = obj.Head;

			for (int n = 0; n < obj.elem_count; ++n)
			{
				CurPtr->data = ptr->data;

				if (CurPtr->next)
					CurPtr = CurPtr->next;

				elem_count++;

				ptr = ptr->next;
				if (ptr == nullptr)
					break;
			}
		}

		list(self&& obj)
		{
			list_size = obj.list_size;
			alloc(list_size);

			//get head ptr
			auto ptr = obj.Head;

			for (int n = 0; n < obj.elem_count; ++n)
			{
				CurPtr->data = ptr->data;

				if (CurPtr->next)
					CurPtr = CurPtr->next;

				elem_count++;

				ptr = ptr->next;
				if (ptr == nullptr)
					break;
			}

			obj.destory();
			obj.elem_count = 0;
			obj.Head = obj.CurPtr = nullptr;
		}

		~list()
		{
			destory();
		}



		[[noreturn]] void assgin(int size , const_reference elem)
		{
			if (size > elem_count)
			{
				iterator beg = begin();

				while (beg != end())
				{
					*beg = elem;
					++beg;
					--size;
				}

				while (size > 0)
				{
					push_back(elem);
					size--;
				}
			}
			else
			{
				iterator beg = begin();
				int step = elem_count - size;

				while (size > 0)
				{
					*beg = elem;
					++beg;
					--size;
				}

				for (int n = 0; n < step; ++n)
				{
					pop_back();
				}
			}
		}

		template<typename iter>
		[[noreturn]] void assgin(iter beg , iter p_end)
		{
			int size = p_end.step() - beg.step();

			if (size > elem_count)
			{
				auto temp = begin();
				while (temp.step() != end().step())
				{
					*temp = (*beg++);
					++temp;
					--size;
				}

				while (size > 0)
				{
					push_back((*beg++));
					--size;
				}
			}
			else
			{
				auto temp = begin();
				int step = elem_count - size;

				while (size > 0)
				{
					*temp = (*beg++);
					++temp;
					--size;
				}

				for (int n = 0; n < step; ++n)
				{
					pop_back();
				}
			}
		}

		[[noreturn]] void assgin(const initializer_list<value_type>& list)
		{
			int size = list.size();

			if (size > elem_count)
			{
				auto temp = begin();
				auto pos = list.begin();

				while (temp != end())
				{
					*temp = (*pos++);
					++temp;
					--size;
				}

				while (size > 0)
				{
					push_back((*pos++));
					--size;
				}
			}
			else
			{
				auto temp = begin();
				auto pos = list.begin();
				int step = elem_count - size;

				while (size > 0)
				{
					*temp = (*pos++);
					++temp;
					--size;
				}

				for (int n = 0; n < step; ++n)
				{
					pop_back();
				}
			}
		}

		[[noreturn]] void insert(const iterator pos , const_reference elem)
		{
			if (pos >= end())
			{
				push_back(elem);
				return;
			}

			push_back(*(end() - 1));
			iterator iter = end() - 2;

			while (iter != pos)
			{
				*iter = *(iter - 1);
				--iter;
			}

			*iter = elem;
		}

		[[noreturn]] void insert(const iterator pos , value_type&& elem)
		{
			if (pos >= end())
			{
				push_back(elem);
				return;
			}

			push_back(*(end() - 1));
			iterator iter = end() - 2;

			while (iter != pos)
			{
				*iter = *(iter - 1);
				--iter;
			}

			*iter = elem;
		}

		template<typename iter>
		[[noreturn]] void insert(const iterator pos , iter beg , iter end)
		{
			while (end >= beg)
			{
				insert(pos , *(end--));
			}
		}

		[[noreturn]] void insert(const iterator pos , const initializer_list<value_type>& list)
		{
			auto temp = list.end() - 1;
			while (temp >= list.begin())
			{
				insert(pos , *(temp--));
			}
		}

		[[noreturn]] void insert(const_reference elem)
		{
			push_back(elem);
		}

		[[noreturn]] void insert(value_type&& elem)
		{
			push_back(elem);
		}

		[[noreturn]] void push_back(const_reference elem)
		{
			CurPtr->data = elem;

			if (CurPtr->next == nullptr)
			{
				CurPtr->next = new node;
				CurPtr->next->last = CurPtr;
				CurPtr->next->next = nullptr;
			}

			CurPtr = CurPtr->next;

			elem_count++;
			while (elem_count >= list_size)
				list_size++;
		}

		[[noreturn]] void push_back(value_type&& elem)
		{
			CurPtr->data = elem;

			if (CurPtr->next == nullptr)
			{
				CurPtr->next = new node;
				CurPtr->next->last = CurPtr;
				CurPtr->next->next = nullptr;
			}

			CurPtr = CurPtr->next;

			elem_count++;
			while (elem_count >= list_size)
				list_size++;
		}

		[[noreturn]] void push_front(const_reference elem)
		{
			node* temp = new node(elem , Head , nullptr);

			Head->last = temp;
			Head = temp;

			elem_count++;
			while (elem_count >= list_size)
				list_size++;
		}

		[[noreturn]] void push_front(value_type&& elem)
		{
			node* temp = new node(elem , Head , nullptr);

			Head->last = temp;
			Head = temp;

			elem_count++;
			while (elem_count >= list_size)
				list_size++;
		}

		[[noreturn]] void pop_back()
		{
			if (elem_count > 0)
			{
				memory::elem_destory(back());

				node* ptr = CurPtr->last;

				CurPtr = CurPtr->last->last;

				delete ptr;
				ptr = nullptr;

				node* temp = new node;
				temp->last = CurPtr;
				temp->next = nullptr;

				CurPtr->next = temp;
				CurPtr = temp;

				elem_count--;
			}
		}

		[[noreturn]] void pop_front()
		{
			if (elem_count > 0)
			{
				memory::elem_destory(front());

				node* ptr = Head;

				Head = Head->next;
				Head->last = nullptr;

				delete ptr;
				ptr = nullptr;

				elem_count--;
			}
		}
		
		template<typename... value>
		[[noreturn]] void emplace_front(value&&... arg)
		{
			emplace(begin() , arg...);
		}

		template<typename... value>
		[[noreturn]] void emplace_back(value&&... arg)
		{
			emplace(end() , arg...);
		}

		template<typename... value>
		_NODISCARD iterator emplace(const iterator pos , value&&... arg)
		{
			if (pos >= end())
			{
				pointer temp = &CurPtr->data;
				new(temp) value_type(arg...);

				if (CurPtr->next == nullptr)
				{
					CurPtr->next = new node;
					CurPtr->next->last = CurPtr;
					CurPtr->next->next = nullptr;
				}

				CurPtr = CurPtr->next;
				elem_count++;

				return begin()+pos.step();
			}

			push_back(*(end() - 1));
			iterator iter = end() - 2;

			while (iter != pos)
			{
				*iter = *(iter - 1);
				--iter;
			}

			auto ptr = Head;
			for (int n = 0; n < pos.step(); ++n)
				ptr = ptr->next;

			pointer temp = &ptr->data;
			new(temp) value_type(arg...);

			return (begin() + pos.step());
		}





		[[noreturn]] void remove(const_reference elem)
		{
			node* ptr = new node;
			ptr->next = Head;

			while (ptr->next)
			{
				if (ptr->next->data == elem)
				{
					if (ptr->next == Head)
					{
						pop_front();
						ptr->next = Head;
					}
					else if (ptr->next == CurPtr)
					{
						pop_back();
						ptr->next = CurPtr;
					}
					else
					{
						node* temp = ptr->next;
						memory::elem_destory(temp->data);

						ptr->next = ptr->next->next;
						ptr->next->last = ptr;

						delete temp;

						elem_count--;
					}
				}
				else
				{
					ptr = ptr->next;
				}
			}
		}

		[[noreturn]] void remove_if(bool(*pred)(value_type))
		{
			iterator beg = begin();

			while (beg != end())
			{
				if (pred(*beg))
					remove(*beg);

				++beg;
			}
		}

		[[noreturn]] void erase(const_reference elem)
		{
			remove(elem);
		}

		_NODISCARD iterator erase(iterator ptr)
		{
			if (ptr == end())
			{
				remove(*ptr);
				return end();
			}

			auto next_val = *(ptr + 1);

			remove(*ptr);
			return find(next_val);
		}

		_NODISCARD const_iterator erase(const_iterator ptr)
		{
			if (ptr == cend())
			{
				remove(*ptr);
				return cend();
			}

			auto next_val = *(ptr + 1);

			remove(*ptr);
			return cfind(next_val);
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
			destory();
			alloc(list_size);
		}




		_NODISCARD const_reference front() const noexcept
		{
			return Head->data;
		}

		_NODISCARD const_reference back() const noexcept
		{
			return CurPtr->last->data;
		}

		_NODISCARD reference front() noexcept
		{
			return Head->data;
		}

		_NODISCARD reference back() noexcept
		{
			return CurPtr->last->data;
		}

		_NODISCARD iterator find(const_reference elem) const
		{
			auto p = begin();
			for (; p != end(); ++p)
			{
				if (*p == elem)
					return p;
			}

			return end();
		}

		_NODISCARD const_iterator cfind(const_reference elem) const
		{
			auto p = cbegin();
			for (; p != cend(); ++p)
			{
				if (*p == elem)
					return p;
			}

			return cend();
		}

		_NODISCARD bool empty() const noexcept
		{
			if (elem_count == 0)
				return true;

			return false;
		}

		_NODISCARD int size() const noexcept
		{
			return elem_count;
		}

		_NODISCARD size_type max_size() const noexcept
		{
			return size_type(-1) / sizeof(value_type);
		}

		[[noreturn]] void resize(size_type size)
		{
		#if _LIB_DEBUG_LEVEL == 1

			_BUG_VERIFY((size > 0) , "container size error");
			assert(size > 0);

		#endif // _LIB_DEBUG_LEVEL == 1

			if (size >= list_size)
			{
				node* ptr = CurPtr;
				for (int n = 0; n < (int)size - list_size; ++n)
				{
					ptr->next = new node;
					ptr = ptr->next;
				}ptr->next = nullptr;
			}
			else
			{
				for (int n = 0; n < list_size - size; ++n)
				{
					pop_back();
				}
			}

			list_size = size;
		}

		[[noreturn]] void swap(self& obj)
		{
			node* temp_head = Head;
			node* temp_CurPtr = CurPtr;
			node* obj_head = obj.Head;
			node* obj_CurPtr = obj.CurPtr;

			Head = obj_head;
			CurPtr = obj_CurPtr;
			obj.Head = temp_head;
			obj.CurPtr = temp_CurPtr;

			int temp_count = elem_count;
			elem_count = obj.elem_count;
			obj.elem_count = temp_count;

			size_t temp_size = list_size;
			list_size = obj.list_size;
			obj.list_size = temp_size;
		}



		_NODISCARD iterator begin() noexcept
		{
			return iterator(Head , 0 , elem_count);
		}

		_NODISCARD iterator end() noexcept
		{
			return iterator(CurPtr , elem_count , elem_count);
		}

		_NODISCARD const_iterator begin() const noexcept
		{
			return const_iterator(Head , 0 , elem_count);
		}

		_NODISCARD const_iterator end() const noexcept
		{
			return const_iterator(CurPtr , elem_count , elem_count);
		}

		_NODISCARD const_iterator cbegin() const noexcept
		{
			return const_iterator(Head , 0 , elem_count);
		}

		_NODISCARD const_iterator cend() const noexcept
		{
			return const_iterator(CurPtr , elem_count , elem_count);
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



		Ty operator[](int n) = delete;

		template<typename coll>
		_NODISCARD bool operator==(const coll& obj) const noexcept
		{
			if (elem_count != obj.size())
				return false;

			auto ptr = Head;
			for (auto p = obj.cbegin(); p != obj.cend(); ++p)
			{
				if ((*p) != ptr->data)
					return false;

				ptr = ptr->next;
			}

			return true;
		}

		template<typename coll>
		_NODISCARD bool operator!=(const coll& obj) const noexcept
		{
			return !((*this) == obj);
		}

		template<typename coll>
		_NODISCARD bool operator>(const coll& obj) const noexcept
		{
			if (elem_count > obj.size())
				return true;

			return false;
		}

		template<typename coll>
		_NODISCARD bool operator<(const coll& obj) const noexcept
		{
			if (elem_count < obj.size())
				return true;

			return false;
		}

		template<typename coll>
		_NODISCARD bool operator>=(const coll& obj) const noexcept
		{
			if (elem_count >= obj.size())
				return true;

			return false;
		}

		template<typename coll>
		_NODISCARD bool operator<=(const coll& obj) const noexcept
		{
			if (elem_count <= obj.size())
				return true;

			return false;
		}

	private:
		[[noreturn]] void alloc(size_type size)
		{
		#if _LIB_DEBUG_LEVEL == 1

			_BUG_VERIFY((size > 0) , "container size error");
			assert(size > 0);

		#endif // _LIB_DEBUG_LEVEL == 1

			//Head node alloc
			CurPtr = new node;
			CurPtr->last = nullptr;

			//set Head node
			Head = CurPtr;
			node* ptr = CurPtr;

			//alloc memory
			for (int n = 0; n < size; ++n)
			{
				ptr->next = new node;
				ptr->next->last = ptr;

				ptr = ptr->next;
			}ptr->next = nullptr;
		}

		[[noreturn]] void destory() noexcept
		{
			node* ptr = Head;

			while (ptr)
			{
				node* temp = ptr;
				memory::elem_destory(temp->data);

				ptr = ptr->next;

				delete temp;
			}

			Head = CurPtr = nullptr;
			elem_count = 0;
		}
}; 