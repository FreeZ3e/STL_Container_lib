/*algorithm implemenation
* 
* Copyright(c) 2021 Mashiro -1262159823@qq.com
* 
* This File is part of CONTAINER LIBRARY project.
* 
* version : 1.2.0-alpha
* 
* author : Mashiro
* 
* File name : algorithm.hpp -algorithm part of library.
* 
* This library is free software;you can redistribute is and/or modify it
* under the APACHE LICENSE 2.0 as published by the Free Software Foundation.
* ---------------------------------------------------------------------------
*/

/*--------------------------Functions--------------------------
* 
*bool equal(obj)
*bool equal(obj1,obj2)-------------------------------------support compare between different container.
*bool equal(iterator p_begin,iterator p_end)
* 
*inline void fill(obj,elem)
*inline void fill(iterator p_begin,iterator p_end,elem)
* 
*void sort(obj,compare = less_compare)
*void sort(iterator p_begin,iterator p_end,compare = less_compare)
* 
*inline decltype(auto) find(obj,elem)
*inline decltype(auto) find(iterator p_begin,iterator p_end)
* 
*inline decltype(auto) find_if(obj,pred)
*inline decltype(auto) find_if(obj,pred)
* 
*inline int count(obj,elem)
*inline int count(iterator p_begin,iterator p_end,elem)
* 
*inline int count_if(obj,function)
*inline int count_if(iterator p_begin,iterator p_end,function)
* 
*inline bool search(obj,elem)
*inline bool search(iterator p_begin,iterator p_end,elem)
* 
*void swap(obj1,obj2)---------------------------------------support swap operation between different container.
* 
*inline void reverse(obj)
*inline void reverse(iterator p_begin,iterator p_end)
* 
*decltype(auto) lower_bound(obj,elem)
*decltype(auto) lower_bound(iterator p_begin,iterator p_end,elem)
* 
*decltype(auto) upper_bound(obj,elem)
*decltype(auto) upper_bound(iterator p_begin,iterator p_end,elem)
* 
*inline decltype(auto) min(obj)
*inline decltype(auto) min(iterator p_begin,iterator p_end)
* 
*inline decltype(auto) max(obj)
*inline decltype(auto) max(iterator p_begin,iterator p_end)
* 
*inline void replace(obj,elem)
*inline void replace(iterator p_begin,iterator p_end,elem)
* 
*void unique(obj)
* 
*auto mismatch(obj)
*t(iterator type) mismatch(iterator p_begin,iterator p_end)
* 
*inline void copy(copy_from,obj)
*inline void copy(iterator p_begin,iterator p_end,obj)
* 
*auto adjacent_find(obj)
*auto adjacent_find(iterator p_begin,iterator p_end)
* 
*bool includes(obj1,obj2)
* 
*inline void for_each(obj,function)
*inline void for_each(iterator p_begin,iterator p_end,function)
* 
*inline void remove_if(obj,function)
*/


#pragma once
#include"type_traits.hpp"
using namespace lib_type;

namespace lib_algo
{

	//equal---------------------------------------------------------

	template<typename t>
	bool equal(const t& obj)
	{
		auto p = obj.cbegin();
		auto elem = *p;

		for (; p != obj.cend(); ++p)
		{
			if (*p != elem)
				return false;
		}

		return true;
	}

	template<typename t1,typename t2>
	bool equal(const t1& obj1 , const t2& obj2)
	{
		if (obj1.size() != obj2.size())
			return false;

		auto p1 = obj1.cbegin();
		auto p2 = obj2.cbegin();

		for (; p1 != obj1.cend() , p2 != obj2.cend(); ++p1 , ++p2)
		{
			if (*(p1) != *(p2))
				return false;
		}

		return true;
	}

	template<typename t>
	bool equal(t p_begin , t p_end)
	{
		int step = p_end.step() - p_begin.step();
		auto elem = *(p_begin);

		for (int n = 0; n < step; ++n , ++p_begin)
		{
			if (*(p_begin) != elem)
				return false;
		}

		return true;
	}

	//--------------------------------------------------------------


	//fill----------------------------------------------------------

	template<typename t,typename any>
	inline void fill(t& obj,any elem)
	{
		auto p = obj.begin();
		for (; p != obj.end(); ++p)
		{
			*p = elem;
		}
	}

	template<typename t,typename any>
	inline void fill(t p_begin , t p_end,any elem)
	{
		int step = p_end.step() - p_begin.step();

		for (int n = 0; n < step; ++n , ++p_begin)
		{
			*p_begin = elem;
		}
	}

