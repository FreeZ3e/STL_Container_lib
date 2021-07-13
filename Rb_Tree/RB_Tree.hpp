/* RB_Tree implementation
 *
 * Copyright(c) 2021 Mashiro -1262159823@qq.com
 *
 * This File is part of CONTAINER LIBRARY project.
 *
 * version : 1.3.0-alpha
 *
 * author : Mashiro
 *
 * File name : RB_Tree.hpp -bottom implementation of associative container.
 *
 * This library is free software;you can redistribute is and/or modify it
 * under the APACHE LICENSE 2.0 as published by the Free Software Foundation.
 * ------------------------------------------------------------------------
 *
 *-------------------------------README------------------------------------
 *
 * template<typename Ty,typename Compare_Class = Unique_Compare,typename alloc = _default_allocator>
 * class RB_Tree
 * {
 *      //iterator : RB_Tree_iterator
 *      //const_iterator : const_RB_Tree_iterator
 *
 *      //ctor
 *
 *      RB_Tree(const RB_Tree<Ty,Compare_Class,alloc>& obj)
 *      RB_Tree(const initializer_list<Ty>& obj)
 *		RB_Tree(Ty elem)
 *      RB_Tree()
 *
 *      //operations
 *
 *      void Destory()-----------------------------------destory tree.
 *      void Insert(Ty elem)-----------------------------insert elem.
 *      void DeleteNode(Ty elem)-------------------------delete node if elem exist.
 *      iterator erase(iterator ptr)---------------------delete node in iterator position.
 *      const_iterator erase(const_iterator& ptr)
 *      void erase(iterator p_begin,iterator p_end)------delete node in iterator range.
 *      bool search(Ty elem)-----------------------------if elem exist,return true.
 *      int count(Ty elem)-------------------------------count number of elem.
 *      int size()---------------------------------------return number of elems.
 *      void swap(self& obj)--------make swap operation.
 *
 *      //iterator
 *
 *      iterator begin()---------------------------------return the position of beginning.
 *      iterator end()-----------------------------------return the position of ending.
 *      const_iterator cbegin() const
 *      const_iterator cend() const
 *
 *      //operator overload
 *
 *      self& operator=(const self& obj)
 *      bool operator==(const coll& obj)
 *      bool operator!=(const coll& obj)
 *      bool operator<(const coll& obj)
 *      bool operator>(const coll& obj)
 *      bool operator>=(const coll& obj)
 *      bool operator<=(const coll& obj)
 *
 *      //private functions
 *
 *      TreeNode<Ty>* Self_Search(Ty elem,TreeNode<Ty>* ptr)--------if elem exist,return ptr of node.
 *      void Self_Destory(TreeNode<Ty>*& ptr)-----------------------make destory operation.
 *      void Self_Insert(Ty elem,TreeNode<Ty>*& ptr,TreeNode<Ty>* father = nullptr)
 *      void Self_Delete(Ty elem,TreeNode<Ty>*& ptr)
 *      void Insert_FixUp(TreeNode<Ty>* ptr)------------------------rotate or recolor by RB_Tree rule.
 *      void Delete_FixUp(TreeNode<Ty>* ptr)
 *      void L_Rotate(TreeNode<Ty>* ptr)----------------------------make left rotate operation.
 *      void R_Rotate(TreeNode<Ty>* ptr)
 *      void TreeCopy(TreeNode<Ty>* ptr)----------------------------make copy operation.
 *      TreeNode<Ty>* FindUncle(TreeNode<Ty>* ptr)------------------if uncle node exist,return uncle node ptr.
 *      TreeNode<Ty>* Maximum(TreeNode<Ty>* ptr)--------------------return node ptr with max val.
 *      TreeNode<Ty>* Minimum(TreeNode<Ty>* ptr)
 * }
 * ----------------------------------------------------------------------------------------------
 */


#pragma once
#include<initializer_list>
#include<functional>
#include"memory.hpp"
#include"iterator.hpp"
#include"memory_allocator.hpp"

using std::initializer_list;
using std::function;

template<typename Ty,typename Compare_Class = Unique_Compare,
					 typename alloc = _default_allocator>
class RB_Tree
{	
	//insert compare function define
	using key_compare = function<bool()>;

