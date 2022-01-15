/* unordered_multiset implementation
 *
 * Copyright(c) 2021 Mashiro -1262159823@qq.com
 *
 * This File is part of CONTAINER LIBRARY project.
 *
 * version : 1.1.0
 *
 * author : Mashiro
 *
 * File name : unordered_multiset.hpp -a kind of unordered container.
 *
 * This library is free software;you can redistribute is and/or modify it
 * under the APACHE LICENSE 2.0 as published by the Free Software Foundation.
 *-------------------------------------------------------------------------
 */

#pragma once
#include"HashTable.hpp"


template<typename Ty , typename Hash = hash_function<Ty> , typename alloc = _default_allocator>
class unordered_multiset
{
	public:
		using value_type = Ty;
		using compare = Equal_Compare;
		using hasher = Hash;
		using reference = Ty&;
		using const_reference = const Ty&;
		using pointer = Ty*;
		using const_pointer = const Ty*;
		using hash_table = hash_table<Ty , alloc , compare , Hash>;
		using iterator = hash_table_iterator<typename hash_table::NodeType* , hash_table>;
		using const_iterator = const_hash_table_iterator<typename hash_table::NodeType* , hash_table>;
		using self = unordered_multiset<Ty , Hash ,alloc>;
		using size_type = size_t;

	private:
		hash_table* ptr = nullptr;

	public:
		unordered_multiset() = delete;

		explicit unordered_multiset(size_type size)
		{
			ptr = new hash_table(size);
		}

		explicit unordered_multiset(const initializer_list<value_type>& list)
		{
			ptr = new hash_table(list.size());
			ptr->insert(list);
		}

		template<typename iter>
		unordered_multiset(iter beg , iter end)
		{
			ptr = new hash_table((size_type)end.step() - beg.step());

			while (beg != end)
				ptr->insert(*beg++);
		}

		unordered_multiset(const self& obj)
		{
			ptr = new hash_table(obj.ptr->size());

			for (auto p : obj)
				ptr->insert(p);
		}

		unordered_multiset(self&& obj)
		{
			ptr = new hash_table(obj.ptr->size());

			for (auto p : obj)
				ptr->insert(p);

			delete obj.ptr;
			obj.ptr = nullptr;
		}

		~unordered_multiset()
		{
			delete ptr;
			ptr = nullptr;
		}



		template<typename... value>
		_NODISCARD iterator emplace(value&&... arg)
		{
			return (ptr->emplace(arg...)).key;
		}

		template<typename... value>
		_NODISCARD iterator emplace_hint(iterator pos , value&&... arg)
		{
			return ptr->emplace_hint(pos , arg...);
		}

		_NODISCARD iterator insert(iterator pos , const_reference elem)
		{
			return ptr->insert(pos , elem);
		}

		_NODISCARD iterator insert(iterator pos , value_type&& elem)
		{
			return ptr->insert(pos , elem);
		}

		template<typename iter>
		[[noreturn]] void insert(iter beg , iter end)
		{
			ptr->insert(beg , end);
		}

		[[noreturn]] void insert(const initializer_list<value_type>& list)
		{
			ptr->insert(list);
		}

		_NODISCARD iterator insert(const_reference elem)
		{
			return (ptr->insert(elem)).key;
		}

		_NODISCARD iterator insert(value_type&& elem)
		{
			return (ptr->insert(elem)).key;
		}

		[[noreturn]] void erase(const_reference elem)
		{
			ptr->erase(elem);
		}

		_NODISCARD iterator erase(iterator p)
		{
			return ptr->erase(p);
		}

		_NODISCARD const_iterator erase(const_iterator p)
		{
			return ptr->erase(p);
		}

		[[noreturn]] void erase(iterator p_begin , iterator p_end)
		{
			ptr->erase(p_begin , p_end);
		}

		[[noreturn]] void clear() noexcept
		{
			ptr->clear();
		}



		_NODISCARD bool empty() const noexcept
		{
			return ptr->empty();
		}

		_NODISCARD int size() const noexcept
		{
			return ptr->size();
		}

		_NODISCARD size_t max_size() const noexcept
		{
			return value_type(-1) / sizeof(value_type);
		}

		_NODISCARD size_t buckets_count() const noexcept
		{
			return ptr->buckets_count();
		}

		_NODISCARD size_type max_buckets_count() const noexcept
		{
			return ptr->max_buckets_count();
		}

		_NODISCARD float load_factor() const noexcept
		{
			return ptr->load_factor();
		}

		_NODISCARD int bucket(const_reference elem) const
		{
			return ptr->bucket(elem);
		}

		_NODISCARD int count(const_reference elem) const
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

		_NODISCARD const_iterator find(const_reference elem) const
		{
			return ptr->const_it_find(elem);
		}

		_NODISCARD iterator find(const_reference elem)
		{
			return ptr->it_find(elem);
		}

		_NODISCARD compare key_comp() const noexcept
		{
			return compare;
		}

		[[noreturn]] void swap(self& obj)
		{
			hash_table* temp_ptr = ptr;
			hash_table* obj_ptr = obj.ptr;

			ptr = obj_ptr;
			obj.ptr = temp_ptr;
		}

		template<typename hash_func>
		[[noreturn]] void rehash(hash_func new_hasher)
		{
			ptr->rehash(new_hasher);
		}

		_NODISCARD auto hash_function() const noexcept
		{
			return ptr->hash_function();
		}

		_NODISCARD auto key_eq() const noexcept
		{
			return ptr->key_eq();
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

		self& operator=(const self& obj)
		{
			clear();

			typename self::const_iterator p = obj.cbegin();
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
			typename self::const_iterator p2 = cbegin();
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