	//--------------------------------------------------------------


	//sort----------------------------------------------------------
	//sort call insert_sort & quick_sort
	//when sort range less than threshold  -just call insert_sort

	//default sort compare function
	template<typename t>
	static inline t less_compare(t elem1 , t elem2)
	{
		return elem1 < elem2 ? elem1 : elem2;
	}


	//insert_sort
	template<typename t>
	void _insert_sort(t p_begin , t p_end ,
					 typename t::TypeValue(*compare)(typename t::TypeValue , typename t::TypeValue) = less_compare)
	{
		int step = p_end.step() - p_begin.step();
		auto beg = p_begin;
		auto next = p_begin + 1;

		for (int n = 0; n < step - 1; ++n)
		{
			next = p_begin + 1;
			for (auto p = p_begin; p >= beg; --p)
			{
				if (compare(*next , *p) != *p)
				{
					//swap
					auto tmp = *next;
					*next = *p;
					*p = tmp;

					//next reset
					next = p;
				}
			}

			p_begin++;
		}
	}
	
	//quick_sort_helper
	template<typename t,typename value>
	void _quick_sort_less(t& beg , t& end , const value& key)
	{
		while (beg < end)
		{
			while (*end >= key && beg < end)
				--end;
			while (*beg <= key && beg < end)
				++beg;

			if (beg < end)
			{
				auto temp = *beg;
				*beg = *end;
				*end = temp;
			}
		}
	}

	template<typename t,typename value>
	void _quick_sort_max(t& beg , t& end , const value& key)
	{
		while (beg < end)
		{
			while (*end <= key && beg < end)
				--end;
			while (*beg >= key && beg < end)
				++beg;

			if (beg < end)
			{
				auto temp = *beg;
				*beg = *end;
				*end = temp;
			}
		}
	}


	//quick_sort
	template<typename t>
	void _quick_sort(t p_begin , t p_end,
					 typename t::TypeValue(*compare)(typename t::TypeValue , typename t::TypeValue) = less_compare)
	{
		int const threshold = 16;
		if (p_begin >= p_end || p_end.step() - p_begin.step() < threshold)
			return;

		int key = *p_begin;
		auto _beg = p_begin;
		auto _end = p_end - 1;

		if (compare(1 , 2) == 1)
			_quick_sort_less(_beg , _end , key);
		else
			_quick_sort_max(_beg , _end , key);

		*p_begin = *_beg;
		*_beg = key;


		_quick_sort(p_begin , _beg , compare);
		_quick_sort(_beg + 1 , p_end , compare);
	}

	//sort
	template<typename t>
	void sort(t p_begin , t p_end ,
			   typename t::TypeValue(*compare)(typename t::TypeValue , typename t::TypeValue) = less_compare)
	{
		const int threshold = 16;

		if (p_begin != p_end)
		{
			if (p_end.step() - p_begin.step() < threshold)
				_insert_sort(p_begin , p_end , compare);

			else
			{
				_quick_sort(p_begin , p_end , compare);
				_insert_sort(p_begin , p_end , compare);
			}
		}
	}

	template<typename t>
	void sort(t& obj ,
			   typename t::TypeValue(*compare)(typename t::TypeValue , typename t::TypeValue) = less_compare)
	{
		const int threshold = 16;

		if (!obj.empty())
		{
			if (obj.size() < threshold)
				_insert_sort(obj.begin() , obj.end() , compare);
			else
			{
				_quick_sort(obj.begin() , obj.end() , compare);
				_insert_sort(obj.begin() , obj.end() , compare);
			}
		}
	}

	//---------------------------------------------------------------


	//find-----------------------------------------------------------

	//find by obj
	template<typename t,typename any>
	inline decltype(auto) find(const t& obj,any elem) noexcept
	{	
		auto p = obj.cbegin();
		for (;p != obj.cend();++p)
		{
			if (*p == elem)
				return p;
		}

		return p-1;
	}

	//find by iterator range
	template<typename t,typename any>
	inline decltype(auto) find(t p_begin , t p_end , any elem) noexcept
	{
		while (p_begin != p_end)
		{
			if (*p_begin == elem)
				return p_begin;
			
			++p_begin;
		}

		return p_begin-1;
	}

	//-----------------------------------------------------------------


	//find_if----------------------------------------------------------