	//color define
	enum TreeColor :int
	{
		Red = 0 , Black = 1
	};

	//treenode define
	template<typename T>
	struct TreeNode
	{
		using TypeValue = T;

		T data;
		TreeColor Color = Red;
		TreeNode<T>* Rchild = nullptr;
		TreeNode<T>* Lchild = nullptr;
		TreeNode<T>* Father = nullptr;

		TreeNode() = default;

		TreeNode(const T& elem , TreeNode<T>* R = nullptr , TreeNode<T>* L = nullptr , TreeNode<T>* F = nullptr) :data(elem) , Rchild(R) , Lchild(L) , Father(F)
		{}

		void* operator new(size_t size)
		{
			return simple_allocator(alloc , TreeNode<T>)::allocate(1);
		}

		void operator delete(void* ptr , size_t size)
		{
			simple_allocator(alloc , TreeNode<T>)::deallocate((TreeNode<T>*)ptr , sizeof(TreeNode<T>*));
		}
	};

	public:
		using self = RB_Tree<Ty , Compare_Class , alloc>;
		using TypeValue = Ty;
		using NodeType = TreeNode<Ty>;
		using iterator = RB_Tree_iterator<TreeNode<Ty>>;
		using const_iterator = const_RB_Tree_iterator<TreeNode<Ty>>;

	private:
		//compare function obj
		key_compare compare = Compare_Class::Compare;

		TreeNode<Ty>* header = nullptr;
		TreeNode<Ty>* head = nullptr;

		int NodeCount = 0;

	public:
		explicit RB_Tree(const RB_Tree<Ty , Compare_Class , alloc>& obj) noexcept :RB_Tree()
		{
			TreeCopy(obj.head);
		}

		explicit RB_Tree(const initializer_list<Ty>& obj) noexcept :RB_Tree()
		{
			for (auto p:obj)
			{
				Insert(p);
			}
		}

		RB_Tree(const Ty& elem) noexcept
		{
			header = new TreeNode<Ty>;
			head = new TreeNode<Ty>(elem,nullptr,nullptr,header);
			head->Color = Black;

			header->Father = head;

			NodeCount++;
		}

		RB_Tree() noexcept
		{	
			header = new TreeNode<Ty>;
		}

		~RB_Tree() noexcept
		{
			delete header;
			header = nullptr;

			Destory();

			head = nullptr;
		}


		//insert and erase operations

		[[noreturn]] void Destory() noexcept
		{
			Self_Destory(head);
			NodeCount = 0;
		}

		[[noreturn]] void Insert(const Ty& elem) noexcept
		{
			Self_Insert(elem , head);

			header->Lchild = Minimum(head);
			header->Rchild = Maximum(head);
		}

		[[noreturn]] void DeleteNode(const Ty& elem) noexcept
		{
			if (Self_Search(elem , head) != nullptr)
			{
				Self_Delete(elem , head);
				NodeCount--;
			}

			if (Self_Search(elem , head) != nullptr)
				DeleteNode(elem);

			header->Lchild = Minimum(head);
			header->Rchild = Maximum(head);
		}

		_NODISCARD iterator erase(iterator ptr) noexcept
		{
			auto temp = ptr;

			int step = ptr.step();
			Ty cur_num = (*ptr);
			Ty next_num = (*(++temp));

			if (compare)
			{
				while (next_num == (*ptr))
				{
					next_num = (*(++temp));
				}
			}

			if (step == NodeCount-1)
			{
				DeleteNode(cur_num);

				return iterator(header , NodeCount);
			}

			DeleteNode(cur_num);

			return iterator(Self_Search(next_num , head),step);
		}

		_NODISCARD const_iterator erase(const_iterator& ptr) noexcept
		{
			auto temp = ptr;

			int step = ptr.step();
			Ty cur_num = (*ptr);
			Ty next_num = (*(++temp));

			if (compare)
			{
				while (next_num == (*ptr))
				{
					next_num = (*(++temp));
				}
			}

			if (step == NodeCount - 1)
			{
				DeleteNode(cur_num);

				return const_iterator(header , NodeCount);
			}

			DeleteNode(cur_num);

			return const_iterator(Self_Search(next_num , head) , step);
		}

