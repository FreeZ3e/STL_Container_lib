/* type_traits implementation
 *
 * Copyright(c) 2021 Mashiro -1262159823@qq.com
 *
 * This File is part of CONTAINER LIBRARY project.
 *
 * version : 1.1.0
 *
 * author : Mashiro
 *
 * File name : type_traits.hpp -traits structs part.
 *
 * This library is free software;you can redistribute is and/or modify it
 * under the APACHE LICENSE 2.0 as published by the Free Software Foundation.
 * ------------------------------------------------------------------------
 *
 * -----------------------------README-------------------------------------
 *
 * template<bool>
 * struct truth_type
 *
 * template<typename t>
 * struct is_void
 *
 * template<typename t>
 * struct is_integer
 *
 * template<typename t>
 * struct is_float
 *
 * template<typename t>
 * struct is_char
 *
 * template<typename t>
 * struct is_bool
 *
 * template<typename t>
 * struct is_pointer
 *
 * template<typename t>
 * struct is_array
 *
 * template<typename t>
 * struct is_reference
 *
 * template<typename t>
 * struct is_rvalue_reference
 * 
 * template<typename t>
 * struct is_const
 * 
 * template<typename t>
 * struct is_const_reference
 * 
 * template<typename t>
 * struct is_const_pointer
 * 
 * template<typename t>
 * struct is_pointer_const
 * 
 * template<typename t>
 * struct is_volatile
 * 
 * template<typename t>
 * struct is_signed
 * 
 * template<typename t>
 * struct is_unsigned
 * 
 * template<typename t>
 * struct is_function
 * 
 * template<typename t>
 * struct is_member_pointer
 * 
 * template<typename t>
 * struct is_object
 *
 * template<typename t>
 * struct is_class
 *
 * 
 * 
 *
 * template<typename t1,typename t2>
 * struct is_same
 *
 * template<typename B,typename D>
 * struct is_base_of
 *
 * template<typename t1,typename t2 = void>
 * struct is_iterator
 *
 * template<typename t>
 * struct is_pod
 * 
 * 
 * 
 * 
 *
 * template<typename t>
 * struct traits
 * 
 * template<typename t,bool is_pod_type = is_pod<t>::value>
 * struct type_traits
 *
 * template<typename t>
 * struct get_value_type
 *
 * template<typename t>
 * struct get_self
 *
 * template<bool,typename t = void>
 * struct enable_if
 * 
 * template<typename t>
 * struct remove_const
 * 
 * template<typename t>
 * struct remove_reference
 * 
 * template<typename t>
 * struct remove_rvalue_reference
 * 
 * template<typename t>
 * struct remove_volatile
 * 
 * template<typename t>
 * struct remove_pointer
 * 
 * template<typename t>
 * struct add_const
 * 
 * template<typename t>
 * struct add_volatile
 * 
 * template<typename t>
 * struct add_pointer
 * 
 * template<typename t>
 * struct add_reference
 * 
 * template<typename t>
 * struct add_rvalue_reference
 * 
 * template<typename t>
 * struct make_signed
 * 
 * template<typename t>
 * struct make_unsigned
 * 
 * -----------------------------------------------------------------------
 */


#pragma once
#include"iterator.hpp"

namespace lib_type
{
	//type_tag
	struct true_type_tag{};
	struct false_type_tag{};

	//truth_type
	template<bool>
	struct truth_type
	{
		enum {value = false};
		using type = false_type_tag;
	};

	template<>
	struct truth_type<true>
	{
		enum {value = true};
		using type = true_type_tag;
	};



	//is_void_type-----------------------------------
	template<typename t>
	struct is_void
	{
		enum {value = false };
		using type = false_type_tag;
	};

	template<>
	struct is_void<void>
	{
		enum {value = true };
		using type = true_type_tag;
	};
	//------------------------------------------------


	//is_integer_type---------------------------------
	//type : int,bool,short,long,long long.
	template<typename t>
	struct is_integer
	{
		enum {value = false };
		using type = false_type_tag;
	};

	template<>
	struct is_integer<int>
	{
		enum {value = true };
		using type = true_type_tag;
	};

	template<>
	struct is_integer<unsigned int>
	{
		enum {value = true };
		using type = true_type_tag;
	};

