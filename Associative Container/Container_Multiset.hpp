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

		bool empty()
		{
			if (elem_count == 0)
				return true;

			return false;
		}

		int size()
		{
			return this->elem_count;
		}

		bool find(Ty elem)
		{
			return tree->Search(elem);
		}

		compare key_comp()
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

		void operator=(const Multiset<Ty>& obj)
		{
			clear();

			Multiset<Ty>::const_iterator p = obj.cbegin();
			for (; p != obj.cend(); ++p)
			{
				insert((*p));
			}
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