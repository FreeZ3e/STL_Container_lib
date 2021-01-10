#pragma once
#include<initializer_list>
#include<typeinfo>
#include"iterator.hpp"

using std::initializer_list;
using std::string;

//Traits classes
template<typename Ty>
using TypeValue = typename Ty::Type;

//array container
template<typename Ty , int Num = 10>
class array
{
    private:
        Ty* arr = new Ty[Num];

    public:
        using TypeValue = Ty;
        using Iterator = Random_iterator<Ty>;

        //initializer_list ctor
        array(const initializer_list<Ty> list)
        {
            int i = 0;
            for (auto p = list.begin(); p != list.end(); ++p)
            {
                if (i < Num)
                {
                    arr[i] = (*p);
                    ++i;
                }
                else
                    break;
            }

            if (typeid(Ty) != typeid(string))
            {
                if (list.size() < Num)
                {
                    for (int n = list.size(); n < Num; ++n)
                        arr[n] = (Ty)0;
                }
            }
        }

        //copy ctor
        array(const array<Ty , Num>& obj)
        {
            for (int i = 0; i < Num; ++i)
            {
                arr[i] = obj.arr[i];
            }
        }

        array(int num)
        {
            for (auto& i : arr)
            {
                arr[i] = num;
            }
        }

        //default ctor
        array()
        {
            for (int i = 0; i < Num; ++i)
                arr[i] = 0;
        }

        ~array()
        {
            delete[] arr;
            arr = nullptr;
        }

        //check array empty or not;
        bool empty()
        {
            int count = 0;

            for (auto& i : arr)
            {
                if (typeid(arr[i]) != typeid(Ty))
                    count++;
            }

            if (count == Num)
                return true;
            else
                return false;
        }

        int size()
        {
            int count = 0;

            for (auto& i : arr)
            {
                if (typeid(arr[i]) == typeid(Ty))
                    count++;
            }

            return count;
        }

        int max_size()
        {
            return Num;
        }

        Ty back_end()
        {
            return arr[Num - 1];
        }

        void fill(Ty n)
        {
            for (int i = 0; i < Num; ++i)
            {
                arr[i] = n;
            }
        }

        Iterator begin()
        {
            return Iterator(arr,Num);
        }

        Iterator end()
        {
            return Iterator(arr+Num,Num);
        }

        Ty operator[](int n)
        {
            return this->arr[n];
        }
};