		[[noreturn]] void erase(iterator p_begin , iterator p_end) noexcept
		{
			int n = p_begin.step();
			for (; n < p_end.step(); ++n)
			{
				p_begin = erase(p_begin);
			}
		}


		//other

		_NODISCARD bool Search(const Ty& elem) const noexcept
		{
			if (Self_Search(elem , head) != nullptr)
				return true;

			return false;
		}

		_NODISCARD int count(const Ty& elem) const noexcept
		{
			int _count = 0;

			auto p = begin();
			for (; p != end(); ++p)
			{
				if ((*p) == elem)
					_count++;
			}

			return _count;
		}

		_NODISCARD int size() const noexcept
		{
			return NodeCount;
		}

		[[noreturn]] void swap(self& obj) noexcept
		{
			TreeNode<Ty>* temp_head = head;
			TreeNode<Ty>* obj_head = obj.head;

			TreeNode<Ty>* temp_header = header;
			TreeNode<Ty>* obj_header = obj.header;

			head = obj_head;
			obj.head = temp_head;

			header = obj_header;
			obj.header = temp_header;

			int temp_count = NodeCount;
			NodeCount = obj.NodeCount;
			obj.NodeCount = temp_count;
		}



		//iterator
		_NODISCARD iterator begin() noexcept
		{
			return iterator(header->Lchild,0);
		}

		_NODISCARD iterator end() noexcept
		{
			return iterator(header,NodeCount);
		}

		_NODISCARD iterator begin() const noexcept
		{
			return iterator(header->Lchild , 0);
		}

		_NODISCARD iterator end() const noexcept
		{
			return iterator(header , NodeCount);
		}

		_NODISCARD const_iterator cbegin() const noexcept
		{
			return const_iterator(header->Lchild,0);
		}

		_NODISCARD const_iterator cend() const noexcept
		{
			return const_iterator(header,NodeCount);
		}


		//operator overload
		self& operator=(const self& obj) noexcept
		{
			typename RB_Tree<Ty , Compare_Class , alloc>::const_iterator p = obj.cbegin();
			for (; p != obj.cend(); ++p)
			{
				Insert((*p));
				NodeCount++;
			}

			return *this;
		}

		template<typename coll>
		_NODISCARD bool operator==(const coll& obj) const noexcept
		{
			if (NodeCount != obj.size())
				return false;

			typename coll::const_iterator p = obj.cbegin();
			typename RB_Tree<Ty , Compare_Class , alloc>::const_iterator self_p = cbegin();
			for (; p != obj.cend(),self_p != cend(); ++p,++self_p)
			{
				if ((*p) != (*self_p))
					return false;
			}	

			return true;
		}

		template<typename coll>
		_NODISCARD bool operator!=(const coll& obj) const noexcept
		{
			return !((*this) == obj);
		}

		template<typename coll>
		_NODISCARD bool operator>(const coll& obj) const noexcept
		{
			if (NodeCount > obj.size())
				return true;

			return false;
		}

		template<typename coll>
		_NODISCARD bool operator<(const coll& obj) const noexcept
		{
			if (NodeCount < obj.size())
				return true;

			return false;
		}

		template<typename coll>
		_NODISCARD bool operator>=(const coll& obj) const noexcept
		{
			if (NodeCount >= obj.size())
				return true;

			return false;
		}

		template<typename coll>
		_NODISCARD bool operator<=(const coll& obj) const noexcept
		{
			if (NodeCount <= obj.size())
				return true;

			return false;
		}

	private:
		TreeNode<Ty>* Self_Search(Ty elem , TreeNode<Ty>* ptr) const noexcept
		{
			if (ptr != nullptr)
			{
				if (ptr->data == elem)
				{
					return ptr;
				}
				else if (ptr->data > elem)
				{
					return Self_Search(elem , ptr->Lchild);
				}
				else if (ptr->data < elem)
				{
					return Self_Search(elem , ptr->Rchild);
				}
			}

			return nullptr;
		}

		[[noreturn]] void Self_Destory(TreeNode<Ty>*& ptr) noexcept
		{
			if (ptr)
			{
				auto p = ptr;
				Self_Destory(ptr->Rchild);
				Self_Destory(ptr->Lchild);

				memory::elem_destory(p->data);
				delete p;
				ptr = nullptr;
			}
		}

