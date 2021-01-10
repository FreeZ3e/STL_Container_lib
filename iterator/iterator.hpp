#pragma once

template<typename Ty>
struct input_iterator
{
    protected:
        Ty* ptr;

    public:
        input_iterator(Ty* InitPtr) :ptr(InitPtr)
        {}

        virtual ~input_iterator()
        {}

        Ty& operator*()
        {
            return *ptr;
        }
};

template<typename Ty>
struct forward_iterator :public input_iterator<Ty>
{
    protected:
        const int& CurrentNum;
        int InitNum;

    private:
        using self = forward_iterator<Ty>;
    public:
        forward_iterator(Ty* InitPtr , const int& num) :input_iterator<Ty>(InitPtr) , CurrentNum(num) , InitNum(num)
        {}

        virtual ~forward_iterator()
        {}

        self& operator++()
        {
            ++input_iterator<Ty>::ptr;
            return *this;
        }

    protected:
        friend bool operator!=(const self& Lhs , const self& Rhs)
        {
            return Lhs.ptr != Rhs.ptr;
        }
};

template<typename Ty>
struct Bid_iterator :public forward_iterator<Ty>
{
    private:
        using self = Bid_iterator<Ty>;
    public:
        Bid_iterator(Ty* InitPtr , const int& num) :forward_iterator<Ty>(InitPtr , num)
        {}

        virtual ~Bid_iterator()
        {}

        self& operator--()
        {
            --forward_iterator<Ty>::ptr;
            return *this;
        }
};

template<typename Ty>
struct Random_iterator :public Bid_iterator<Ty>
{
    private:
        using self = Random_iterator<Ty>;
    public:
        Random_iterator(Ty* IninPtr , const int& num) :Bid_iterator<Ty>(IninPtr , num)
        {}

        self& operator=(Ty* NewPtr)
        {
            this->ptr = NewPtr;
            return *this;
        }
};

//iterator for list
template<typename Ty>
struct List_iterator
{
    private:
        Ty* ptr;
        using self = List_iterator<Ty>;

    public:
        List_iterator(Ty* InitPtr):ptr(InitPtr)
        {}

        decltype(ptr->data)& operator*() const
        {
            return ptr->data;
        }

        self& operator++()
        {
            if (ptr->next)
                ptr = ptr->next;
            return *this;
        }

        self& operator--()
        {
            if (ptr->last)
                ptr = ptr->last;
            return *this;
        }

    private:
        friend bool operator!=(const self& Lhs , const self& Rhs)
        {
            return Lhs.ptr != Rhs.ptr;
        }
};


//iterator for RB_Tree
template<typename Ty>
struct RB_Tree_iterator
{
    private:
        Ty* ptr;

        const int Red = 0;
        const int Black = 1;
        using self = RB_Tree_iterator<Ty>;

    public:
        RB_Tree_iterator(Ty* p):ptr(p)
        {}

        decltype(ptr->data) operator*() const
        {
            return ptr->data;
        }

        self& operator++()
        {
            increment();
            return *this;
        }

        self& operator--()
        {
            decrement();
            return *this;
        }

    private:
        void increment()
        {
            if (ptr->Rchild != nullptr)
            {
                ptr = ptr->Rchild;

                while (ptr->Lchild != nullptr)
                {
                    ptr = ptr->Lchild;
                }
            }
            else
            {
                Ty* p = ptr->Father;

                while (ptr == p->Rchild)
                {
                    ptr = p;
                    p = p->Father;
                }
                if (ptr->Rchild != p)
                {
                    ptr = p;
                }
            }
        }

        void decrement()
        {
            if (ptr->Color == 0 && ptr->Father->Father == ptr)
            {
                ptr = ptr->Rchild;
            }
            else if (ptr->Lchild != nullptr)
            {
                auto p = ptr->Lchild;

                while (p->Rchild != nullptr)
                {
                    p = p->Rchild;
                }

                ptr = p;
            }
            else
            {
                Ty* p = ptr->Father;
                
                while (ptr == p->Lchild)
                {
                    ptr = p;
                    p = p->Father;
                }

                ptr = p;
            }
        }

    private:
        friend bool operator!=(const self& Lhs , const self& Rhs)
        {
            return Lhs.ptr != Rhs.ptr;
        }


};