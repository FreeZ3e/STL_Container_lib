#pragma once
#include"iterator.hpp"
#include<functional>

using std::function;

//Compare sturct define
struct Compare_Method
{
	static bool Compare()
	{ }
};

struct Equal_Compare :public Compare_Method
{
	static bool Compare()
	{
		return true;
	}
};

struct Unique_Compare :public Compare_Method
{
	static bool Compare()
	{
		return false;
	}
};

template<typename Ty,typename Compare_Class = Unique_Compare>
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
		T data;
		TreeColor Color = Red;
		TreeNode<T>* Rchild;
		TreeNode<T>* Lchild;
		TreeNode<T>* Father;

		TreeNode(T elem , TreeNode<T>* R = nullptr , TreeNode<T>* L = nullptr , TreeNode<T>* F = nullptr) :data(elem) , Rchild(R) , Lchild(L) , Father(F)
		{
		}

		TreeNode()
		{ }
	};

	public:
		using TypeValue = Ty;
		using NodeType = TreeNode<Ty>;
		using iterator = RB_Tree_iterator<TreeNode<Ty>>;

	private:
		//compare function obj
		key_compare compare = Compare_Class::Compare;

		TreeNode<Ty>* header;
		TreeNode<Ty>* head;

		int NodeCount = 0;

	public:
		RB_Tree(Ty elem)
		{
			header = new TreeNode<Ty>;
			head = new TreeNode<Ty>(elem,nullptr,nullptr,header);
			head->Color = Black;

			header->Father = head;

			NodeCount++;
		}

		RB_Tree()
		{	
			header = new TreeNode<Ty>;
		}

		~RB_Tree()
		{
			delete header;
			header = nullptr;

			Destory();
		}

		void Destory()
		{
			Self_Destory(head);
			NodeCount = 0;
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

		bool Search(Ty elem)
		{
			return Self_Search(elem , head);
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
		bool Self_Search(Ty elem , TreeNode<Ty>* ptr)
		{
			if (ptr != nullptr)
			{
				if (ptr->data == elem)
				{
					return true;
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

			return false;
		}

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
				ptr = new TreeNode<Ty>(elem , nullptr , nullptr , father);

				if (NodeCount == 0)
				{
					ptr->Color = Black;
					ptr->Father = header;
					header->Father = ptr;
				}
			}
			else if (elem > ptr->data)
			{
				Self_Insert(elem , ptr->Rchild , ptr);

				if (ptr->Father != header)
				{
					Insert_FixUp(ptr , 1);
				}
			}
			else if (elem < ptr->data)
			{
				Self_Insert(elem , ptr->Lchild , ptr);

				if (ptr->Father != header)
				{
					Insert_FixUp(ptr , 2);
				}
			}
			else if (elem == ptr->data)
			{
				if (compare())
				{
					Self_Insert(elem , ptr->Rchild , ptr);

					if (ptr->Father != header)
					{
						Insert_FixUp(ptr , 1);
					}
				}
			}
		}
		
		void Self_Delete(Ty elem , TreeNode<Ty>*& ptr)
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
					else if(ptr->Lchild != nullptr)
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
					Self_Delete(elem,ptr->Rchild);

					Delete_FixUp(ptr);
				}
			}
		}

		void Insert_FixUp(TreeNode<Ty>*& ptr, int tag)
		{	
			TreeNode<Ty>* UnclePtr = FindUncle(ptr);

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
						L_Rotate(ptr->Father,head);
					}
					else//insert Lchild
					{
						ptr->Father->Color = Black;

						if(ptr->Father->Father != nullptr)
							ptr->Father->Father->Color = Red;

						R_Rotate(ptr->Father->Father,head);
					}
				}
			}
		}
		
		void Delete_FixUp(TreeNode<Ty>*& ptr)
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

						L_Rotate(ptr->Father , head);
						UnclePtr = ptr->Father->Rchild;
					}
					else if ((UnclePtr->Rchild->Color == Black || UnclePtr->Rchild == nullptr) && (UnclePtr->Lchild->Color == Black || UnclePtr->Lchild == nullptr))
					{
						UnclePtr->Color = Red;
						ptr = ptr->Father;
					}
					else if (UnclePtr->Lchild->Color == Red && (UnclePtr->Rchild->Color == Black || UnclePtr->Rchild == nullptr))
					{
						UnclePtr->Lchild->Color = Black;
						UnclePtr->Color = Red;

						R_Rotate(UnclePtr , head);
						UnclePtr = ptr->Father->Rchild;
					}
					else if (UnclePtr->Rchild->Color == Red)
					{
						UnclePtr->Color = ptr->Father->Color;
						ptr->Father->Color = Black;
						UnclePtr->Rchild->Color = Black;

						L_Rotate(ptr->Father , head);							
						head = ptr;
					}
				}
			}
		}
		
		void Check_Up(TreeNode<Ty>* ptr)
		{
			if (ptr->Father != nullptr)
			{
				TreeNode<Ty>* temp = FindUncle(ptr);

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

		void L_Rotate(TreeNode<Ty>*& ptr,TreeNode<Ty>*& head)
		{
			if (ptr != nullptr)
			{
				TreeNode<Ty>* k1 = ptr->Rchild;

				ptr->Rchild = k1->Lchild;
				if (k1->Lchild != nullptr)
					k1->Lchild->Father = ptr;

				k1->Father = ptr->Father;

				if (ptr->Father == header)
				{
					head = k1;
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

		void R_Rotate(TreeNode<Ty>*& ptr,TreeNode<Ty>*& head)
		{
			if (ptr != nullptr)
			{
				TreeNode<Ty>* k1 = ptr->Lchild;

				ptr->Lchild = k1->Rchild;
				if (k1->Rchild != nullptr)
					k1->Rchild->Father = ptr;

				k1->Father = ptr->Father;

				if (ptr->Father == header)
				{
					head = k1;
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

		TreeNode<Ty>* FindUncle(TreeNode<Ty>* ptr)
		{
			if (ptr->Father)
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