/*function adapters implementation
* 
* Copyright(c) 2021 Mashiro -1262159823@qq.com
* 
* This File is part of CONTAINER LIBRARY project.
* 
* version : 1.2.0-alpha
* 
* author : Mashiro
* 
* File name : functional.hpp -implementation of function adapters.
* 
* This library is free software;you can redistribute is and/or modify it
* under the APACHE LICENSE 2.0 as published by the Free Sortware Foundation.
* -------------------------------------------------------------------------
*/

/*--------------------------------README-----------------------------------
* 
*unary_function
*bianry_function
* 
*Arithmentic functors:
*					
*					plus
*					minus
*					multiplies
*					divides
*					modulus
*					negate
* 
*identify element
* 
*
*Relational functors:
* 
*					equal_to
*					not_equal_to
*					greater
*					greater_equal
*					less
*					less_equal
*
*Logical functors:
* 
*					logical_add
*					logical_or
*					logical_not
* 
*function adapters:
* 
*					not1,not2
*					bind1st,bind2nd
*					compose1,compose2
*					ptr_fun
*					mem_fun,mem_fun_ref
*/


//unary_function
template<typename Arg,typename Result>
struct unary_function
{
	using argument_type = Arg;
	using result_type = Result;
};

//bianry_function
template<typename Arg1,typename Arg2,typename Result>
struct bianry_function
{
	using first_argument_type = Arg1;
	using second_argument_type = Arg2;
	using result_type = Result;
};


//--------------------------------adaptable functors------------------------

//Arithmentic functors

//plus
template<typename T>
struct plus:public bianry_function<T,T,T>
{
	T operator()(const T& a , const T& b) const
	{
		return a + b;
	}
};

//minus
template<typename T>
struct minus :public bianry_function<T , T , T>
{
	T operator()(const T& a , const T& b) const
	{
		return a - b;
	}
};

//mult
template<typename T>
struct multiplies :public bianry_function<T , T , T>
{
	T operator()(const T& a , const T& b) const
	{
		return a * b;
	}
};

//divide
template<typename T>
struct divides :public bianry_function<T , T , T>
{
	T operator()(const T& a , const T& b) const
	{
		return a / b;
	}
};

//modulu
template<typename T>
struct modulus :public bianry_function<T , T , T>
{
	T operator()(const T& a , const T& b) const
	{
		return a % b;
	}
};

//negate
template<typename T>
struct negate :public unary_function<T , T>
{
	T operator()(const T& a) const
	{
		return -a;
	}
};



//identity element

template<typename T>
inline T identity_element(plus<T>)
{
	return T(0);
}

template<typename T>
inline T identity_element(multiplies<T>)
{
	return T(1);
}



//Relational functors

//equal_to
template<typename T>
struct equal_to :public bianry_function<T , T , bool>
{
	bool operator()(const T& a , const T& b) const
	{
		return a == b;
	}
};

//not_equal_to
template<typename T>
struct not_equal_to :public bianry_function<T , T , bool>
{
	bool operator()(const T& a , const T& b) const
	{
		return a != b;
	}
};

//greater than
template<typename T>
struct greater :public bianry_function<T , T , bool>
{
	bool operator()(const T& a , const T& b) const
	{
		return a > b;
	}
};

//greater than or equal
template<typename T>
struct greater_equal :public bianry_function<T , T , bool>
{
	bool operator()(const T& a , const T& b) const
	{
		return a >= b;
	}
}; 

//less
template<typename T>
struct less :public bianry_function<T , T , bool>
{
	bool operator()(const T& a , const T& b) const
	{
		return a < b;
	}
};

//less than or equal
template<typename T>
struct less_equal :public bianry_function<T , T , bool>
{
	bool operator()(const T& a , const T& b) const
	{
		return a <= b;
	}
};



//Logical functors

//add
template<typename T>
struct logical_add :public bianry_function<T , T , bool>
{
	bool operator()(const T& a , const T& b) const
	{
		return a && b;
	}
};

//or
template<typename T>
struct logical_or :public bianry_function<T , T , bool>
{
	bool operator()(const T& a , const T& b) const
	{
		return a || b;
	}
};

//not
template<typename T>
struct logical_not :public unary_function<T , bool>
{
	bool operator()(const T& a) const
	{
		return !a;
	}
};

//----------------------------------------------------------------------



//--------------------------function adapters---------------------------

//not1

template<typename functor>
struct unary_negate :public unary_function<typename functor::argument_type , bool>
{
	private:
		functor func;

	public:
		explicit unary_negate(const functor& obj) :func(obj)
		{}

		bool operator()(const typename functor::argument_type& arg) const
		{
			return !func(arg);
		}
};

//helper function
template<typename functor>
inline unary_negate<functor> not1(const functor& obj)
{
	return unary_negate<functor>(obj);
}