	template<>
	struct is_integer<bool>
	{
		enum {value = true };
		using type = true_type_tag;
	};

	template<>
	struct is_integer<short>
	{
		enum {value = true };
		using type = true_type_tag;
	};

	template<>
	struct is_integer<unsigned short>
	{
		enum {value = true };
		using type = true_type_tag;
	};

	template<>
	struct is_integer<long>
	{
		enum {value = true };
		using type = true_type_tag;
	};

	template<>
	struct is_integer<unsigned long>
	{
		enum {value = true };
		using type = true_type_tag;
	};

	template<>
	struct is_integer<long long>
	{
		enum {value = true };
		using type = true_type_tag;
	};

	template<>
	struct is_integer<unsigned long long>
	{
		enum {value = true };
		using type = true_type_tag;
	};
	//---------------------------------------------------


	//is_float_type--------------------------------------
	template<typename t>
	struct is_float
	{
		enum {value = false };
		using type = false_type_tag;
	};

	template<>
	struct is_float<float>
	{
		enum {value = true };
		using type = true_type_tag;
	};

	template<>
	struct is_float<double>
	{
		enum {value = true };
		using type = true_type_tag;
	};
	//-----------------------------------------------------


	//is_char_type-----------------------------------------
	template<typename t>
	struct is_char
	{
		enum {value = false};
		using type = false_type_tag;
	};

	template<>
	struct is_char<char>
	{
		enum {value = true };
		using type = true_type_tag;
	};

	template<>
	struct is_char<unsigned char>
	{
		enum {value = true };
		using type = true_type_tag;
	};
	//------------------------------------------------------


	//is_bool_type------------------------------------------
	template<typename t>
	struct is_bool
	{
		enum {value = false };
		using type = false_type_tag;
	};

	template<>
	struct is_bool<bool>
	{
		enum {value = true };
		using type = true_type_tag;
	};
	//-------------------------------------------------------


	//is_pointer_type----------------------------------------
	template<typename t>
	struct is_pointer
	{
		enum {value = false };
		using type = false_type_tag;
	};

	template<typename t>
	struct is_pointer<t*>
	{
		enum {value = true };
		using type = true_type_tag;
	};
	//--------------------------------------------------------


	//is_array_type-------------------------------------------
	template<typename t>
	struct is_array
	{
		enum {value = false};
		using type = false_type_tag;
	};

	template<typename t,size_t size>
	struct is_array<t[size]>
	{
		enum {value = true};
		using type = true_type_tag;
	};

	template<typename t>
	struct is_array<t[]>
	{
		enum {value = true };
		using type = true_type_tag;
	};
	//---------------------------------------------------------


	//is_reference_type----------------------------------------
	template<typename t>
	struct is_reference
	{
		enum {value = false};
		using type = false_type_tag;
	};

	template<typename t>
	struct is_reference<t&>
	{
		enum {value = true};
		using type = true_type_tag;
	};
	//---------------------------------------------------------


	//is_rvalue_reference_type---------------------------------
	template<typename t>
	struct is_rvalue_reference
	{
		enum {value = false};
		using type = false_type_tag;
	};

	template<typename t>
	struct is_rvalue_reference<t&&>
	{
		enum {value = true};
		using type = true_type_tag;
	};
	//---------------------------------------------------------


	//is_const_type--------------------------------------------
	template<typename t>
	struct is_const
	{
		enum {value = false};
		using type = false_type_tag;
	};

	template<typename t>
	struct is_const<const t>
	{
		enum {value = true};
		using type = true_type_tag;
	};
	//---------------------------------------------------------


	//is_const_reference_type----------------------------------
	template<typename t>
	struct is_const_reference
	{
		enum {value = false};
		using type = false_type_tag;
	};

	template<typename t>
	struct is_const_reference<const t&>
	{
		enum {value = true};
		using type = true_type_tag;
	};
	//---------------------------------------------------------


	//is_const_pointer_type------------------------------------
	template<typename t>
	struct is_const_pointer
	{
		enum {value = false};
		using type = false_type_tag;
	};

	template<typename t>
	struct is_const_pointer<const t*>
	{
		enum {value = true};
		using type = true_type_tag;
	};
	//---------------------------------------------------------