	template<typename t>
	inline decltype(auto) find_if(const t& obj , bool(*pred)(typename t::TypeValue))
	{
		auto p = obj.cbegin();
		for (; p != obj.cend(); ++p)
		{
			if (pred(*p) == true)
				return p;
		}

		return p - 1;
	}

	template<typename t>
	inline decltype(auto) find_if(t p_begin , t p_end , bool(*pred)(typename t::TypeValue))
	{
		while (p_begin != p_end)
		{
			if (pred(*p_begin) == true)
				return p_begin;

			++p_begin;
		}

		return p_begin - 1;
	}

	//-----------------------------------------------------------------


	//count------------------------------------------------------------

	//count by obj
	template<typename t,typename any>
	inline int count(const t& obj , any elem)
	{
		int count = 0;

		auto p = obj.cbegin();
		for (; p != obj.cend(); ++p)
		{
			if (*p == elem)
				count++;
		}

		return count;
	}

	//count by iterator range
	template<typename t,typename any>
	inline int count(t p_begin , t p_end , any elem)
	{
		int count = 0;

		while (p_begin != p_end)
		{
			if (*p_begin == elem)
				count++;

			++p_begin;
		}

		return count;
	}

	//-----------------------------------------------------------------


	//count_if---------------------------------------------------------

	template<typename t>
	inline int count_if(const t& obj , bool(*function)(typename t::TypeValue))
	{
		int count = 0;

		auto p = obj.cbegin();
		for (; p != obj.cend(); ++p)
		{
			if (function(*p) == true)
				++count;
		}

		return count;
	}

	template<typename t>
	inline int count_if(t p_begin , t p_end , bool(*function)(typename t::TypeValue))
	{
		int count = 0;
		int step = p_end.step() - p_begin.step();

		for (int n = 0; n < step; ++n)
		{
			if (function(*p_begin) == true)
				++count;

			++p_begin;
		}

		return count;
	}

	//-----------------------------------------------------------------


	//search-----------------------------------------------------------

	template<typename t,typename any>
	inline bool search(const t& obj , any elem)
	{
		auto p = obj.cbegin();
		for (; p != obj.cend(); ++p)
		{
			if (*p == elem)
				return true;
		}

		return false;
	}

	template<typename t,typename any>
	inline bool search(t p_begin , t p_end , any elem)
	{
		while (p_begin != p_end)
		{
			if (*p_begin == elem)
				return true;

			++p_begin;
		}

		return false;
	}

	//-----------------------------------------------------------------


	//swap-------------------------------------------------------------

	//inside functions

	template<typename t1,typename t2>//not pod type
	void __swap(t1& obj1 , t2& obj2,false_type_tag)
	{
		int arr1_size = obj1.size();
		int arr2_size = obj2.size();

		typename t1::TypeValue* arr1 = new typename t1::TypeValue[arr1_size];
		typename t2::TypeValue* arr2 = new typename t2::TypeValue[arr2_size];


		int count = 0;
		for (auto p : obj1)
		{
			arr1[count++] = p;
		}count = 0;

		for (auto p : obj2)
		{
			arr2[count++] = p;
		}


		obj1.clear();
		obj2.clear();

		int n = 0;
		while (1)
		{
			if (n < arr2_size)
				obj1.insert(arr2[n]);

			if (n < arr1_size)
				obj2.insert(arr1[n]);

			if (n >= arr1_size && n >= arr2_size)
				break;

			n++;
		}
	}

	template<typename t1,typename t2>//is pod type
	inline void __swap(t1& obj1 , t2& obj2 , true_type_tag)
	{
		auto temp = obj1;
		obj1 = (t1)obj2;
		obj2 = (t2)temp;
	}

	template<typename t>
	inline void __swap(t& obj1 , t& obj2,false_type_tag)
	{
		obj1.swap(obj2);
	}

	template<typename t>
	inline void __swap(t& obj1 , t& obj2 , true_type_tag)
	{
		t temp = obj1;
		obj1 = obj2;
		obj2 = temp;
	}


	//warrper

	template<typename t1 , typename t2>
	inline void swap(t1& obj1 , t2& obj2)
	{
		typename is_pod<t1>::type type_tag;
		__swap(obj1 , obj2 , type_tag);
	}

	template<typename t>
	inline void swap(t& obj1 , t& obj2)
	{
		typename is_pod<t>::type type_tag;
		__swap(obj1 , obj2 , type_tag);
	}

	//-----------------------------------------------------------------


	//reverse----------------------------------------------------------

