/* hash_table implementation
 *
 * Copyright(c) 2021 Mashiro -1262159823@qq.com
 *
 * This File is part of CONTAINER LIBRARY project.
 *
 * version : 1.2.0-alpha
 *
 * author : Mashiro
 *
 * File name : HashTable.hpp -bottom implementation of unordered container.
 *
 * This library is free software;you can redistribute is and/or modify it
 * under the APACHE LICENSE 2.0 as published by the Free Software Foundation.
 * ------------------------------------------------------------------------
 *
 *-------------------------------README------------------------------------
 *
 * template<typename Ty,typename Compare_Class = Unique_Compare,typename hash_function<Ty>>
 * class hash_table
 * {
 *      //bucket node
 *
 *      template<typename value>
 *      struct hash_node
 *      {
 *			using TypeValue = value;
 * 
 *          value val;
 *          hash_node* next;
 *
 *          hash_node(value elem):val(elem),next(nullptr)
 *          {}
 *
 *          hash_node() = default;
 *      }
 *
 *
 *      //data struct:   (buckets list array)
 *                          |bucket|----(bucket list)-->node-->node...
 *                          |bucket|
 *                          |bucket|
 *                          |bucket|
 *                              .
 *                              .
 *                              .
 *
 *
 *      //iterator : hash_table_iterator
 *      //const_iterator : const_hash_table_iterator
 *
 *
 *      //ctor
 *
 *      hash_table(size_t size)----------------------init buckets array with size.
 *
 *      //operations
 *
 *      void insert(Ty elem)
 *      void erase(Ty elem)
 *      iterator erase(iterator p)
 *      const_iterator erase(const_iterator p)
 *      void erase(iterator p_begin,iterator p_end)
 *      void clear()
 *      hash_node<Ty>* find(Ty elem)--------------------------if elem exist,return node ptr.
 *      void resize(size_t size)
 *      int size()
 *      size_t buckets_count()--------------------------------return bucket size.
 *      bool empty()
 *      size_t get_key(Ty elem)-------------------------------return key of elem.
 *		void rehash(hash_func new_hasher)---------------------set new hash function and rehash.
 *      void swap(self& obj)
 *
 *      //iterator
 *
 *      iterator begin()
 *      iterator end()
 *      const_iterator cbegin()
 *      const_iterator cend()
 *
 *      //operator overload
 *
 *      hash_node<Ty>*& operator[](size_t key)
 *      self& operator=(const self& obj)
 *      bool operator==(const self& obj)
 *      bool operator!=(const self& obj)
 *      bool operator>(const self& obj)
 *      bool operator<(const self& obj)
 *      bool operator>=(const self& obj)
 *      bool operator<=(const self& obj)
 *
 *      //private functions
 *
 *      void MemoryExpand(size_t resize)------------------make resize operation.
 *      void init_bucket(size_t size)---------------------initialize buckets array.
 *      int elem_count_find()----------------------------return number of elems.
 * }
 * ----------------------------------------------------------------------------------------------
 */



#pragma once
#include"iterator.hpp"
#include"Hash_Function.hpp"
#include<functional>

using std::function;

