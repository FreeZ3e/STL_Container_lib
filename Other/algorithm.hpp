/*algorithm implemenation
* 
* Copyright(c) 2021 Mashiro -1262159823@qq.com
* 
* This File is part of CONTAINER LIBRARY project.
* 
* version : 1.1.2-alpha
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
*inline int count(obj,elem)
*inline int count(iterator p_begin,iterator p_end,elem)
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
*/


#pragma once


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

	//default sort compare function
	template<typename t>
	inline t less_compare(t elem1 , t elem2)
	{
		return elem1 < elem2 ? elem1 : elem2;
	}

	//sort by obj
	template<typename t>
	void sort(t& obj , 
			  typename t::TypeValue(*compare)(typename t::TypeValue , typename t::TypeValue) = less_compare) noexcept
	{
		auto p = obj.begin();
		for (; p < obj.end() - 1;++p)//bubble sort
		{
			for (auto p1 = obj.begin(); p1 < obj.end() - p.step()-1;)
			{
				auto cur = *p1;
				auto ptr = p1;
				auto next = *(++p1);

				if (compare(next,cur) != cur)//compare function
				{
					auto temp = *ptr;
					*ptr = *p1;
					*p1 = temp;
				}
			}
		}
	}

	//sort by iterator range
	template<typename t>
	void sort(t p_begin , t p_end, 
			  typename t::TypeValue(*compare)(typename t::TypeValue , typename t::TypeValue) = less_compare) noexcept
	{
		int step = p_end.step() - p_begin.step();
		auto begin_save = p_begin;

		for (int n = 0; n < step - 1; ++n)//bubble sort
		{
			p_begin = begin_save;
			for (int i = 0; i < step - 1 - n; ++i)
			{
				auto cur = *p_begin;
				auto ptr = p_begin;
				auto next = *(++p_begin);

				if (compare(next , cur) != cur)//compare function
				{
					auto temp = *ptr;
					*ptr = *p_begin;
					*p_begin = temp;
				}
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

	template<typename t1,typename t2>
	void swap(t1& obj1 , t2& obj2)
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
	inline void copy(const t1& copy_from, t2& obj)
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
	inline void copy(t1 p_begin , t1 p_end , t2& obj)
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
	inline void for_each(t& obj ,
				  typename t::TypeValue(*function)(typename t::TypeValue))
	{
		auto p = obj.begin();

		for (; p != obj.end(); ++p)
		{
			*p = function(*p);
		}
	}

	template<typename t>
	inline void for_each(t p_begin , t p_end ,
				  typename t::TypeValue(*function)(typename t::TypeValue))
	{
		int step = p_end.step() - p_begin.step();

		for (int n = 0; n < step; ++n,++p_begin)
		{
			*p_begin = function(*p_begin);
		}
	}

	//------------------------------------------------------------------
}