	//is_pointer_const_type------------------------------------
	template<typename t>
	struct is_pointer_const
	{
		enum {value = false};
		using type = false_type_tag;
	};

	template<typename t>
	struct is_pointer_const<t* const>
	{
		enum {value = true};
		using type = true_type_tag;
	};
	//---------------------------------------------------------


	//is_volatile_type-----------------------------------------
	template<typename t>
	struct is_volatile
	{
		enum {value = false};
		using type = false_type_tag;
	};

	template<typename t>
	struct is_volatile<volatile t>
	{
		enum {value = true};
		using type = true_type_tag;
	};
	//---------------------------------------------------------


	//is_signed_type-------------------------------------------
	template<typename t>
	struct is_signed
	{
		enum {value = true};
		using type = true_type_tag;
	};

	template<>
	struct is_signed<unsigned>
	{
		enum {value = false};
		using type = false_type_tag;
	};
	//---------------------------------------------------------


	//is_unsigned_type-----------------------------------------
	template<typename t>
	struct is_unsigned
	{
		enum {value = false};
		using type = false_type_tag;
	};

	template<>
	struct is_unsigned<unsigned>
	{
		enum {value = true};
		using type = true_type_tag;
	};
	//---------------------------------------------------------


	//is_function_type-----------------------------------------
	template<typename t>
	struct is_function
	{
		enum {value = false};
		using type = false_type_tag;
	};

	template<typename t , typename... args>
	struct is_function<t(args...)>
	{
		enum {value = true};
		using type = true_type_tag;
	};

	template<typename t,typename... args>
	struct is_function<t(args...) const>
	{
		enum {value = true};
		using type = true_type_tag;
	};

	template<typename t,typename... args>
	struct is_function<t(args...) volatile>
	{
		enum {value = true};
		using type = true_type_tag;
	};

	template<typename t,typename... args>
	struct is_function<t(args...) const volatile>
	{
		enum {value = true};
		using type = true_type_tag;
	};

	template<typename t,typename... args>
	struct is_function<t(args...) &>
	{
		enum {value = ture};
		using type = true_type_tag;
	};

	template<typename t,typename... args>
	struct is_function<t(args...) const&>
	{
		enum {value = true};
		using type = true_type_tag;
	};

	template<typename t,typename... args>
	struct is_function<t(args...) volatile&>
	{
		enum {value = true};
		using type = true_type_tag;
	};

	template<typename t,typename... args>
	struct is_function<t(args...) const volatile&>
	{
		enum {value = true};
		using type = true_type_tag;
	};

	template<typename t,typename... args>
	struct is_function<t(args...) &&>
	{
		enum {value = ture};
		using type = true_type_tag;
	};

	template<typename t,typename... args>
	struct is_function<t(args...) const&&>
	{
		enum {value = true};
		using type = true_type_tag;
	};

	template<typename t,typename... args>
	struct is_function<t(args...) volatile&&>
	{
		enum {value = true};
		using type = true_type_tag;
	};

	template<typename t,typename... args>
	struct is_function<t(args...) const volatile&&>
	{
		enum {value = true};
		using type = true_type_tag;
	};
	//---------------------------------------------------------


	//is_member_pointer-----------------------------------------
	template<typename t>
	struct is_member_pointer
	{
		enum {value = false};
		using type = false_type_tag;
	};

	template<typename t,typename u>
	struct is_member_pointer<t u::*>
	{
		enum {value = true};
		using type = true_type_tag;
	};
	//----------------------------------------------------------


	//is_object_type--------------------------------------------
	template<typename t>
	struct is_object
	{
		enum {value = is_array<t>::value || is_class<t>::value};
	};
	//----------------------------------------------------------


	//is_class_type--------------------------------------------
	template<typename t>
	struct is_class
	{
		private:
			template<typename u>
			static char helper(int u::*);//only class
			
			template<typename u>
			static int helper(...);//any template args

		public:
			enum {value = sizeof(helper<t>(0)) == 1};
	};
	//----------------------------------------------------------




	//is_same_type-------------------------------------------------
	template<typename t1,typename t2>
	struct is_same
	{
		enum {value = false};
		using type = false_type_tag;
	};

	template<typename t>
	struct is_same<t , t>
	{
		enum {value = true};
		using type = true_type_tag;
	};
	//-------------------------------------------------------------


