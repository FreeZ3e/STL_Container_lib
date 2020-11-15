#pragma once
#include<iostream>
#include<cstdlib>
#include<initializer_list>
#include"new_iterator.hpp"

using std::initializer_list;

template<typename Ty>
class deque
{
    private:
        Ty head = 0;
        Ty* body;

        size_t size = 10;
        int InsertCount = 0;

    public:
        using TypeValue = Ty;
        using iterator = Random_iterator<Ty>;

        deque()
        {
            body = new Ty[size];
        }

        deque(initializer_list<Ty> list)
        {
            size = list.size() * 2;
            body = new Ty[size];

            for (auto p = list.begin(); p != list.end(); ++p)
            {
                body[InsertCount] = (*p);
                InsertCount++;
            }
        }

        ~deque()
        {
            delete[] body;
            body = nullptr;
        }

        void push_back(Ty elem)
        {
            if (InsertCount == size)
            {
                size = size * 2;
                MemoryExpand(size);
            }

            body[InsertCount] = elem;
            InsertCount++;
        }

        void push_front(Ty elem)
        {
            head = elem;
            InsertCount++;

            complex();
        }

        void pop_back()
        {   
            size_t resize = InsertCount - 1;
            Ty* temp = new Ty[resize];

            for (int n = 0; n < InsertCount - 1; ++n)
                temp[n] = body[n];

            delete[] body;
            body = new Ty[size];

            for (int n = 0; n < InsertCount - 1; ++n)
                body[n] = temp[n];

            delete[] temp;
            temp = nullptr;
            InsertCount--;
        }

        void resize(size_t resize)
        {
            MemoryExpand(resize);

            if (resize < size)
            {
                InsertCount = resize;
                size = resize;
            }
        }

        int Size()
        {
            return InsertCount;
        }

        Ty operator[](int n)
        {
            return body[n];
        }

        iterator begin()
        {
            return iterator(body , InsertCount);
        }

        iterator end()
        {
            return iterator(body + InsertCount , InsertCount);
        }

    private:
        void MemoryExpand(size_t resize)
        {
            Ty* temp = new Ty[InsertCount];

            for (int n = 0; n < InsertCount; ++n)
                temp[n] = body[n];

            delete[] body;
            body = new Ty[resize];

            for (int n = 0; n < InsertCount; ++n)
                body[n] = temp[n];

            delete[] temp;
            temp = nullptr;
        }
           
        //complex head and body with one arr
        void complex()
        {
            Ty* temp = new Ty[InsertCount];

            for (int n = 0; n < InsertCount; ++n)
            {
                if (n == 0)
                    temp[n] = head;
                else
                    temp[n] = body[n - 1];
            }

            delete[] body;
            body = new Ty[size];

            for (int n = 0; n < InsertCount; ++n)
                body[n] = temp[n];

            delete[] temp;
            temp = nullptr;
        }
};