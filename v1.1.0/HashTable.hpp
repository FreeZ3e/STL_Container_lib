/* hash_table implementation
 *
 * Copyright(c) 2021 Mashiro -1262159823@qq.com
 *
 * This File is part of CONTAINER LIBRARY project.
 *
 * version : 1.1.0
 *
 * author : Mashiro
 *
 * File name : HashTable.hpp -bottom container part.
 *
 * This library is free software;you can redistribute is and/or modify it
 * under the APACHE LICENSE 2.0 as published by the Free Software Foundation.
 * ------------------------------------------------------------------------
 */

#pragma once
#include<functional>
#include<initializer_list>
#include"errors.hpp"
#include"memory.hpp"
#include"iterator.hpp"
#include"Hash_Function.hpp"
#include"memory_allocator.hpp"
#include"Pair.hpp"

#if _LIB_DEBUG_LEVEL == 1

#include<iostream>
#include<assert.h>

#endif // __LIB_DEBUG_LEVEL == 1

using std::initializer_list;
using std::function;

//hash_table
template<typename Ty , typename alloc = _default_allocator , 
		typename Compare_Class = Unique_Compare , typename Hash_Class = hash_function<Ty>>
class hash_table
{	
	//hasher
	using hash_func = function<size_t(Ty)>;
	//compare
	using key_compare = function<bool()>;

	//bucket node
	template<typename value>
	struct hash_node
	{
		using value_type = value;

		value val;
		hash_node* next = nullptr;

		hash_node(value elem):val(elem),next(nullptr)
		{ }

		hash_node() = default;

		void* operator new(size_t size)
		{
			return simple_allocator(alloc , hash_node<value>)::allocate(1);
		}

		void operator delete(void* ptr , size_t size)
		{
			simple_allocator(alloc , hash_node<value>)::deallocate((hash_node<value>*)ptr , sizeof(hash_node<value>));
		}

		void* operator new[](size_t size)
		{
			return simple_allocator(alloc , hash_node<value>)::allocate(size);
		}

		void operator delete[](void* ptr , size_t size)
		{
			simple_allocator(alloc , hash_node<value>)::deallocate((hash_node<value>*)ptr , sizeof(hash_node<value>) * size);
		}
	};

	//friend iterator
	template<typename Ty,typename Hash>
	friend struct hash_table_iterator;

	template<typename Ty,typename Hash>
	friend struct const_hash_table_iterator;

	public:
		using value_type = Ty;
		using NodeType = hash_node<Ty>;
		using reference = Ty&;
		using const_reference = const Ty&;
		using pointer = Ty*;
		using const_pointer = const Ty*;
		using iterator = hash_table_iterator<hash_node<Ty>*,hash_table<Ty, alloc , Compare_Class,Hash_Class>>;
		using const_iterator = const_hash_table_iterator<hash_node<Ty>* , hash_table<Ty , alloc , Compare_Class , Hash_Class>>;
		using size_type = size_t;
		using self = hash_table<Ty , alloc , Compare_Class , Hash_Class>;

	private:
		key_compare compare_func = Compare_Class::Compare;
		hash_func hasher = Hash_Class::hash;

		hash_node<Ty>** buckets = nullptr;

		int elem_count = 0;
		size_t bucket_size = 0;
		
	public:
		hash_table() = delete;

		explicit hash_table(size_type size)
		{
		#if _LIB_DEBUG_LEVEL == 1

			_BUG_VERIFY((size > 0) , "container size error");
			assert(size > 0);

		#endif // _LIB_DEBUG_LEVEL == 1

			buckets = simple_allocator(alloc , hash_node<Ty>*)::allocate(size * 2);
			this->bucket_size = size * 2;

			init_bucket(bucket_size);
		}

		~hash_table() noexcept
		{
			clear();
			buckets = nullptr;
		}
			


		//insert and erase operations