	//is_base_of---------------------------------------------------
	template<typename B,typename D>
	struct is_base_of
	{
		private:
			template<typename any>
			static char helper(D , any);

			static int helper(B , int);

			struct conv
			{
				operator D();
				operator B() const;
			};

		public:
			enum {value = sizeof(helper(conv(),0)) == 1 && 
							is_class<D>::value && is_class<B>::value};
	};

	template<>
	struct is_base_of<void , void>
	{
		enum {value = false};
	};

	template<typename B>
	struct is_base_of<B , void>
	{
		enum {value = false};
	};

	template<typename D>
	struct is_base_of<void , D>
	{
		enum {value = false};
	};
	//---------------------------------------------------------------


	//is_iterator_type-----------------------------------------------
	template<typename t1,typename t2 = void>
	struct is_iterator
	{
		enum {value = false};
		using type = false_type_tag;
	};

	template<typename u>
	struct is_iterator<input_iterator<u>>
	{
		enum {value = true};
		using type = true_type_tag;
	};

	template<typename u>
	struct is_iterator<const_input_iterator<u>>
	{
		enum {value = true};
		using type = true_type_tag;
	};

	template<typename u>
	struct is_iterator<forward_iterator<u>>
	{
		enum {value = true};
		using type = true_type_tag;
	};

	template<typename u>
	struct is_iterator<const_forward_iterator<u>>
	{
		enum {value = true};
		using type = true_type_tag;
	};

	template<typename u>
	struct is_iterator<Bid_iterator<u>>
	{
		enum {value = true};
		using type = true_type_tag;
	};

	template<typename u>
	struct is_iterator<const_Bid_iterator<u>>
	{
		enum {value = true};
		using type = true_type_tag;
	};

	template<typename u>
	struct is_iterator<Random_iterator<u>>
	{
		enum {value = true};
		using type = true_type_tag;
	};

	template<typename u>
	struct is_iterator<const_Random_iterator<u>>
	{
		enum {value = true};
		using type = true_type_tag;
	};

	template<typename u>
	struct is_iterator<List_iterator<u>>
	{
		enum {value = true};
		using type = true_type_tag;
	};

	template<typename u>
	struct is_iterator<const_List_iterator<u>>
	{
		enum {value = true};
		using type = true_type_tag;
	};

	template<typename u>
	struct is_iterator<RB_Tree_iterator<u>>
	{
		enum {value = true};
		using type = true_type_tag;
	};

	template<typename u>
	struct is_iterator<const_RB_Tree_iterator<u>>
	{
		enum {value = true};
		using type = true_type_tag;
	};

	template<typename u1,typename u2>
	struct is_iterator<hash_table_iterator<u1,u2>>
	{
		enum {value = true};
		using type = true_type_tag;
	};

	template<typename u1,typename u2>
	struct is_iterator<const_hash_table_iterator<u1 , u2>>
	{
		enum {value = true};
		using type = true_type_tag;
	};
	//---------------------------------------------------------


	//is_pod---------------------------------------------------

	template<typename t>
	struct is_pod
	{
		enum {value = false};
		using type = false_type_tag;
	};

	template<>
	struct is_pod<char>
	{
		enum {value = true};
		using type = true_type_tag;
	};

	template<>
	struct is_pod<unsigned char>
	{
		enum {value = true};
		using type = true_type_tag;
	};

	template<>
	struct is_pod<short>
	{
		enum {value = true};
		using type = true_type_tag;
	};

	template<>
	struct is_pod<unsigned short>
	{
		enum {value = true};
		using type = true_type_tag;
	};

	template<>
	struct is_pod<int>
	{
		enum {value = true};
		using type = true_type_tag;
	};

	template<>
	struct is_pod<unsigned int>
	{
		enum {value = true};
		using type = true_type_tag;
	};

	template<>
	struct is_pod<long>
	{
		enum {value = true};
		using type = true_type_tag;
	};

	template<>
	struct is_pod<unsigned long>
	{
		enum {value = true};
		using type = true_type_tag;
	};

	template<>
	struct is_pod<long long>
	{
		enum {value = true};
		using type = true_type_tag;
	};

	template<>
	struct is_pod<float>
	{
		enum {value = true};
		using type = true_type_tag;
	};

