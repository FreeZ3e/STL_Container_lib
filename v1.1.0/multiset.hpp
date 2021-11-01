/* multiset implementation
 *
 * Copyright(c) 2021 Mashiro -1262159823@qq.com
 *
 * This File is part of CONTAINER LIBRARY project.
 *
 * version : 1.1.0
 *
 * author : Mashiro
 *
 * File name : multiset.hpp -a kind of associative container.
 *
 * This library is free software;you can redistribute is and/or modify it
 * under the APACHE LICENSE 2.0 as published by the Free Software Foundation.
 *-------------------------------------------------------------------------
 */

#pragma once
#include "RB_Tree.hpp"


template<typename Ty,typename alloc = _default_allocator>
class multiset
{
	public:
		using value_type = Ty;
		using compare = Equal_Compare;
		using reference = Ty&;
		using const_reference = const Ty&;
		using pointer = Ty*;
		using const_pointer = const Ty*;
		using RB_Tree = RB_Tree<Ty , Equal_Compare , alloc>;
		using iterator = RB_Tree_iterator<typename RB_Tree::NodeType>;
		using const_iterator = const_RB_Tree_iterator<typename RB_Tree::NodeType>;
		using const_reverse_iterator = reverse_iterator<const_iterator>;
		using reverse_iterator = reverse_iterator<iterator>;
		using size_type = size_t;
		using self = multiset<Ty , alloc>;

	private:
		RB_Tree* tree = nullptr;

		int elem_count = 0;

	public:
		multiset()
		{
			tree = new RB_Tree;
		}

		explicit multiset(const_reference elem)
		{
			tree = new RB_Tree(elem);
			elem_count++;
		}

		explicit multiset(const initializer_list<value_type>& list) :multiset()
		{
			for (auto p : list)
				insert(p);
		}

		template<typename iter>
		multiset(iter beg , iter end) :multiset()
		{
			while (beg != end)
				insert(*beg++);
		}

		multiset(const self& obj) :multiset()
		{
			typename RB_Tree::const_iterator p = obj.tree->cbegin();
			for (; p != obj.tree->cend(); ++p)
			{
				tree->Insert((*p));
			}

			this->elem_count = obj.elem_count;
		}

		multiset(self&& obj) :multiset()
		{
			typename RB_Tree::const_iterator p = obj.tree->cbegin();
			for (; p != obj.tree->cend(); ++p)
			{
				tree->Insert((*p));
			}

			this->elem_count = obj.elem_count;

			delete obj.tree;
			obj.tree = nullptr;
			obj.elem_count = 0;
		}

		~multiset()
		{
			delete tree;
			tree = nullptr;
		}




		_NODISCARD iterator insert(iterator pos , const_reference elem)
		{
			if (pos >= end())
				return insert(elem);

			auto pos_elem = *pos;
			*pos = elem;
			insert(pos_elem);

			return pos;
		}

		_NODISCARD iterator insert(iterator pos , value_type&& elem)
		{
			if (pos >= end())
				return insert(elem);

			auto pos_elem = *pos;
			*pos = elem;
			insert(pos_elem);

			return pos;
		}

		_NODISCARD iterator insert(const_reference elem)
		{
			tree->Insert(elem);
			elem_count++;

			return find(elem);
		}

		_NODISCARD iterator insert(value_type&& elem)
		{
			tree->Insert(elem);
			elem_count++;

			return find(elem);
		}

		[[noreturn]] void insert(const initializer_list<value_type>& list)
		{
			for (auto p : list)
				insert(p);
		}

		template<typename iter>
		[[noreturn]] void insert(iter beg , iter end)
		{
			while (beg != end)
				insert(*beg++);
		}

		template<typename... value>
		_NODISCARD iterator emplace(value&&... arg)
		{
			auto pair = tree->emplace(arg...);
			elem_count++;

			return pair.key;
		}

		template<typename... value>
		_NODISCARD iterator emplace_hint(iterator pos , value&&... arg)
		{
			if (pos >= end())
			{
				emplace(arg...);

				return end()-1;
			}

			value_type elem = *--end();
			iterator iter = end() - 1;

			while (iter != pos)
			{
				*iter = *(iter - 1);
				--iter;
			}

			pointer temp = &(*iter);
			new(temp) value_type(arg...);

			tree->Insert(elem);
			elem_count++;

			return begin() + pos.step();
		}

		[[noreturn]] void erase(const_reference elem)
		{
			if (tree->Search(elem))
			{
				tree->DeleteNode(elem);
				elem_count--;
			}
		}

		_NODISCARD iterator erase(iterator ptr)
		{
			elem_count--;
			return tree->erase(ptr);
		}

		_NODISCARD const_iterator erase(const_iterator ptr)
		{
			elem_count--;
			return tree->erase(ptr);
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
			tree->Destory();
			elem_count = 0;
		}



		_NODISCARD bool empty() const noexcept
		{
			if (elem_count == 0)
				return true;

			return false;
		}

		_NODISCARD int size() const noexcept
		{
			return this->elem_count;
		}

		_NODISCARD size_type max_size() const noexcept
		{
			return size_type(-1) / sizeof(value_type);
		}

		_NODISCARD iterator find(const_reference elem)
		{
			auto pos = begin();
			for (; pos != end(); ++pos)
			{
				if (*pos == elem)
					return pos;
			}

			return pos;
		}

		_NODISCARD const_iterator find(const_reference elem) const
		{
			auto pos = cbegin();
			for (; pos != cend(); ++pos)
			{
				if (*pos == elem)
					return pos;
			}

			return pos;
		}

		_NODISCARD compare key_comp() const noexcept
		{
			return compare;
		}

		[[noreturn]] void swap(self& obj)
		{
			RB_Tree* temp_tree = tree;
			RB_Tree* obj_tree = obj.tree;

			tree = obj_tree;
			obj.tree = temp_tree;

			int temp_count = elem_count;
			elem_count = obj.elem_count;
			obj.elem_count = temp_count;
		}



		_NODISCARD iterator begin() noexcept
		{
			return tree->begin();
		}

		_NODISCARD iterator end() noexcept
		{
			return tree->end();
		}

		_NODISCARD iterator begin() const noexcept
		{
			return tree->begin();
		}

		_NODISCARD iterator end() const noexcept
		{
			return tree->end();
		}

		_NODISCARD const_iterator cbegin() const noexcept
		{
			return tree->cbegin();
		}

		_NODISCARD const_iterator cend() const noexcept
		{
			return tree->cend();
		}

		_NODISCARD reverse_iterator rbegin() noexcept
		{
			return tree->rbegin();
		}

		_NODISCARD reverse_iterator rend() noexcept
		{
			return tree->rend();
		}

		_NODISCARD const_reverse_iterator crbegin() const noexcept
		{
			return tree->crbegin();
		}

		_NODISCARD const_reverse_iterator crend() const noexcept
		{
			return tree->crend();
		}



		self& operator=(const self& obj)
		{
			clear();

			typename set<Ty , alloc>::const_iterator p = obj.cbegin();
			for (; p != obj.cend(); ++p)
			{
				insert((*p));
			}

			return *this;
		}

		template<typename coll>
		_NODISCARD bool operator==(const coll& obj) const noexcept
		{
			if (elem_count != obj.size())
				return false;

			typename coll::const_iterator p1 = obj.cbegin();
			typename set<Ty , alloc>::const_iterator p2 = cbegin();
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
};