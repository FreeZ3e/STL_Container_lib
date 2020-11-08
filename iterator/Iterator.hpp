#pragma once
#include<iostream>
#include<cstdlib>

//traits classes
template<typename Ty>
using ValueType = typename Ty::self;

//iterator type define
enum iterator_type
{
    Bid_iterator , forward_iterator , reverse_iterator  , Random_iterator
};

//Bid_iterator
template<typename Ty , iterator_type itTy>
struct iterator
{
    private:
        Ty* ptr;
        const int& CurrentNum;
        int InitNum;

        using self = iterator<Ty , itTy>;
    public:
        iterator(Ty* InitPtr , const int& Num) :ptr(InitPtr) , CurrentNum(Num) , InitNum(Num)
        {
        }

        Ty& operator*() const
        {
            return *ptr;
        }

        iterator<Ty , itTy>& operator++()
        {
            ++ptr;
            return *this;
        }

        iterator<Ty , itTy>& operator--()
        {
            --ptr;
            return *this;
        }

    private:
        friend bool operator!=(const iterator& Lhs , const iterator& Rhs)
        {
            return Lhs.ptr != Rhs.ptr;
        }

        friend bool operator== (const iterator& Lhs , const iterator& Rhs)
        {
            return Lhs.ptr == Rhs.ptr;
        }

};


//forward_iterator
template<typename Ty>
struct iterator<Ty , forward_iterator>
{
    private:
        Ty* ptr;
        const int& CurrentNum;
        int InitNum;

        using self = iterator<Ty , forward_iterator>;
    public:
        iterator(Ty* InitPtr , const int& Num) :ptr(InitPtr) , CurrentNum(Num) , InitNum(Num)
        {
        }

        Ty& operator*() const
        {
            return *ptr;
        }

        iterator<Ty , forward_iterator>& operator++()
        {
            ++ptr;
            return *this;
        }

        iterator<Ty , forward_iterator>& operator--() = delete;

    private:
        friend bool operator!=(const iterator& Lhs , const iterator& Rhs)
        {
            return Lhs.ptr != Rhs.ptr;
        }

        friend bool operator== (const iterator& Lhs , const iterator& Rhs)
        {
            return Lhs.ptr == Rhs.ptr;
        }
};


//Reverse_iterator
template<typename Ty>
struct iterator<Ty , reverse_iterator>
{
    private:
        Ty* ptr;
        const int& CurrentNum;
        int InitNum;

        using self = iterator<Ty , reverse_iterator>;
    public:
        iterator(Ty* InitPtr , const int& Num) :ptr(InitPtr) , CurrentNum(Num) , InitNum(Num)
        {
        }

        Ty& operator*() const
        {
            return *ptr;
        }

        iterator<Ty , reverse_iterator>& operator++()
        {
            --ptr;
            return *this;
        }

        iterator<Ty , reverse_iterator>& operator--()
        {
            ++ptr;
            return *this;
        }

    private:
        friend bool operator!=(const iterator& Lhs , const iterator& Rhs)
        {
            return Lhs.ptr != Rhs.ptr;
        }

        friend bool operator== (const iterator& Lhs , const iterator& Rhs)
        {
            return Lhs.ptr == Rhs.ptr;
        }
};


//Random_iterator
template<typename Ty>
struct iterator<Ty , Random_iterator>
{
    private:
        Ty* ptr;
        const int& CurrentNum;
        int InitNum;

        using self = iterator<Ty , Random_iterator>;
    public:
        iterator(Ty* InitPtr , const int& num) :ptr(InitPtr) , CurrentNum(num) , InitNum(num)
        {
        }

        Ty& operator*() const
        {
            return *ptr;
        }

        iterator<Ty , Random_iterator>& operator++()
        {
            ++ptr;
            return *this;
        }

        iterator<Ty , Random_iterator>& operator--()
        {
            --ptr;
            return *this;
        }

        iterator<Ty , Random_iterator>& operator=(Ty* newPtr)
        {
            this->ptr = newPtr;
            return *this;
        }

    private:
        friend bool operator!=(const iterator<Ty , Random_iterator>& Lhs , const iterator<Ty , Random_iterator>& Rhs)
        {
            return Lhs.ptr != Rhs.ptr;
        }

        friend bool operator== (const iterator<Ty , Random_iterator>& Lhs , const iterator<Ty , Random_iterator>& Rhs)
        {
            return Lhs.ptr == Rhs.ptr;
        }
};


//Bid_iterator use for list
template<typename node>
struct iterator<node,Bid_iterator>
{
    private:
        node* ptr;

        using self = iterator<node , Bid_iterator>;
    public:
        iterator(node* InitPtr) :ptr(InitPtr)
        {
        }

        decltype(ptr->data)& operator*() const
        {
            return (ptr->data);
        }

        self& operator++()
        {   
            if(ptr->next)
                ptr = ptr->next;
            return *this;
        }

        self& operator--()
        {
            if(ptr->last)
                ptr = ptr->last;
            return *this;
        }

    private:
        friend bool operator!=(const self& Lhs , const self& Rhs)
        {
            return Lhs.ptr != Rhs.ptr;
        }

        friend bool operator== (const self& Lhs , const self& Rhs)
        {
            return Lhs.ptr == Rhs.ptr;
        }

};