/*container lib errors
 * 
 * Copyright(c) 2021 Mashiro -1262159823@qq.com
 * 
 * This File is part of CONTAINER LIBRARY project.
 * 
 * version : 1.1.0
 * 
 * author : Mashiro
 * 
 * File name : errors.hpp -error message print and tips.
 * 
 * This library is free software;you can redistribute is and/or modify it
 * under the APACHE LICENSE 2.0 as published by the Free Software Foundation.
 * ------------------------------------------------------------------------
 */


#pragma once
#include<iostream>


//-------------DEBUG LEVEL-------------
// 0 : without lib debugging
// 1 : lib debugging open

#define _LIB_DEBUG_LEVEL 1


//mes_print
#define _mes_print(mes) std::cout<<"file:"<<__FILE__<<'\n'		\
							   <<"line:"<<__LINE__<<'\n'		\
							   <<"message:"<<mes<<'\n';			\


#if _LIB_DEBUG_LEVEL == 1 

//_BUG_VERIFY--------------------------
#define _BUG_VERIFY(cond,mes)		\
			if(!cond)				\
				_mes_print(mes)		\
//-------------------------------------

#endif // _LIB_DEBUG_LEVEL == 1


//out_of_memory_handler_check----------
#define _BAD_ALLOC_THROW		      \
		_mes_print("bad alloc error");\
		throw;						  \
//-------------------------------------


//memory_free_check--------------------
#define _MEMORY_FREE_CHECK _mes_print("memory free error")
//-------------------------------------

