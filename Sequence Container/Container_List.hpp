#pragma once
#include<iostream>
#include<cstdlib>
#include<initializer_list>
#include"new_iterator.hpp"

using std::initializer_list;

template<typename Ty>
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

        size_t size = 10;
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
            while (Head)
            {
                node* ptr = Head;
                delete ptr;
                Head = Head->next;
            }

            delete Head;
            delete CurPtr;
        }

        void push_back(Ty elem)
        {
            CurPtr->data = elem;

            CurPtr->next = new node;
            CurPtr->next->last = CurPtr;
            CurPtr->next->next = nullptr;
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

        Ty operator[](int n) = delete;

        iterator begin()
        {
            return iterator(Head);
        }

        iterator end()
        {
            return iterator(CurPtr);
        }

    private:
        void alloc(size_t size)
        {
            Head = new node;
            Head->last = nullptr;

            CurPtr = Head;
            node* ptr = Head;

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