/* Unordered_Multiset implementation
 *
 * Copyright(c) 2021 Mashiro -1262159823@qq.com
 *
 * This File is part of CONTAINER LIBRARY project.
 *
 * version : 1.2.0-alpha
 *
 * author : Mashiro
 *
 * File name : Container_Unordered_Multiset.hpp -a kind of unordered container.
 *
 * This library is free software;you can redistribute is and/or modify it
 * under the APACHE LICENSE 2.0 as published by the Free Software Foundation.
 * ------------------------------------------------------------------------
 *
 *-------------------------------README------------------------------------
 *
 * template<typename Ty>
 * class Unordered_Multiset
 * {
 *      //iterator : hash_table_iterator
 *      //const_iterator : const_hash_table_iterator
 *
 *		//compare : Equal_Compare
 * 
 *      //ctor
 *
 *      Unordered_Multiset(size_t size)--------------------initialize with size.
 *      Unordered_Multiset(const initializer_list<Ty>& list)
 *      Unordered_Multiset(const Unordered_Multiset<Ty>& obj)
 *
 *      //operations
 *
 *      void insert(Ty elem)
 *      void erase(Ty elem)
 *      iterator erase(iterator p)
 *      const_iterator erase(const_iterator p)
 *      void erase(iterator p_begin,iterator p_end)
 *      void clear()
 *      bool empty()
 *      int size()
 *      size_t buckets_count()
 *      int count(Ty elem)
 *      bool find(Ty elem)
 *      compare key_comp()
 *      void swap(Unordered_Multiset<Ty>& obj)
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
 *      self& operator=(const Unordered_Multiset<Ty>& obj)
 *      bool operator==(const Unordered_Multiset<Ty>& obj)
 *      bool operator!=(const Unordered_Multiset<Ty>& obj)
 *      bool operator>(const Unordered_Multiset<Ty>& obj)
 *      bool operator<(const Unordered_Multiset<Ty>& obj)
 *      bool operator>=(const Unordered_Multiset<Ty>& obj)
 *      bool operator<=(const Unordered_Multiset<Ty>& obj)
 * }
 * ----------------------------------------------------------------------------------------------
 */


#pragma once
#include"HashTable.hpp"
#include<initializer_list>

using std::initializer_list;

template<typename Ty>
class Unordered_Multiset
{
	public:
		using self = Unordered_Multiset<Ty>;
		using TypeValue = Ty;
		using compare = Equal_Compare;
		using iterator = hash_table_iterator<typename hash_table<Ty, Equal_Compare>::NodeType* , hash_table<Ty, Equal_Compare>>;
		using const_iterator = const_hash_table_iterator<typename hash_table<Ty , Equal_Compare>::NodeType* , hash_table<Ty , Equal_Compare>>;

	private:
		hash_table<Ty,Equal_Compare>* ptr;

	public:
		Unordered_Multiset() = delete;

		Unordered_Multiset(size_t size)
		{
			ptr = new hash_table<Ty,Equal_Compare>(size);
		}

		explicit Unordered_Multiset(const initializer_list<Ty>& list)
		{
			size_t size = list.size();
			ptr = new hash_table<Ty, Equal_Compare>(size);

			for (auto p : list)
			{
				ptr->insert(p);
			}
		}

		explicit Unordered_Multiset(const Unordered_Multiset<Ty>& obj)
		{
			size_t size = obj.ptr->buckets_count();
			ptr = new hash_table<Ty,Equal_Compare>(size);

			auto p = obj.cbegin();
			for (; p != obj.cend(); ++p)
			{
				ptr->insert((*p));
			}
		}

		~Unordered_Multiset()
		{
			delete ptr;
			ptr = nullptr;
		}



		//insert and erase operations

		void insert(Ty elem)
		{
			ptr->insert(elem);
		}

		void erase(Ty elem)
		{
			ptr->erase(elem);
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
			return ptr->erase(p_begin,p_end);
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

		int count(Ty elem) const
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

		compare key_comp() const
		{
			return compare;
		}

		void swap(Unordered_Multiset<Ty>& obj)
		{
			hash_table<Ty , Equal_Compare>* temp_ptr = ptr;
			hash_table<Ty , Equal_Compare>* obj_ptr = obj.ptr;

			ptr = obj_ptr;
			obj.ptr = temp_ptr;
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

		self& operator=(const Unordered_Multiset<Ty>& obj)
		{
			clear();

			Unordered_Multiset<Ty>::const_iterator p = obj.cbegin();
			for (; p != obj.cend(); ++p)
			{
				insert(*p);
			}

			return *this;
		}

		bool operator==(const Unordered_Multiset<Ty>& obj) const
		{
			if (size() != obj.size() || buckets_count() != obj.buckets_count())
				return false;

			Unordered_Multiset<Ty>::const_iterator p1 = obj.cbegin();
			Unordered_Multiset<Ty>::const_iterator p2 = cbegin();
			for (; p1 != obj.cend() , p2 != cend(); ++p1 , ++p2)
			{
				if ((*p1) != (*p2))
					return false;
			}

			return true;
		}

		bool operator!=(const Unordered_Multiset<Ty>& obj) const
		{
			return !((*this) == obj);
		}

		bool operator>(const Unordered_Multiset<Ty>& obj) const
		{
			if (size() > obj.size())
				return true;

			return false;
		}

		bool operator<(const Unordered_Multiset<Ty>& obj) const
		{
			if (size() < obj.size())
				return true;

			return false;
		}

		bool operator>=(const Unordered_Multiset<Ty>& obj) const
		{
			if (size() >= obj.size())
				return true;

			return false;
		}

		bool operator<=(const Unordered_Multiset<Ty>& obj) const
		{
			if (size() <= obj.size())
				return true;

			return false;
		}
};