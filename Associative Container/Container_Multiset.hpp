/* Multiset implementation
 *
 * Copyright(c) 2021 Mashiro -1262159823@qq.com
 *
 * This File is part of CONTAINER LIBRARY project.
 *
 * version : 1.1.1-alpha
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
 * template<typename Ty>
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
 *      Multiset(const Multiset<Ty>& obj)
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
 *      void swap(Multiset<Ty>& obj)
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
 *      self& operator=(const Multiset<Ty>& obj)
 *      bool operator==(const Multiset<Ty>& obj)
 *      bool operator!=(const Multiset<Ty>& obj)
 *      bool operator>(const Multiset<Ty>& obj)
 *      bool operator<(const Multiset<Ty>& obj)
 *      bool operator>=(const Multiset<Ty>& obj)
 *      bool operator<=(const Multiset<Ty>& obj)
 * }
 * ----------------------------------------------------------------------------------------------
 */


#pragma once
#include<initializer_list>
#include<iostream>
#include"RB_Tree.hpp"

using std::cout;
using std::endl;
using std::initializer_list;

template<typename Ty>
class Multiset
{	
	public:
		using self = Multiset<Ty>;
		using compare = Equal_Compare;
		using TypeValue = Ty;
		using RB_Tree = RB_Tree<Ty , Equal_Compare>;
		using iterator = RB_Tree_iterator<typename RB_Tree::NodeType>;
		using const_iterator = const_RB_Tree_iterator<typename RB_Tree::NodeType>;
		
	private:
		RB_Tree* tree;

		int elem_count = 0;

	public:
		Multiset()
		{
			tree = new RB_Tree();
		}

		Multiset(Ty elem)
		{
			tree = new RB_Tree(elem);
			elem_count++;
		}

		Multiset(const initializer_list<Ty>& list)
		{
			tree = new RB_Tree();

			for (auto p : list)
			{
				tree->Insert(p);
				elem_count++;
			}
		}

		Multiset(const Multiset<Ty>& obj)
		{
			tree = new RB_Tree();

			typename RB_Tree::const_iterator p = obj.tree->cbegin();
			for (; p != obj.tree->cend(); ++p)
			{
				tree->Insert((*p));
			}

			this->elem_count = obj.elem_count;
		}

		~Multiset()
		{
			tree->Destory();

			delete tree;
			tree = nullptr;
		}



		//insert and erase operations

		void insert(Ty elem)
		{
			tree->Insert(elem);

			elem_count++;
		}

		void insert(const initializer_list<Ty>& obj)
		{
			for (auto p : obj)
			{
				tree->Insert(p);
				elem_count++;
			}
		}

		void erase(Ty elem)
		{
			while (tree->Search(elem))
			{
				tree->DeleteNode(elem);
				elem_count--;
			}
		}

		iterator erase(iterator ptr)
		{
			for (int n = 0; n < tree->count(*ptr); ++n)
				elem_count--;

			return tree->erase(ptr);
		}

		const_iterator erase(const_iterator& ptr)
		{
			for (int n = 0; n < tree->count(*ptr); ++n)
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

		bool find(Ty elem) const
		{
			return tree->Search(elem);
		}

		compare key_comp() const
		{
			return compare;
		}

		void swap(Multiset<Ty>& obj)
		{
			//keep obj tree
			Ty* arr = new Ty[obj.elem_count];

			int count = 0;
			for (auto p : obj)
			{
				arr[count] = p;
				count++;
			}

			//swap obj tree
			obj.clear();

			Multiset<Ty>::const_iterator p = cbegin();
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

		self& operator=(const Multiset<Ty>& obj)
		{
			clear();

			Multiset<Ty>::const_iterator p = obj.cbegin();
			for (; p != obj.cend(); ++p)
			{
				insert((*p));
			}

			return *this;
		}

		bool operator==(const Multiset<Ty>& obj)
		{
			if (elem_count != obj.elem_count)
				return false;

			Multiset<Ty>::const_iterator p1 = obj.cbegin();
			Multiset<Ty>::const_iterator p2 = cbegin();
			for (; p1 != obj.cend() , p2 != cend(); ++p1 , ++p2)
			{
				if ((*p1) != (*p2))
					return false;
			}

			return true;
		}

		bool operator!=(const Multiset<Ty>& obj)
		{
			return !((*this) == obj);
		}

		bool operator>(const Multiset<Ty>& obj)
		{
			if (elem_count > obj.elem_count)
				return true;

			return false;
		}

		bool operator<(const Multiset<Ty>& obj)
		{
			if (elem_count < obj.elem_count)
				return true;

			return false;
		}

		bool operator>=(const Multiset<Ty>& obj)
		{
			if (elem_count >= obj.elem_count)
				return true;

			return false;
		}

		bool operator<=(const Multiset<Ty>& obj)
		{
			if (elem_count <= obj.elem_count)
				return true;

			return false;
		}
};