#pragma once
#include"HashTable.hpp"
#include<initializer_list>

using std::initializer_list;

template<typename Ty>
class Unordered_Multiset
{
	public:
		using TypeValue = Ty;

	private:
		hash_table<Ty,Equal_Compare>* ptr;

	public:
		Unordered_Multiset() = delete;

		explicit Unordered_Multiset(const size_t& size)
		{
			ptr = new hash_table<Ty,Equal_Compare>(size);
		}

		Unordered_Multiset(const initializer_list<Ty>& list)
		{
			size_t size = list.size();
			ptr = new hash_table<Ty, Equal_Compare>(size);

			for (auto p : list)
			{
				ptr->insert(p);
			}
		}

		~Unordered_Multiset()
		{
			delete ptr;
			ptr = nullptr;
		}

		void insert(Ty elem)
		{
			ptr->insert(elem);
		}

		void erase(Ty elem)
		{
			ptr->erase(elem);
		}

		void clear()
		{
			ptr->clear();
		}

		bool empty()
		{
			return ptr->empty();
		}

		int size()
		{
			return ptr->size();
		}

		int buckets_count()
		{
			return ptr->buckets_count();
		}

		int count(Ty elem)
		{
			int count = 0;

			for (auto p = ptr->begin(); p != ptr->end(); ++p)
			{
				if ((*p) == elem)
				{
					count++;
				}
			}

			return count;
		}

		bool find(Ty elem)
		{
			return ptr->find(elem);
		}


		//hash_table iterator
		auto begin() ->decltype(ptr->begin())
		{
			return ptr->begin();
		}

		auto end() ->decltype(ptr->end())
		{
			return ptr->end();
		}
};