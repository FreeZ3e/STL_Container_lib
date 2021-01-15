#pragma once
#include"RB_Tree.hpp"
#include"Pair.hpp"
#include<initializer_list>

using std::initializer_list;

template<typename key,typename value>
class map
{
	using pair = pair<key , value>;
	using RB_Tree = RB_Tree<pair>;

	public:
		using TypeValue = pair;

	private:
		RB_Tree* tree;

		int elem_count = 0;

	public:
		map()
		{
			tree = new RB_Tree();
		}
		
		map(const pair obj)
		{
			tree = new RB_Tree(pair);

			elem_count++;
		}

		map(const initializer_list<pair> obj)
		{
			tree = new RB_Tree();

			for (auto p : obj)
			{
				tree->Insert(p);
				elem_count++;
			}
		}
		
		~map()
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

		void erase(const pair& obj)
		{
			tree->DeleteNode(obj);
			elem_count--;
		}

		void erase(const key& k)
		{
			tree->DeleteNode(make_pair(k , 0));
			elem_count--;
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

		//RB_Tree iterator
		auto begin() ->decltype(tree->begin())
		{
			return tree->begin();
		}

		auto end() ->decltype(tree->end())
		{
			return tree->end();
		}
};