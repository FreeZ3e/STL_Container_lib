/* Unordered_Set implementation
 *
 * Copyright(c) 2021 Mashiro -1262159823@qq.com
 *
 * This File is part of CONTAINER LIBRARY project.
 *
 * version : 1.2.0-alpha
 *
 * author : Mashiro
 *
 * File name : Container_Unordered_Set.hpp -a kind of unordered container.
 *
 * This library is free software;you can redistribute is and/or modify it
 * under the APACHE LICENSE 2.0 as published by the Free Software Foundation.
 * ------------------------------------------------------------------------
 *
 *-------------------------------README------------------------------------
 *
 * template<typename Ty>
 * class Unordered_Set
 * {
 *      //iterator : hash_table_iterator
 *      //const_iterator : const_hash_table_iterator
 * 
 *		//compare : Unique_Compare
 *
 *      //ctor
 *
 *      Unordered_Set(size_t size)--------------------initialize with size.
 *      Unordered_Set(const initializer_list<Ty>& list)
 *      Unordered_Set(const Unordered_Set<Ty>& obj)
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
 *      void swap(Unordered_Set<Ty>& obj)
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
 *      self& operator=(const Unordered_Set<Ty>& obj)
 *      bool operator==(const Unordered_Set<Ty>& obj)
 *      bool operator!=(const Unordered_Set<Ty>& obj)
 *      bool operator>(const Unordered_Set<Ty>& obj)
 *      bool operator<(const Unordered_Set<Ty>& obj)
 *      bool operator>=(const Unordered_Set<Ty>& obj)
 *      bool operator<=(const Unordered_Set<Ty>& obj)
 * }
 * ----------------------------------------------------------------------------------------------
 */


#pragma once
#include"HashTable.hpp"
#include<initializer_list>

using std::initializer_list;

template<typename Ty>
class Unordered_Set
{
	public:
		using self = Unordered_Set<Ty>;
		using TypeValue = Ty;
		using compare = Unique_Compare;
		using iterator = hash_table_iterator<typename hash_table<Ty>::NodeType* , hash_table<Ty>>;
		using const_iterator = const_hash_table_iterator<typename hash_table<Ty>::NodeType* , hash_table<Ty>>;

	private:
		hash_table<Ty>* ptr;

	public:
		Unordered_Set() = delete;

		Unordered_Set(size_t size)
		{
			ptr = new hash_table<Ty>(size);
		}

		explicit Unordered_Set(const initializer_list<Ty>& list)
		{
			size_t size = list.size();
			ptr = new hash_table<Ty>(size);

			for (auto p : list)
			{
				ptr->insert(p);
			}
		}

		explicit Unordered_Set(const Unordered_Set<Ty>& obj)
		{
			size_t size = obj.ptr->buckets_count();
			ptr = new hash_table<Ty>(size);

			auto p = obj.cbegin();
			for (; p != obj.cend(); ++p)
			{
				ptr->insert((*p));
			}
		}

		~Unordered_Set()
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
			ptr->erase(p_begin , p_end);
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

		bool find(Ty elem) const
		{
			return ptr->find(elem);
		}

		compare key_comp() const
		{
			return compare;
		}

		void swap(Unordered_Set<Ty>& obj)
		{
			hash_table<Ty>* temp_ptr = ptr;
			hash_table<Ty>* obj_ptr = obj.ptr;

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

		self& operator=(const Unordered_Set<Ty>& obj)
		{
			clear();

			Unordered_Set<Ty>::const_iterator p = obj.cbegin();
			for (; p != obj.cend(); ++p)
			{
				insert(*p);
			}

			return *this;
		}

		bool operator==(const Unordered_Set<Ty>& obj) const
		{
			if (size() != obj.size() || buckets_count() != obj.buckets_count())
				return false;

			Unordered_Set<Ty>::const_iterator p1 = obj.cbegin();
			Unordered_Set<Ty>::const_iterator p2 = cbegin();
			for (; p1 != obj.cend(),p2 != cend(); ++p1,++p2)
			{
				if ((*p1) != (*p2))
					return false;
			}

			return true;
		}

		bool operator!=(const Unordered_Set<Ty>& obj) const
		{
			return !((*this) == obj);
		}

		bool operator>(const Unordered_Set<Ty>& obj) const
		{
			if (size() > obj.size())
				return true;

			return false;
		}

		bool operator<(const Unordered_Set<Ty>& obj) const
		{
			if (size() < obj.size())
				return true;

			return false;
		}

		bool operator>=(const Unordered_Set<Ty>& obj) const
		{
			if (size() >= obj.size())
				return true;

			return false;
		}

		bool operator<=(const Unordered_Set<Ty>& obj) const
		{
			if (size() <= obj.size())
				return true;

			return false;
		}
};