#pragma once
#include<initializer_list>
#include"RB_Tree.hpp"

using std::initializer_list;

template<typename Ty>
class set
{
	public:
	    using TypeValue = Ty;
	private:
		RB_Tree<Ty>* tree;
		
		int elem_count = 0;

	public:
		set()
		{
			tree = new RB_Tree<Ty>();
		}

		set(Ty elem)
		{
			tree = new RB_Tree<Ty>(elem);
			elem_count++;
		}

		set(initializer_list<Ty> list)
		{
			tree = new RB_Tree<Ty>();

			for (auto &p : list)
			{
				tree->Insert(p);
				elem_count++;
			}
		}

		~set()
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
			tree->DeleteNode(elem);
			elem_count--;
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