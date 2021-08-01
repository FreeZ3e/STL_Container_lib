/* Unordered_Multiset implementation
 *
 * Copyright(c) 2021 Mashiro -1262159823@qq.com
 *
 * This File is part of CONTAINER LIBRARY project.
 *
 * version : 1.0.0
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
 * template<typename Ty,typename alloc = _default_allocator>
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
 *      Unordered_Multiset(const Unordered_Multiset<Ty,alloc>& obj)
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

template<typename Ty , typename alloc = _default_allocator>
class Unordered_Multiset
{
	public:
		using self = Unordered_Multiset<Ty , alloc>;
		using TypeValue = Ty;
		using compare = Equal_Compare;
		using iterator = hash_table_iterator<typename hash_table<Ty, alloc,Equal_Compare>::NodeType* , hash_table<Ty, alloc,Equal_Compare>>;
		using const_iterator = const_hash_table_iterator<typename hash_table<Ty , alloc,Equal_Compare>::NodeType* , hash_table<Ty , alloc,Equal_Compare>>;

	private:
		hash_table<Ty, alloc,Equal_Compare>* ptr = nullptr;

	public:
		Unordered_Multiset() = delete;

		explicit Unordered_Multiset(const size_t& size)
		{
			ptr = new hash_table<Ty, alloc , Equal_Compare>(size);
		}

		explicit Unordered_Multiset(const initializer_list<Ty>& list) noexcept
		{
			size_t size = list.size();
			ptr = new hash_table<Ty, alloc , Equal_Compare>(size);

			for (auto p : list)
			{
				ptr->insert(p);
			}
		}

		Unordered_Multiset(const Unordered_Multiset<Ty , alloc>& obj) noexcept
		{
			size_t size = obj.ptr->buckets_count();
			ptr = new hash_table<Ty, alloc , Equal_Compare>(size);

			auto p = obj.cbegin();
			for (; p != obj.cend(); ++p)
			{
				ptr->insert((*p));
			}
		}

		~Unordered_Multiset() noexcept
		{
			delete ptr;
			ptr = nullptr;
		}



		//insert and erase operations

		[[noreturn]] void insert(const Ty& elem) noexcept
		{
			ptr->insert(elem);
		}

		[[noreturn]] void erase(const Ty& elem) noexcept
		{
			ptr->erase(elem);
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
			return ptr->erase(p_begin,p_end);
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

		_NODISCARD int count(const Ty& elem) const noexcept
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

		_NODISCARD bool find(const Ty& elem) const noexcept
		{
			return ptr->find(elem);
		}

		_NODISCARD compare key_comp() const noexcept
		{
			return compare;
		}

		[[noreturn]] void swap(self& obj) noexcept
		{
			hash_table<Ty , alloc , Equal_Compare>* temp_ptr = ptr;
			hash_table<Ty , alloc , Equal_Compare>* obj_ptr = obj.ptr;

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

			typename Unordered_Multiset<Ty , alloc>::const_iterator p = obj.cbegin();
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
			typename Unordered_Multiset<Ty , alloc>::const_iterator p2 = cbegin();
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