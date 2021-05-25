/*container lib errors
 * 
 * Copyright(c) 2021 Mashiro -1262159823@qq.com
 * 
 * This File is part of CONTAINER LIBRARY project.
 * 
 * version : 1.2.1-alpha
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



//-------------DEBUG LEVEL-------------
// 0 : without lib debugging
// 1 : lib debugging open

#define _LIB_DEBUG_LEVEL 1


//mes_print
#define _mes_print(mes) std::cout<<"file:"<<__FILE__<<std::endl			\
							   <<"line:"<<__LINE__<<std::endl			\
							   <<"message:"<<mes<<std::endl;			\


#if _LIB_DEBUG_LEVEL == 1 

//_BUG_VERIFY--------------------------
#define _BUG_VERIFY(cond,mes)		\
			if(!cond)				\
				_mes_print(mes)		\
//-------------------------------------

#endif // _LIB_DEBUG_LEVEL == 1