	template<typename t>
	inline void reverse(t& obj)
	{
		auto p_begin = obj.begin();
		auto p_end = obj.end()-1;
		int step = obj.end().step() / 2;

		for (int n = 0; n < step; ++n)
		{
			auto temp = *(p_end);

			*(p_end--) = *(p_begin);
			*(p_begin++) = temp;
		}
		
	}

	template<typename t>
	inline void reverse(t p_begin , t p_end)
	{
		int step = (p_end.step() - p_begin.step()) / 2;
		p_end--;

		for (int n = 0 ; n < step; ++n)
		{
			auto temp = *(p_end);

			*(p_end--) = *(p_begin);
			*(p_begin++) = temp;
		}
	}

	//-----------------------------------------------------------------


	//min--------------------------------------------------------------

	template<typename t>
	inline decltype(auto) min(const t& obj)
	{
		auto p = obj.cbegin();
		auto res = *(obj.cbegin());

		for (; p != obj.cend(); ++p)
		{
			if ((*p) < res)
			{
				res = (*p);
			}
		}

		return res;
	}

	template<typename t>
	inline decltype(auto) min(t p_begin , t p_end)
	{
		auto res = *(p_begin);
		int step = p_end.step() - p_begin.step();

		for (int n = 0; n < step; ++n,++p_begin)
		{
			if (*(p_begin) < res)
			{
				res = *(p_begin);
			}
		}

		return res;
	}

	//-----------------------------------------------------------------


	//max--------------------------------------------------------------

	template<typename t>
	inline decltype(auto) max(const t& obj)
	{
		auto p = obj.cbegin();
		auto res = *(obj.cbegin());

		for (; p != obj.cend(); ++p)
		{
			if ((*p) > res)
			{
				res = (*p);
			}
		}

		return res;
	}

	template<typename t>
	inline decltype(auto) max(t p_begin , t p_end)
	{
		auto res = *(p_begin);
		int step = p_end.step() - p_begin.step();

		for (int n = 0; n < step; ++n , ++p_begin)
		{
			if (*(p_begin) > res)
			{
				res = *(p_begin);
			}
		}

		return res;
	}

	//------------------------------------------------------------------


	//lower_bound-------------------------------------------------------

	template<typename t,typename any>
	decltype(auto) lower_bound(const t& obj , any elem)
	{
		auto min_val = min(obj);

		if (min_val >= elem)
		{
			return elem;
		}
		else
		{
			auto count = elem - 1;

			while (!search(obj , count))
			{
				count--;
				if (count < min_val)
					break;
			}

			if (count > min_val)
				return count;
		}
	}

	template<typename t,typename any>
	decltype(auto) lower_bound(t p_begin , t p_end , any elem)
	{
		auto min_val = min(p_begin , p_end);

		if (min_val >= elem)
		{
			return elem;
		}
		else
		{
			auto count = elem - 1;

			while (!search(p_begin , p_end , elem))
			{
				count--;
				if (count < min_val)
					break;
			}

			if (count > min_val)
				return count;
		}
	}

	//------------------------------------------------------------------


	//upper_bound-------------------------------------------------------

	template<typename t,typename any>
	decltype(auto) upper_bound(const t& obj , any elem)
	{
		auto max_val = max(obj);

		if (max_val <= elem)
		{
			return elem;
		}
		else
		{
			auto count = elem + 1;

			while (!search(obj , count))
			{
				count++;
				if (count > max_val)
					break;
			}

			if (count < max_val)
				return count;
		}
	}

	template<typename t,typename any>
	decltype(auto) upper_bound(t p_begin , t p_end , any elem)
	{
		auto max_val = max(p_begin , p_end);

		if (max_val <= elem)
		{
			return elem;
		}
		else
		{
			auto count = elem + 1;

			while (!search(p_begin , p_end , elem))
			{
				count++;
				if (count > max_val)
					break;
			}

			if (count < max_val)
				return count;
		}
	}

	//------------------------------------------------------------------


	//replace-----------------------------------------------------------

	template<typename t,typename any>
	inline void replace(t& obj , any elem)
	{
		auto p = obj.begin();

		for (; p != obj.end(); ++p)
		{
			*p = elem;
		}
	}

	template<typename t,typename any>
	inline void replace(t p_begin , t p_end , any elem)
	{
		int step = p_end.step() - p_begin.step();

		for (int n = 0; n < step; ++n)
		{
			*p_begin = elem;
			++p_begin;
		}
	}

	//------------------------------------------------------------------


	//unique------------------------------------------------------------

