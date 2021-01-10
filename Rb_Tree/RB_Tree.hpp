#pragma once
#include"iterator.hpp"


template<typename Ty>
class RB_Tree
{
	//color define
	enum TreeColor:int{Red = 0,Black = 1};

	//TreeNode define
	template<typename T>
	struct TreeNode
	{
		T data;
		TreeColor Color = Red;
		TreeNode<T>* Rchild;
		TreeNode<T>* Lchild;
		TreeNode<T>* Father;

		TreeNode(T elem, TreeNode<T>* R = nullptr, TreeNode<T>*L = nullptr, TreeNode<T>*F = nullptr):data(elem),Rchild(R),Lchild(L),Father(F)
		{ }

		TreeNode() = delete;
	};

	using TypeValue = Ty;
	using iterator = RB_Tree_iterator<TreeNode<Ty>>;

	private:
		TreeNode<Ty>* header;
		TreeNode<Ty>* head;

		TreeNode<Ty>* k1;
		TreeNode<Ty>* uncle;
		TreeNode<Ty>* temp;

		int NodeCount = 0;

	public:
		RB_Tree(Ty elem)
		{
			header = new TreeNode<Ty>(0);
			head = new TreeNode<Ty>(elem,nullptr,nullptr,header);
			head->Color = Black;

			header->Father = head;
			k1 = uncle = temp = nullptr;
		}

		~RB_Tree()
		{
			k1 = nullptr;
			uncle = nullptr;
			temp = nullptr;

			destory();
		}

		void destory()
		{
			delete header;
			header = nullptr;

			Self_Destory(head);
		}

		void Insert(Ty elem)
		{
			Self_Insert(elem , head);

			header->Lchild = Minimum(head);
			header->Rchild = Maximum(head);
			NodeCount++;
		}

		void DeleteNode(Ty elem)
		{
			Self_Delete(elem , head);

			header->Lchild = Minimum(head);
			header->Rchild = Maximum(head);
			NodeCount--;
		}

		//iterator
		iterator begin()
		{
			return iterator(header->Lchild);
		}

		iterator end()
		{
			return iterator(header);
		}

	private:
		void Self_Destory(TreeNode<Ty>*& ptr)
		{
			if (ptr)
			{
				auto p = ptr;
				Self_Destory(ptr->Rchild);
				Self_Destory(ptr->Lchild);

				delete p;
				ptr = nullptr;
			}
		}


		void Self_Insert(Ty elem , TreeNode<Ty>*& ptr , TreeNode<Ty>* father = nullptr)
		{
			if (ptr == nullptr)
			{
				ptr = new TreeNode<Ty>(elem,nullptr,nullptr,father);
			}
			else if (elem > ptr->data)
			{
				Self_Insert(elem , ptr->Rchild , ptr);

				if (ptr->Father != header)
				{
					uncle = FindUncle(ptr);
					Insert_FixUp(ptr , uncle , 1);
				}
			}
			else if (elem < ptr->data)
			{
				Self_Insert(elem , ptr->Lchild , ptr);

				if (ptr->Father != header)
				{
					uncle = FindUncle(ptr);
					Insert_FixUp(ptr , uncle , 2);
				}
			}
		}

		TreeNode<Ty>* Self_Delete(Ty elem , TreeNode<Ty>*& ptr)
		{
			if (ptr != nullptr)
			{
				if (ptr->data == elem)
				{
					if (ptr->Lchild != nullptr && ptr->Rchild != nullptr)
					{
						temp = Minimum(ptr->Rchild);
						ptr->data = temp->data;

						ptr->Rchild = Self_Delete(temp->data , temp);
					}
					else if(ptr->Lchild != nullptr)
					{
						temp = Maximum(ptr->Lchild);
						ptr->data = temp->data;

						ptr->Lchild = Self_Delete(temp->data , temp);
					}
					else if (ptr->Rchild != nullptr)
					{
						temp = Minimum(ptr->Rchild);
						ptr->data = temp->data;

						ptr->Rchild = Self_Delete(temp->data , temp);
					}
					else
					{
						temp = ptr;

						delete temp;
						ptr = nullptr;
					}

					return nullptr;
				}
				else if (ptr->data > elem)
				{
					return Self_Delete(elem , ptr->Lchild);

					uncle = FindUncle(ptr);
					Delete_FixUp(ptr , uncle);
				}
				else if (ptr->data < elem)
				{
					return Self_Delete(elem,ptr->Rchild);

					uncle = FindUncle(ptr);
					Delete_FixUp(ptr , uncle);
				}
			}

			return nullptr;
		}

