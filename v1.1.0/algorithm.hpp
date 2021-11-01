/* algorithm implementation
 *
 * Copyright(c) 2021 Mashiro -1262159823@qq.com
 *
 * This File is part of CONTAINER LIBRARY project.
 *
 * version : 1.1.0
 *
 * author : Mashiro
 *
 * File name : algorithm.hpp -algorithm part.
 *
 * This library is free software;you can redistribute is and/or modify it
 * under the APACHE LICENSE 2.0 as published by the Free Software Foundation.
 * ------------------------------------------------------------------------
 */

#pragma once
#include"type_traits.hpp"
using namespace lib_type;

namespace lib_algo
{

	//equal---------------------------------------------------------

	template<typename t>
	_NODISCARD bool equal(const t& obj)
	{
		auto p = obj.cbegin();
		auto p_end = obj.cend();
		auto elem = *p;

		for (; p != p_end; ++p)
		{
			if (*p != elem)
				return false;
		}

		return true;
	}

	template<typename t1,typename t2>
	_NODISCARD bool equal(const t1& obj1 , const t2& obj2)
	{
		if (obj1.size() != obj2.size())
			return false;

		auto p1 = obj1.cbegin();
		auto p2 = obj2.cbegin();
		auto p1_end = obj1.cend();
		auto p2_end = obj2.cend();

		for (; p1 != p1_end , p2 != p2_end; ++p1 , ++p2)
		{
			if (*(p1) != *(p2))
				return false;
		}

		return true;
	}

	template<typename t>
	_NODISCARD bool equal(t p_begin , t p_end)
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
	inline void fill(t& obj,any&& elem)
	{
		auto p = obj.begin();
		auto p_end = obj.end();

		for (; p != p_end; ++p)
		{
			*p = elem;
		}
	}

	template<typename t,typename any>
	inline void fill(t p_begin , t p_end,any&& elem)
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
	//when sort range less than threshold  ----just call insert_sort
	//when depth_limit == 0 ---- return to heap_sort

	//default sort compare function
	template<typename t>
	static inline t default_compare(t elem1 , t elem2)
	{
		return elem1 < elem2 ? elem1 : elem2;
	}

	//compare function define
	template<typename t>
	using pred = t(*)(t , t);



	//insert_sort
	template<typename iterator>
	void insert_sort(iterator p_beg , iterator p_end ,
					 pred<typename iterator::value_type> compare)
	{
		int step = p_end.step() - p_beg.step();
		iterator beg = p_beg;

		for (int n = 0; n < step; ++n)
		{
			iterator next = beg + 1;
			while (next > p_beg && compare(*(next) , *(next - 1)) == *next)
			{
				auto temp = *next;
				*next = *(next - 1);
				*(next - 1) = temp;

				--next;
			}

			beg++;
		}
	}

	//heap sort
	template<typename iterator>
	void precolate(iterator& p_beg , int index , int size ,
					  pred<typename iterator::value_type> compare)
	{
		int max;
		int step = (index * 2) + 1;

		while (step < size)//lchild exist
		{
			max = step;
			if (step + 1 < size)//rchild exist
			{
				iterator lchild = p_beg + step;
				iterator rchild = p_beg + (step + 1);

				if (compare(*lchild , *rchild) == *lchild)
					max = step + 1;
			}

			iterator p_index = p_beg + index;
			iterator p_max = p_beg + max;
			if (compare(*p_index , *p_max) == *p_max)//index value is max
				break;
			else
			{
				auto temp = *p_index;
				*p_index = *p_max;
				*p_max = temp;

				index = max;
				step = (index * 2) + 1;
			}
		}
	}

	template<typename iterator>
	void build_heap(iterator& p_beg , iterator& p_end ,
					pred<typename iterator::value_type> compare)
	{
		int size = p_end.step() - p_beg.step();

		for (int n = size / 2 - 1; n >= 0; --n)
		{
			precolate(p_beg , n , size , compare);
		}
	}

