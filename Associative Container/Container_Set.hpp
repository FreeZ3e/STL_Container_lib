/* set implementation
 *
 * Copyright(c) 2021 Mashiro -1262159823@qq.com
 *
 * This File is part of CONTAINER LIBRARY project.
 *
 * version : 1.3.0-alpha
 *
 * author : Mashiro
 *
 * File name : Container_Set.hpp -a kind of associative contiainer.
 *
 * This library is free software;you can redistribute is and/or modify it
 * under the APACHE LICENSE 2.0 as published by the Free Software Foundation.
 * ------------------------------------------------------------------------
 *
 *-------------------------------README------------------------------------
 *
 * template<typename Ty>
 * class set
 * {
 *      //iterator : RB_Tree_iterator
 *      //const_iterator : const_RB_Tree_iterator
 *
 *      //compare : Unique_Compare
 *
 *      //ctor
 *
 *      set()------------------------------------initialize RB_Tree ptr.
 *      set(Ty elem)-----------------------------insert elem.
 *      set(const initializer_list<Ty>& list)
 *      set(const set<Ty>& obj)
 *
 *      //operations
 *
 *      void insert(Ty elem)
 *      void insert(const initializer_list<Ty>& obj)
 *      void erase(Ty elem)
 *      iterator erase(iterator ptr)
 *      const_iterator erase(const_iterator& ptr)
 *      void erase(iterator p_begin,iterator p_end)
 *      void clear()
 *      bool empty()
 *      int size()
 *      bool find(Ty elem)
 *      compare key_comp--------------------------return compare function.
 *      void swap(set<Ty>& obj)
 *
 *
 *      //iterator
 *
 *      iterator begin()
 *      iterator end()
 *      const_iterator cbegin() const
 *      const_iterator cend() const
 *
 *
 *      //operator overload
 *
 *      self& operator=(const set<Ty>& obj)
 *      bool operator==(const set<Ty>& obj)
 *      bool operator!=(const set<Ty>& obj)
 *      bool operator>(const set<Ty>& obj)
 *      bool operator<(const set<Ty>& obj)
 *      bool operator>=(const set<Ty>& obj)
 *      bool operator<=(const set<Ty>& obj)
 * }
 * ----------------------------------------------------------------------------------------------
 */


#pragma once
#include<initializer_list>
#include"RB_Tree.hpp"

using std::initializer_list;

template<typename Ty,typename alloc = _default_allocator>
class set
{
	public:
		using self = set<Ty,alloc>;
		using compare = Unique_Compare;
	    using TypeValue = Ty;
		using iterator = RB_Tree_iterator<typename RB_Tree<Ty , Unique_Compare , alloc>::NodeType>;
		using const_iterator = const_RB_Tree_iterator<typename RB_Tree<Ty , Unique_Compare , alloc>::NodeType>;
		
	private:
		RB_Tree<Ty,Unique_Compare,alloc>* tree = nullptr;
		
		int elem_count = 0;

	public:
		set() noexcept
		{
			tree = new RB_Tree<Ty , Unique_Compare , alloc>();
		}

		set(const Ty& elem) noexcept
		{
			tree = new RB_Tree<Ty , Unique_Compare , alloc>(elem);
			elem_count++;
		}

		explicit set(const initializer_list<Ty>& list) noexcept
		{
			tree = new RB_Tree<Ty , Unique_Compare , alloc>();

			for (auto p : list)
			{
				insert(p);
			}
		}

		explicit set(const set<Ty , alloc>& obj) noexcept
		{
			tree = new RB_Tree<Ty , Unique_Compare , alloc>();

			typename RB_Tree<Ty , Unique_Compare , alloc>::const_iterator p = obj.tree->cbegin();
			for (; p != obj.tree->cend(); ++p)
			{
				tree->Insert((*p));
			}

			this->elem_count = obj.elem_count;
		}

		~set() noexcept
		{
			clear();

			delete tree;
			tree = nullptr;
		}


		//insert and erase operations

