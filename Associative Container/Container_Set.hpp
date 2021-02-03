#pragma once
#include<initializer_list>
#include"RB_Tree.hpp"

using std::initializer_list;

template<typename Ty>
class set
{
	public:
		using compare = Unique_Compare;
	    using TypeValue = Ty;
		using iterator = RB_Tree_iterator<typename RB_Tree<Ty>::NodeType>;
		using const_iterator = const_RB_Tree_iterator<typename RB_Tree<Ty>::NodeType>;
		
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

		set(const initializer_list<Ty>& list)
		{
			tree = new RB_Tree<Ty>();

			for (auto p : list)
			{
				tree->Insert(p);
				elem_count++;
			}
		}

		set(const set<Ty>& obj)
		{
			tree = new RB_Tree<Ty>();

			typename RB_Tree<Ty>::const_iterator p = obj.tree->cbegin();
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
			tree->DeleteNode(elem);
			elem_count--;
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

		bool find(Ty elem)
		{
			return tree->Search(elem);
		}

		compare key_comp()
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

		void operator=(const set<Ty>& obj)
		{
			clear();

			set<Ty>::const_iterator p = obj.cbegin();
			for (; p != obj.cend(); ++p)
			{
				insert((*p));
			}
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