	template<typename iterator>
	void heap_sort(iterator& p_beg , iterator& p_end ,
				   pred<typename iterator::value_type> compare)
	{
		build_heap(p_beg , p_end , compare);

		int size = p_end.step() - p_beg.step() + 1;

		for (int n = size - 1; n > 0; --n)
		{
			//swap
			auto temp = *p_beg;
			*p_beg = *(p_beg + n);
			*(p_beg + n) = temp;

			size--;
			precolate(p_beg , 0 , size , compare);
		}
	}


	//quick_sort
	template<typename iterator>
	auto median3(iterator& p_beg , iterator& p_end)
	{
		int middle = (p_end.step() - p_beg.step()) / 2;
		iterator p_mid = p_beg + middle;

		if (*p_beg > *p_end)
		{
			auto temp = *p_beg;
			*p_beg = *p_end;
			*p_end = temp;
		}
		if (*p_mid > *p_end)
		{
			auto temp = *p_mid;
			*p_mid = *p_end;
			*p_end = temp;
		}
		if (*p_mid > *p_beg)
		{
			auto temp = *p_mid;
			*p_mid = *p_beg;
			*p_beg = temp;
		}

		//*p_mid <= *p_beg <= *p_end
		return *p_beg;
	}


	template<typename iterator>
	void quick_sort(iterator p_beg , iterator p_end , int depth_limit ,
					pred<typename iterator::value_type> compare)
	{
		if (p_end.step() - p_beg.step() <= 4)//threshold = 4
		{
			insert_sort(p_beg , p_end , compare);
			return;
		}

		if (depth_limit <= 0)
		{
			heap_sort(p_beg , p_end , compare);
			return;
		}

		depth_limit--;

		iterator beg = p_beg;
		iterator end = p_end;

		//range equal pivot
		iterator right = p_end;
		iterator left = p_beg;
		int right_len = 0;
		int left_len = 0;

		//set pivot midian
		auto pivot = median3(p_beg , p_end);

		while (beg < end)
		{
			while (beg < end && compare(*end , pivot) == pivot)
			{
				if (*end == pivot)
				{
					auto temp = *end;
					*end = *right;
					*right = temp;

					--right;
					++right_len;
				}

				--end;
			}

			*beg = *end;

			while (beg < end && compare(*beg , pivot) == *beg)
			{
				if (*beg == pivot)
				{
					auto temp = *beg;
					*beg = *left;
					*left = temp;

					++left;
					++left_len;
				}

				++beg;
			}

			*end = *beg;
		}

		*beg = pivot;

		//move the val(= pivot) to around pivot
		iterator p_pivot = beg - 1;
		iterator pos = p_beg;

		while (pos < left && *p_pivot != pivot)
		{
			auto temp = *p_pivot;
			*p_pivot = *pos;
			*pos = temp;

			--p_pivot;
			++pos;
		}

		p_pivot = beg + 1;
		pos = p_end;

		while (pos > right && *p_pivot != pivot)
		{
			auto temp = *p_pivot;
			*p_pivot = *pos;
			*pos = temp;

			++p_pivot;
			--pos;
		}


		quick_sort(p_beg , beg - 1 - left_len , depth_limit , compare);
		quick_sort(beg + 1 + right_len , p_end , depth_limit , compare);
	}


	//get depth_limit
	static int limit(int n)
	{
		int res = 0;
		for (; n > 1; n >>= 1)
			++res;

		return res;
	}


	template<typename iterator>
	void sort(iterator p_beg , iterator p_end ,
				   pred<typename iterator::value_type> compare = default_compare)
	{
		if (p_beg != p_end)
		{
			if (p_end.step() - p_beg.step() <= 4)
				insert_sort(p_beg , p_end , compare);
			else
			{
				int depth = limit(p_end.step() - p_beg.step() + 1) * 2;
				quick_sort(p_beg , p_end , depth , compare);
			}
		}
	}

