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

		explicit Unordered_Set(size_t size)
		{
			ptr = new hash_table<Ty>(size);
		}

		Unordered_Set(const initializer_list<Ty>& list)
		{
			size_t size = list.size();
			ptr = new hash_table<Ty>(size);

			for (auto p : list)
			{
				ptr->insert(p);
			}
		}

		Unordered_Set(const Unordered_Set<Ty>& obj)
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

		bool empty()
		{
			return ptr->empty();
		}

		int size()
		{
			return ptr->size();
		}

		size_t buckets_count()
		{
			return ptr->buckets_count();
		}

		int count(Ty elem)
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

		compare key_comp()
		{
			return compare;
		}

		void swap(Unordered_Set<Ty>& obj)
		{
			hash_table<Ty>* temp = new hash_table<Ty>(obj.buckets_count());

			for (auto p : obj)
			{
				temp->insert(p);
			}

			//swap obj data
			obj.clear();

			for (auto p = begin() ; p != end(); ++p)
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

		bool operator==(const Unordered_Set<Ty>& obj)
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

		bool operator!=(const Unordered_Set<Ty>& obj)
		{
			return !((*this) == obj);
		}

		bool operator>(const Unordered_Set<Ty>& obj)
		{
			if (size() > obj.size())
				return true;

			return false;
		}

		bool operator<(const Unordered_Set<Ty>& obj)
		{
			if (size() < obj.size())
				return true;

			return false;
		}

		bool operator>=(const Unordered_Set<Ty>& obj)
		{
			if (size() >= obj.size())
				return true;

			return false;
		}

		bool operator<=(const Unordered_Set<Ty>& obj)
		{
			if (size() <= obj.size())
				return true;

			return false;
		}
};