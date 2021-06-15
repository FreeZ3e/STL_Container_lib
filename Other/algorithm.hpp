/*algorithm implemenation
* 
* Copyright(c) 2021 Mashiro -1262159823@qq.com
* 
* This File is part of CONTAINER LIBRARY project.
* 
* version : 1.3.0-alpha
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
*iterator search_n(obj,elem,n)
*iterator search_n(iterator p_begin,iterator p_end,elem,n)
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
*inline decltype(auto) min_element(obj)
*inline decltype(auto) min_element(iterator p_begin,iterator p_end)
*
*inline decltype(auto) max_element(obj)
*inline decltype(auto) max_element(iterator p_begin,iterator p_end)
* 
*inline t min(obj1,obj2)
*inline t min(obj1,obj2,comp)
* 
*inline t max(obj1,obj2)
*inline t max(obj1,obj2,comp)
* 
*inline void replace(obj,elem)
*inline void replace(iterator p_begin,iterator p_end,elem)
* 
*void unique(obj)
* 
*auto mismatch_element(obj)
*t(iterator type) mismatch_element(iterator p_begin,iterator p_end)
* 
*iterator mismatch(obj1,obj2)
*iterator mismatch(iterator p_begin1,iterator p_end1,iterator p_begin2,iterator p_end2)
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
* 
*iterator merge(obj1,obj2,result)
*iterator merge(iterator p_begin1,iterator p_end2,iterator p_begin2,iterator p_end2,result)
*/


#pragma once
#include"type_traits.hpp"
using namespace lib_type;

namespace lib_algo
{

	//equal---------------------------------------------------------

	template<typename t>
	_NODISCARD bool equal(const t& obj) noexcept
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
	_NODISCARD bool equal(const t1& obj1 , const t2& obj2) noexcept
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
	_NODISCARD bool equal(t p_begin , t p_end) noexcept
	{
		auto elem = *(p_begin);

		for (;p_begin < p_end; ++p_begin)
		{
			if (*(p_begin) != elem)
				return false;
		}

		return true;
	}

	//--------------------------------------------------------------


	//fill----------------------------------------------------------

	template<typename t,typename any>
	inline void fill(t& obj,any elem) noexcept
	{
		auto p = obj.begin();
		for (; p != obj.end(); ++p)
		{
			*p = elem;
		}
	}

	template<typename t,typename any>
	inline void fill(t p_begin , t p_end,any elem) noexcept
	{
		int step = p_end.step() - p_begin.step();

		for (int n = 0; n < step; ++n , ++p_begin)
		{
			*p_begin = elem;
		}
	}

	//--------------------------------------------------------------


	//sort----------------------------------------------------------
	//sort call insert_sort , quick_sort & heap_sort
	//when sort range less than threshold  -just call insert_sort
	//when depth_limit == 0 - return to heap_sort

	//default sort compare function
	template<typename t>
	static inline t less_compare(t elem1 , t elem2) noexcept
	{
		return elem1 < elem2 ? elem1 : elem2;
	}



	template<typename t>
	void _PercolateDown(t p_begin , int index , int size) noexcept
	{
		int min = 0;

		while (index * 2 + 1 < size)
		{
			min = index * 2 + 1;

			if (index * 2 + 2 < size)
			{
				if (*(p_begin + min) > *(p_begin + (index * 2 + 2)))
					min = index * 2 + 2;
			}

			if (*(p_begin + index) < *(p_begin + min))
				break;
			else
			{
				auto temp = *(p_begin + index);
				*(p_begin + index) = *(p_begin + min);
				*(p_begin + min) = temp;

				index = min;
			}
		}
	}