	template<typename coll>
	void sort(coll& obj , pred<typename coll::value_type> compare = default_compare)
	{
		int size = obj.size();
		auto beg = obj.begin();
		auto end = obj.end()-1;

		if (size > 0)
		{
			if (size <= 4)
				insert_sort(beg , end , compare);
			else
			{
				int depth = limit(size) * 2;
				quick_sort(beg , end , depth , compare);
			}
		}
	}


	//---------------------------------------------------------------


	//find-----------------------------------------------------------

	//find by obj
	template<typename t,typename any>
	_NODISCARD decltype(auto) find(const t& obj,any&& elem)
	{	
		auto p = obj.cbegin();
		auto p_end = obj.cend();

		for (;p != p_end;++p)
		{
			if (*p == elem)
				return p;
		}

		return p-1;
	}

	//find by iterator range
	template<typename t,typename any>
	_NODISCARD decltype(auto) find(t p_begin , t p_end , any&& elem)
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
	_NODISCARD decltype(auto) find_if(const t& obj , bool(*pred)(typename t::value_type))
	{
		auto p = obj.cbegin();
		auto p_end = obj.cend();

		for (; p != p_end; ++p)
		{
			if (pred(*p) == true)
				return p;
		}

		return p - 1;
	}

	template<typename t>
	_NODISCARD decltype(auto) find_if(t p_begin , t p_end , bool(*pred)(typename t::value_type))
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
	_NODISCARD int count(const t& obj , any&& elem)
	{
		int count = 0;

		auto p = obj.cbegin();
		auto p_end = obj.cend();

		for (; p != p_end; ++p)
		{
			if (*p == elem)
				count++;
		}

		return count;
	}

	//count by iterator range
	template<typename t,typename any>
	_NODISCARD int count(t p_begin , t p_end , any&& elem)
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
	_NODISCARD int count_if(const t& obj , bool(*function)(typename t::value_type))
	{
		int count = 0;

		auto p = obj.cbegin();
		auto p_end = obj.cend();

		for (; p != p_end; ++p)
		{
			if (function(*p) == true)
				++count;
		}

		return count;
	}

	template<typename t>
	_NODISCARD int count_if(t p_begin , t p_end , bool(*function)(typename t::value_type))
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
	_NODISCARD bool search(const t& obj , any&& elem)
	{
		auto p = obj.cbegin();
		auto p_end = obj.cend();

		for (; p != p_end; ++p)
		{
			if (*p == elem)
				return true;
		}

		return false;
	}

	template<typename t,typename any>
	_NODISCARD bool search(t p_begin , t p_end , any&& elem)
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
	_NODISCARD auto search_n(const t& obj , const arg& elem , int n)
	{
		if (n <= 0)
			return obj.cbegin();

		auto p = find(obj , elem);
		auto p_end = obj.cend();
		int count = 0;

		while (p != p_end)
		{
			if ((*p) == elem)
				count++;
			
			if (count == n)
				return find(obj , elem);

			++p;
		}

		return p_end - 1;
	}

	template<typename t,typename arg>
	_NODISCARD auto search_n(t p_begin , t p_end , const arg& elem , int n)
	{
		if (n <= 0)
			return p_begin;

		auto p = find(p_begin , p_end , elem);
		int count = 0;

		while (p != p_end)
		{
			if ((*p) == elem)
				count++;

			if (count == n)
				return find(p_begin , p_end , elem);

			++p;
		}

		return p_end - 1;
	}

	//-----------------------------------------------------------------


	//swap-------------------------------------------------------------

	//inside functions