		template<typename... value>
		_NODISCARD pair<iterator , bool> emplace(value&&... arg)
		{
			size_t key = hasher(value_type(arg...));

			while (key >= bucket_size || elem_count >= bucket_size)
			{
				resize(bucket_size);
			}

			if (buckets[key] == nullptr)//unique
			{
				hash_node<Ty>* ptr = new hash_node<Ty>;
				pointer temp = &ptr->val;
				new(temp) value_type(arg...);

				buckets[key] = ptr;

				elem_count++;

				return make_pair(it_find(value_type(arg...)) , true);
			}
			else if (buckets[key] != nullptr && compare_func())//equal
			{
				hash_node<Ty>* ptr = buckets[key];

				while (buckets[key]->next != nullptr)
				{
					buckets[key] = buckets[key]->next;
				}

				buckets[key]->next = new hash_node<Ty>;
				pointer temp = &buckets[key]->next->val;
				new(temp) value_type(arg...);
				
				buckets[key] = ptr;

				elem_count++;

				return make_pair(it_find(value_type(arg...)) , true);
			}

			return make_pair(begin() , false);
		}

		template<typename... value>
		_NODISCARD iterator emplace_hint(iterator pos , value&&... arg)
		{
			if (compare_func() == false)
			{
				if (find(value_type(arg...)) != nullptr)
					return end();
			}

			if (pos >= end())
			{
				emplace(arg...);
				return it_find(value_type(arg...));
			}

			value_type elem = *pos;

			pointer temp = &(*pos);
			new(temp) value_type(arg...);

			iterator beg = pos+1;
			while (beg != end())
			{
				value_type cur = *beg;
				*beg = elem;
				elem = cur;

				++beg;
			}

			insert(elem , -1);

			return begin() + pos.step();
		}

		_NODISCARD iterator insert(iterator pos , value_type&& elem)
		{
			if (compare_func() == false)
			{
				if (find(elem) != nullptr)
					return end();
			}

			if (pos >= end())
				return insert(elem).key;

			value_type pos_elem = *pos;
			*pos = elem;
			insert(pos_elem , -1);

			return pos;
		}

		_NODISCARD iterator insert(iterator pos , const_reference elem)
		{
			if (compare_func() == false)
			{
				if (find(elem) != nullptr)
					return end();
			}

			if (pos >= end())
				return insert(elem).key;

			value_type pos_elem = *pos;
			*pos = elem;
			insert(pos_elem , -1);

			return pos;
		}

		template<typename iter>
		[[noreturn]] void insert(iter beg , iter end)
		{
			while (beg != end)
			{
				insert(*beg++);
			}
		}

		[[noreturn]] void insert(const initializer_list<value_type>& list)
		{
			for (auto p : list)
			{
				insert(p);
			}
		}

		//insert_key : set -1 will insert elem whatever compare_func is
		_NODISCARD pair<iterator , bool> insert(value_type&& elem , int insert_key = 0)
		{
			size_t key = hasher(elem);
			
			while (key >= bucket_size || elem_count >= bucket_size)
			{
				resize(bucket_size);
			}

			if (buckets[key] == nullptr)//unique
			{
				hash_node<Ty>* ptr = new hash_node<Ty>(elem);
				buckets[key] = ptr;

				elem_count++;

				return make_pair(it_find(elem) , true);
			}
			else if (buckets[key] != nullptr && compare_func() || insert_key == -1)//equal
			{
				hash_node<Ty>* ptr = buckets[key];

				while (buckets[key]->next != nullptr)
				{
					buckets[key] = buckets[key]->next;
				}
				
				buckets[key]->next = new hash_node<Ty>(elem);
				buckets[key] = ptr;

				elem_count++;

				return make_pair(it_find(elem) , true);
			}

			return make_pair(begin() , false);
		}