	template<typename t>
	void _PercolateUp(t p_begin, int index , int size) noexcept
	{
		int max = 0;

		while (index * 2 + 1 < size)
		{
			max = index * 2 + 1;

			if (index * 2 + 2 < size)
			{
				if(*(p_begin+max) < *(p_begin+(index * 2 + 2)))
				   max = index * 2 + 2;
			}

			if(*(p_begin + index) > *(p_begin + max))
				break;
			else
			{
				auto temp = *(p_begin + index);
				*(p_begin + index) = *(p_begin + max);
				*(p_begin + max) = temp;

				index = max;
			}
		}
	}

	template<typename t>
	void _heap_built(t p_begin , t p_end,
					 typename t::TypeValue(*compare)(typename t::TypeValue , typename t::TypeValue) = less_compare) noexcept
	{
		for (int n = (p_end.step() - p_begin.step()) / 2 - 1; n >= 0; --n)
		{
			if(compare(1,2) == 1)
				_PercolateUp(p_begin , n , p_end.step() - p_begin.step());
			else
				_PercolateDown(p_begin , n , p_end.step() - p_begin.step());
		}
	}

	//heap_sort
	template<typename t>
	void _heap_sort(t p_begin , t p_end,
				   typename t::TypeValue(*compare)(typename t::TypeValue , typename t::TypeValue) = less_compare) noexcept
	{
		int size = p_end.step() - p_begin.step();
		_heap_built(p_begin,p_end,compare);

		auto beg = p_begin;
		auto cur = p_end - 1;
		for (int n = size - 1; n >= 1; --n)
		{
			auto temp = *beg;
			*beg = *cur;
			*cur = temp;

			--cur;
			--size;

			if (compare(1 , 2) == 1)
				_PercolateUp(p_begin , 0 , size);
			else
				_PercolateDown(p_begin , 0 , size);
		}
	}
	

	//insert sort
	template<typename t>
	void _insert_sort(t p_begin , t p_end ,
					  typename t::TypeValue(*compare)(typename t::TypeValue , typename t::TypeValue) = less_compare) noexcept
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
	void _quick_sort_less(t& beg , t& end , const value& key) noexcept
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
	void _quick_sort_max(t& beg , t& end , const value& key) noexcept
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


	//median3 pivot
	template<typename t>
	auto _median3(t p_begin , t p_end) noexcept	//retrun pivot value of container
	{
		int middle = (p_end.step() - p_begin.step()) / 2;	//middle point

		//keep left val min
		if (*p_begin > *p_end)
		{
			auto temp = *p_begin;
			*p_begin = *p_end;
			*p_end = temp;
		}
		if (*(p_begin + middle) > *p_end)
		{
			auto temp = *(p_begin + middle);
			*(p_begin + middle) = *p_end;
			*p_end = temp;
		}
		if (*(p_begin + middle) > *p_begin)
		{
			auto temp = *(p_begin + middle);
			*(p_begin + middle) = *p_begin;
			*p_begin = temp;
		}

		return *p_end;
	}

	template<typename t>
	auto _median3_max(t p_begin , t p_end) noexcept	//retrun pivot value of container
	{
		int middle = (p_end.step() - p_begin.step()) / 2;	//middle point

		//keep left val min
		if (*p_begin < *p_end)
		{
			auto temp = *p_begin;
			*p_begin = *p_end;
			*p_end = temp;
		}
		if (*(p_begin + middle) < *p_end)
		{
			auto temp = *(p_begin + middle);
			*(p_begin + middle) = *p_end;
			*p_end = temp;
		}
		if (*(p_begin + middle) < *p_begin)
		{
			auto temp = *(p_begin + middle);
			*(p_begin + middle) = *p_begin;
			*p_begin = temp;
		}

		return *p_end;
	}