		[[noreturn]] void Self_Insert(const Ty& elem , TreeNode<Ty>*& ptr , TreeNode<Ty>* father = nullptr)
		{
			if (ptr == nullptr)
			{
				ptr = new TreeNode<Ty>(elem , nullptr , nullptr , father);

				if (NodeCount == 0)
				{
					ptr->Color = Black;
					ptr->Father = header;
					header->Father = ptr;
				}

				NodeCount++;
			}
			else if (elem > ptr->data)
			{
				Self_Insert(elem , ptr->Rchild , ptr);

				if (ptr != nullptr && ptr->Rchild != nullptr && ptr->Father != header)
				{
					Insert_FixUp(ptr->Rchild);
				}
			}
			else if (elem < ptr->data)
			{
				Self_Insert(elem , ptr->Lchild , ptr);

				if (ptr != nullptr && ptr->Lchild != nullptr && ptr->Father != header)
				{
					Insert_FixUp(ptr->Lchild);
				}
			}
			else if (elem == ptr->data)
			{
				if (compare())
				{
					Self_Insert(elem , ptr->Rchild , ptr);

					if (ptr != nullptr && ptr->Rchild != nullptr && ptr->Father != header)
					{
						Insert_FixUp(ptr->Rchild);
					}
				}
			}
		}
		
		[[noreturn]] void Self_Delete(const Ty& elem , TreeNode<Ty>*& ptr)
		{
			if (ptr != nullptr)
			{
				if (ptr->data == elem)
				{
					if (ptr->Lchild != nullptr && ptr->Rchild != nullptr)
					{
						TreeNode<Ty>* temp = Minimum(ptr->Rchild);
						ptr->data = temp->data;

						Self_Delete(temp->data , ptr->Rchild);
					}
					else if (ptr->Lchild != nullptr)
					{
						TreeNode<Ty>* temp = Maximum(ptr->Lchild);
						ptr->data = temp->data;

						Self_Delete(temp->data , ptr->Lchild);
					}
					else if (ptr->Rchild != nullptr)
					{
						TreeNode<Ty>* temp = Minimum(ptr->Rchild);
						ptr->data = temp->data;

						Self_Delete(temp->data , ptr->Rchild);
					}
					else
					{
						TreeNode<Ty>* temp = ptr;
						memory::elem_destory(ptr->data);

						delete temp;
						ptr = nullptr;
					}
				}
				else if (ptr->data > elem)
				{
					Self_Delete(elem , ptr->Lchild);

					Delete_FixUp(ptr);
				}
				else if (ptr->data < elem)
				{
					Self_Delete(elem , ptr->Rchild);

					Delete_FixUp(ptr);
				}
			}
		}

		[[noreturn]] void Insert_FixUp(TreeNode<Ty>* ptr)
		{
			ptr->Color = Red;

			while (ptr != head && ptr->Father->Color == Red)
			{
				TreeNode<Ty>* uncle = FindUncle(ptr->Father);

				if (uncle == nullptr)
					break;

				if (ptr->Father == ptr->Father->Father->Lchild)//father => Lchild
				{
					if (uncle->Color == Red) //case 1
					{
						ptr->Father->Color = Black;
						uncle->Color = Black;
						ptr->Father->Father->Color = Red;

						ptr = ptr->Father->Father;
					}
					else
					{
						if (ptr == ptr->Father->Rchild)//case 2
						{
							ptr = ptr->Father;
							L_Rotate(ptr);
						}

						//case 3
						ptr->Father->Color = Black;
						ptr->Father->Father->Color = Red;
						R_Rotate(ptr->Father->Father);
					}
				}
				else//father => Rchild
				{
					if (uncle->Color == Red)//case 1
					{
						ptr->Father->Color = Black;
						uncle->Color = Black;
						ptr->Father->Father->Color = Red;

						ptr = ptr->Father->Father;
					}
					else
					{
						if (ptr == ptr->Father->Lchild)//case 2
						{
							ptr = ptr->Father;
							R_Rotate(ptr);
						}

						//case 3
						ptr->Father->Color = Black;
						ptr->Father->Father->Color = Red;
						L_Rotate(ptr->Father->Father);
					}
				}
			}

			this->head->Color = Black;
		}
		
