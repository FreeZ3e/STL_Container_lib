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

		Multimap(const pair& obj)
		{
			tree = new RB_Tree(pair);

			elem_count++;
		}

		Multimap(const initializer_list<pair>& obj)
		{
			tree = new RB_Tree();

			for (auto p : obj)
			{
				tree->Insert(p);
				elem_count++;
			}
		}

		Multimap(const Multimap<key , value>& obj)
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



		void insert(const pair& obj)
		{
			tree->Insert(obj);

			elem_count++;
		}

		void insert(const key& k , const value& v)
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

		void erase(const key& k)
		{
			while(tree->Search(make_pair(k , 0)))
			{
				tree->DeleteNode(make_pair(k , 0));
				elem_count--;
			}
		}

		iterator erase(iterator ptr)
		{
			tree->DeleteNode((*ptr));
			elem_count--;

			return tree->begin();
		}

		const_iterator erase(const_iterator ptr)
		{
			tree->DeleteNode((*ptr));
			elem_count--;

			return tree->cbegin();
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

		bool find(const pair& elem)
		{
			return tree->Search(elem);
		}

		bool find(const key& k)
		{
			return tree->Search(make_pair(k , 0));
		}

		compare key_comp()
		{
			return compare;
		}

		void swap(Multimap<key , value>& obj)
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

			Multimap<key , value>::const_iterator p = cbegin();
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

		void operator=(const Multimap<key , value>& obj)
		{
			clear();

			Multimap<key , value>::const_iterator p = obj.cbegin();
			for (; p != obj.cend(); ++p)
			{
				insert((*p));
			}
		}

		bool operator==(const Multimap<key , value>& obj)
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

		bool operator!=(const Multimap<key , value>& obj)
		{
			return !((*this) == obj);
		}

		bool operator>(const Multimap<key , value>& obj)
		{
			if (elem_count > obj.elem_count)
				return true;

			return false;
		}

		bool operator<(const Multimap<key , value>& obj)
		{
			if (elem_count < obj.elem_count)
				return true;

			return false;
		}

		bool operator>=(const Multimap<key , value>& obj)
		{
			if (elem_count >= obj.elem_count)
				return true;

			return false;
		}

		bool operator<=(const Multimap<key , value>& obj)
		{
			if (elem_count <= obj.elem_count)
				return true;

			return false;
		}
};