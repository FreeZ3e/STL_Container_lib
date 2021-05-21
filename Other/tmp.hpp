/*Template Meta Programming implementation
* 
* Copyright(c) 2021 Mashiro -1262159823@qq.com
*
* This File is part of CONTAINER LIBRARY project.
*
* version : 1.2.1-alpha
*
* author : Mashiro
*
* File name : tmp.hpp -Template Meta Programming part.
*
* This library is free software;you can redistribute is and/or modify it
* under the APACHE LICENSE 2.0 as published by the Free Software Foundation.
* -----------------------------------------------------------------------------
*/

/*------------------------------README-----------------------------------------
* 
*unary_mate
*bianry_mate
* 
*argument type:
* 
*				_int
*				_short
*				_long
*				_longlong
*				_char
*				_bool
* 
*mate functors:
* 
*				plus_f
*				minus_f
*				multiplies_f
*				divides_f
*				modulus_f
*				negate_f
* 
* 
*mult arguments mate functors:
* 
*				mult_plus
*				mult_minus
*				mult_multiplies
*				mult_divides
*				mult_modulu
* 
* 
*relational mate functors:
* 
*				equal_to_f
*				not_equal_to_f
*				greater_than_f
*				greater_equal_f
*				less_f
*				less_equal_f
* 
* 
*logical mate functors:
* 
*				add_f
*				and_f
*				not_f
* 
* 
*higher level mate functor composer:
* 
*				twice_f
*				negate1_f
*				negate2_f
*				compose1_f
*				compose2_f
*/


#pragma once

namespace lib_mate
{ 
	//unary_mate
	template<typename arg,typename result>
	struct unary_mate
	{
		using argument_type = arg;
		using result_type = result;
	};

	//bianry_mate
	template<typename arg1,typename arg2,typename result>
	struct bianry_mate
	{
		using first_argument_type = arg1;
		using second_argument_type = arg2;
		using result_type = result;
	};


	//argument type--------------------------------------------------

	template<int arg>
	struct _int
	{
		enum {value = arg};
		using ValueType = int;
	};

	template<short arg>
	struct _short
	{
		enum {value = arg};
		using ValueType = short;
	};

	template<long arg>
	struct _long
	{
		enum {value = arg};
		using ValueType = long;
	};

	template<long long arg>
	struct _longlong
	{
		enum {value = arg};
		using ValueType = long long;
	};

	template<char arg>
	struct _char
	{
		enum {value = arg};
		using ValueType = char;
	};

	template<bool arg>
	struct _bool
	{
		enum {value = arg};
		using ValueType = bool;
	};

	//--------------------------------------------------------------------------


	//mate functors-------------------------------------------------------------

	struct plus_f
	{
		template<typename arg1,typename arg2>
		struct apply :public bianry_mate<typename arg1::ValueType ,
										 typename arg2::ValueType ,
										 typename arg1::ValueType>
		{
			enum {value = arg1::value + arg2::value};
		};
	};

	struct minus_f
	{
		template<typename arg1,typename arg2>
		struct apply :public bianry_mate<typename arg1::ValueType ,
										 typename arg2::ValueType ,
										 typename arg1::ValueType>
		{
			enum {value = arg1::value - arg2::value};
		};
	};

	struct multiplies_f
	{
		template<typename arg1 , typename arg2>
		struct apply :public bianry_mate<typename arg1::ValueType ,
										 typename arg2::ValueType ,
										 typename arg1::ValueType>
		{
			enum {value = arg1::value * arg2::value};
		};
	};

	struct divides_f
	{
		template<typename arg1 , typename arg2>
		struct apply :public bianry_mate<typename arg1::ValueType ,
										 typename arg2::ValueType ,
										 typename arg1::ValueType>
		{
			enum {value = arg1::value / arg2::value};
		};
	};

	struct modulus_f
	{
		template<typename arg1 , typename arg2>
		struct apply :public bianry_mate<typename arg1::ValueType ,
										 typename arg2::ValueType ,
										 typename arg1::ValueType>
		{
			enum {value = arg1::value % arg2::value};
		};
	};

	struct negate_f
	{
		template<typename arg>
		struct apply :public unary_mate<typename arg::ValueType ,
										typename arg::ValueType>
		{
			using ValueType = typename arg::ValueType;
			enum {value = !arg::value};
		};
	};

	//-----------------------------------------------------------------------------


	//mult arguments mate functors-------------------------------------------------

	//plus
	template<typename... arg>
	struct mult_plus;

	template<typename arg0,typename... args>
	struct mult_plus<arg0 , args...>
	{
		enum {value = mult_plus<arg0>::value + mult_plus<args...>::value};
	};

	template<typename arg>
	struct mult_plus<arg>
	{
		enum {value = arg::value};
	};


	//minus
	template<typename... arg>
	struct mult_minus;

	template<typename arg0,typename... args>
	struct mult_minus<arg0,args...>
	{
		enum {value = mult_minus<arg0>::value - mult_minus<args...>::value};
	};

