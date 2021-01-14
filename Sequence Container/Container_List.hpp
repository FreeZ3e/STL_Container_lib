#pragma once
#include<initializer_list>
#include"iterator.hpp"

using std::initializer_list;

template<typename Ty,int default_size = 0>
class list
{
    private:
        struct node
        {
            node* next;
            node* last;
            Ty data;
        };

        node* Head;
        node* CurPtr;

        size_t size = default_size;
        int InsertCount = 0;

    public:
        using TypeValue = Ty;
        using iterator = List_iterator<node>;

        list()
        {
            alloc(size);
        }

        list(initializer_list<Ty> list)
        {
            size = list.size();
            alloc(size);

            for (auto p = list.begin(); p != list.end(); ++p)
            {
                CurPtr->data = (*p);

                if (CurPtr->next)
                    CurPtr = CurPtr->next;

                InsertCount++;
            }
        }

        ~list()
        {
            node* ptr = Head;

            while (ptr)
            {
                node* temp = ptr;
                ptr = ptr->next;

                delete temp;
            }

            Head = CurPtr = nullptr;
        }

        void push_back(Ty elem)
        {
            CurPtr->data = elem;

            if (CurPtr->next == nullptr)
            {
                CurPtr->next = new node;
                CurPtr->next->last = CurPtr;
                CurPtr->next->next = nullptr;
            }

            CurPtr = CurPtr->next;

            InsertCount++;
        }

        void push_front(Ty elem)
        {
            node* temp = new node;

            temp->data = elem;
            temp->next = Head;
            temp->last = nullptr;
            Head->last = temp;

            Head = temp;

            InsertCount++;
        }

        void pop_back()
        {
            CurPtr = CurPtr->last;
            CurPtr->next = nullptr;

            InsertCount--;
        }

        int Size()
        {
            return InsertCount;
        }

        iterator begin()
        {
            return iterator(Head);
        }

        iterator end()
        {
            return iterator(CurPtr);
        }

        //Random visit ban
        Ty operator[](int n) = delete;

    private:
        void alloc(size_t size)
        {
            //Head node alloc
            CurPtr = new node;
            CurPtr->last = nullptr;

            //set Head node
            Head = CurPtr;
            node* ptr = CurPtr;

            //alloc memory
            for (int n = 0; n < size; ++n)
            {
                ptr->next = new node;

                if (n != 0)
                {
                    ptr->next->last = ptr;
                }

                ptr = ptr->next;
            }ptr->next = nullptr;
        }
};