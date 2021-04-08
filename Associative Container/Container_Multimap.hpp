/* Multimap implementation
 *
 * Copyright(c) 2021 Mashiro -1262159823@qq.com
 *
 * This File is part of CONTAINER LIBRARY project.
 *
 * version : 1.2.0-alpha
 *
 * author : Mashiro
 *
 * File name : Container_Multimap.hpp -a kind of associative contiainer.
 *
 * This library is free software;you can redistribute is and/or modify it
 * under the APACHE LICENSE 2.0 as published by the Free Software Foundation.
 * ------------------------------------------------------------------------
 *
 *-------------------------------README------------------------------------
 *
 * template<typename key,typename value>
 * class Multimap
 * {
 *      //iterator : RB_Tree_iterator
 *      //const_iterator : const_RB_Tree_iterator
 *
 *      //compare : Equal_Compare
 *      //pair : pair<key,value>
 *
 *      //ctor
 *
 *      Multimap()--------------------------------------------initialize RB_Tree ptr.
 *      Multimap(const pair& obj)-----------------------------insert obj.
 *      Multimap(const initializer_list<pair>& list)
 *      Multimap(const Multimap<key,value>& obj)
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
 *      void swap(Multimap<key , value>& obj)
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
 *      self& operator=(const Multimap<key , value>& obj)
 *      bool operator==(const Multimap<key , value>& obj)
 *      bool operator!=(const Multimap<key , value>& obj)
 *      bool operator>(const Multimap<key , value>& obj)
 *      bool operator<(const Multimap<key , value>& obj)
 *      bool operator>=(const Multimap<key , value>& obj)
 *      bool operator<=(const Multimap<key , value>& obj)
 * }
 * ----------------------------------------------------------------------------------------------
 */


#pragma once
#include"RB_Tree.hpp"
#include"Pair.hpp"
#include<initializer_list>

using std::initializer_list;

template<typename key , typename value>
class Multimap
{	
	using pair = pair<key , value>;
	using RB_Tree = RB_Tree<pair,Equal_Compare>;

	public:
		using self = Multimap<key , value>;
		using compare = Equal_Compare;
		using TypeValue = pair;
		using iterator = RB_Tree_iterator<typename RB_Tree::NodeType>;
		using const_iterator = const_RB_Tree_iterator<typename RB_Tree::NodeType>;

	private:
		RB_Tree* tree;

		int elem_count = 0;

	public:
		Multimap()
		{
			tree = new RB_Tree();
		}

		explicit Multimap(const pair& obj)
		{
			tree = new RB_Tree(pair);

			elem_count++;
		}

		explicit Multimap(const initializer_list<pair>& obj)
		{
			tree = new RB_Tree();

			for (auto p : obj)
			{
				tree->Insert(p);
				elem_count++;
			}
		}

		explicit Multimap(const Multimap<key , value>& obj)
		{
			tree = new RB_Tree();

			typename RB_Tree::const_iterator p = obj.tree->cbegin();
			for (; p != obj.tree->cend(); ++p)
			{
				tree->Insert((*p));
			}

			this->elem_count = obj.elem_count;
		}

		~Multimap()
		{
			tree->Destory();

			delete tree;
			tree = nullptr;
		}



		//insert and erase operations

		void insert(const pair& obj)
		{
			tree->Insert(obj);

			elem_count++;
		}

		void insert(key k , value v)
		{
			tree->Insert(make_pair(k , v));
			elem_count++;
		}

		void insert(const initializer_list<pair>& obj)
		{
			for (auto p : obj)
			{
				tree->Insert(p);
				elem_count++;
			}
		}

		void erase(const pair& obj)
		{
			tree->DeleteNode(obj);
			elem_count--;
		}

		void erase(key k)
		{
			while(tree->Search(make_pair(k , 0)))
			{
				tree->DeleteNode(make_pair(k , 0));
				elem_count--;
			}
		}

		iterator erase(iterator ptr)
		{
			elem_count--;
			return tree->erase(ptr);
		}

		const_iterator erase(const_iterator& ptr)
		{
			elem_count--;
			return tree->erase(ptr);
		}

		void erase(iterator p_begin , iterator p_end)
		{
			int n = p_begin.step();
			for (; n < p_end.step(); ++n)
			{
				p_begin = erase(p_begin);
			}
		}

		void clear()
		{
			tree->Destory();
			elem_count = 0;
		}


		//other

		bool empty() const
		{
			if (elem_count == 0)
				return true;

			return false;
		}

		int size() const
		{
			return this->elem_count;
		}

		bool find(const pair& elem) const
		{
			return tree->Search(elem);
		}

		bool find(key k) const
		{
			return tree->Search(make_pair(k , 0));
		}

		compare key_comp() const
		{
			return compare;
		}

		void swap(Multimap<key , value>& obj)
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
		iterator begin()
		{
			return tree->begin();
		}

		iterator end()
		{
			return tree->end();
		}

		const_iterator cbegin() const
		{
			return tree->cbegin();
		}

		const_iterator cend() const
		{
			return tree->cend();
		}


		//operator overload

		self& operator=(const Multimap<key , value>& obj)
		{
			clear();

			Multimap<key , value>::const_iterator p = obj.cbegin();
			for (; p != obj.cend(); ++p)
			{
				insert((*p));
			}

			return *this;
		}

		bool operator==(const Multimap<key , value>& obj) const
		{
			if (elem_count != obj.elem_count)
				return false;

			Multimap<key , value>::const_iterator p1 = obj.cbegin();
			Multimap<key , value>::const_iterator p2 = cbegin();
			for (; p1 != obj.cend() , p2 != cend(); ++p1 , ++p2)
			{
				if ((*p1) != (*p2))
					return false;
			}

			return true;
		}

		bool operator!=(const Multimap<key , value>& obj) const
		{
			return !((*this) == obj);
		}

		bool operator>(const Multimap<key , value>& obj) const
		{
			if (elem_count > obj.elem_count)
				return true;

			return false;
		}

		bool operator<(const Multimap<key , value>& obj) const
		{
			if (elem_count < obj.elem_count)
				return true;

			return false;
		}

		bool operator>=(const Multimap<key , value>& obj) const
		{
			if (elem_count >= obj.elem_count)
				return true;

			return false;
		}

		bool operator<=(const Multimap<key , value>& obj) const
		{
			if (elem_count <= obj.elem_count)
				return true;

			return false;
		}
};