	template<>
	struct is_pod<double>
	{
		enum {value = true};
		using type = true_type_tag;
	};

	template<>
	struct is_pod<long double>
	{
		enum {value = true};
		using type = true_type_tag;
	};

	template<typename t>
	struct is_pod<t*>
	{
		enum {value = true};
		using type = true_type_tag;
	};
	//---------------------------------------------------------



	//traits---------------------------------------------------
	template<typename t>
	struct traits
	{
		using value_type = t;
	};
	//---------------------------------------------------------


	//type_tratis----------------------------------------------
	template<typename t,bool is_pod_type = is_pod<t>::value>
	struct type_traits
	{ };

	template<typename t>
	struct type_traits<t,false>
	{
		using value_type = typename t::value_type;
		using self_type = typename t::self;
		using iterator = typename t::iterator;
		using const_iterator = typename t::const_iterator;
	};

	template<typename t>
	struct type_traits<t , true>
	{
		using value_type = t;
	};
	//---------------------------------------------------------


	//get_value_type--------------------------------------------
	template<typename t>
	struct get_value_type
	{
		using value_type = typename t::value_type;
	};
	//---------------------------------------------------------


	//get_self-------------------------------------------------
	template<typename t>
	struct get_self
	{
		using self = typename t::self;
	};
	//---------------------------------------------------------


	//enable_if------------------------------------------------
	template<bool,typename t = void>
	struct enable_if
	{};

	template<typename t>
	struct enable_if<true , t>
	{
		using value_type = t;
	};
	//---------------------------------------------------------


	//remove_const---------------------------------------------
	template<typename t>
	struct remove_const
	{
		using value_type = t;
	};

	template<typename t>
	struct remove_const<const t>
	{
		using value_type = t;
	};
	//---------------------------------------------------------


	//remove_reference-----------------------------------------
	template<typename t>
	struct remove_reference
	{
		using value_type = t;
	};

	template<typename t>
	struct remove_reference<t&>
	{
		using value_type = t;
	};
	//---------------------------------------------------------


	//remove_rvalue_reference----------------------------------
	template<typename t>
	struct remove_rvalue_reference
	{
		using value_type = t;
	};

	template<typename t>
	struct remove_rvalue_reference<t&&>
	{
		using value_type = t;
	};
	//---------------------------------------------------------


	//remove_volatile------------------------------------------
	template<typename t>
	struct remove_volatile
	{
		using value_type = t;
	};

	template<typename t>
	struct remove_volatile<volatile t>
	{
		using value_type = t;
	};
	//---------------------------------------------------------


	//remove_pointer-------------------------------------------
	template<typename t>
	struct remove_pointer
	{
		using value_type = t;
	};

	template<typename t>
	struct remove_pointer<t*>
	{
		using value_type = t;
	};
	//----------------------------------------------------------


	//add_const-------------------------------------------------
	template<typename t>
	struct add_const
	{
		using value_type = const t;
	};

	template<typename t>
	struct add_const<const t>
	{
		using value_type = t;
	};
	//-----------------------------------------------------------

	
	//add_volatile-----------------------------------------------
	template<typename t>
	struct add_volatile
	{
		using value_type = volatile t;
	};

	template<typename t>
	struct add_volatile<volatile t>
	{
		using value_type = t;
	};
	//-----------------------------------------------------------


	//add_pointer------------------------------------------------
	template<typename t>
	struct add_pointer
	{
		using value_type = t*;
	};

	template<typename t>
	struct add_pointer<t*>
	{
		using value_type = t;
	};
	//-----------------------------------------------------------


	//add_reference----------------------------------------------
	template<typename t>
	struct add_reference
	{
		using value_type = t&;
	};

	template<typename t>
	struct add_reference<t&>
	{
		using value_type = t;
	};
	//-----------------------------------------------------------


	//add_rvalue_reference---------------------------------------
	template<typename t>
	struct add_rvalue_reference
	{
		using value_type = t&&;
	};

	template<typename t>
	struct add_rvalue_reference<t&&>
	{
		using value_type = t;
	};
	//-----------------------------------------------------------


	//make_signed------------------------------------------------
	template<typename t>
	struct make_signed
	{
		using value_type = t;
	};