		_NODISCARD pair<iterator , bool> insert(const_reference elem , int insert_key = 0)
		{
			size_t key = hasher(elem);

			while (key >= bucket_size || elem_count >= bucket_size)
			{
				resize(bucket_size);
			}

			if (buckets[key] == nullptr)//unique
			{
				hash_node<Ty>* ptr = new hash_node<Ty>(elem);
				buckets[key] = ptr;

				elem_count++;

				return make_pair(it_find(elem) , true);
			}
			else if (buckets[key] != nullptr && compare_func() || insert_key == -1)//equal
			{
				hash_node<Ty>* ptr = buckets[key];

				while (buckets[key]->next != nullptr)
				{
					buckets[key] = buckets[key]->next;
				}

				buckets[key]->next = new hash_node<Ty>(elem);
				buckets[key] = ptr;

				elem_count++;

				return make_pair(it_find(elem) , true);
			}

			return make_pair(begin() , false);
		}

		[[noreturn]] void erase(const_reference elem)
		{
			int key = (int)hasher(elem);

			hash_node<Ty>* ptr = new hash_node<Ty>;
			ptr->next = buckets[key];

			while (ptr->next)
			{
				if (ptr->next->val == elem)
				{
					hash_node<Ty>* temp;

					if (ptr->next == buckets[key])//head
					{
						temp = buckets[key];

						buckets[key] = buckets[key]->next;
						ptr->next = buckets[key];
					}
					else//node
					{
						temp = ptr->next;

						ptr->next = ptr->next->next;
					}

					elem_count--;

					memory::elem_destory(temp->val);
					delete temp;
					temp = nullptr;
				}
				else
				{
					ptr = ptr->next;
				}
			}
		}

		_NODISCARD iterator erase(iterator p)
		{
			auto temp = p;
			int step = p.step();

			if (step == elem_count-1)
			{
				erase(*temp);

				return iterator(nullptr , this , bucket_size , step , elem_count);
			}

			Ty elem = (*(++p));
			erase(*temp);

			return iterator(find(elem) , this , bucket_size , step , elem_count);
		}

		_NODISCARD const_iterator erase(const_iterator p)
		{
			auto temp = p;
			int step = p.step();

			if (step == elem_count - 1)
			{
				erase(*temp);

				return const_iterator(nullptr , this , bucket_size , step , elem_count);
			}

			Ty elem = (*(++p));
			erase(*temp);

			return const_iterator(find(elem) , this , bucket_size , step , elem_count);
		}

		[[noreturn]] void erase(iterator p_begin , iterator p_end)
		{
			int n = p_begin.step();
			for (; n < p_end.step(); ++n)
			{
				p_begin = erase(p_begin);
			}
		}

		[[noreturn]] void clear() noexcept
		{
			simple_allocator(alloc , hash_node<Ty>*)::deallocate(buckets , sizeof(hash_node<Ty>*) * bucket_size);
			buckets = simple_allocator(alloc , hash_node<Ty>*)::allocate(bucket_size);
			init_bucket(bucket_size);

			elem_count = 0;
		}

		

		//other

		_NODISCARD hash_node<Ty>* find(const_reference elem)
		{
			for (int n = 0; n < (int)bucket_size; ++n)
			{
				hash_node<Ty>* ptr = new hash_node<Ty>;
				ptr->next = buckets[n];

				while (ptr->next)
				{
					if (ptr->next->val == elem)
					{
						return ptr->next;
					}
					else
						ptr = ptr->next;
				}
			}

			return nullptr;
		}

		_NODISCARD const hash_node<Ty>* find(const_reference elem) const
		{
			for (int n = 0; n < (int)bucket_size; ++n)
			{
				hash_node<Ty>* ptr = new hash_node<Ty>;
				ptr->next = buckets[n];

				while (ptr->next)
				{
					if (ptr->next->val == elem)
					{
						return ptr->next;
					}
					else
						ptr = ptr->next;
				}
			}

			return nullptr;
		}

