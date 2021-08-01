/*memory implemenation
* 
* Copyright(c) 2021 Mashiro -1262159823@qq.com
* 
* This File is part of CONTAINER LIBRARY project.
* 
* version : 1.0.0
* 
* author : Mashiro
* 
* File name : memory.hpp -destory elem in container.
* 
* This library is free software;you can redistribute is and/or modify it
* under the APACHE LICENSE 2.0 as published by the Free Software Foundation.
* ------------------------------------------------------------------------------
*/

/*---------------------------Functions--------------------------
* 
* void _class_destory(Ty& elem,int value)
* 
* void _pointer_destory(Ty& elem,lib_type::true_type_tag)
* 
* void _elem_destory(Ty& elem,lib_type::true_type_tag)
* 
* void elem_destory(Ty& elem)
* 
*/


#pragma once
#include"type_traits.hpp"

namespace memory
{
	//call dtor
	template<typename Ty>
	[[noreturn]] inline void _class_destory(Ty& elem , int value) noexcept
	{
		if (value == 1)
			elem.~Ty();
	}

	//set pointer null
	template<typename Ty>
	[[noreturn]] inline void _pointer_destory(Ty& elem , lib_type::true_type_tag) noexcept
	{
		elem = nullptr;
	}

	//do nothing
	template<typename Ty>
	[[noreturn]] inline void _pointer_destory(Ty& elem , lib_type::false_type_tag) noexcept
	{
	}

	//free pod data
	template<typename Ty>
	[[noreturn]] inline void _elem_destory(Ty& elem , lib_type::true_type_tag) noexcept
	{
		typename lib_type::is_pointer<Ty>::type type_tag;
		_pointer_destory(elem , type_tag);
	}

	//free non-pod data
	template<typename Ty>
	[[noreturn]] inline void _elem_destory(Ty& elem , lib_type::false_type_tag) noexcept
	{
		_class_destory(elem , lib_type::is_class<Ty>::value);
	}


	//elem destory warrper
	template<typename Ty>
	[[noreturn]] inline void elem_destory(Ty& elem) noexcept
	{
		typename lib_type::is_pod<Ty>::type type_tag;
		_elem_destory(elem , type_tag);
	}
}