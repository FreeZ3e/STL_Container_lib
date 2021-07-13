/* list implementation
 *
 * Copyright(c) 2021 Mashiro -1262159823@qq.com
 *
 * This File is part of CONTAINER LIBRARY project.
 *
 * version : 1.3.0-alpha
 *
 * author : Mashiro
 *
 * File name : Container_List.hpp -a kind of sequence container.
 *
 * This library is free software;you can redistribute is and/or modify it
 * under the APACHE LICENSE 2.0 as published by the Free Software Foundation.
 * ------------------------------------------------------------------------
 *
 *-------------------------------README------------------------------------
 *
 * template<typename Ty,int default_size = 0,typename _alloc = _default_allocator>
 * class list
 * {
 *		//iterator : List_iterator
 *		//const_iterator : const_List_iterator
 *
 *      //node define
 *      struct node
 *      {
 *          node* next;
 *          node* last;
 *          Ty data;
 *
 *          node() = default;
 *          node(Ty elem,node* n_ptr = nullptr,node* l_ptr = nullptr):data(elem),next(n_ptr),last(l_ptr)
 *          {}
 *      }
 *
 *      //ctor
 *
 *      list()
 *      list(size_t size)---------------------------------initialize with size.
 *      list(size_t size,Ty elem)-------------------------initialize with size and fill container with elem.
 *      list(const initializer_list<Ty>& list)
 *      list(const list<Ty,default_size,_alloc>& obj)
 *
 *      //operations
 *
 *		void insert(Ty elem)------------------------------call push_back().
 *      void push_back(Ty elem)
 *      void push_front(Ty elem)
 *      void pop_back()
 *      void pop_front()
 *      void remove(Ty elem)------------------------------remove elem from container.
 *		void erase(Ty elem)
 *      iterator erase(iterator ptr)----------------------remove elem in position of iterator.
 *      const_iterator erase(const_iterator ptr)
 *      void erase(iterator p_being,iterator p_end)-------remove elem in range of iterator.
 *      void clear()
 *      Ty front()
 *      Ty back()
 *		iterator find(Ty elem)
 *		const_iterator cfind(Ty elem)
 *      bool empty()
 *      int size()
 *      size_t max_size()
 *      void resize(size_t size)
 *      void swap(self& obj)
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
 *      Ty operator[](int n) = delete
 *      bool operator==(const coll& obj)
 *      bool operator!=(const coll& obj)
 *      bool operator>(const coll& obj)
 *      bool operator<(const coll& obj)
 *      bool operator>=(const coll& obj)
 *      bool operator<=(const coll& obj)
 *
 *      //private function
 *
 *      void alloc(size_t list_size)------------------allocation memory and initialize container.
 *		void destory()
 * }
 * ----------------------------------------------------------------------------------------------
*/

#pragma once
#include<initializer_list>
#include"memory.hpp"
#include"iterator.hpp"
#include"errors.hpp"
#include"memory_allocator.hpp"

#if _LIB_DEBUG_LEVEL == 1

#include<assert.h>

#endif //_LIB_DEBUG_LEVEL == 1

using std::initializer_list;

template<typename Ty , int default_size = 8,
						typename _alloc = _default_allocator>
class list
{
	private:
		struct node
		{
			using TypeValue = Ty;

			node* next = nullptr;
			node* last = nullptr;
			Ty data;

			node() = default;

			node(Ty elem , node* n_ptr = nullptr , node* l_ptr = nullptr) :data(elem) , next(n_ptr) , last(l_ptr)
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

		node* Head = nullptr;
		node* CurPtr = nullptr;

		size_t list_size = default_size;
		int elem_count = 0;

	public:
		using self = list<Ty , default_size , _alloc>;
		using TypeValue = Ty;
		using iterator = List_iterator<node>;
		using const_iterator = const_List_iterator<node>;

	public:
		static_assert(default_size > 0 , "default size must bigger than 0");


		list() noexcept
		{
			alloc(list_size);
		}

