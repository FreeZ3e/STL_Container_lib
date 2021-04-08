/* hash_function implementation
 *
 * Copyright(c) 2021 Mashiro -1262159823@qq.com
 *
 * This File is part of CONTAINER LIBRARY project.
 *
 * version : 1.2.0-alpha
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
#include"Pair.hpp"
#include<string>

using std::string;

//hash function
template<typename Ty>
struct hash_function
{
	static size_t hash(Ty elem)
	{
		return (size_t)elem;
	}
};

template<>
struct hash_function<string>
{
	static size_t hash(string elem)
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
	static size_t hash(char* elem)
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
	static size_t hash(const pair<key , value>& obj)
	{
		return (size_t)obj.key;
	}
};

template<typename value>
struct pair_hash<string , value>
{
	static size_t hash(const pair<string , value>& obj)
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
struct pair_hash<char* , value>
{
	static size_t hash(const pair<char* , value>& obj)
	{
		unsigned long h = 0;

		for (; *(obj.key); ++obj.key)
		{
			h = 5 * h + *(obj.key);
		}

		return (size_t)h;
	}
};
