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
*/


#pragma once


namespace lib_algo
{

	//equal---------------------------------------------------------

	template<typename t>
	bool equal(const t& obj)
	{
		auto p = obj.cbegin();
		auto elem = *(obj.cbegin());

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
		int begin = p_begin.step();
		int end = p_end.step();
		auto elem = *(p_begin);

		for (int n = begin; n < end; ++n,++p_begin)
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
	t less_compare(t elem1 , t elem2)
	{
		return elem1 < elem2 ? elem1 : elem2;
	}

	//sort by obj
	template<typename t>
	void sort(t& obj , 
			  typename t::TypeValue(*compare)(typename t::TypeValue , typename t::TypeValue) = less_compare) noexcept
	{
		auto p = obj.begin();
		for (; p < obj.end() - 1;)
		{
			auto cur = *p;
			auto ptr = p;
			auto next = *(++p);

			if (compare(next , cur) != cur)
			{
				auto temp = *ptr;
				*ptr = *p;
				*p = temp;
			}
		}
	}

	//sort by iterator range
	template<typename t>
	void sort(t p_begin , t p_end, 
			  typename t::TypeValue(*compare)(typename t::TypeValue , typename t::TypeValue) = less_compare) noexcept
	{
		int begin = p_begin.step();
		int end = p_end.step();

		for (int n = begin; n < end - 1; ++n)
		{
			auto cur = (*p_begin);
			auto ptr = p_begin;
			auto next = *(++p_begin);

			if (compare(next , cur) != cur)
			{
				auto temp = *ptr;
				*ptr = *p_begin;
				*p_begin = temp;
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

		//insert api different
		for (int n = 0; n < arr2_size; ++n)
		{
			obj1.insert(arr2[n]);
		}

		for (int n = 0; n < arr1_size; ++n)
		{
			obj2.insert(arr1[n]);
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

	//--------------------------------------------------------------------
}