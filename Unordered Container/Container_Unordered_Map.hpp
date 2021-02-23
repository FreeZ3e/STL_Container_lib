/* Unordered_Map implementation
 *
 * Copyright(c) 2021 Mashiro -1262159823@qq.com
 *
 * This File is part of CONTAINER LIBRARY project.
 *
 * version : 1.1.1-alpha
 *
 * author : Mashiro
 *
 * File name : Container_Unordered_Map.hpp -a kind of unordered container.
 *
 * This library is free software;you can redistribute is and/or modify it
 * under the APACHE LICENSE 2.0 as published by the Free Software Foundation.
 * ------------------------------------------------------------------------
 *
 *-------------------------------README------------------------------------
 *
 * template<typename key,typename value>
 * class Unordered_Map
 * {
 *      //iterator : hash_table_iterator
 *      //const_iterator : const_hash_table_iterator
 *
 *      //compare : Unique_Compare
 *      //pair : pair<key,value>
 *
 *      //ctor
 *
 *      explicit Unordered_Map(size_t size)--------------------initialize with size.
 *      Unordered_Map(const initializer_list<pair>& list)
 *      Unordered_Map(const Unordered_Map<key,value>& obj)
 *
 *      //operations
 *
 *      void insert(const pair& obj)
 *      void insert(key k,value v)----------------------------insert by make_pair().
 *      void erase(const pair& obj)
 *      void erase(key k)-------------------------------------erase if node's key equal k.
 *      iterator erase(iterator p)
 *      const_iterator erase(const_iterator p)
 *      void erase(iterator p_begin,iterator p_end)
 *      void clear()
 *      bool empty()
 *      int size()
 *      size_t buckets_count()
 *      int count(const pair& obj)
 *      int count(key k)--------------------------------------return number of node with k.
 *      bool find(const pair& obj)
 *      bool find(key k)--------------------------------------if node with k exist,return true.
 *      compare key_comp()
 *      void swap(Unordered_Map<key,value>& obj)
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
 *      self& operator=(const Unordered_Map<key,value>& obj)
 *      bool operator==(const Unordered_Map<key,value>& obj)
 *      bool operator!=(const Unordered_Map<key,value>& obj)
 *      bool operator>(const Unordered_Map<key,value>& obj)
 *      bool operator<(const Unordered_Map<key,value>& obj)
 *      bool operator>=(const Unordered_Map<key,value>& obj)
 *      bool operator<=(const Unordered_Map<key,value>& obj)
 * }
 * ----------------------------------------------------------------------------------------------
 */


#pragma once
#include"HashTable.hpp"
#include<initializer_list>

using std::initializer_list;

template<typename key,typename value>
class Unordered_Map
{
	using pair = pair<key , value>;
	using hash_table = hash_table<pair , Unique_Compare , pair_hash<key , value>>;

	public:
		using self = Unordered_Map<key , value>;
		using TypeValue = pair;
		using compare = Unique_Compare;
		using iterator = hash_table_iterator<typename hash_table::NodeType* , hash_table>;
		using const_iterator = const_hash_table_iterator<typename hash_table::NodeType* , hash_table>;

	private:
		hash_table* ptr;

	public:
		Unordered_Map() = delete;

		explicit Unordered_Map(size_t size)
		{
			ptr = new hash_table(size);
		}

		Unordered_Map(const initializer_list<pair>& list)
		{
			size_t size = list.size();
			ptr = new hash_table(size);

			for (auto p : list)
			{
				ptr->insert(p);
			}
		}

		Unordered_Map(const Unordered_Map<key , value>& obj)
		{
			size_t size = obj.ptr->buckets_count();
			ptr = new hash_table(size);

			auto p = obj.cbegin();
			for (; p != obj.cend(); ++p)
			{
				ptr->insert((*p));
			}
		}

		~Unordered_Map()
		{
			delete ptr;
			ptr = nullptr;
		}



		//insert and erase operations

		void insert(const pair& obj)
		{
			ptr->insert(obj);
		}

		void insert(key k , value v)
		{
			ptr->insert(make_pair(k , v));
		}

		void erase(const pair& obj)
		{
			ptr->erase(obj);
		}

		void erase(key k)
		{
			ptr->erase(make_pair(k , 0));
		}

		iterator erase(iterator p)
		{
			return ptr->erase(p);
		}

		const_iterator erase(const_iterator p)
		{
			return ptr->erase(p);
		}

		void erase(iterator p_begin , iterator p_end)
		{
			ptr->erase(p_begin,p_end);
		}

		void clear()
		{
			ptr->clear();
		}


		//other

		bool empty() const
		{
			return ptr->empty();
		}

		int size() const
		{
			return ptr->size();
		}

		size_t buckets_count() const
		{
			return ptr->buckets_count();
		}

		int count(const pair& obj) const
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

		int count(key k) const
		{
			int count = 0;

			for (auto p = ptr->begin(); p != ptr->end(); ++p)
			{
				if ((*p) == make_pair(k,0))
				{
					count++;
				}
			}

			return count;
		}

		bool find(const pair& obj) const
		{
			return ptr->find(obj);
		}

		bool find(key k) const
		{
			return ptr->find(make_pair(k , 0));
		}

		compare key_comp() const
		{
			return compare;
		}

		void swap(Unordered_Map<key , value>& obj)
		{
			hash_table* temp = new hash_table(obj.buckets_count());

			for (auto p : obj)
			{
				temp->insert(p);
			}

			//swap obj data
			obj.clear();

			for (auto p = begin(); p != end(); ++p)
			{
				obj.insert((*p));
			}

			//swap this data;
			this->clear();

			for (auto p = temp->begin(); p != temp->end(); ++p)
			{
				this->insert(*p);
			}
		}


		//hash_table iterator

		iterator begin()
		{
			return ptr->begin();
		}

		iterator end()
		{
			return ptr->end();
		}

		const_iterator cbegin() const
		{
			return ptr->cbegin();
		}

		const_iterator cend() const
		{
			return ptr->cend();
		}


		//operator overload

		self& operator=(const Unordered_Map<key,value>& obj)
		{
			clear();

			Unordered_Map<key,value>::const_iterator p = obj.cbegin();
			for (; p != obj.cend(); ++p)
			{
				insert(*p);
			}

			return *this;
		}

		bool operator==(const Unordered_Map<key,value>& obj)
		{
			if (size() != obj.size() || buckets_count() != obj.buckets_count())
				return false;

			Unordered_Map<key,value>::const_iterator p1 = obj.cbegin();
			Unordered_Map<key,value>::const_iterator p2 = cbegin();
			for (; p1 != obj.cend() , p2 != cend(); ++p1 , ++p2)
			{
				if ((*p1) != (*p2))
					return false;
			}

			return true;
		}

		bool operator!=(const Unordered_Map<key,value>& obj)
		{
			return !((*this) == obj);
		}

		bool operator>(const Unordered_Map<key,value>& obj)
		{
			if (size() > obj.size())
				return true;

			return false;
		}

		bool operator<(const Unordered_Map<key,value>& obj)
		{
			if (size() < obj.size())
				return true;

			return false;
		}

		bool operator>=(const Unordered_Map<key,value>& obj)
		{
			if (size() >= obj.size())
				return true;

			return false;
		}

		bool operator<=(const Unordered_Map<key,value>& obj)
		{
			if (size() <= obj.size())
				return true;

			return false;
		}
};