	template<typename arg>
	struct mult_minus<arg>
	{
		enum {value = arg::value};
	};


	//multiplies
	template<typename... arg>
	struct mult_multiplies;

	template<typename arg0,typename... args>
	struct mult_multiplies<arg0,args...>
	{
		enum {value = mult_multiplies<arg0>::value * mult_multiplies<args...>::value};
	};

	template<typename arg>
	struct mult_multiplies<arg>
	{
		enum {value = arg::value};
	};


	//divides
	template<typename... arg>
	struct mult_divides;

	template<typename arg0,typename... args>
	struct mult_divides<arg0 , args...>
	{
		enum {value = mult_divides<arg0>::value / mult_divides<args...>::value};
	};

	template<typename arg>
	struct mult_divides<arg>
	{
		enum {value = arg::value};
	};


	//modulu
	template<typename... arg>
	struct mult_modulu;

	template<typename arg0 , typename... args>
	struct mult_modulu<arg0 , args...>
	{
		enum {value = mult_modulu<arg0>::value % mult_modulu<args...>::value};
	};

	template<typename arg>
	struct mult_modulu<arg>
	{
		enum {value = arg::value};
	};


	//---------------------------------------------------------------------


	//relational mate functors---------------------------------------------

	//equal_to
	struct equal_to_f
	{
		template<typename arg1,typename arg2>
		struct apply :bianry_mate<typename arg1::ValueType ,
								  typename arg1::ValueType , bool>
		{
			enum {value = (arg1::value == arg2::value)};
		};
	};


	//not_equal_to
	struct not_equal_to_f
	{
		template<typename arg1 , typename arg2>
		struct apply :bianry_mate<typename arg1::ValueType ,
								  typename arg1::ValueType , bool>
		{
			enum {value = (arg1::value != arg2::value)};
		};
	};

	//greater than
	struct greater_than_f
	{
		template<typename arg1 , typename arg2>
		struct apply :bianry_mate<typename arg1::ValueType ,
								  typename arg1::ValueType , bool>
		{
			enum {value = (arg1::value > arg2::value)};
		};
	};


	//greater than or equal
	struct greater_equal_f
	{
		template<typename arg1 , typename arg2>
		struct apply :bianry_mate<typename arg1::ValueType ,
								  typename arg1::ValueType , bool>
		{
			enum {value = (arg1::value >= arg2::value)};
		};
	};


	//less
	struct less_f
	{
		template<typename arg1 , typename arg2>
		struct apply :bianry_mate<typename arg1::ValueType ,
								  typename arg1::ValueType , bool>
		{
			enum {value = (arg1::value < arg2::value)};
		};
	};


	//less than or equal
	struct less_equal_f
	{
		template<typename arg1 , typename arg2>
		struct apply :bianry_mate<typename arg1::ValueType ,
								  typename arg1::ValueType , bool>
		{
			enum {value = (arg1::value <= arg2::value)};
		};
	};


	//---------------------------------------------------------------------


	//Logical mate functors------------------------------------------------

	//add
	struct add_f
	{
		template<typename arg1 , typename arg2>
		struct apply :bianry_mate<typename arg1::ValueType ,
								  typename arg2::ValueType , bool>
		{
			enum {value = (arg1::value && arg2::value)};
		};
	};


	//or
	struct or_f
	{
		template<typename arg1 , typename arg2>
		struct apply :bianry_mate<typename arg1::ValueType ,
								  typename arg2::ValueType , bool>
		{
			enum {value = (arg1::value || arg2::value)};
		};
	};


	//not
	struct not_f
	{
		template<typename arg>
		struct apply :unary_mate<typename arg::ValueType , bool>
		{
			using ValueType = typename arg::ValueType;
			enum {value = (!arg::value)};
		};
	};

	//---------------------------------------------------------------------



	//higher level mate functor composer-----------------------------------

	struct twice_f
	{
		template<typename func , typename arg>
		struct twice
		{
			using once = typename func::template apply<arg>;
			enum {value = func::template apply<once>::value};
		};
	};


	struct negate1_f
	{
		template<typename func , typename arg>
		struct negate1
		{
			enum {value = !func::template apply<arg>::value};
		};
	};


	struct negate2_f
	{
		template<typename func,typename arg1,typename arg2>
		struct negate2
		{
			enum {value = !func::template apply<arg1,arg2>::value};
		};
	};


	//make h(x) = f(g(x))
	struct compose1_f
	{
		template<typename func1,typename func2,typename arg>
		struct compose1
		{
			using once = typename func1::template apply<arg>;
			enum {value = func2::template apply<once>::value};
		};
	};


	//make h(x) = f(g1(x),g2(x))
	struct compose2_f
	{
		template<typename func1,typename func2,typename func3,typename arg>
		struct compose2
		{
			using first = typename func1::template apply<arg>;
			using second = typename func2::template apply<arg>;
			enum {value = func3::template apply<first,second>::value};
		};
	};

	//----------------------------------------------------------------------

}