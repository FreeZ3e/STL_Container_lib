/* Multiset implementation
 *
 * Copyright(c) 2021 Mashiro -1262159823@qq.com
 *
 * This File is part of CONTAINER LIBRARY project.
 *
 * version : 1.3.0-alpha
 *
 * author : Mashiro
 *
 * File name : Container_Multiset.hpp -a kind of associative contiainer.
 *
 * This library is free software;you can redistribute is and/or modify it
 * under the APACHE LICENSE 2.0 as published by the Free Software Foundation.
 * ------------------------------------------------------------------------
 *
 *-------------------------------README------------------------------------
 *
 * template<typename Ty,typename alloc = _default_allocator>
 * class Multiset
 * {
 *      //iterator : RB_Tree_iterator
 *      //const_iterator : const_RB_Tree_iterator
 *
 *      //compare : Equal_Compare
 *
 *      //ctor
 *
 *      Multiset()------------------------------------initialize RB_Tree ptr.
 *      Multiset(Ty elem)-----------------------------insert elem.
 *      Multiset(const initializer_list<Ty>& list)
 *      Multiset(const Multiset<Ty,alloc>& obj)
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
 *      void swap(self& obj)
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
 *      self& operator=(const self& obj)
 *      bool operator==(const coll& obj)
 *      bool operator!=(const coll& obj)
 *      bool operator>(const coll& obj)
 *      bool operator<(const coll& obj)
 *      bool operator>=(const coll& obj)
 *      bool operator<=(const coll& obj)
 * }
 * ----------------------------------------------------------------------------------------------
 */


#pragma once
#include<initializer_list>
#include"RB_Tree.hpp"

using std::initializer_list;

template<typename Ty,typename alloc = _default_allocator>
class Multiset
{	
	public:
		using self = Multiset<Ty , alloc>;
		using compare = Equal_Compare;
		using TypeValue = Ty;
		using RB_Tree = RB_Tree<Ty , Equal_Compare , alloc>;
		using iterator = RB_Tree_iterator<typename RB_Tree::NodeType>;
		using const_iterator = const_RB_Tree_iterator<typename RB_Tree::NodeType>;
		
	private:
		RB_Tree* tree = nullptr;

		int elem_count = 0;

	public:
		Multiset() noexcept
		{
			tree = new RB_Tree();
		}

		Multiset(const Ty& elem) noexcept
		{
			tree = new RB_Tree(elem);
			elem_count++;
		}

		explicit Multiset(const initializer_list<Ty>& list) noexcept
		{
			tree = new RB_Tree();

			for (auto p : list)
			{
				tree->Insert(p);
				elem_count++;
			}
		}

		explicit Multiset(const Multiset<Ty , alloc>& obj) noexcept
		{
			tree = new RB_Tree();

			typename RB_Tree::const_iterator p = obj.tree->cbegin();
			for (; p != obj.tree->cend(); ++p)
			{
				tree->Insert((*p));
			}

			this->elem_count = obj.elem_count;
		}

		~Multiset() noexcept
		{
			tree->Destory();

			delete tree;
			tree = nullptr;
		}



		//insert and erase operations

		[[noreturn]] void insert(const Ty& elem) noexcept
		{
			tree->Insert(elem);

			elem_count++;
		}

		[[noreturn]] void insert(const initializer_list<Ty>& obj) noexcept
		{
			for (auto p : obj)
			{
				tree->Insert(p);
				elem_count++;
			}
		}

		[[noreturn]] void erase(const Ty& elem) noexcept
		{
			while (tree->Search(elem))
			{
				elem_count = elem_count - tree->count(elem);
				tree->DeleteNode(elem);
			}
		}

		_NODISCARD iterator erase(iterator ptr) noexcept
		{
			elem_count = elem_count - tree->count(*ptr);
			return tree->erase(ptr);
		}

		_NODISCARD const_iterator erase(const_iterator& ptr) noexcept
		{
			elem_count = elem_count - tree->count(*ptr);
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

		[[noreturn]] void swap(self& obj) noexcept
		{
			RB_Tree* temp_tree = tree;
			RB_Tree* obj_tree = obj.tree;

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

		self& operator=(const self& obj) noexcept
		{
			clear();

			typename Multiset<Ty , alloc>::const_iterator p = obj.cbegin();
			for (; p != obj.cend(); ++p)
			{
				insert((*p));
			}

			return *this;
		}

		template<typename coll>
		_NODISCARD bool operator==(const coll& obj) const noexcept
		{
			if (elem_count != obj.size())
				return false;

			typename coll::const_iterator p1 = obj.cbegin();
			typename Multiset<Ty , alloc>::const_iterator p2 = cbegin();
			for (; p1 != obj.cend() , p2 != cend(); ++p1 , ++p2)
			{
				if ((*p1) != (*p2))
					return false;
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
};