	//quick_sort
	template<typename t>
	void _quick_sort(t p_begin , t p_end , int depth_limit , 
					 typename t::TypeValue(*compare)(typename t::TypeValue , typename t::TypeValue) = less_compare) noexcept
	{
		if (p_end.step() - p_begin.step() <= 32)	//threshold = 32
		{
			_insert_sort(p_begin , p_end , compare);	//trun to insert sort
			return;
		}


		if (depth_limit <= 0)		//if too many divisions
		{
			_heap_sort(p_begin , p_end , compare);		//trun to heap sort
			return;
		}

		depth_limit = (depth_limit >> 1) + (depth_limit >> 2);	//allow 1.5 log2(N) divisions
		
		auto key = *p_begin;	//find pivot by median3
		if (compare(1 , 2) == 1)
			key = _median3(p_begin , p_end - 1);
		else
			key = _median3_max(p_begin , p_end - 1);

		auto _beg = p_begin;
		auto _end = p_end-1;


		if (compare(1 , 2) == 1)
			_quick_sort_less(_beg , _end , key);
		else
			_quick_sort_max(_beg , _end , key);


		*p_begin = *_beg;
		*_beg = key;


		auto middle = _beg;
		if (middle.step() != -1)
		{
			_quick_sort(p_begin , middle - 1 , depth_limit , compare);	//into left loop
			_quick_sort(middle + 1 , p_end , depth_limit , compare);	//into right loop
		}
	}


	//quick sort depth limit
	inline int limit(int n) noexcept
	{ 
		int res = 0;
		for (; n > 1; n >>= 1)
			++res;

		return res;
	}


	//sort
	template<typename t>
	void sort(t p_begin , t p_end ,
			   typename t::TypeValue(*compare)(typename t::TypeValue , typename t::TypeValue) = less_compare) noexcept
	{
		if (p_begin != p_end)
		{
			if (p_end.step() - p_begin.step() < 32)		//threshold = 32
				_insert_sort(p_begin , p_end, compare);

			else
			{
				_quick_sort(p_begin , p_end, limit(p_end.step() - p_begin.step()) * 2 , compare);
			}
		}
	}

	template<typename t>
	void sort(t& obj ,
			   typename t::TypeValue(*compare)(typename t::TypeValue , typename t::TypeValue) = less_compare) noexcept
	{
		if (!obj.empty())
		{
			if (obj.size() < 32)		//threshold = 32
				_insert_sort(obj.begin() , obj.end() , compare);
			else
			{
				_quick_sort(obj.begin() , obj.end() , limit(obj.size()) * 2 , compare);
			}
		}
	}

	//---------------------------------------------------------------


	//find-----------------------------------------------------------

	//find by obj
	template<typename t,typename any>
	_NODISCARD inline decltype(auto) find(const t& obj,any elem) noexcept
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
	_NODISCARD inline decltype(auto) find(t p_begin , t p_end , any elem) noexcept
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
	_NODISCARD inline decltype(auto) find_if(const t& obj , bool(*pred)(typename t::TypeValue)) noexcept
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
	_NODISCARD inline decltype(auto) find_if(t p_begin , t p_end , bool(*pred)(typename t::TypeValue)) noexcept
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
	_NODISCARD inline int count(const t& obj , any elem) noexcept
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
	_NODISCARD inline int count(t p_begin , t p_end , any elem) noexcept
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
	_NODISCARD inline int count_if(const t& obj , bool(*function)(typename t::TypeValue)) noexcept
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
	_NODISCARD inline int count_if(t p_begin , t p_end , bool(*function)(typename t::TypeValue)) noexcept
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
	_NODISCARD inline bool search(const t& obj , any elem) noexcept
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
	_NODISCARD inline bool search(t p_begin , t p_end , any elem) noexcept
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


	//search_n---------------------------------------------------------

	template<typename t,typename arg>
	_NODISCARD auto search_n(const t& obj , const arg& elem , int n) noexcept
	{
		if (n <= 0)
			return obj.cbegin();

		auto first = find(obj,elem);

		while(first != obj.cend())
		{
			int count = n - 1;
			auto i = first;
			++i;

			while (i != obj.cend() && count != 0 && *i == elem)
			{
				++i;
				--count;
			}

			if (count == 0)
				return first;
			else
				first = find(i , obj.cend() , elem);
		}

		return obj.cend() - 1;
	}