		[[noreturn]] void Delete_FixUp(TreeNode<Ty>* ptr)
		{
			TreeNode<Ty>* UnclePtr = FindUncle(ptr);

			if (ptr != nullptr)
			{
				if (ptr->Color == Red)//Red+Black
				{
					ptr->Color = Black;
				}
				else if (ptr->Color == Black && ptr != head && UnclePtr != nullptr)//Black+Black & ptr != head
				{
					if (UnclePtr->Color == Red)
					{
						UnclePtr->Color = Black;
						ptr->Father->Color = Red;

						L_Rotate(ptr->Father);
						UnclePtr = ptr->Father->Rchild;
					}
					else if ((UnclePtr->Rchild == nullptr || UnclePtr->Rchild->Color == Black) && (UnclePtr->Lchild == nullptr || UnclePtr->Lchild->Color == Black))
					{
						UnclePtr->Color = Red;
						ptr = ptr->Father;
					}
					else if (UnclePtr->Lchild->Color == Red && (UnclePtr->Rchild == nullptr || UnclePtr->Rchild->Color == Black))
					{
						UnclePtr->Lchild->Color = Black;
						UnclePtr->Color = Red;

						R_Rotate(UnclePtr);
						UnclePtr = ptr->Father->Rchild;
					}
					else if (UnclePtr->Rchild != nullptr && UnclePtr->Rchild->Color == Red)
					{
						UnclePtr->Color = ptr->Father->Color;
						ptr->Father->Color = Black;
						UnclePtr->Rchild->Color = Black;

						L_Rotate(ptr->Father);
						head = ptr;
					}

				}
			}
		}
		
		[[noreturn]] void L_Rotate(TreeNode<Ty>* ptr) noexcept
		{
			if (ptr != nullptr)
			{
				TreeNode<Ty>* k1 = ptr->Rchild;

				ptr->Rchild = k1->Lchild;
				if (k1->Lchild != nullptr)
					k1->Lchild->Father = ptr;

				k1->Father = ptr->Father;

				if (ptr->Father == this->header)
				{
					this->head = k1;
				}
				else
				{
					if (ptr->Father->Lchild == ptr)
						ptr->Father->Lchild = k1;
					else
						ptr->Father->Rchild = k1;
				}

				
				k1->Lchild = ptr;
				ptr->Father = k1;
			}
		}

		[[noreturn]] void R_Rotate(TreeNode<Ty>* ptr) noexcept
		{
			if (ptr != nullptr)
			{
				TreeNode<Ty>* k1 = ptr->Lchild;

				ptr->Lchild = k1->Rchild;
				if (k1->Rchild != nullptr)
					k1->Rchild->Father = ptr;

				k1->Father = ptr->Father;

				if (ptr->Father == this->header)
				{
					this->head = k1;
				}
				else
				{
					if (ptr == ptr->Father->Rchild)
						ptr->Father->Rchild = k1;
					else
						ptr->Father->Lchild = k1;
				}

			
				k1->Rchild = ptr;
				ptr->Father = k1;
			}
		}

		[[noreturn]] void TreeCopy(TreeNode<Ty>* ptr) noexcept
		{
			if (ptr)
			{
				this->Insert(ptr->data);
				TreeCopy(ptr->Lchild);
				TreeCopy(ptr->Rchild);
			}
		}

		TreeNode<Ty>* FindUncle(TreeNode<Ty>* ptr) const noexcept
		{
			if (ptr->Father != nullptr && ptr != this->head)
			{
				if (ptr->Father->Lchild != nullptr && ptr->Father->Rchild != nullptr)
				{
					if (ptr->Father->Lchild == ptr)
						return ptr->Father->Rchild;
					else
						return ptr->Father->Lchild;
				}
			}

			return nullptr;
		}
			
		TreeNode<Ty>* Maximum(TreeNode<Ty>* ptr) const noexcept
		{
			if (ptr != nullptr)
			{
				while (ptr->Rchild != nullptr)
				{
					ptr = ptr->Rchild;
				}

				return ptr;
			}

			return nullptr;
		}

		TreeNode<Ty>* Minimum(TreeNode<Ty>* ptr) const noexcept
		{
			if (ptr != nullptr)
			{
				while (ptr->Lchild != nullptr)
				{
					ptr = ptr->Lchild;
				}

				return ptr;
			}

			return nullptr;
		}
};