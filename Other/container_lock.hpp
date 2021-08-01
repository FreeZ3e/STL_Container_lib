/* threads lock implementation
* 
*  Copyright(c) 2021 Mashiro -126215923@qq.com
* 
*  This File is part of CONTAINER LIBRARY project.
* 
*  version : 1.0.0
* 
*  author : Mashiro
* 
*  File name : container_lock.hpp -threads lock for container.
*
*  This library is free software;you can redistribute is and/or modify it
*  under the APACHE LICENSE 2.0 as published by the Free Software Foundation.
* ------------------------------------------------------------------------
*/


#pragma once
#include<thread>
#include<mutex>
#include<initializer_list>
#include<functional>

using std::thread;
using std::bind;
using std::mutex;
using std::unique_lock;
using std::initializer_list;


//thread lock for container
template<typename coll>
class thread_lock
{
	private:
		coll* ptr = nullptr;
		mutex mute;

	public:
		using iterator = typename coll::iterator;
		using const_iterator = typename coll::const_iterator;
		using TypeValue = typename coll::TypeValue;
		using self = thread_lock<coll>;

	public:
		thread_lock() = delete;
		thread_lock(self& obj) = delete;
		self operator=(self obj) = delete;

		//create new obj in thread_lock
		explicit thread_lock(coll* new_ptr):ptr(new_ptr)
		{ }

		//share obj with thread_lock
		explicit thread_lock(coll& obj) :ptr(&obj)
		{ }

		[[noreturn]] void push(const TypeValue& elem)
		{
			unique_lock<mutex> lock(mute);
			ptr->insert(elem);
		}

		[[noreturn]] void push(const initializer_list<TypeValue>& list)
		{
			unique_lock<mutex> lock(mute);
			for (auto p : list)
			{
				ptr->insert(p);
			}
		}

		_NODISCARD iterator erase(const iterator it)
		{
			unique_lock<mutex> lock(mute);
			return ptr->erase(it);
		}

		_NODISCARD const_iterator erase(const const_iterator it)
		{
			unique_lock<mutex> lock(mute);
			return ptr->erase(it);
		}

		[[noreturn]] void erase(const iterator beg , const iterator end)
		{
			unique_lock<mutex> lock(mute);
			ptr->erase(beg , end);
		}

		[[noreturn]] void clear()
		{
			unique_lock<mutex> lock(mute);
			ptr->clear();
		}

		_NODISCARD const_iterator cbegin() const noexcept
		{
			return ptr->cbegin();
		}

		_NODISCARD const_iterator cend() const noexcept
		{
			return ptr->cend();
		}
};


//thread_lock create helper function
template<typename coll>
thread_lock<coll> make_thread_lock(coll* ptr)
{
	return thread_lock<coll>(ptr);
}


//thread create helper functions

template<typename lock>
thread thread_push(lock& obj , const typename lock::TypeValue& elem)
{
	using func = void (lock::*)(const typename lock::TypeValue&);
	func push = &lock::push;

	return thread(bind(push,&obj,elem));
}

template<typename lock>
thread thread_push(lock& obj , const initializer_list<typename lock::TypeValue>& list)
{
	using func = void (lock::*)(const initializer_list<typename lock::TypeValue>&);
	func push = &lock::push;

	return thread(bind(push , &obj , list));
}

template<typename lock>
thread thread_erase(lock& obj , typename lock::iterator pos)
{
	using func = typename lock::iterator (lock::*)(const typename lock::iterator);
	func erase = &lock::erase;

	return thread(bind(erase,&obj,pos));
}

template<typename lock>
thread thread_erase(lock& obj , typename lock::const_iterator pos)
{
	using func = typename lock::const_iterator(lock::*)(const typename lock::const_iterator);
	func erase = &lock::erase;

	return thread(bind(erase , &obj , pos));
}

template<typename lock>
thread thread_erase(lock& obj , typename lock::iterator beg ,
							   typename lock::iterator end)
{
	using func = void (lock::*)(const typename lock::iterator ,
								const typename lock::iterator);
	func erase = &lock::erase;

	return thread(bind(erase , &obj , beg , end));
}

template<typename lock>
thread thread_clear(lock& obj)
{
	return thread(&lock::clear , &obj);
}