	template<typename t,typename arg>
	_NODISCARD auto search_n(t p_begin , t p_end , const arg& elem , int n) noexcept
	{
		if (n <= 0)
			return p_begin;

		auto first = find(p_begin , p_end , elem);

		while (p_begin != p_end)
		{
			int count = n - 1;
			auto i = first;
			++i;

			while (i != p_end && count != 0 && *i == elem)
			{
				++i;
				--count;
			}

			if (count == 0)
				return first;
			else
				first = find(i , p_end , elem);
		}

		return p_end - 1;
	}

	//-----------------------------------------------------------------


	//swap-------------------------------------------------------------

	//inside functions

	template<typename t1,typename t2>//not pod type
	void __swap(t1& obj1 , t2& obj2,false_type_tag) noexcept
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
	inline void __swap(t1& obj1 , t2& obj2 , true_type_tag) noexcept
	{
		auto temp = obj1;
		obj1 = (t1)obj2;
		obj2 = (t2)temp;
	}

	template<typename t>//swap of container
	inline void __swap(t& obj1 , t& obj2,false_type_tag) noexcept
	{
		obj1.swap(obj2);
	}

	template<typename t>
	inline void __swap(t& obj1 , t& obj2 , true_type_tag) noexcept
	{
		t temp = obj1;
		obj1 = obj2;
		obj2 = temp;
	}


	//warrper

	template<typename t1 , typename t2>
	inline void swap(t1& obj1 , t2& obj2) noexcept
	{
		typename is_pod<t1>::type type_tag;
		__swap(obj1 , obj2 , type_tag);
	}

	template<typename t>
	inline void swap(t& obj1 , t& obj2) noexcept
	{
		typename is_pod<t>::type type_tag;
		__swap(obj1 , obj2 , type_tag);
	}

	//-----------------------------------------------------------------


	//reverse----------------------------------------------------------

	template<typename t>
	inline void reverse(t& obj) noexcept
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
	inline void reverse(t p_begin , t p_end) noexcept
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
	_NODISCARD inline decltype(auto) min_element(const t& obj) noexcept
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
	_NODISCARD inline decltype(auto) min_element(t p_begin , t p_end) noexcept
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
	_NODISCARD inline decltype(auto) max_element(const t& obj) noexcept
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
	_NODISCARD inline decltype(auto) max_element(t p_begin , t p_end) noexcept
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


	//max---------------------------------------------------------------

	template<typename t>
	_NODISCARD inline const t& max(const t& obj1 , const t& obj2) noexcept
	{
		return obj1 > obj2 ? obj1 : obj2;
	}

	template<typename t,typename compare>
	_NODISCARD inline const t& max(const t& obj1 , const t& obj2 , compare comp) noexcept
	{
		return comp(obj1 , obj2) ? obj1 : obj2;
	}

	//------------------------------------------------------------------


	//min---------------------------------------------------------------

	template<typename t>
	_NODISCARD inline const t& min(const t& obj1 , const t& obj2) noexcept
	{
		return obj1 < obj2 ? obj1 : obj2;
	}

	template<typename t,typename compare>
	_NODISCARD inline const t& min(const t& obj1 , const t& obj2 , compare comp) noexcept
	{
		return comp(obj1 , obj2) ? obj1 : obj2;
	}

	//------------------------------------------------------------------

	//lower_bound-------------------------------------------------------

	template<typename t,typename any>
	_NODISCARD decltype(auto) lower_bound(const t& obj , any elem) noexcept
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
	_NODISCARD decltype(auto) lower_bound(t p_begin , t p_end , any elem) noexcept
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
	_NODISCARD decltype(auto) upper_bound(const t& obj , any elem) noexcept
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
	_NODISCARD decltype(auto) upper_bound(t p_begin , t p_end , any elem) noexcept
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
	inline void replace(t& obj , any elem) noexcept
	{
		auto p = obj.begin();

		for (; p != obj.end(); ++p)
		{
			*p = elem;
		}
	}

