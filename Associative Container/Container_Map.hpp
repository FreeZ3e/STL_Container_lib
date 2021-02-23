/* map implementation
 *
 * Copyright(c) 2021 Mashiro -1262159823@qq.com
 *
 * This File is part of CONTAINER LIBRARY project.
 *
 * version : 1.1.1-alpha
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
 * template<typename key,typename value>
 * class map
 * {
 *      //operator : RB_Tree_iterator
 *      //const_operator : const_RB_Tree_iterator
 *
 *      //compare : Unique_Compare
 *		//pair : pair<key,value>
 *
 *      //ctor
 *
 *      map()--------------------------------------------initialize RB_Tree ptr.
 *      map(const pair& obj)-----------------------------insert obj.
 *      map(const initializer_list<pair>& list)
 *      map(const map<key,value>& obj)
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
 *      void swap(map<key , value>& obj)
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
 *      self& operator=(const map<key , value>& obj)
 *      bool operator==(const map<key , value>& obj)
 *      bool operator!=(const map<key , value>& obj)
 *      bool operator>(const map<key , value>& obj)
 *      bool operator<(const map<key , value>& obj)
 *      bool operator>=(const map<key , value>& obj)
 *      bool operator<=(const map<key , value>& obj)
 * }
 * ----------------------------------------------------------------------------------------------
 */


#pragma once
#include"RB_Tree.hpp"
#include"Pair.hpp"
#include<initializer_list>

using std::initializer_list;

template<typename key,typename value>
class map
{
	using pair = pair<key , value>;
	using RB_Tree = RB_Tree<pair,Unique_Compare>;

	public:
		using self = map<key , value>;
		using compare = Unique_Compare;
		using TypeValue = pair;
		using iterator = RB_Tree_iterator<typename RB_Tree::NodeType>;
		using const_iterator = const_RB_Tree_iterator<typename RB_Tree::NodeType>;

	private:
		RB_Tree* tree;

		int elem_count = 0;

	public:
		map()
		{
			tree = new RB_Tree();
		}
		
		map(const pair& obj)
		{
			tree = new RB_Tree(pair);

			elem_count++;
		}

		map(const initializer_list<pair>& obj)
		{
			tree = new RB_Tree();

			for (auto p : obj)
			{
				insert(p);
			}
		}
		
		map(const map<key , value>& obj)
		{
			tree = new RB_Tree();

			typename RB_Tree::const_iterator p = obj.tree->cbegin();
			for (; p != obj.tree->cend(); ++p)
			{
				tree->Insert((*p));
			}

			this->elem_count = obj.elem_count;
		}

		~map()
		{
			tree->Destory();

			delete tree;
			tree = nullptr;
		}



		//insert and erase operations

		void insert(const pair& obj)
		{
			if (tree->Search(obj) == false)
			{
				tree->Insert(obj);
				elem_count++;
			}
		}

		void insert(key k , value v)
		{
			insert(make_pair(k , v));
		}

		void insert(const initializer_list<pair>& obj)
		{
			for (auto p : obj)
			{
				insert(p);
			}
		}

		void erase(const pair& obj)
		{
			tree->DeleteNode(obj);
			elem_count--;
		}

		void erase(key k)
		{
			tree->DeleteNode(make_pair(k , 0));
			elem_count--;
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

		void swap(map<key , value>& obj)
		{
			//keep obj tree
			pair* arr = new pair[obj.elem_count];

			int count = 0;
			for (auto p : obj)
			{
				arr[count] = p;
				count++;
			}

			//swap obj tree
			obj.clear();

			map<key,value>::const_iterator p = cbegin();
			for (; p != cend(); ++p)
			{
				obj.insert((*p));
			}

			//swap this tree
			this->clear();

			for (int n = 0; n < count; ++n)
			{
				insert(arr[n]);
			}

			delete[] arr;
			arr = nullptr;
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

		self& operator=(const map<key , value>& obj)
		{
			clear();

			map<key , value>::const_iterator p = obj.cbegin();
			for (; p != obj.cend(); ++p)
			{
				insert((*p));
			}

			return *this;
		}

		bool operator==(const map<key , value>& obj)
		{
			if (elem_count != obj.elem_count)
				return false;

			map<key , value>::const_iterator p1 = obj.cbegin();
			map<key , value>::const_iterator p2 = cbegin();
			for (; p1 != obj.cend() , p2 != cend(); ++p1 , ++p2)
			{
				if ((*p1) != (*p2))
					return false;
			}

			return true;
		}

		bool operator!=(const map<key,value>& obj)
		{
			return !((*this) == obj);
		}

		bool operator>(const map<key , value>& obj)
		{
			if (elem_count > obj.elem_count)
				return true;

			return false;
		}

		bool operator<(const map<key , value>& obj)
		{
			if (elem_count < obj.elem_count)
				return true;

			return false;
		}

		bool operator>=(const map<key , value>& obj)
		{
			if (elem_count >= obj.elem_count)
				return true;

			return false;
		}

		bool operator<=(const map<key , value>& obj)
		{
			if (elem_count <= obj.elem_count)
				return true;

			return false;
		}
};