		[[noreturn]] void insert(const Ty& elem) noexcept
		{
			if (tree->Search(elem) == false)
			{
				tree->Insert(elem);
				elem_count++;
			}
		}

		[[noreturn]] void insert(const initializer_list<Ty>& obj) noexcept
		{
			for (auto p : obj)
			{
				insert(p);
			}
		}

		[[noreturn]] void erase(const Ty& elem) noexcept
		{
			if (tree->Search(elem))
			{
				tree->DeleteNode(elem);
				elem_count--;
			}
		}

		_NODISCARD iterator erase(iterator ptr) noexcept
		{
			elem_count--;
			return tree->erase(ptr);
		}

		_NODISCARD const_iterator erase(const_iterator& ptr) noexcept
		{
			elem_count--;
			return tree->erase(ptr);
		}

		[[noreturn]] void erase(iterator p_begin , iterator p_end) noexcept
		{
			int n = p_begin.step();
			for (; n < p_end.step(); ++n)
			{
				p_begin = erase(p_begin);
			}
		}

		[[noreturn]] void clear() noexcept
		{
			tree->Destory();
			elem_count = 0;
		}


		//other

		_NODISCARD bool empty() const noexcept
		{
			if (elem_count == 0)
				return true;

			return false;
		}

		_NODISCARD int size() const noexcept
		{
			return this->elem_count;
		}

		_NODISCARD bool find(const Ty& elem) const noexcept
		{
			return tree->Search(elem);
		}

		_NODISCARD compare key_comp() const noexcept
		{
			return compare;
		}

		[[noreturn]] void swap(set<Ty , alloc>& obj) noexcept
		{
			RB_Tree<Ty , Unique_Compare , alloc>* temp_tree = tree;
			RB_Tree<Ty , Unique_Compare , alloc>* obj_tree = obj.tree;

			tree = obj_tree;
			obj.tree = temp_tree;

			int temp_count = elem_count;
			elem_count = obj.elem_count;
			obj.elem_count = temp_count;
		}


		//RB_Tree iterator

		_NODISCARD iterator begin() noexcept
		{
			return tree->begin();
		}

		_NODISCARD iterator end() noexcept
		{
			return tree->end();
		}

		_NODISCARD iterator begin() const noexcept
		{
			return tree->begin();
		}

		_NODISCARD iterator end() const noexcept
		{
			return tree->end();
		}

		_NODISCARD const_iterator cbegin() const noexcept
		{
			return tree->cbegin();
		}

		_NODISCARD const_iterator cend() const noexcept
		{
			return tree->cend();
		}


		//operator overload

		self& operator=(const set<Ty , alloc>& obj) noexcept
		{
			clear();

			set<Ty , alloc>::const_iterator p = obj.cbegin();
			for (; p != obj.cend(); ++p)
			{
				insert((*p));
			}

			return *this;
		}

		_NODISCARD bool operator==(const set<Ty , alloc>& obj) const noexcept
		{
			if (elem_count != obj.elem_count)
				return false;

			set<Ty , alloc>::const_iterator p1 = obj.cbegin();
			set<Ty , alloc>::const_iterator p2 = cbegin();
			for (; p1 != obj.cend() , p2 != cend(); ++p1 , ++p2)
			{
				if ((*p1) != (*p2))
					return false;
			}

			return true;
		}

		_NODISCARD bool operator!=(const set<Ty , alloc>& obj) const noexcept
		{
			return !((*this) == obj);
		}

		_NODISCARD bool operator>(const set<Ty , alloc>& obj) const noexcept
		{
			if (elem_count > obj.elem_count)
				return true;

			return false;
		}

		_NODISCARD bool operator<(const set<Ty , alloc>& obj) const noexcept
		{
			if (elem_count < obj.elem_count)
				return true;

			return false;
		}

		_NODISCARD bool operator>=(const set<Ty , alloc>& obj) const noexcept
		{
			if (elem_count >= obj.elem_count)
				return true;

			return false;
		}

		_NODISCARD bool operator<=(const set<Ty , alloc>& obj) const noexcept
		{
			if (elem_count <= obj.elem_count)
				return true;

			return false;
		}
};