		_NODISCARD iterator it_find(const_reference elem)
		{
			iterator beg = begin();
			for (; beg != end(); ++beg)
			{
				if ((*beg) == elem)
					break;
			}

			return beg;
		}

		_NODISCARD const_iterator const_it_find(const_reference elem) const
		{
			const_iterator beg = begin();
			for (; beg != end(); ++beg)
			{
				if ((*beg) == elem)
					break;
			}

			return beg;
		}

		_NODISCARD int bucket(const_reference elem) const
		{
			for (int n = 0; n < (int)bucket_size; ++n)
			{
				hash_node<Ty>* ptr = new hash_node<Ty>;
				ptr->next = buckets[n];

				while (ptr->next)
				{
					if (ptr->next->val == elem)
					{
						return n+1;
					}
					else
						ptr = ptr->next;
				}
			}

			return -1;
		}

		[[noreturn]] void resize(size_type size)
		{
		#if _LIB_DEBUG_LEVEL == 1

			_BUG_VERIFY((size > 0) , "container size error");
			assert(size > 0);

		#endif // _LIB_DEBUG_LEVEL == 1

			MemoryExpand(size);

			if(size >= bucket_size)
				bucket_size = size * 2;
			else
			{
				bucket_size = size;
				elem_count = elem_count_find();
			}
		}

		_NODISCARD int size() const noexcept
		{
			return this->elem_count;
		}

		_NODISCARD size_t buckets_count() const noexcept
		{
			return this->bucket_size;
		}

		_NODISCARD size_t max_buckets_count() const noexcept
		{
			return (value_type(-1) / sizeof(NodeType));
		}

		_NODISCARD float load_factor() const noexcept
		{
			return (float)elem_count / buckets_count;
		}

		_NODISCARD bool empty() const noexcept
		{
			if (elem_count == 0)
				return true;

			return false;
		}

		_NODISCARD size_t get_key(const_reference elem) const
		{
			return hasher(elem);
		}

		[[noreturn]] void rehash(hash_func new_hasher)
		{
			hasher = new_hasher;

			auto ptr = begin();

			for (; ptr != end(); ++ptr)
			{
				auto value = *ptr;

				ptr = erase(ptr);
				insert(value);
			}
		}

		[[noreturn]] void swap(self& obj)
		{
			hash_node<Ty>** temp_ptr = buckets;
			hash_node<Ty>** obj_ptr = obj.buckets;

			buckets = obj_ptr;
			obj.buckets = temp_ptr;

			int temp_count = elem_count;
			elem_count = obj.elem_count;
			obj.elem_count = temp_count;

			size_t temp_size = bucket_size;
			bucket_size = obj.bucket_size;
			obj.bucket_size = temp_size;
		}

		_NODISCARD hash_func hash_function() const noexcept
		{
			return hasher;
		}

		_NODISCARD key_compare key_eq() const noexcept
		{
			return compare_func;
		}


		//iterator

		_NODISCARD iterator begin() noexcept
		{
			return iterator(buckets[0],this,bucket_size,0, elem_count);
		}

		_NODISCARD iterator end() noexcept
		{
			return iterator(nullptr,this,bucket_size,elem_count,elem_count);
		}

		_NODISCARD const_iterator cbegin() noexcept
		{
			return const_iterator(buckets[0] , this , bucket_size,0, elem_count);
		}

		_NODISCARD const_iterator cend() noexcept
		{
			return const_iterator(nullptr , this , bucket_size,elem_count,elem_count);
		}


		//operator overload

		_NODISCARD hash_node<Ty>*& operator[](size_type key)
		{
		#if _LIB_DEBUG_LEVEL == 1

			_BUG_VERIFY(((key < (int)bucket_size) && (key >= 0)) , "out of range");
			assert(key < (int)bucket_size && key >= 0);

		#endif // _LIB_DEBUG_LEVEL == 1

			return buckets[key];
		}