//not2

template<typename functor>
struct bianry_negate :
	public bianry_function<typename functor::first_argument_type ,
							typename functor::second_argument_type , bool>
{
	private:
		functor func;

	public:
		explicit bianry_negate(const functor& obj) :func(obj)
		{}

		bool operator()(const typename functor::first_argument_type& arg1 ,
						const typename functor::second_argument_type& arg2) const
		{
			return !func(arg1 , arg2);
		}
};

template<typename functor>
inline bianry_negate<functor> not2(const functor& obj)
{
	return bianry_negate<functor>(obj);
}


//bind1st

template<typename operation>
struct binder1st:public unary_function<typename operation::second_argument_type,
										typename operation::result_type>
{
	private:
		operation op;
		typename operation::first_argument_type value;

	public:
		binder1st(const operation& obj,const typename operation::first_argument_type& x):op(obj),value(x)
		{ }

		typename operation::result_type operator()(const typename operation::second_argument_type& x) const
		{
			return op(value,x);
		}
};

template<typename operation,typename t>
inline binder1st<operation> bind1st(const operation& op , const t& x)
{
	using arg1_type = typename operation::first_argument_type;
	return binder1st<operation>(op , (arg1_type)x);
}


//bind2nd

template<typename operation>
struct binder2nd :public unary_function<typename operation::first_argument_type ,
										typename operation::result_type>
{
	private:
		operation op;
		typename operation::second_argument_type value;

	public:
		binder2nd(const operation& obj,const typename operation::second_argument_type& x):op(obj),value(x)
		{ }

		typename operation::result_type operator()(const typename operation::first_argument_type& x) const
		{
			return op(x , value);
		}
};


template<typename operation,typename t>
inline binder2nd<operation> bind2nd(const operation& obj , const t& x)
{
	using arg2_type = typename operation::second_argument_type;
	return binder2nd<operation>(obj , (arg2_type)(x));
}



//compose1
//make h(x) = f(g(x))

template<typename operation1,typename operation2>
struct unary_compose :public unary_function<typename operation2::argument_type ,
											typename operation1::result_type>
{
	private:
		operation1 op1;
		operation2 op2;

	public:
		unary_compose(const operation1& x,const operation2& y):op1(x),op2(y)
		{ }

		typename operation1::result_type operator()(const typename operation2::argument_type& x) const
		{
			return op1(op2(x));
		}
};

template<typename operation1,typename operation2>
inline unary_compose<operation1 , operation2> compose1(const operation1& op1 , const operation2& op2)
{
	return unary_compose<operation1 , operation2>(op1 , op2);
}


//compose2
//make h(x) = f(g1(x),g2(x))

template<typename operation1,typename operation2,typename operation3>
struct bianry_compose :public unary_function<typename operation2::argument_type ,
												typename operation1::result_type>
{
	private:
		operation1 op1;
		operation2 op2;
		operation3 op3;

	public:
		bianry_compose(const operation1& x,const operation2& y,const operation3& z):op1(x),op2(y),op3(z)
		{ }

		typename operation1::result_type operator()(const typename operation2::argument_type& x) const
		{
			return op1(op2(x) , op3(x));
		}
};


template<typename operation1,typename operation2,typename operation3>
inline bianry_compose<operation1 , operation2 , operation3> compose2(const operation1& op1 , const operation2& op2 ,
																	 const operation3& op3)
{
	return bianry_compose<operation1 , operation2 , operation3>(op1 , op2 , op3);
}



//ptr_fun

//for unary_function
template<typename Arg,typename Result>
struct pointer_to_unary_function :public unary_function<Arg , Result>
{
	private:
		Result (*ptr)(Arg);

	public:
		pointer_to_unary_function() = default;

		explicit pointer_to_unary_function(Result (*x)(Arg)):ptr(x)
		{ }

		Result operator()(Arg x) const
		{
			return ptr(x);
		}
};


//for bianry_function
template<typename Arg1,typename Arg2,typename Result>
struct pointer_to_bianry_function :public bianry_function<Arg1 , Arg2 , Result>
{
	private:
		Result (*ptr)(Arg1 , Arg2);

	public:
		pointer_to_bianry_function() = default;

		explicit pointer_to_bianry_function(Result(*x)(Arg1 , Arg2)):ptr(x)
		{}

		Result operator()(Arg1 x , Arg2 y) const
		{
			return ptr(x , y);
		}
};


//helper functions

template<typename Arg,typename Result>
inline pointer_to_unary_function<Arg , Result> ptr_fun(Result (*x)(Arg))
{
	return pointer_to_unary_function<Arg , Result>(x);
}

template<typename Arg1,typename Arg2,typename Result>
inline pointer_to_bianry_function<Arg1 , Arg2 , Result> ptr_fun(Result (*x)(Arg1 , Arg2))
{
	return pointer_to_bianry_function<Arg1 , Arg2 , Result>(x);
}