	template<typename t,typename any>
	inline void replace(t p_begin , t p_end , any elem) noexcept
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
	void unique(t& obj) noexcept
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


	//mismatch_element----------------------------------------------------------
	//return first diff elem iterator position in same container

	template<typename t>
	_NODISCARD auto mismatch_element(const t& obj) noexcept
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
	_NODISCARD t mismatch_element(t p_begin,t p_end) noexcept
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


	//mismatch----------------------------------------------------------
	//return first diff elem between two different containers

	template<typename t1,typename t2>
	_NODISCARD auto mismatch(const t1& obj1 , const t2& obj2)  noexcept	//obj1:greater range  obj2:less range
	{																	//return less range container's iterator
		auto p1 = obj1.cbegin();
		auto p2 = obj2.cbegin();

		for (; p1 != obj1.cend() , p2 != obj2.cend(); ++p1 , ++p2)
		{
			if (*p1 != *p2)
				return p2;
		}

		return p2;
	}

	template<typename t1,typename t2>
	_NODISCARD auto mismatch(t1 p_begin1 , t1 p_end1,			// greater range
							t2 p_begin2 , t2 p_end2)  noexcept	// less range
	{
		for (; p_begin1 != p_end1 , p_begin2 != p_end2; ++p_begin1 , ++p_begin2)
		{
			if (*p_begin1 != *p_begin2)
				return p_begin2;
		}

		return p_begin2;
	}

	//------------------------------------------------------------------


	//copy--------------------------------------------------------------


	template<typename t1,typename t2>
	void _range_greater(t1 p_begin , t1 p_end , t2& obj) noexcept
	{
		for (auto p = obj.begin(); p != obj.end(); ++p,++p_begin)
		{
			*p = *p_begin;
		}

		while (p_begin != p_end)
		{
			obj.insert(*p_begin);
			++p_begin;
		}
	}

	template<typename t1,typename t2>
	inline void _range_equal(t1 p_begin , t1 p_end , t2& obj) noexcept
	{
		for (auto p = obj.begin(); p != obj.end(),p_begin != p_end; ++p , ++p_begin)
		{
			*p = *p_begin;
		}
	}

	template<typename t1,typename t2>
	inline void _range_less(t1 p_begin , t1 p_end , t2& obj) noexcept
	{
		obj.clear();

		while (p_begin != p_end)
		{
			obj.insert(*(p_begin++));
		}
	}



	template<typename t1,typename t2>
	inline void copy(t1 p_begin , t1 p_end , t2& obj) noexcept
	{
		if (p_end.step() - p_begin.step() == obj.size())
			_range_equal(p_begin , p_end , obj);
		else if (p_end.step() - p_begin.step() > obj.size())
			_range_greater(p_begin , p_end , obj);
		else
			_range_less(p_begin , p_end , obj);
	}

	//not pod type
	template<typename t1,typename t2>
	inline void _copy(const t1& copy_from , t2& obj , false_type_tag) noexcept
	{
		if (copy_from.size() == obj.size())
			_range_equal(copy_from.cbegin() , copy_from.cend() , obj);
		else if (copy_from.size() > obj.size())
			_range_greater(copy_from.cbegin() , copy_from.cend() , obj);
		else
			_range_less(copy_from.cbegin() , copy_from.cend() , obj);
	}

	//is pod type
	template<typename t1,typename t2>
	inline void _copy(const t1& copy_from , t2& obj , true_type_tag) noexcept
	{
		obj = (t2)copy_from;
	}

	template<typename t1,typename t2>
	inline void copy(const t1& copy_from , t2& obj) noexcept
	{
		typename is_pod<t1>::type type_tag;
		_copy(copy_from , obj , type_tag);
	}

	//------------------------------------------------------------------


