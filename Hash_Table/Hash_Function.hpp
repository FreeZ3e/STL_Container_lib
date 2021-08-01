/* hash_function implementation
 *
 * Copyright(c) 2021 Mashiro -1262159823@qq.com
 *
 * This File is part of CONTAINER LIBRARY project.
 *
 * version : 1.0.0
 *
 * author : Mashiro
 *
 * File name : Hash_Function.hpp -hasher.
 *
 * This library is free software;you can redistribute is and/or modify it
 * under the APACHE LICENSE 2.0 as published by the Free Software Foundation.
 * ------------------------------------------------------------------------
 */


#pragma once
#include<string>
#include"Pair.hpp"
#include"type_traits.hpp"

using std::string;
using namespace lib_type;

//hash function
template<typename Ty>
struct hash_function
{

	//is pointer
	static _NODISCARD inline size_t _is_ptr_hash(const Ty& elem , true_type_tag) noexcept
	{
		unsigned long h = sizeof(*elem);
		return (size_t)h;
	}

	//non pointer
	static _NODISCARD inline size_t _is_ptr_hash(const Ty& elem , false_type_tag) noexcept
	{
		unsigned long h = elem > 0 ? elem : -elem;
		return (size_t)h;
	}

	//pod type handle
	static _NODISCARD inline size_t _hash(const Ty& elem , true_type_tag) noexcept
	{
		typename is_pointer<Ty>::type type_tag;
		return _is_ptr_hash(elem , type_tag);
	}

	//non-pod type handle
	static _NODISCARD inline size_t _hash(const Ty& elem , false_type_tag) noexcept
	{
		unsigned long h = sizeof(elem);
		return (size_t)h;
	}

	//hash function
	static _NODISCARD inline size_t hash(const Ty& elem) noexcept
	{
		typename is_pod<Ty>::type type_tag;
		return _hash(elem , type_tag);
	}
};

template<>
struct hash_function<string>
{
	static _NODISCARD size_t hash(const string& elem) noexcept
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
	static _NODISCARD size_t hash(const char*& elem) noexcept
	{
		unsigned long h = 0;

		for (; *elem; ++elem)
		{
			h = 5 * h + *elem;
		}

		return (size_t)h;
	}
};


//hash function for pair
template<typename key , typename value>
struct pair_hash
{
	//is pointer
	static _NODISCARD inline size_t _is_ptr_hash(const key& elem , true_type_tag) noexcept
	{
		unsigned long h = sizeof(*elem);
		return (size_t)h;
	}

	//non pointer
	static _NODISCARD inline size_t _is_ptr_hash(const key& elem , false_type_tag) noexcept
	{
		unsigned long h = elem > 0 ? elem : -elem;
		return (size_t)h;
	}

	//pod type handle
	static _NODISCARD inline size_t _hash(const key& elem , true_type_tag) noexcept
	{
		typename is_pointer<key>::type type_tag;
		return _is_ptr_hash(elem , type_tag);
	}

	//non-pod type handle
	static _NODISCARD inline size_t _hash(const key& elem , false_type_tag) noexcept
	{
		unsigned long h = sizeof(elem);
		return (size_t)h;
	}

	//hash function
	static _NODISCARD inline size_t hash(const pair<const key , value>& obj) noexcept
	{
		typename is_pod<key>::type type_tag;
		return _hash(obj.key , type_tag);
	}
};

template<typename value>
struct pair_hash<const string , value>
{
	static _NODISCARD size_t hash(const pair<const string , value>& obj) noexcept
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
struct pair_hash<const char* , value>
{
	static _NODISCARD size_t hash(const pair<const char* , value>& obj) noexcept
	{
		unsigned long h = 0;

		for (; *(obj.key); ++obj.key)
		{
			h = 5 * h + *(obj.key);
		}

		return (size_t)h;
	}
};