//mem_fun & mem_fun_ref


//without argument
//call by pointer
//non-const member function
template<typename s,typename t>
struct mem_fun_t : public unary_function<t* , s>
{
	private:
		s (t::* f)();

	public:
		explicit mem_fun_t(s (t::*pf)()):f(pf)
		{ }

		s operator()(t* p) const
		{
			return (p->*f)();
		}
};


//without argument
//call by pointer
//const member function
template<typename s,typename t>
struct const_mem_fun_t :public unary_function<const t* , s>
{
	private:
		s (t::* f)() const;

	public:
		explicit const_mem_fun_t(s (t::* pf)() const) :f(pf)
		{}

		s operator()(const t* p) const
		{
			return (p->*f)();
		}
};


//without argument
//call by ref
//non-const member function
template<typename s,typename t>
struct mem_fun_ref_t :public unary_function<t , s>
{
	private:
		s (t::* f)();

	public:
		explicit mem_fun_ref_t(s (t::* pf)()) :f(pf)
		{}

		s operator ()(t& r) const
		{
			return(r.*f)();
		}
};


//without argument
//call by ref
//const member function
template<typename s,typename t>
class const_mem_fun_ref_t :public unary_function<t , s>
{
	private:
		s (t::* f)() const;

	public:
		explicit const_mem_fun_ref_t(s (t::*pf)() const):f(pf)
		{ }

		s operator()(const t& r) const
		{
			return (r.*f)();
		}
};


//accept a argument
//call by pointer
//non-const member function
template<typename s,typename t,typename a>
struct mem_fun1_t :public bianry_function<t* , a , s>
{
	private:
		s (t::* f)(a);

	public:
		explicit mem_fun1_t(s (t::* pf)(a)) :f(pf)
		{}

		s operator()(t* p , a x) const
		{
			return (p->*f)(x);
		}
};


//accept a argument
//call by pointer
//const member function
template<typename s,typename t,typename a>
struct const_mem_fun1_t :public bianry_function<const t* , a , s>
{
	private:
		s (t::* f)(a) const;

	public:
		explicit const_mem_fun1_t(s (t::*pf)(a) const):f(pf)
		{ }

		s operator()(const t* p , a x) const
		{
			return (p->*f)(x);
		}
};


//accept a argument
//call by ref
//non-const member function
template<typename s,typename t,typename a>
struct mem_fun1_ref_t :public bianry_function<t , a , s>
{
	private:
		s (t::* f)(a);

	public:
		explicit mem_fun1_ref_t(s (t::*pf)(a)):f(pf)
		{ }

		s operator()(t& r , a x) const
		{
			return (r.*f)(x);
		}
};


//accpet a argument
//call by ref
//const member function
template<typename s,typename t,typename a>
struct const_mem_fun1_ref_t :public bianry_function<t , a , s>
{
	private:
		s (t::* f)(a) const;

	public:
		explicit const_mem_fun1_ref_t(s(t::* pf)(a) const) :f(pf)
		{}

		s operator()(const t& r , a x) const
		{
			return (r.*f)(x);
		}
};


//mem_fun adapter helper functions

//without argument
template<typename s,typename t>
inline mem_fun_t<s , t> mem_fun(s (t::* f)())
{
	return mem_fun_t<s , t>(f);
}

template<typename s,typename t>
inline const_mem_fun_t<s , t> mem_fun(s (t::* f)() const)
{
	return const_mem_fun_t<s , t>(f);
}

template<typename s,typename t>
inline mem_fun_ref_t<s , t> mem_fun_ref(s (t::* f)())
{
	return mem_fun_ref_t<s , t>(f);
}

template<typename s,typename t>
inline const_mem_fun_ref_t<s , t> mem_fun_ref(s (t::* f)() const)
{
	return const_mem_fun_ref_t<s , t>(f);
}

//accept a argument
template<typename s,typename t,typename a>
inline mem_fun1_t<s , t , a> mem_fun(s (t::* f)(a))
{
	return mem_fun1_t<s , t , a>(f);
}

template<typename s,typename t,typename a>
inline const_mem_fun1_t<s , t , a> mem_fun(s (t::* f)(a) const)
{
	return const_mem_fun1_t<s , t , a>(f);
}

template<typename s,typename t,typename a>
inline mem_fun1_ref_t<s , t , a> mem_fun_ref(s (t::* f)(a))
{
	return mem_fun1_ref_t<s , t , a>(f);
}

template<typename s,typename t,typename a>
inline const_mem_fun1_ref_t<s , t , a> mem_fun_ref(s (t::* f)(a) const)
{
	return const_mem_fun1_ref_t<s , t , a>(f);
}