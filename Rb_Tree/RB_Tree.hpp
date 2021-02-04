#pragma once
#include"iterator.hpp"
#include<initializer_list>
#include<functional>

using std::initializer_list;
using std::function;

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

		TreeNode() = default;

		TreeNode(T elem , TreeNode<T>* R = nullptr , TreeNode<T>* L = nullptr , TreeNode<T>* F = nullptr) :data(elem) , Rchild(R) , Lchild(L) , Father(F)
		{}
	};

	public:
		using self = RB_Tree<Ty , Compare_Class>;
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
		RB_Tree(const RB_Tree<Ty , Compare_Class>& obj):RB_Tree()
		{
			TreeCopy(obj.head);
		}

		RB_Tree(const initializer_list<Ty>& obj):RB_Tree()
		{
			for (auto p:obj)
			{
				Insert(p);
			}
		}

		explicit RB_Tree(Ty elem)
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

			head = nullptr;
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

		iterator erase(iterator ptr)
		{
			auto temp = ptr;

			int step = ptr.step();
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
				DeleteNode((*ptr));

				return iterator(header , NodeCount);
			}

			DeleteNode((*ptr));

			return iterator(Self_Search(next_num , head),step);
		}

		const_iterator erase(const_iterator& ptr)
		{
			auto temp = ptr;

			int step = ptr.step();
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
				DeleteNode((*ptr));

				return const_iterator(header , NodeCount);
			}

			DeleteNode((*ptr));

			return const_iterator(Self_Search(next_num , head) , step);
		}

		void erase(iterator p_begin , iterator p_end)
		{
			int n = p_begin.step();
			for (; n < p_end.step(); ++n)
			{
				p_begin = erase(p_begin);
			}
		}

		bool Search(Ty elem)
		{
			if (Self_Search(elem , head) != nullptr)
				return true;

			return false;
		}

		int count(Ty elem)
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

		int size()
		{
			return NodeCount;
		}

		void swap(RB_Tree<Ty , Compare_Class>& obj)
		{
			//keep obj tree
			Ty* arr = new Ty[obj.NodeCount];

			int count = 0;
			for (auto p : obj)
			{
				arr[count] = p;
				count++;
			}

			//swap obj tree
			obj.Destory();
			obj.TreeCopy(this->head);

			//swap this tree
			this->Destory();

			for (int n = 0; n < count; ++n)
			{
				Insert(arr[n]);
			}

			delete[] arr;
			arr = nullptr;
		}


		//iterator
		iterator begin()
		{
			return iterator(header->Lchild,0);
		}

		iterator end()
		{
			return iterator(header,NodeCount);
		}

		const_iterator cbegin() const
		{
			return const_iterator(header->Lchild,0);
		}

		const_iterator cend() const
		{
			return const_iterator(header,NodeCount);
		}


		//operator overload
		self& operator=(const RB_Tree<Ty , Compare_Class>& obj)
		{
			RB_Tree<Ty , Compare_Class>::const_iterator p = obj.cbegin();
			for (; p != obj.cend(); ++p)
			{
				Insert((*p));
				NodeCount++;
			}

			return *this;
		}

		bool operator==(const RB_Tree<Ty,Compare_Class>& obj)
		{
			if (NodeCount != obj.NodeCount)
				return false;

			RB_Tree<Ty , Compare_Class>::const_iterator p = obj.cbegin();
			RB_Tree<Ty , Compare_Class>::const_iterator self_p = cbegin();
			for (; p != obj.cend(),self_p != cend(); ++p,++self_p)
			{
				if ((*p) != (*self_p))
					return false;
			}	

			return true;
		}

		bool operator!=(const RB_Tree<Ty , Compare_Class>& obj)
		{
			return !((*this) == obj);
		}

		bool operator>(const RB_Tree<Ty , Compare_Class>& obj)
		{
			if (NodeCount > obj.NodeCount)
				return true;

			return false;
		}

		bool operator<(const RB_Tree<Ty , Compare_Class>& obj)
		{
			if (NodeCount < obj.NodeCount)
				return true;

			return false;
		}

		bool operator>=(const RB_Tree<Ty , Compare_Class>& obj)
		{
			if (NodeCount >= obj.NodeCount)
				return true;

			return false;
		}

		bool operator<=(const RB_Tree<Ty , Compare_Class>& obj)
		{
			if (NodeCount <= obj.NodeCount)
				return true;

			return false;
		}

	private:
		TreeNode<Ty>* Self_Search(Ty elem , TreeNode<Ty>* ptr)
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
					Insert_FixUp(ptr->Rchild);
				}
			}
			else if (elem < ptr->data)
			{
				Self_Insert(elem , ptr->Lchild , ptr);

				if (ptr->Father != header)
				{
					Insert_FixUp(ptr->Lchild);
				}
			}
			else if (elem == ptr->data)
			{
				if (compare())
				{
					Self_Insert(elem , ptr->Rchild , ptr);

					if (ptr->Father != header)
					{
						Insert_FixUp(ptr->Rchild);
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

		void Insert_FixUp(TreeNode<Ty>* ptr)
		{
			ptr->Color = Red;

			while (ptr != head && ptr->Father->Color == Red)
			{
				TreeNode<Ty>* uncle = FindUncle(ptr->Father);

				if (ptr->Father == ptr->Father->Father->Lchild)//father => Lchild
				{
					if (uncle != nullptr && uncle->Color == Red) //case 1
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
					if (uncle && uncle->Color == Red)//case 1
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
		
		void Delete_FixUp(TreeNode<Ty>* ptr)
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
		
		void L_Rotate(TreeNode<Ty>* ptr)
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

		void R_Rotate(TreeNode<Ty>* ptr)
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

		void TreeCopy(TreeNode<Ty>* ptr)
		{
			if (ptr)
			{
				this->Insert(ptr->data);
				TreeCopy(ptr->Lchild);
				TreeCopy(ptr->Rchild);
			}
		}

		TreeNode<Ty>* FindUncle(TreeNode<Ty>* ptr)
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