	template<typename t>
	void unique(t& obj)
	{
		typename t::TypeValue* arr = new typename t::TypeValue[obj.size()];
		int count = 0;

		for (auto p : obj)
		{
			bool tag = false;
			for (int n = 0; n < count; ++n)
			{
				if (p == arr[n])
					tag = true;
			}

			if (tag == false)
				arr[count++] = p;
		}

		obj.clear();

		for (int n = 0; n < count; ++n)
		{
			obj.insert(arr[n]);
		}
	}


	//------------------------------------------------------------------


	//mismatch----------------------------------------------------------
	//return first position where two ranges differ

	template<typename t>
	auto mismatch(const t& obj)
	{
		auto p = obj.cbegin();

		for (; p != obj.cend();)
		{
			auto cur = (*p);
			auto ptr = p;
			auto next = *(++p);

			if (cur != next)
			{
				return ptr;
			}
		}
	}

	template<typename t>
	t mismatch(t p_begin,t p_end)
	{
		int step = p_end.step() - p_begin.step();

		for (int n = 0; n < step; ++n)
		{
			auto cur = (*p_begin);
			auto ptr = p_begin;
			auto next = *(++p_begin);

			if (cur != next)
			{
				return ptr;
			}
		}
	}

	//------------------------------------------------------------------


	//copy--------------------------------------------------------------

	//copy_from --> obj
	template<typename t1,typename t2>
	void copy(const t1& copy_from , t2& obj)
	{
		auto p = copy_from.cbegin();
		obj.clear();

		for (; p != copy_from.cend(); ++p)
		{
			obj.insert(*p);
		}
	}

	//copy elem in range to obj
	template<typename t1,typename t2>
	void copy(t1 p_begin , t1 p_end , t2& obj)
	{
		int step = p_end.step() - p_begin.step();
		obj.clear();

		for (int n = 0; n < step; ++n)
		{
			obj.insert(*(p_begin++));
		}
	}

	//------------------------------------------------------------------


	//adjacent_find-----------------------------------------------------
	//find equal adjacent elements in range.

	template<typename t>
	auto adjacent_find(const t& obj)
	{
		auto p = obj.cbegin();

		for (; p != obj.cend();)
		{
			auto cur = *p;
			auto next = *(++p);

			if (cur == next)
			{
				return cur;
			}
		}
	}

	template<typename t>
	auto adjacent_find(t p_begin , t p_end)
	{
		int step = p_end.step() - p_begin.step();

		for (int n = 0; n < step; ++n)
		{
			auto cur = *p_begin;
			auto next = *(++p_begin);

			if (cur == next)
			{
				return cur;
			}
		}
	}

	//------------------------------------------------------------------


	//includes----------------------------------------------------------
	//if obj1 includes obj2,return true.

	template<typename t1,typename t2>
	bool includes(const t1& obj1 , const t2& obj2)
	{
		auto p = obj2.cbegin();

		for (; p != obj2.cend(); ++p)
		{
			if (search(obj1 , *p) == false)
			{
				return false;
			}
		}

		return true;
	}

	//------------------------------------------------------------------


	//for_each----------------------------------------------------------

	template<typename t>
	inline void for_each(t& obj , void(*function)(typename t::TypeValue))
	{
		auto p = obj.begin();

		for (; p != obj.end(); ++p)
		{
			function(*p);
		}
	}

	template<typename t>
	inline void for_each(t& obj , typename t::TypeValue(*function)(typename t::TypeValue))
	{
		auto p = obj.begin();

		for (; p != obj.end(); ++p)
		{
			*p = function(*p);
		}
	}

	template<typename t>
	inline void for_each(t& p_begin , t& p_end , void(*function)(typename t::TypeValue))
	{
		int step = p_end.step() - p_begin.step();

		for (int n = 0; n < step; ++n,++p_begin)
		{
			function(*p_begin);
		}
	}

	template<typename t>
	inline void for_each(t p_begin , t p_end , typename t::TypeValue(*function)(typename t::TypeValue))
	{
		int step = p_end.step() - p_begin.step();

		for (int n = 0; n < step; ++n , ++p_begin)
		{
			*p_begin = function(*p_begin);
		}
	}

	//------------------------------------------------------------------


	//remove_if---------------------------------------------------------

	template<typename t>
	inline void remove_if(t& obj , bool(*function)(typename t::TypeValue))
	{
		auto p = obj.begin();
		for (; p != obj.end();)
		{
			if (function(*p) == true)
				p = obj.erase(p);
			else
				++p;
		}
	}

	//------------------------------------------------------------------
}