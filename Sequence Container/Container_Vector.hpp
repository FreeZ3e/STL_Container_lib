#pragma once
#include<initializer_list>
#include"iterator.hpp"

using std::initializer_list;

template<typename Ty>
class vector
{
    private:
        Ty* arr;

        size_t size = 10;
        int InsertCount = 0;
        size_t capacity = size;

    public:
        //class type
        using TypeValue = Ty;
        //iterator type
        using iterator = Random_iterator<Ty>;

        //default ctor
        vector()
        {
            arr = new Ty[size];
        }

        //initializer_list ctor
        vector(initializer_list<Ty> list)
        {
            size = list.size();
            arr = new Ty[size];

            for (auto p = list.begin(); p != list.end(); ++p)
            {
                arr[InsertCount] = (*p);
                InsertCount++;
            }
        }

        ~vector()
        {
            delete[] arr;
            arr = nullptr;
        }

        void push_back(Ty elem)
        {
            if (InsertCount == size)
            {
                MemoryExpand(size);
                size = size * 2;
            }

            arr[InsertCount] = elem;
            InsertCount++;
        }

        void pop_back()
        {
            InsertCount = InsertCount - 1;

            Ty* Temp = new Ty[InsertCount];

            for (int n = 0; n < InsertCount; ++n)
            {
                Temp[n] = arr[n];
            }

            delete[] arr;
            arr = new Ty[size];

            for (int n = 0; n < InsertCount; ++n)
            {
                arr[n] = Temp[n];
            }

            delete[] Temp;
            Temp = nullptr;
        }

        Ty back_end()
        {
            return arr[InsertCount - 1];
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

        size_t max_size()
        {
            return this->capacity;
        }

        int Size()
        {
            return InsertCount;
        }

        Ty operator[](int n)
        {
            return arr[n];
        }

        iterator begin()
        {
            return iterator(arr,InsertCount);
        }

        iterator end()
        {
            return iterator(arr + InsertCount , InsertCount);
        }

    private:
        void MemoryExpand(size_t resize)
        {
            Ty* TempArr = new Ty[resize];

            for (int n = 0; n < resize; n++)
            {
                TempArr[n] = arr[n];
            }

            delete[] arr;
            arr = new Ty[resize * 2];

            for (int n = 0; n < resize; n++)
            {
                arr[n] = TempArr[n];
            }

            delete[] TempArr;
            TempArr = nullptr;
        }
};