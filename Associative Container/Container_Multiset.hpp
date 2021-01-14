#pragma once
#include<initializer_list>
#include"RB_Tree.hpp"

using std::initializer_list;

template<typename Ty>
class Multiset
{
	public:
		using TypeValue = Ty;
		using RB_Tree = RB_Tree<Ty , Equal_Compare>;
		
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

		Multiset(initializer_list<Ty> list)
		{
			tree = new RB_Tree();

			for (auto p : list)
			{
				tree->Insert(p);
				elem_count++;
			}
		}

		~Multiset()
		{
			tree->Destory();

			delete tree;
			tree = nullptr;
		}

		void Insert(Ty elem)
		{
			tree->Insert(elem);

			elem_count++;
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

		void erase(Ty elem)
		{
			while (tree->Search(elem))
			{
				tree->DeleteNode(elem);
				elem_count--;
			}
		}

		void clear()
		{
			tree->Destory();
			elem_count = 0;
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