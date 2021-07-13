/* Unordered_Multimap implementation
 *
 * Copyright(c) 2021 Mashiro -1262159823@qq.com
 *
 * This File is part of CONTAINER LIBRARY project.
 *
 * version : 1.3.0-alpha
 *
 * author : Mashiro
 *
 * File name : Container_Unordered_Multimap.hpp -a kind of unordered container.
 *
 * This library is free software;you can redistribute is and/or modify it
 * under the APACHE LICENSE 2.0 as published by the Free Software Foundation.
 * ------------------------------------------------------------------------
 *
 *-------------------------------README------------------------------------
 *
 * template<typename key,typename value,typename alloc = _default_allocator>
 * class Unordered_Multimap
 * {
 *      //iterator : hash_table_iterator
 *      //const_iterator : const_hash_table_iterator
 *
 *      //compare : Equal_Compare
 *      //pair : pair<key,value>
 *
 *      //ctor
 *
 *      Unordered_Multimap(size_t size)--------------------initialize with size.
 *      Unordered_Multimap(const initializer_list<pair>& list)
 *      Unordered_Multimap(const Unordered_Multimap<key,value,alloc>& obj)
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
 *      void swap(self& obj)
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
 *      self& operator=(const self& obj)
 *      bool operator==(const coll& obj)
 *      bool operator!=(const coll& obj)
 *      bool operator>(const coll& obj)
 *      bool operator<(const coll& obj)
 *      bool operator>=(const coll& obj)
 *      bool operator<=(const coll& obj)
 * }
 * ----------------------------------------------------------------------------------------------
 */


#pragma once
#include<initializer_list>
#include"HashTable.hpp"
#include"memory_allocator.hpp"

using std::initializer_list;

template<typename key , typename value , typename alloc = _default_allocator>
class Unordered_Multimap
{
		using pair = pair<const key , value>;
		using hash_table = hash_table<pair , alloc,Equal_Compare , pair_hash<key , value>>;

	public:
		using self = Unordered_Multimap<key , value , alloc>;
		using TypeValue = pair;
		using compare = Equal_Compare;
		using iterator = hash_table_iterator<typename hash_table::NodeType* , hash_table>;
		using const_iterator = const_hash_table_iterator<typename hash_table::NodeType* , hash_table>;

	private:
		hash_table* ptr = nullptr;

	public:
		Unordered_Multimap() = delete;

		Unordered_Multimap(const size_t& size)
		{
			ptr = new hash_table(size);
		}

		explicit Unordered_Multimap(const initializer_list<pair>& list) noexcept
		{
			size_t size = list.size();
			ptr = new hash_table(size);

			for (auto p : list)
			{
				ptr->insert(p);
			}
		}

		explicit Unordered_Multimap(const Unordered_Multimap<key , value , alloc>& obj) noexcept
		{
			size_t size = obj.ptr->buckets_count();
			ptr = new hash_table(size);

			auto p = obj.cbegin();
			for (; p != obj.cend(); ++p)
			{
				ptr->insert((*p));
			}
		}

		~Unordered_Multimap() noexcept
		{
			ptr->~hash_table();
			delete ptr;
			ptr = nullptr;
		}



		//insert and erase operations

		[[noreturn]] void insert(const pair& obj) noexcept
		{
			ptr->insert(obj);
		}

		[[noreturn]] void insert(const key& k , const value& v) noexcept
		{
			ptr->insert(make_pair(k , v));
		}

		[[noreturn]] void erase(const pair& obj) noexcept
		{
			ptr->erase(obj);
		}

		[[noreturn]] void erase(const key& k) noexcept
		{
			ptr->erase(make_pair(k , 0));
		}

		_NODISCARD iterator erase(iterator p) noexcept
		{
			return ptr->erase(p);
		}

		_NODISCARD const_iterator erase(const_iterator p) noexcept
		{
			return ptr->erase(p);
		}

		[[noreturn]] void erase(iterator p_begin , iterator p_end) noexcept
		{
			ptr->erase(p_begin , p_end);
		}

		[[noreturn]] void clear() noexcept
		{
			ptr->clear();
		}


		//other

		_NODISCARD bool empty() const noexcept
		{
			return ptr->empty();
		}

		_NODISCARD int size() const noexcept
		{
			return ptr->size();
		}

		_NODISCARD size_t buckets_count() const noexcept
		{
			return ptr->buckets_count();
		}

		_NODISCARD int count(const pair& obj) const noexcept
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

		_NODISCARD int count(const key& k) const noexcept
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

		_NODISCARD bool find(const pair& obj) const noexcept
		{
			return ptr->find(obj);
		}

		_NODISCARD bool find(const key& k) const noexcept
		{
			return ptr->find(make_pair(k , 0));
		}

		_NODISCARD compare key_comp() const noexcept
		{
			return compare;
		}

		[[noreturn]] void swap(self& obj) noexcept
		{
			hash_table* temp_ptr = ptr;
			hash_table* obj_ptr = obj.ptr;

			ptr = obj_ptr;
			obj.ptr = temp_ptr;
		}


		//hash_table iterator

		_NODISCARD iterator begin() noexcept
		{
			return ptr->begin();
		}

		_NODISCARD iterator end() noexcept
		{
			return ptr->end();
		}

		_NODISCARD iterator begin() const noexcept
		{
			return ptr->begin();
		}

		_NODISCARD iterator end() const noexcept
		{
			return ptr->end();
		}

		_NODISCARD const_iterator cbegin() const noexcept
		{
			return ptr->cbegin();
		}

		_NODISCARD const_iterator cend() const noexcept
		{
			return ptr->cend();
		}


		//operator overload

		self& operator=(const self& obj) noexcept
		{
			clear();

			typename Unordered_Multimap<key,value , alloc>::const_iterator p = obj.cbegin();
			for (; p != obj.cend(); ++p)
			{
				insert(*p);
			}

			return *this;
		}

		template<typename coll>
		_NODISCARD bool operator==(const coll& obj) const noexcept
		{
			if (size() != obj.size() || buckets_count() != obj.buckets_count())
				return false;

			typename coll::const_iterator p1 = obj.cbegin();
			typename Unordered_Multimap<key,value , alloc>::const_iterator p2 = cbegin();
			for (; p1 != obj.cend() , p2 != cend(); ++p1 , ++p2)
			{
				if ((*p1) != (*p2))
					return false;
			}

			return true;
		}

		template<typename coll>
		_NODISCARD bool operator!=(const coll& obj) const noexcept
		{
			return !((*this) == obj);
		}

		template<typename coll>
		_NODISCARD bool operator>(const coll& obj) const noexcept
		{
			if (size() > obj.size())
				return true;

			return false;
		}

		template<typename coll>
		_NODISCARD bool operator<(const coll& obj) const noexcept
		{
			if (size() < obj.size())
				return true;

			return false;
		}

		template<typename coll>
		_NODISCARD bool operator>=(const coll& obj) const noexcept
		{
			if (size() >= obj.size())
				return true;

			return false;
		}

		template<typename coll>
		_NODISCARD bool operator<=(const coll& obj) const noexcept
		{
			if (size() <= obj.size())
				return true;

			return false;
		}
};