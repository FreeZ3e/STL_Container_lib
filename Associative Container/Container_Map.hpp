/* map implementation
 *
 * Copyright(c) 2021 Mashiro -1262159823@qq.com
 *
 * This File is part of CONTAINER LIBRARY project.
 *
 * version : 1.0.0
 *
 * author : Mashiro
 *
 * File name : Container_Map.hpp -a kind of associative contiainer.
 *
 * This library is free software;you can redistribute is and/or modify it
 * under the APACHE LICENSE 2.0 as published by the Free Software Foundation.
 * ------------------------------------------------------------------------
 *
 *-------------------------------README------------------------------------
 *
 * template<typename key,typename value,typename alloc = _default_allocator>
 * class map
 * {
 *      //iterator : RB_Tree_iterator
 *      //const_iterator : const_RB_Tree_iterator
 *
 *      //compare : Unique_Compare
 *		//pair : pair<key,value>
 *
 *      //ctor
 *
 *      map()--------------------------------------------initialize RB_Tree ptr.
 *      map(const pair& obj)-----------------------------insert obj.
 *      map(const initializer_list<pair>& list)
 *      map(const map<key,value,alloc>& obj)
 *
 *      //operations
 *
 *      void insert(const pair& obj)
 *      void insert(key k,value v)-----------------------using make_pair() to insert k & v.
 *      void insert(const initializer_list<pair>& obj)
 *      void erase(key k)
 *      iterator erase(iterator ptr)
 *      const_iterator erase(const_iterator& ptr)
 *      void erase(iterator p_begin,iterator p_end)
 *      void clear()
 *      bool empty()
 *      int size()
 *      bool find(const pair& obj)
 *      bool find(key k)
 *      compare key_comp()---------------------------------return compare function.
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
#include"RB_Tree.hpp"
#include"Pair.hpp"
#include<initializer_list>

using std::initializer_list;

template<typename key,typename value,typename alloc = _default_allocator>
class map
{
	using pair = pair<const key , value>;
	using RB_Tree = RB_Tree<pair,Unique_Compare,alloc>;

	public:
		using self = map<key , value , alloc>;
		using compare = Unique_Compare;
		using TypeValue = pair;
		using iterator = RB_Tree_iterator<typename RB_Tree::NodeType>;
		using const_iterator = const_RB_Tree_iterator<typename RB_Tree::NodeType>;

	private:
		RB_Tree* tree = nullptr;

		int elem_count = 0;

	public:
		map() noexcept
		{
			tree = new RB_Tree();
		}
		
		explicit map(const pair& obj) noexcept
		{
			tree = new RB_Tree(pair);

			elem_count++;
		}

		explicit map(const initializer_list<pair>& obj) noexcept
		{
			tree = new RB_Tree();

			for (auto p : obj)
			{
				insert(p);
			}
		}
		
		map(const map<key , value , alloc>& obj) noexcept
		{
			tree = new RB_Tree();

			typename RB_Tree::const_iterator p = obj.tree->cbegin();
			for (; p != obj.tree->cend(); ++p)
			{
				tree->Insert((*p));
			}

			this->elem_count = obj.elem_count;
		}

		~map() noexcept
		{
			delete tree;
			tree = nullptr;
		}



		//insert and erase operations

		[[noreturn]] void insert(const pair& obj) noexcept
		{
			if (tree->Search(obj) == false)
			{
				tree->Insert(obj);
				elem_count++;
			}
		}

		[[noreturn]] void insert(const key& k , const value& v) noexcept
		{
			insert(make_pair(k , v));
		}

		[[noreturn]] void insert(const initializer_list<pair>& obj) noexcept
		{
			for (auto p : obj)
			{
				insert(p);
			}
		}

		[[noreturn]] void erase(const pair& obj) noexcept
		{
			if (tree->Search(obj))
			{
				tree->DeleteNode(obj);
				elem_count--;
			}
		}

		[[noreturn]] void erase(const key& k) noexcept
		{
			if (tree->Search(make_pair(k , 0)))
			{
				tree->DeleteNode(make_pair(k , 0));
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

		_NODISCARD bool find(const pair& elem) const noexcept
		{
			return tree->Search(elem);
		}

		_NODISCARD bool find(const key& k) const noexcept
		{
			return tree->Search(make_pair(k , 0));
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

			typename map<key , value , alloc>::const_iterator p = obj.cbegin();
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
			typename map<key , value , alloc>::const_iterator p2 = cbegin();
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