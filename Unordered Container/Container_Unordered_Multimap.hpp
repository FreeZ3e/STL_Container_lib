#pragma once
#include"HashTable.hpp"
#include<initializer_list>

using std::initializer_list;

template<typename key , typename value>
class Unordered_Multimap
{
		using pair = pair<key , value>;
		using hash_table = hash_table<pair , Equal_Compare , pair_hash<key , value>>;

	public:
		using TypeValue = pair;

	private:
		hash_table* ptr;

	public:
		Unordered_Multimap() = delete;

		explicit Unordered_Multimap(const size_t& size)
		{
			ptr = new hash_table(size);
		}

		Unordered_Multimap(const initializer_list<pair> list)
		{
			size_t size = list.size();
			ptr = new hash_table(size);

			for (auto p : list)
			{
				ptr->insert(p);
			}
		}

		~Unordered_Multimap()
		{
			delete ptr;
			ptr = nullptr;
		}

		void insert(const pair& obj)
		{
			ptr->insert(obj);
		}

		void insert(const key& k , const value& v)
		{
			ptr->insert(make_pair(k , v));
		}

		void erase(const pair& obj)
		{
			ptr->erase(obj);
		}

		void erase(const key& k)
		{
			ptr->erase(make_pair(k , 0));
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

		int count(const pair& obj)
		{
			int count = 0;

			for (auto p = ptr->begin(); p != ptr->end(); ++p)
			{
				if ((*p) == obj)
				{
					count++;
				}
			}

			return count;
		}

		int count(const key& k)
		{
			int count = 0;

			for (auto p = ptr->begin(); p != ptr->end(); ++p)
			{
				if ((*p) == make_pair(k , 0))
				{
					count++;
				}
			}

			return count;
		}

		bool find(const pair& obj)
		{
			return ptr->find(obj);
		}

		bool find(const key& k)
		{
			return ptr->find(make_pair(k , 0));
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