		void Insert_FixUp(TreeNode<Ty>*& ptr , TreeNode<Ty>*& UnclePtr , int tag)
		{	
			if (UnclePtr != nullptr)
			{
				if (UnclePtr->Color == Red)
				{
					ptr->Father->Color = Black;
					UnclePtr->Color = Black;

					if (ptr->Father->Father != nullptr)
						ptr->Father->Father->Color = Red;

					Check_Up(ptr);
				}
				else
				{
					if (tag == 1)//insert Rchild
					{
						ptr->Father = L_Rotate(ptr->Father);
					}
					else//insert Lchild
					{
						ptr->Father->Color = Black;

						if(ptr->Father->Father != nullptr)
							ptr->Father->Father->Color = Red;

						ptr->Father->Father = R_Rotate(ptr->Father->Father);
					}
				}
			}
		}
		
		void Delete_FixUp(TreeNode<Ty>*& ptr , TreeNode<Ty>*& UnclePtr)
		{
			if (ptr->Color == Red)
			{
				ptr->Color = Black;
			}
			else if (ptr->Color == Black && ptr->Father != nullptr)
			{
				if (UnclePtr->Color == Red)
				{
					UnclePtr->Color = Black;
					ptr->Father->Color = Red;

					ptr->Father = L_Rotate(ptr->Father);
				}
				else if (UnclePtr->Color == Black && UnclePtr->Lchild->Color == Black && UnclePtr->Rchild->Color == Black)
				{
					UnclePtr->Color = Red;
				}
				else if (UnclePtr->Color == Black && UnclePtr->Lchild->Color == Red && UnclePtr->Rchild->Color == Black)
				{
					UnclePtr->Lchild->Color = Black;
					UnclePtr->Color = Red;

					UnclePtr = R_Rotate(UnclePtr);
				}
				else if (UnclePtr->Color == Black && UnclePtr->Rchild->Color == Red)
				{
					UnclePtr->Color = ptr->Father->Color;
					ptr->Father->Color = Black;

					UnclePtr->Rchild->Color = Black;
					ptr->Father = L_Rotate(ptr->Father);
				}
			}
		}
		
		void Check_Up(TreeNode<Ty>* ptr)
		{
			if (ptr->Father != nullptr)
			{
				temp = FindUncle(ptr);

				if (ptr->Color != temp->Color)
				{
					temp->Color = ptr->Color;
				}

				if (ptr->Father->Father != nullptr)
				{
					if(ptr->Father != header)
						Check_Up(ptr->Father);
				}
			}
		}

		TreeNode<Ty>* L_Rotate(TreeNode<Ty>* ptr)
		{
			if (ptr != nullptr)
			{
				k1 = ptr->Rchild;

				ptr->Rchild = k1->Lchild;
				if (k1->Lchild != nullptr)
					k1->Lchild->Father = ptr;

				k1->Father = ptr->Father;

				k1->Lchild = ptr;
				ptr->Father = k1;

				return k1;
			}

			return nullptr;
		}

		TreeNode<Ty>* R_Rotate(TreeNode<Ty>* ptr)
		{
			if (ptr != nullptr)
			{
				k1 = ptr->Lchild;

				ptr->Lchild = k1->Rchild;
				if (k1->Rchild != nullptr)
					k1->Rchild->Father = ptr;

				k1->Father = ptr->Father;

				k1->Rchild = ptr;
				ptr->Father = k1;

				return k1;
			}

			return nullptr;
		}

		TreeNode<Ty>* FindUncle(TreeNode<Ty>* ptr)
		{
			if (ptr->Father)
			{
				if (ptr->Father->Lchild != nullptr && ptr->Father->Rchild)
				{
					if (ptr->Father->Lchild == ptr)
						return ptr->Father->Rchild;
					else
						return ptr->Father->Lchild;
				}
			}

			return nullptr;
		}
			
		TreeNode<Ty>* Maximum(TreeNode<Ty>* ptr)
		{
			if (ptr)
			{
				while (ptr->Rchild != nullptr)
				{
					ptr = ptr->Rchild;
				}

				return ptr;
			}

			return nullptr;
		}

		TreeNode<Ty>* Minimum(TreeNode<Ty>* ptr)
		{
			if (ptr)
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