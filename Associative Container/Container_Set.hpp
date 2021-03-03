/* set implementation
 *
 * Copyright(c) 2021 Mashiro -1262159823@qq.com
 *
 * This File is part of CONTAINER LIBRARY project.
 *
 * version : 1.1.1-alpha
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

template<typename Ty>
class set
{
	public:
		using self = set<Ty>;
		using compare = Unique_Compare;
	    using TypeValue = Ty;
		using iterator = RB_Tree_iterator<typename RB_Tree<Ty , Unique_Compare>::NodeType>;
		using const_iterator = const_RB_Tree_iterator<typename RB_Tree<Ty , Unique_Compare>::NodeType>;
		
	private:
		RB_Tree<Ty,Unique_Compare>* tree = nullptr;
		
		int elem_count = 0;

	public:
		set()
		{
			tree = new RB_Tree<Ty , Unique_Compare>();
		}

		set(Ty elem)
		{
			tree = new RB_Tree<Ty , Unique_Compare>(elem);
			elem_count++;
		}

		set(const initializer_list<Ty>& list)
		{
			tree = new RB_Tree<Ty , Unique_Compare>();

			for (auto p : list)
			{
				insert(p);
			}
		}

		set(const set<Ty>& obj)
		{
			tree = new RB_Tree<Ty , Unique_Compare>();

			typename RB_Tree<Ty , Unique_Compare>::const_iterator p = obj.tree->cbegin();
			for (; p != obj.tree->cend(); ++p)
			{
				tree->Insert((*p));
			}

			this->elem_count = obj.elem_count;
		}

		~set()
		{
			clear();

			delete tree;
			tree = nullptr;
		}


		//insert and erase operations

		void insert(Ty elem)
		{
			if (tree->Search(elem) == false)
			{
				tree->Insert(elem);
				elem_count++;
			}
		}

		void insert(const initializer_list<Ty>& obj)
		{
			for (auto p : obj)
			{
				insert(p);
			}
		}

		void erase(Ty elem)
		{
			tree->DeleteNode(elem);
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

		bool find(Ty elem) const
		{
			return tree->Search(elem);
		}

		compare key_comp() const
		{
			return compare;
		}

		void swap(set<Ty>& obj)
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
			
			set<Ty>::const_iterator p = cbegin();
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

		self& operator=(const set<Ty>& obj)
		{
			clear();

			set<Ty>::const_iterator p = obj.cbegin();
			for (; p != obj.cend(); ++p)
			{
				insert((*p));
			}

			return *this;
		}

		bool operator==(const set<Ty>& obj)
		{
			if (elem_count != obj.elem_count)
				return false;

			set<Ty>::const_iterator p1 = obj.cbegin();
			set<Ty>::const_iterator p2 = cbegin();
			for (; p1 != obj.cend() , p2 != cend(); ++p1 , ++p2)
			{
				if ((*p1) != (*p2))
					return false;
			}

			return true;
		}

		bool operator!=(const set<Ty>& obj)
		{
			return !((*this) == obj);
		}

		bool operator>(const set<Ty>& obj)
		{
			if (elem_count > obj.elem_count)
				return true;

			return false;
		}

		bool operator<(const set<Ty>& obj)
		{
			if (elem_count < obj.elem_count)
				return true;

			return false;
		}

		bool operator>=(const set<Ty>& obj)
		{
			if (elem_count >= obj.elem_count)
				return true;

			return false;
		}

		bool operator<=(const set<Ty>& obj)
		{
			if (elem_count <= obj.elem_count)
				return true;

			return false;
		}
};