		self& operator=(const self& obj)
		{
			simple_allocator(alloc , hash_node<Ty>*)::deallocate(buckets , sizeof(hash_node<Ty>*) * bucket_size);
			buckets = simple_allocator(alloc , hash_node<Ty>*)::allocate(obj.bucket_size);
			init_bucket(obj.bucket_size);

			for (int n = 0; n < (int)bucket_size ; ++n)
			{
				hash_node<Ty>* ptr = obj.buckets[n];
				if (ptr != nullptr)
				{
					buckets[n] = new hash_node<Ty>;
					hash_node<Ty>* temp = buckets[n];

					while (ptr != nullptr)
					{
						if (temp == nullptr)
							temp = new hash_node<Ty>;

						temp->val = ptr->val;
						temp = temp->next;
						ptr = ptr->next;
					}
				}
			}

			this->bucket_size = obj.bucket_size;
			this->elem_count = obj.elem_count;

			return *this;
		}

		_NODISCARD bool operator==(const self& obj) const noexcept
		{
			if (elem_count != obj.elem_count || bucket_size != obj.bucket_size)
				return false;

			for (int n = 0; n < bucket_size; ++n)
			{
				if (buckets[n] != obj.buckets[n])
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
			if (elem_count > obj.size())
				return true;

			return false;
		}

		template<typename coll>
		_NODISCARD bool operator<(const coll& obj) const noexcept
		{
			if (elem_count < obj.size())
				return true;

			return false;
		}

		template<typename coll>
		_NODISCARD bool operator>=(const coll& obj) const noexcept
		{
			if (elem_count >= obj.size())
				return true;

			return false;
		}
		 
		template<typename coll>
		_NODISCARD bool operator<=(const coll& obj) const noexcept
		{
			if (elem_count <= obj.size())
				return true;

			return false;
		}

	private:
		[[noreturn]] void MemoryExpand(size_type resize)
		{
		#if _LIB_DEBUG_LEVEL == 1

			_BUG_VERIFY((resize > 0) , "container size error");
			assert(resize > 0);

		#endif // _LIB_DEBUG_LEVEL == 1

			hash_node<Ty>** temp = simple_allocator(alloc , hash_node<Ty>*)::allocate(bucket_size);

			//keep old data
			for (int n = 0; n < (int)bucket_size; n++)
			{
				if (buckets[n] == nullptr)
					temp[n] = nullptr;
				else
					temp[n] = buckets[n];
			}

			//alloc new buckets
			simple_allocator(alloc , hash_node<Ty>*)::deallocate(buckets , sizeof(hash_node<Ty>*) * bucket_size);

			if (resize >= bucket_size)
			{
				buckets = simple_allocator(alloc , hash_node<Ty>*)::allocate(resize * 2);
				init_bucket(resize * 2);

				//get old data
				for (int n = 0; n < (int)bucket_size; n++)
				{
					buckets[n] = temp[n];
				}
			}
			else
			{
				buckets = simple_allocator(alloc , hash_node<Ty>*)::allocate(resize);
				init_bucket(resize);

				for (int n = 0; n < resize; n++)
				{
					buckets[n] = temp[n];
				}
			}

			//set temp free
			simple_allocator(alloc , hash_node<Ty>*)::deallocate(temp , sizeof(hash_node<Ty>*) * bucket_size);
			temp = nullptr;
		}

		[[noreturn]] void init_bucket(size_type size)
		{
			for (int n = 0; n < (int)size; ++n)
			{
				buckets[n] = nullptr;
			}
		}

		_NODISCARD int elem_count_find() noexcept
		{
			int count = 0;

			for (int n = 0; n < (int)bucket_size; ++n)
			{
				hash_node<Ty>* ptr = new hash_node<Ty>;
				ptr->next = buckets[n];

				while (ptr->next)
				{
					count++;
					ptr = ptr->next;
				}
			}

			return count;
		}
};