	//adjacent_find-----------------------------------------------------
	//find equal adjacent elements in range.

	template<typename t>
	_NODISCARD auto adjacent_find(const t& obj) noexcept
	{
		auto p = obj.cbegin();

		for (; p != obj.cend();)
		{
			auto cur = *p;
			auto next = *(++p);

			if (cur == next)
			{
				return p;
			}
		}
	}

	template<typename t>
	_NODISCARD auto adjacent_find(t p_begin , t p_end) noexcept
	{
		int step = p_end.step() - p_begin.step();

		for (int n = 0; n < step; ++n)
		{
			auto cur = *p_begin;
			auto next = *(++p_begin);

			if (cur == next)
			{
				return p_begin;
			}
		}
	}

	//------------------------------------------------------------------


	//includes----------------------------------------------------------
	//if obj1 includes obj2,return true.

	template<typename t1,typename t2>
	_NODISCARD bool includes(const t1& obj1 , const t2& obj2) noexcept	//obj1 : greater range  obj2 : less range
	{
		if (obj1.size() < obj2.size())
			return false;

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
	inline void for_each(t& obj , void(*function)(typename t::TypeValue)) noexcept
	{
		auto p = obj.begin();

		for (; p != obj.end(); ++p)
		{
			function(*p);
		}
	}

	template<typename t>
	inline void for_each(t& obj , typename t::TypeValue(*function)(typename t::TypeValue)) noexcept
	{
		auto p = obj.begin();

		for (; p != obj.end(); ++p)
		{
			*p = function(*p);
		}
	}

	template<typename t>
	inline void for_each(t& p_begin , t& p_end , void(*function)(typename t::TypeValue)) noexcept
	{
		int step = p_end.step() - p_begin.step();

		for (int n = 0; n < step; ++n,++p_begin)
		{
			function(*p_begin);
		}
	}

	template<typename t>
	inline void for_each(t p_begin , t p_end , typename t::TypeValue(*function)(typename t::TypeValue)) noexcept
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
	inline void remove_if(t& obj , bool(*function)(typename t::TypeValue)) noexcept
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


	//merge-------------------------------------------------------------
	//support different type containers

	template<typename t1,typename t2,typename t3>
	_NODISCARD auto merge(const t1& obj1 , const t2& obj2 , t3& result) noexcept
	{
		auto p1 = obj1.cbegin();
		auto p2 = obj2.cbegin();
		
		while (p1 != obj1.cend() && p2 != obj2.cend())
		{
			if (*p1 < *p2)
			{
				result.insert(*p1);
				++p1;
			}
			else
			{
				result.insert(*p2);
				++p2;
			}
		}

		if (p1 != obj1.cend())
		{
			while (p1 != obj1.cend())
			{
				result.insert(*p1);
				++p1;
			}
		}
		if (p2 != obj2.cend())
		{
			while (p2 != obj2.cend())
			{
				result.insert(*p2);
				++p2;
			}
		}

		return result.begin();
	}

	
	template<typename t1,typename t2,typename t3>
	_NODISCARD auto merge(t1 p_begin1 , t1 p_end1 ,
			   t2 p_begin2 , t2 p_end2 , t3& result) noexcept
	{
		while (p_begin1 != p_end1 && p_begin2 != p_end2)
		{
			if (*p_begin1 < *p_begin2)
			{
				result.insert(*p_begin1);
				++p_begin1;
			}
			else
			{
				result.insert(*p_begin2);
				++p_begin2;
			}
		}

		if (p_begin1 != p_end1)
		{
			while (p_begin1 != p_end1)
			{
				result.insert(*p_begin1);
				++p_begin1;
			}
		}
		if (p_begin2 != p_end2)
		{
			while (p_begin2 != p_end2)
			{
				result.insert(*p_begin2);
				++p_begin2;
			}
		}

		return result.begin();
	}

	//------------------------------------------------------------------
}