		list(const size_t& size)
		{
		#if _LIB_DEBUG_LEVEL == 1

			_BUG_VERIFY((size > 0) , "container size error");
			assert(size > 0);

		#endif // _LIB_DEBUG_LEVEL == 1

			list_size = size;
			alloc(list_size);
		}

		list(const size_t& size , const Ty& elem) :list(size)
		{
		#if _LIB_DEBUG_LEVEL == 1

			_BUG_VERIFY((size > 0) , "container size error");
			assert(size > 0);

		#endif // _LIB_DEBUG_LEVEL == 1

			for (int n = 0; n < size; ++n)
				push_back(elem);
		}

		explicit list(const initializer_list<Ty>& list) noexcept
		{
			list_size = list.size();
			alloc(list_size);

			for (auto p = list.begin(); p != list.end(); ++p)
			{
				CurPtr->data = (*p);

				if (CurPtr->next)
					CurPtr = CurPtr->next;

				elem_count++;
			}
		}

		explicit list(const list<Ty , default_size , _alloc>& obj) noexcept
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

		~list() noexcept
		{
			destory();
		}


		//push and pop operation

		[[noreturn]] void insert(const Ty& elem) noexcept
		{
			push_back(elem);
		}

		[[noreturn]] void push_back(const Ty& elem) noexcept
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

		[[noreturn]] void push_front(const Ty& elem) noexcept
		{
			node* temp = new node(elem , Head , nullptr);

			Head->last = temp;
			Head = temp;

			elem_count++;
			while (elem_count >= list_size)
				list_size++;
		}

		[[noreturn]] void pop_back() noexcept
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

		[[noreturn]] void pop_front() noexcept
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


		//erase and clear operation

		[[noreturn]] void remove(const Ty& elem) noexcept
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

		[[noreturn]] void erase(const Ty& elem) noexcept
		{
			remove(elem);
		}

		_NODISCARD iterator erase(iterator ptr) noexcept
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

		_NODISCARD const_iterator erase(const_iterator ptr) noexcept
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
			destory();
			alloc(list_size);
		}


		//other

		_NODISCARD const Ty& front() const noexcept
		{
			return Head->data;
		}

		_NODISCARD const Ty& back() const noexcept
		{
			return CurPtr->last->data;
		}

		_NODISCARD Ty& front() noexcept
		{
			return Head->data;
		}

		_NODISCARD Ty& back() noexcept
		{
			return CurPtr->last->data;
		}

		_NODISCARD iterator find(const Ty& elem) const noexcept
		{
			auto p = begin();
			for (; p != end(); ++p)
			{
				if (*p == elem)
					return p;
			}

			return end();
		}

		_NODISCARD const_iterator cfind(const Ty& elem) const noexcept
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

		_NODISCARD size_t max_size() const noexcept
		{
			return list_size;
		}

		[[noreturn]] void resize(const size_t& size)
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

		[[noreturn]] void swap(self& obj) noexcept
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



		//iterator
		_NODISCARD iterator begin() noexcept
		{
			return iterator(Head , 0);
		}

		_NODISCARD iterator end() noexcept
		{
			return iterator(CurPtr , elem_count);
		}

		_NODISCARD iterator begin() const noexcept
		{
			return iterator(Head , 0);
		}

		_NODISCARD iterator end() const noexcept
		{
			return iterator(CurPtr , elem_count);
		}

		_NODISCARD const_iterator cbegin() const noexcept
		{
			return const_iterator(Head , 0);
		}

		_NODISCARD const_iterator cend() const noexcept
		{
			return const_iterator(CurPtr , elem_count);
		}


		//operator overload

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
		[[noreturn]] void alloc(const size_t& list_size)
		{
		#if _LIB_DEBUG_LEVEL == 1

			_BUG_VERIFY((list_size > 0) , "container size error");
			assert(list_size > 0);

		#endif // _LIB_DEBUG_LEVEL == 1

			//Head node alloc
			CurPtr = new node;
			CurPtr->last = nullptr;

			//set Head node
			Head = CurPtr;
			node* ptr = CurPtr;

			//alloc memory
			for (int n = 0; n < list_size; ++n)
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