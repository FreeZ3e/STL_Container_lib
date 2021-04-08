/* pair implementation
 *
 * Copyright(c) 2021 Mashiro -1262159823@qq.com
 *
 * This File is part of CONTAINER LIBRARY project.
 *
 * version : 1.1.0-alpha
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

template<typename Key_Ty,typename Value_Ty>
struct pair
{
	using self = pair<Key_Ty , Value_Ty>;

	Key_Ty key;
	Value_Ty value;

	pair(Key_Ty k,Value_Ty v):key(k),value(v)
	{ }

	pair()
	{ }

	//operations

	void swap(pair<Key_Ty , Value_Ty>& obj)
	{
		auto temp_key = key;
		auto temp_value = value;

		key = obj.key;
		value = obj.value;

		obj.key = temp_key;
		obj.value = temp_value;
	}

	void get(const pair<Key_Ty , Value_Ty>& obj)
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

	bool operator==(const pair<Key_Ty , Value_Ty>& obj) const
	{
		return key == obj.key;
	}

	bool operator!=(const pair<Key_Ty , Value_Ty>& obj) const
	{
		return key != obj.key;
	}

	bool operator>=(const pair<Key_Ty , Value_Ty>& obj) const
	{
		return key >= obj.key;
	}

	bool operator<=(const pair<Key_Ty , Value_Ty>& obj) const
	{
		return key <= obj.key;
	}

	bool operator>(const pair<Key_Ty , Value_Ty>& obj) const
	{
		return key > obj.key;
	}

	bool operator<(const pair<Key_Ty , Value_Ty>& obj) const
	{
		return key < obj.key;
	}
};


template<typename key,typename value>
inline pair<key , value> make_pair(const key &k , const value &v)
{
	return pair<key , value>(k , v);
}