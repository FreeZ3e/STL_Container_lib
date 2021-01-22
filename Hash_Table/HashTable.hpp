#pragma once
#include"iterator.hpp"
#include"Pair.hpp"
#include<functional>
#include<string>

using std::function;
using std::string;

//hash function
template<typename Ty>
struct hash_function
{
	static size_t hash(const Ty elem)
	{
		return (size_t)elem;
	}
};

template<>
struct hash_function<string>
{
	static size_t hash(const string elem)
	{
		unsigned long h = 0;

		for (auto p : elem)
		{
			h = 5 * h + p;
		}

		return (size_t)h;
	}
};

template<>
struct hash_function<char*>
{
	static size_t hash(const char* elem)
	{
		unsigned long h = 0;

		for (; *elem; ++elem)
		{
			h = 5 * h + *elem;
		}

		return (size_t)h;
	}
};

template<typename key,typename value>
struct pair_hash
{
	static size_t hash(const pair<key , value>& obj)
	{
		return obj.key;
	}
};

template<typename value>
struct pair_hash<string , value>
{
	static size_t hash(const pair<string , value>& obj)
	{
		unsigned long h = 0;

		for (auto p : obj.key)
		{
			h = 5 * h + p;
		}

		return (size_t)h;
	}
};

template<typename value>
struct pair_hash<char* , value>
{
	static size_t hash(const pair<char*,value>& obj)
	{
		unsigned long h = 0;

		for (; *(obj.key); ++obj.key)
		{
			h = 5 * h + *(obj.key);
		}

		return (size_t)h;
	}
};


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
		value val;
		hash_node* next;

		hash_node(value elem):val(elem),next(nullptr)
		{ }

		hash_node() = default;
	};

	//friend iterator
	template<typename Ty,typename Hash>
	friend struct hash_table_iterator;

	public:
		using TypeValue = Ty;
		using iterator = hash_table_iterator<hash_node<Ty>*,hash_table<Ty,Compare_Class,Hash_Class>>;

	private:
		key_compare compare_func = Compare_Class::Compare;
		hash_func hasher = Hash_Class::hash;

		hash_node<Ty>** buckets;

		int elem_count = 0;
		size_t bucket_size = 0;
		
	public:
		hash_table() = delete;

		//ctor
		hash_table(const size_t size)
		{
			buckets = new hash_node<Ty>*[size * 10];
			this->bucket_size = size * 10;

			init_bucket(bucket_size);
		}

		~hash_table()
		{
			clear();
		}
			
		void insert(const Ty elem)
		{
			size_t key = hasher(elem);
			
			while (key > bucket_size || elem_count >= bucket_size)//oversize
			{
				resize(bucket_size);
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

		void erase(const Ty elem)
		{
			for (int n = 0; n < (int)bucket_size; ++n)//bucket jump
			{
				if (buckets[n] != nullptr)//find bucket list
				{
					hash_node<Ty>* ptr = new hash_node<Ty>;
					ptr->next = buckets[n];

					while (ptr->next)
					{
						if (ptr->next->val == elem)
						{
							hash_node<Ty>* temp;

							if (ptr->next == buckets[n])//head
							{
								temp = buckets[n];

								buckets[n] = buckets[n]->next;
								ptr->next = buckets[n];
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
			}
		}

		void clear()
		{
			delete[] buckets;
			buckets = new hash_node<Ty>*[bucket_size];
			init_bucket(bucket_size);

			elem_count = 0;
		}

		bool find(const Ty elem)
		{
			for (int n = 0; n < (int)bucket_size; ++n)
			{
				hash_node<Ty>* ptr = new hash_node<Ty>;
				ptr->next = buckets[n];

				while (ptr->next)
				{
					if (ptr->next->val == elem)
					{
						return true;
					}
				}
			}

			return false;
		}

		void resize(const size_t size)
		{
			MemoryExpand(size);
		}

		int size()
		{
			return this->elem_count;
		}

		int buckets_count()
		{
			return this->bucket_size;
		}

		bool empty()
		{
			if (elem_count == 0)
				return true;

			return false;
		}

		size_t get_key(int elem)
		{
			return hasher(elem);
		}

		iterator begin()
		{
			return iterator(buckets[0],this,bucket_size);
		}

		iterator end()
		{
			return iterator(nullptr,this,bucket_size);
		}

		hash_node<Ty>* operator[](size_t key)
		{
			return buckets[key];
		}

	private:
		void MemoryExpand(const size_t resize)
		{
			hash_node<Ty>** temp = new hash_node<Ty>*[bucket_size];

			//keep old data
			for (int n = 0; n < (int)bucket_size; n++)
			{
				temp[n] = buckets[n];
			}

			//alloc new buckets
			delete[] buckets;
			buckets = new hash_node<Ty>*[resize * 2];
			init_bucket(resize*2);

			//get old data
			for (int n = 0; n < (int)bucket_size; n++)
			{
				buckets[n] = temp[n];
			}

			//set temp free
			delete[] temp;
			temp = nullptr;

			//set new bucket_size
			bucket_size = resize*2;
		}

		void init_bucket(size_t size)
		{
			for (int n = 0; n < (int)size; ++n)
			{
				buckets[n] = nullptr;
			}
		}
};