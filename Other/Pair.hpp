/* pair implementation
 *
 * Copyright(c) 2021 Mashiro -1262159823@qq.com
 *
 * This File is part of CONTAINER LIBRARY project.
 *
 * version : 1.3.0-alpha
 *
 * author : Mashiro
 *
 * File name : Pair.hpp -a kind of type.
 *
 * This library is free software;you can redistribute is and/or modify it
 * under the APACHE LICENSE 2.0 as published by the Free Software Foundation.
 * ------------------------------------------------------------------------
 */

#pragma once
#include"type_traits.hpp"
#include"memory_allocator.hpp"

template<typename Key_Ty,typename Value_Ty,typename alloc = _default_allocator>
struct pair
{
	using self = pair<Key_Ty , Value_Ty , alloc>;

	Key_Ty key = 0;
	Value_Ty value;

	pair(Key_Ty k,Value_Ty v):key(k),value(v)
	{ }

	pair()
	{ }

	//operations

	void swap(pair<Key_Ty , Value_Ty , alloc>& obj)
	{
		auto temp_key = key;
		auto temp_value = value;

		key = obj.key;
		value = obj.value;

		obj.key = temp_key;
		obj.value = temp_value;
	}

	void get(const pair<Key_Ty , Value_Ty , alloc>& obj)
	{
		key = obj.key;
		value = obj.value;
	}


	//operator overloads

	self& operator+()
	{
		key++;
		return *this;
	}

	self operator+(int)
	{
		auto temp = *this;
		key++;

		return temp;
	}

	self& operator-()
	{
		key--;
		return *this;
	}

	self operator-(int)
	{
		auto temp = *this;
		key--;

		return temp;
	}

	bool operator==(const pair<Key_Ty , Value_Ty , alloc>& obj) const
	{
		return key == obj.key;
	}

	bool operator!=(const pair<Key_Ty , Value_Ty , alloc>& obj) const
	{
		return key != obj.key;
	}

	bool operator>=(const pair<Key_Ty , Value_Ty , alloc>& obj) const
	{
		return key >= obj.key;
	}

	bool operator<=(const pair<Key_Ty , Value_Ty , alloc>& obj) const
	{
		return key <= obj.key;
	}

	bool operator>(const pair<Key_Ty , Value_Ty , alloc>& obj) const
	{
		return key > obj.key;
	}

	bool operator<(const pair<Key_Ty , Value_Ty , alloc>& obj) const
	{
		return key < obj.key;
	}



	void* operator new(size_t size)
	{
		return simple_allocator(alloc , self)::allocate(1);
	}

	void operator delete(void* ptr , size_t size)
	{
		simple_allocator(alloc , self)::deallocate((self*)ptr , sizeof(self*));
	}
};



template<typename key,typename value>
_NODISCARD inline auto make_pair(const key& k , const value& v) noexcept
{
	return pair<const key , value>(k , v);
}