	template<>
	struct make_signed<unsigned>
	{
		using value_type = signed;
	};
	//-----------------------------------------------------------


	//make_unsigned----------------------------------------------
	template<typename t>
	struct make_unsigned
	{
		using value_type = unsigned;
	};

	template<>
	struct make_unsigned<unsigned>
	{
		using value_type = unsigned;
	};
	//-----------------------------------------------------------


	//is_trivial-------------------------------------------------
	template<typename t,typename ctor = t>
	struct is_trivial
	{
		enum{value = 0};
	};

	template<typename t>
	struct is_trivial<t , decltype(t())>
	{
		enum{value = 1};
	};
	//-----------------------------------------------------------

	
	//ifThenElse-------------------------------------------------
	template<bool b,typename _true,typename _false>
	struct ifThenElse
	{
		using value_type = _false;
	};

	template<typename _true , typename _false>
	struct ifThenElse<true , _true, _false>
	{
		using value_type = _true;
	};
	//-----------------------------------------------------------



	template<typename t>
	bool isVoid = is_void<t>::value;

	template<typename t>
	bool isInt = is_integer<t>::value;

	template<typename t>
	bool isFloat = is_float<t>::value;

	template<typename t>
	bool isChar = is_char<t>::value;

	template<typename t>
	bool isBool = is_bool<t>::value;

	template<typename t>
	bool isPtr = is_pointer<t>::value;

	template<typename t>
	bool isArr = is_array<t>::value;

	template<typename t>
	bool isRef = is_reference<t>::value;

	template<typename t>
	bool isRvalueRef = is_rvalue_reference<t>::value;

	template<typename t>
	bool isConst = is_const<t>::value;

	template<typename t>
	bool isConstRef = is_const_reference<t>::value;

	template<typename t>
	bool isConstPtr = is_const_pointer<t>::value;

	template<typename t>
	bool isPtrConst = is_pointer_const<t>::value;

	template<typename t>
	bool isVolatile = is_volatile<t>::value;

	template<typename t>
	bool isSigned = is_signed<t>::value;

	template<typename t>
	bool isUnsigned = is_unsigned<t>::value;

	template<typename t>
	bool isFunc = is_function<t>::value;

	template<typename t>
	bool isMemPtr = is_member_pointer<t>::value;

	template<typename t>
	bool isObj = is_object<t>::value;

	template<typename t>
	bool isClass = is_class<t>::value;

	template<typename t1 , typename t2>
	bool isSame = is_same<t1 , t2>::value;

	template<typename t1 , typename t2>
	bool isBase = is_base_of<t1 , t2>::value;

	template<typename t1 , typename t2>
	bool isIterator = is_iterator<t1 , t2>::value;

	template<typename t>
	bool isPod = is_pod<t>::value;

	template<typename t>
	bool isTrivial = is_trivial<t>::value;

	template<typename t>
	using type = typename traits<t>::value_type;

	template<typename t>
	using getValueType = typename get_value_type<t>::value_type;

	template<typename t>
	using getSelf = typename get_self<t>::self;

	template<bool b, typename t = void>
	using enableIfV = typename enable_if<b,t>::value_type;

	template<typename t>
	using removeConst = typename remove_const<t>::value_type;

	template<typename t>
	using removeRef = typename remove_reference<t>::value_type;

	template<typename t>
	using removeRvRef = typename remove_rvalue_reference<t>::value_type;

	template<typename t>
	using removeVolatile = typename remove_volatile<t>::value_type;

	template<typename t>
	using removePtr = typename remove_pointer<t>::value_type;

	template<typename t>
	using addConst = typename add_const<t>::value_type;

	template<typename t>
	using addVolatile = typename add_volatile<t>::value_type;

	template<typename t>
	using addPtr = typename add_pointer<t>::value_type;

	template<typename t>
	using addRef = typename add_reference<t>::value_type;

	template<typename t>
	using addRvRef = typename add_rvalue_reference<t>::value_type;

	template<typename t>
	using makeSigned = typename make_signed<t>::value_type;

	template<typename t>
	using makeUnsigned = typename make_unsigned<t>::value_type;

	template<bool b,typename t,typename f>
	using ifThenElseV = typename ifThenElse<b , t , f>::value_type;
}