//hash_table
template<typename Ty , typename Compare_Class = Unique_Compare , typename Hash_Class = hash_function<Ty>>
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
		using TypeValue = value;

		value val;
		hash_node* next;

		hash_node(value elem):val(elem),next(nullptr)
		{ }

		hash_node() = default;
	};

	//friend iterator
	template<typename Ty,typename Hash>
	friend struct hash_table_iterator;

	template<typename Ty,typename Hash>
	friend struct const_hash_table_iterator;

	public:
		using self = hash_table<Ty , Compare_Class , Hash_Class>;
		using TypeValue = Ty;
		using NodeType = hash_node<Ty>;
		using iterator = hash_table_iterator<hash_node<Ty>*,hash_table<Ty,Compare_Class,Hash_Class>>;
		using const_iterator = const_hash_table_iterator<hash_node<Ty>* , hash_table<Ty , Compare_Class , Hash_Class>>;

	private:
		key_compare compare_func = Compare_Class::Compare;
		hash_func hasher = Hash_Class::hash;

		hash_node<Ty>** buckets;

		int elem_count = 0;
		size_t bucket_size = 0;
		
	public:
		hash_table() = delete;

		//ctor
		hash_table(size_t size)
		{
			buckets = new hash_node<Ty>*[size * 2];
			this->bucket_size = size * 2;

			init_bucket(bucket_size);
		}

		~hash_table()
		{
			clear();
			buckets = nullptr;
		}
			


		//insert and erase operations

		void insert(Ty elem)
		{
			size_t key = hasher(elem);
			
			while (key >= bucket_size || elem_count >= bucket_size)//oversize
			{
				resize(bucket_size);
				bucket_size = bucket_size * 2;
			}

			if (buckets[key] == nullptr)//unique
			{
				hash_node<Ty>* ptr = new hash_node<Ty>(elem);
				buckets[key] = ptr;

				elem_count++;
			}
			else if (buckets[key] != nullptr && compare_func())//equal
			{
				hash_node<Ty>* ptr = buckets[key];

				while (buckets[key]->next != nullptr)
				{
					buckets[key] = buckets[key]->next;
				}
				
				buckets[key]->next = new hash_node<Ty>(elem);
				buckets[key] = ptr;

				elem_count++;
			}
		}

		void erase(Ty elem)
		{
			int key = hasher(elem);

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
					delete temp;
					temp = nullptr;
				}
				else
				{
					ptr = ptr->next;
				}
			}
		}

		iterator erase(iterator p)
		{
			auto temp = p;
			int step = p.step();

			if (step == elem_count-1)
			{
				erase(*temp);

				return iterator(nullptr , this , bucket_size , step);
			}

			Ty elem = (*(++p));
			erase(*temp);

			return iterator(find(elem) , this , bucket_size , step);
		}

		const_iterator erase(const_iterator p)
		{
			auto temp = p;
			int step = p.step();

			if (step == elem_count - 1)
			{
				erase(*temp);

				return const_iterator(nullptr , this , bucket_size , step);
			}

			Ty elem = (*(++p));
			erase(*temp);

			return const_iterator(find(elem) , this , bucket_size , step);
		}

		void erase(iterator p_begin , iterator p_end)
		{
			int n = p_begin.step();
			for (; n < p_end.step(); ++n)
			{
				p_begin = erase(p_begin);
			}
		}

		void clear()
		{
			delete[] buckets;
			buckets = new hash_node<Ty>*[bucket_size];
			init_bucket(bucket_size);

			elem_count = 0;
		}

		
		//other

		hash_node<Ty>* find(Ty elem) const
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

		void resize(size_t size) 
		{
			MemoryExpand(size);

			if(size >= bucket_size)
				bucket_size = size * 2;
			else
			{
				bucket_size = size;
				elem_count = elem_count_find();
			}
		}

		int size() const
		{
			return this->elem_count;
		}

		size_t buckets_count() const
		{
			return this->bucket_size;
		}

		bool empty() const
		{
			if (elem_count == 0)
				return true;

			return false;
		}

		size_t get_key(Ty elem) const
		{
			return hasher(elem);
		}

		void rehash(hash_func new_hasher)
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

		void swap(self& obj)
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



		//iterator

		iterator begin()
		{
			return iterator(buckets[0],this,bucket_size,0);
		}

		iterator end()
		{
			return iterator(nullptr,this,bucket_size,elem_count);
		}

		const_iterator cbegin()
		{
			return const_iterator(buckets[0] , this , bucket_size,0);
		}

		const_iterator cend()
		{
			return const_iterator(nullptr , this , bucket_size,elem_count);
		}


		//operator overload

		hash_node<Ty>*& operator[](size_t key)
		{
			return buckets[key];
		}

		self& operator=(const self& obj)
		{
			delete[] buckets;
			buckets = new hash_node<Ty>*[obj.bucket_size];
			init_bucket(obj.bucket_size);

			for (int n = 0; n < (int)bucket_size ; ++n)
			{
				buckets[n] = obj.buckets[n];
			}

			this->bucket_size = obj.bucket_size;
			this->elem_count = obj.elem_count;

			return *this;
		}

		bool operator==(const self& obj) const
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

		bool operator!=(const self& obj) const
		{
			return !((*this) == obj);
		}

		bool operator>(const self& obj) const
		{
			if (elem_count > obj.elem_count)
				return true;

			return false;
		}

		bool operator<(const self& obj) const
		{
			if (elem_count < obj.elem_count)
				return true;

			return false;
		}

		bool operator>=(const self& obj) const
		{
			if (elem_count >= obj.elem_count)
				return true;

			return false;
		}

		bool operator<=(const self& obj) const
		{
			if (elem_count <= obj.elem_count)
				return true;

			return false;
		}

	private:
		void MemoryExpand(size_t resize)
		{
			hash_node<Ty>** temp = new hash_node<Ty>*[bucket_size];

			//keep old data
			for (int n = 0; n < (int)bucket_size; n++)
			{
				if (buckets[n] == nullptr)
					temp[n] = nullptr;
				else
					temp[n] = buckets[n];
			}

			//alloc new buckets
			delete[] buckets;

			if (resize >= bucket_size)
			{
				buckets = new hash_node<Ty>*[resize * 2];
				init_bucket(resize * 2);

				//get old data
				for (int n = 0; n < (int)bucket_size; n++)
				{
					buckets[n] = temp[n];
				}
			}
			else
			{
				buckets = new hash_node<Ty>*[resize];
				init_bucket(resize);

				for (int n = 0; n < resize; n++)
				{
					buckets[n] = temp[n];
				}
			}

			//set temp free
			delete[] temp;
			temp = nullptr;
		}

		void init_bucket(size_t size)
		{
			for (int n = 0; n < (int)size; ++n)
			{
				buckets[n] = nullptr;
			}
		}

		int elem_count_find()
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