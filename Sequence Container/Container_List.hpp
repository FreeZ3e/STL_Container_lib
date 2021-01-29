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

			node() = default;

			node(Ty elem , node* n_ptr=nullptr , node* l_ptr=nullptr):data(elem),next(n_ptr),last(l_ptr)
			{ }
		};

		node* Head = nullptr;
		node* CurPtr = nullptr;

		size_t list_size = default_size;
		int elem_count = 0;

	public:
		using TypeValue = Ty;
		using iterator = List_iterator<node>;

		list()
		{
			alloc(list_size);
		}

		list(size_t size)
		{
			list_size = size;
			alloc(list_size);
		}

		list(size_t size , Ty elem):list(size)
		{
			for(int n=0;n<size;++n)
				push_back(elem);
		}

		list(const initializer_list<Ty>& list)
		{
			list_size = list.size();
			alloc(list_size);

			for (auto p = list.begin(); p != list.end(); ++p)
			{
				CurPtr->data = (*p);

				if (CurPtr->next)
					CurPtr = CurPtr->next;

				elem_count++;
			}
		}

		list(const list<Ty , default_size>& obj)
		{
			list_size = obj.list_size;
			alloc(list_size);

			//get head ptr
			auto ptr = obj.Head;

			for (int n=0;n<obj.elem_count;++n)
			{
				Ty temp = ptr->data;
				CurPtr->data = temp;

				if (CurPtr->next)
					CurPtr = CurPtr->next;

				elem_count++;

				ptr = ptr->next;
				if (ptr == nullptr)
					break;
			}
		}

		~list()
		{
			clear();
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

			elem_count++;
		}

		void push_front(Ty elem)
		{
			node* temp = new node(elem,Head,nullptr);

			Head->last = temp;
			Head = temp;

			elem_count++;
		}

		void pop_back()
		{	
			node* ptr = CurPtr->last;
			
			CurPtr = CurPtr->last->last;

			delete ptr;
			ptr = nullptr;

			node* temp = new node;
			temp->last = CurPtr;
			temp->next = nullptr;

			CurPtr->next = temp;
			CurPtr = temp;

			elem_count--;
		}

		void pop_front()
		{
			node* ptr = Head;

			Head = Head->next;
			Head->last = nullptr;

			delete ptr;
			ptr = nullptr;

			elem_count--;
		}

		void remove(Ty elem)
		{
			node* ptr = new node;
			ptr->next = Head;

			while (ptr->next)
			{
				if (ptr->next->data == elem)
				{
					if (ptr->next == Head)
					{
						pop_front();
						ptr->next = Head;
					}
					else if (ptr->next == CurPtr)
					{
						pop_back();
						ptr->next = CurPtr;
					}
					else
					{
						node* temp = ptr->next;

						ptr->next = ptr->next->next;
						ptr->next->last = ptr;

						delete temp;

						elem_count--;
					}
				}
				else
				{
					ptr = ptr->next;
				}
			}
		}

		void clear()
		{
			node* ptr = Head;

			while (ptr)
			{
				node* temp = ptr;
				ptr = ptr->next;

				delete temp;
			}

			Head = CurPtr = nullptr;
			elem_count = 0;
		}

		Ty front()
		{
			return Head->data;
		}

		Ty back()
		{
			return CurPtr->last->data;
		}

		bool empty()
		{
			if (elem_count == 0)
				return true;

			return false;
		}

		int size()
		{
			return elem_count;
		}

		size_t max_size()
		{
			return list_size;
		}

		void resize(size_t size)
		{
			if (size >= list_size)
			{
				node* ptr = CurPtr;
				for (int n = 0; n < (int)size - list_size; ++n)
				{
					ptr->next = new node;
					ptr = ptr->next;
				}ptr->next = nullptr;
			}
			else
			{
				for (int n = 0; n < list_size - size; ++n)
				{
					pop_back();
				}
			}

			list_size = size;
		}

		void swap(list<Ty , default_size>& obj)
		{
			//keep data
			int temp_count = elem_count;
			Ty* arr = new Ty[elem_count];
			node* ptr = Head;

			int count = 0;
			while (ptr)
			{
				arr[count] = ptr->data;

				ptr = ptr->next;
				count++;
			}count = 0;

			//keep obj data
			int obj_elem_count = obj.elem_count;
			Ty* obj_arr = new Ty[obj.elem_count];
			ptr = obj.Head;

			while (ptr)
			{
				obj_arr[count] = ptr->data;

				ptr = ptr->next;
				count++;
			}count = 0;

			//free & alloc memory
			obj.clear();
			obj.alloc(list_size);
			clear();
			alloc(obj.list_size);

			//obj
			for (int n = 0; n < temp_count; ++n)
			{
				Ty temp = arr[n];
				obj.push_back(temp);
			}

			//this
			for (int n = 0; n < obj_elem_count; ++n)
			{
				Ty temp = obj_arr[n];
				push_back(temp);
			}

			//swap size
			size_t temp_size = list_size;
			list_size = obj.list_size;
			obj.list_size = temp_size;

			//swap elem_count
			elem_count = obj_elem_count;
			obj.elem_count = temp_count;
		}



		//iterator
		iterator begin()
		{
			return iterator(Head);
		}

		iterator end()
		{
			return iterator(CurPtr);
		}

		iterator cbegin() const
		{
			return iterator(Head);
		}

		iterator cend() const
		{
			return iterator(CurPtr);
		}


		//operator overload

		Ty operator[](int n) = delete;

		bool operator==(const list<int , default_size>& obj)
		{
			if (elem_count != obj.elem_count)
				return false;

			auto ptr = Head;
			for (auto p = obj.cbegin(); p!=obj.cend();++p)
			{
				if ((*p) != ptr->data)
					return false;

				ptr = ptr->next;
			}

			return true;
		}

		bool operator!=(const list<int , default_size>& obj)
		{
			return !((*this) == obj);
		}

		bool operator>(const list<int , default_size>& obj)
		{
			if (list_size > obj.list_size)
				return true;

			return false;
		}

		bool operator<(const list<int , default_size>& obj)
		{
			if (list_size < obj.list_size)
				return true;

			return false;
		}

		bool operator>=(const list<int , default_size>& obj)
		{
			if (list_size >= obj.list_size)
				return true;

			return false;
		}

		bool operator<=(const list<int , default_size>& obj)
		{
			if (list_size <= obj.list_size)
				return true;

			return false;
		}

	private:
		void alloc(size_t list_size)
		{
			//Head node alloc
			CurPtr = new node;
			CurPtr->last = nullptr;

			//set Head node
			Head = CurPtr;
			node* ptr = CurPtr;

			//alloc memory
			for (int n = 0; n < list_size; ++n)
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