	template<typename t1,typename t2>//not pod type
	void __swap(t1& obj1 , t2& obj2,false_type_tag)
	{
		int arr1_size = obj1.size();
		int arr2_size = obj2.size();

		typename t1::value_type* arr1 = new typename t1::value_type[arr1_size];
		typename t2::value_type* arr2 = new typename t2::value_type[arr2_size];


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
	void __swap(t1& obj1 , t2& obj2 , true_type_tag)
	{
		auto temp = obj1;
		obj1 = (t1)obj2;
		obj2 = (t2)temp;
	}

	template<typename t>//swap of container
	void __swap(t& obj1 , t& obj2,false_type_tag)
	{
		obj1.swap(obj2);
	}

	template<typename t>
	void __swap(t& obj1 , t& obj2 , true_type_tag)
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
	void reverse(t& obj)
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
	void reverse(t p_begin , t p_end)
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
	_NODISCARD decltype(auto) min_element(const t& obj)
	{
		auto p = obj.cbegin();
		auto p_end = obj.cend();
		auto res = *(obj.cbegin());

		for (; p != p_end; ++p)
		{
			if ((*p) < res)
			{
				res = (*p);
			}
		}

		return res;
	}

	template<typename t>
	_NODISCARD decltype(auto) min_element(t p_begin , t p_end)
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
	_NODISCARD decltype(auto) max_element(const t& obj)
	{
		auto p = obj.cbegin();
		auto p_end = obj.cend();
		auto res = *(obj.cbegin());

		for (; p != p_end; ++p)
		{
			if ((*p) > res)
			{
				res = (*p);
			}
		}

		return res;
	}

	template<typename t>
	_NODISCARD decltype(auto) max_element(t p_begin , t p_end)
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
	_NODISCARD inline const t& max(const t& obj1 , const t& obj2)
	{
		return obj1 > obj2 ? obj1 : obj2;
	}

	template<typename t,typename compare>
	_NODISCARD inline const t& max(const t& obj1 , const t& obj2 , compare comp)
	{
		return comp(obj1 , obj2) ? obj1 : obj2;
	}

	//------------------------------------------------------------------


	//min---------------------------------------------------------------

	template<typename t>
	_NODISCARD inline const t& min(const t& obj1 , const t& obj2)
	{
		return obj1 < obj2 ? obj1 : obj2;
	}

	template<typename t,typename compare>
	_NODISCARD inline const t& min(const t& obj1 , const t& obj2 , compare comp)
	{
		return comp(obj1 , obj2) ? obj1 : obj2;
	}

	//------------------------------------------------------------------

	//lower_bound-------------------------------------------------------

	template<typename t,typename any>
	_NODISCARD decltype(auto) lower_bound(const t& obj , any&& elem)
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
	_NODISCARD decltype(auto) lower_bound(t p_begin , t p_end , any&& elem)
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
	_NODISCARD decltype(auto) upper_bound(const t& obj , any&& elem)
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
	_NODISCARD decltype(auto) upper_bound(t p_begin , t p_end , any&& elem)
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
	void replace(t& obj , any&& elem)
	{
		auto p = obj.begin();
		auto p_end = obj.end();

		for (; p != p_end; ++p)
		{
			*p = elem;
		}
	}

	template<typename t,typename any>
	void replace(t p_begin , t p_end , any&& elem)
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
		typename t::value_type* arr = new typename t::value_type[obj.size()];
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
	_NODISCARD auto mismatch_element(const t& obj)
	{
		auto p = obj.cbegin();
		auto p_end = obj.cend();

		for (; p != p_end;)
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
	_NODISCARD t mismatch_element(t p_begin,t p_end)
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
	_NODISCARD auto mismatch(const t1& obj1 , const t2& obj2)			//obj1:greater range  obj2:less range
	{																	//return less range container's iterator
		auto p1 = obj1.cbegin();
		auto p2 = obj2.cbegin();
		auto p1_end = obj1.cend();
		auto p2_end = obj2.cend();

		for (; p1 != p1_end , p2 != p2_end; ++p1 , ++p2)
		{
			if (*p1 != *p2)
				return p2;
		}

		return p2;
	}

	template<typename t1,typename t2>
	_NODISCARD auto mismatch(t1 p_begin1 , t1 p_end1,			// greater range
							t2 p_begin2 , t2 p_end2)			// less range
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
	void _range_greater(t1 p_begin , t1 p_end , t2& obj)
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
	void _range_equal(t1 p_begin , t1 p_end , t2& obj)
	{
		for (auto p = obj.begin(); p != obj.end(),p_begin != p_end; ++p , ++p_begin)
		{
			*p = *p_begin;
		}
	}

	template<typename t1,typename t2>
	void _range_less(t1 p_begin , t1 p_end , t2& obj)
	{
		obj.clear();

		while (p_begin != p_end)
		{
			obj.insert(*(p_begin++));
		}
	}



	template<typename t1,typename t2>
	inline void copy(t1 p_begin , t1 p_end , t2& obj)
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
	void _copy(const t1& copy_from , t2& obj , false_type_tag)
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
	void _copy(const t1& copy_from , t2& obj , true_type_tag)
	{
		obj = (t2)copy_from;
	}

	template<typename t1,typename t2>
	inline void copy(const t1& copy_from , t2& obj)
	{
		typename is_pod<t1>::type type_tag;
		_copy(copy_from , obj , type_tag);
	}

	//------------------------------------------------------------------


	//adjacent_find-----------------------------------------------------
	//find equal adjacent elements in range.

	template<typename t>
	_NODISCARD auto adjacent_find(const t& obj)
	{
		auto p = obj.cbegin();
		auto p_end = obj.cend();

		for (; p != p_end;)
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
	_NODISCARD auto adjacent_find(t p_begin , t p_end)
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
	_NODISCARD bool includes(const t1& obj1 , const t2& obj2)		//obj1 : greater range  obj2 : less range
	{
		if (obj1.size() < obj2.size())
			return false;

		auto p = obj2.cbegin();
		auto p_end = obj2.cend();

		for (; p != p_end; ++p)
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
	inline void for_each(t& obj , void(*function)(typename t::value_type))
	{
		auto p = obj.begin();
		auto p_end = obj.end();

		for (; p != p_end; ++p)
		{
			function(*p);
		}
	}

	template<typename t>
	inline void for_each(t& obj , typename t::value_type(*function)(typename t::value_type))
	{
		auto p = obj.begin();
		auto p_end = obj.end();

		for (; p != p_end; ++p)
		{
			*p = function(*p);
		}
	}

	template<typename t>
	inline void for_each(t& p_begin , t& p_end , void(*function)(typename t::value_type))
	{
		int step = p_end.step() - p_begin.step();

		for (int n = 0; n < step; ++n,++p_begin)
		{
			function(*p_begin);
		}
	}

	template<typename t>
	inline void for_each(t p_begin , t p_end , typename t::value_type(*function)(typename t::value_type))
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
	void remove_if(t& obj , bool(*function)(typename t::value_type))
	{
		auto p = obj.begin();
		auto p_end = obj.end();

		for (; p != p_end;)
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
	_NODISCARD auto merge(const t1& obj1 , const t2& obj2 , t3& result)
	{
		auto p1 = obj1.cbegin();
		auto p2 = obj2.cbegin();
		auto p1_end = obj1.cend();
		auto p2_end = obj2.cend();

		while (p1 != p1_end && p2 != p2_end)
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

		if (p1 != p1_end)
		{
			while (p1 != p1_end)
			{
				result.insert(*p1);
				++p1;
			}
		}
		if (p2 != p2_end)
		{
			while (p2 != p2_end)
			{
				result.insert(*p2);
				++p2;
			}
		}

		return result.begin();
	}

	
	template<typename t1,typename t2,typename t3>
	_NODISCARD auto merge(t1 p_begin1 , t1 p_end1 ,
			   t2 p_begin2 , t2 p_end2 , t3& result)
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