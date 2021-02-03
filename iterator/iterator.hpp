#pragma once

//compare struct
struct Compare_Method
{
	static bool Compare()
	{
	}
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


//iterator
template<typename Ty>
struct input_iterator
{
	private:
		Ty* ptr = nullptr;

	public:
		using self = input_iterator<Ty>;

	public:
		input_iterator() = default;

		input_iterator(Ty* InitPtr) :ptr(InitPtr)
		{
		}

		Ty& operator*()
		{
			return *ptr;
		}

		self& operator=(const self& obj)
		{
			this->ptr = obj.ptr;
			return *this;
		}

	protected:
		friend bool operator!=(const self& Lhs , const self& Rhs)
		{
			return Lhs.ptr != Rhs.ptr;
		}
};

template<typename Ty>
struct forward_iterator
{
	private:
		Ty* ptr = nullptr;

	public:
		using self = forward_iterator<Ty>;

	public:
		forward_iterator() = default;

		forward_iterator(Ty* InitPtr) :ptr(InitPtr)
		{
		}

		~forward_iterator()
		{
			delete ptr;
			ptr = nullptr;
		}


		Ty& operator*()
		{
			return *ptr;
		}

		self& operator++()
		{
			++ptr;
			return *this;
		}

		self operator++(int)
		{
			auto temp = *this;
			++ptr;

			return temp;
		}

		self& operator=(const self& obj)
		{
			this->ptr = obj.ptr;
			return *this;
		}

	protected:
		friend bool operator!=(const self& Lhs , const self& Rhs)
		{
			return Lhs.ptr != Rhs.ptr;
		}
};

template<typename Ty>
struct Bid_iterator
{
	private:
		Ty* ptr = nullptr;

	public:
		using self = Bid_iterator<Ty>;

	public:
		Bid_iterator() = default;

		Bid_iterator(Ty* InitPtr) :ptr(InitPtr)
		{
		}

		Ty& operator*()
		{
			return *ptr;
		}

		self& operator--()
		{
			--ptr;
			return *this;
		}

		self operator--(int)
		{
			auto temp = *this;
			--ptr;

			return temp;
		}

		self& operator++()
		{
			++ptr;
			return *this;
		}

		self operator++(int)
		{
			auto temp = *this;
			++ptr;

			return temp;
		}

		self& operator=(const self& obj)
		{
			this->ptr = obj.ptr;
			return *this;
		}

	protected:
		friend bool operator!=(const self& Lhs , const self& Rhs)
		{
			return Lhs.ptr != Rhs.ptr;
		}
};

template<typename Ty>
struct Random_iterator
{
	private:
		Ty* ptr = nullptr;

	public:
		using self = Random_iterator<Ty>;

	public:
		Random_iterator() = default;

		Random_iterator(Ty* InitPtr) :ptr(InitPtr)
		{}

		Ty& operator*()
		{
			return *ptr;
		}

		self& operator--()
		{
			--ptr;
			return *this;
		}

		self operator--(int)
		{
			auto temp = *this;
			--ptr;

			return temp;
		}

		self& operator++()
		{
			++ptr;
			return *this;
		}

		self operator++(int)
		{
			auto temp = *this;
			++ptr;

			return temp;
		}

		self& operator=(const self& obj)
		{
			this->ptr = obj.ptr;
			return *this;
		}

		bool operator>(const self& obj)
		{
			if (ptr > obj.ptr)
				return true;

			return false;
		}

		bool operator<(const self& obj)
		{
			if (ptr < obj.ptr)
				return true;

			return false;
		}

	protected:
		friend bool operator!=(const self& Lhs , const self& Rhs)
		{
			return Lhs.ptr != Rhs.ptr;
		}
};


//const iterator
template<typename Ty>
struct const_input_iterator
{
	private:
		Ty* ptr = nullptr;

	public:
		using self = const_input_iterator<Ty>;

	public:
		const_input_iterator(const self& obj)
		{
			this->ptr = obj.ptr;
		}

		const_input_iterator(Ty* InitPtr) :ptr(InitPtr)
		{
		}

		Ty operator*() const
		{
			return *ptr;
		}

	protected:
		friend bool operator!=(const self& Lhs , const self& Rhs)
		{
			return Lhs.ptr != Rhs.ptr;
		}
};

template<typename Ty>
struct const_forward_iterator
{
	private:
		Ty* ptr = nullptr;

	public:
		using self = const_forward_iterator<Ty>;

	public:
		const_forward_iterator(const self& obj)
		{
			this->ptr = obj.ptr;
		}

		const_forward_iterator(Ty* InitPtr) :ptr(InitPtr)
		{
		}

		Ty operator*() const
		{
			return *ptr;
		}

		self& operator++()
		{
			++ptr;
			return *this;
		}

		self operator++(int)
		{
			auto temp = *this;
			++ptr;

			return temp;
		}

	protected:
		friend bool operator!=(const self& Lhs , const self& Rhs)
		{
			return Lhs.ptr != Rhs.ptr;
		}
};

template<typename Ty>
struct const_Bid_iterator
{
	private:
		Ty* ptr = nullptr;

	public:
		using self = const_Bid_iterator<Ty>;

	public:
		const_Bid_iterator(const self& obj)
		{
			this->ptr = obj.ptr;
		}

		const_Bid_iterator(Ty* InitPtr) :ptr(InitPtr)
		{
		}

		Ty operator*() const
		{
			return *ptr;
		}


		self& operator--()
		{
			--ptr;
			return *this;
		}

		self operator--(int)
		{
			auto temp = *this;
			--ptr;

			return temp;
		}

		self& operator++()
		{
			++ptr;
			return *this;
		}

		self operator++(int)
		{
			auto temp = *this;
			++ptr;

			return temp;
		}

	protected:
		friend bool operator!=(const self& Lhs , const self& Rhs)
		{
			return Lhs.ptr != Rhs.ptr;
		}
};

template<typename Ty>
struct const_Random_iterator
{
	private:
		Ty* ptr = nullptr;

	public:
		using self = const_Random_iterator<Ty>;

	public:
		const_Random_iterator(const self& obj)
		{
			this->ptr = obj.ptr;
		}

		const_Random_iterator(Ty* InitPtr) :ptr(InitPtr)
		{
		}

		Ty operator*() const
		{
			return *ptr;
		}

		self& operator--()
		{
			--ptr;
			return *this;
		}

		self operator--(int)
		{
			auto temp = *this;
			--ptr;

			return temp;
		}

		self& operator++()
		{
			++ptr;
			return *this;
		}

		self operator++(int)
		{
			auto temp = *this;
			++ptr;

			return temp;
		}

		bool operator>(const self& obj)
		{
			if (ptr > obj.ptr)
				return true;

			return false;
		}

		bool operator<(const self& obj)
		{
			if (ptr < obj.ptr)
				return true;

			return false;
		}

	protected:
		friend bool operator!=(const self& Lhs , const self& Rhs)
		{
			return Lhs.ptr != Rhs.ptr;
		}
};



//iterator for list
template<typename Ty>
struct List_iterator
{
	private:
		Ty* ptr = nullptr;

	public:
		using self = List_iterator<Ty>;

	public:
		List_iterator() = default;

		List_iterator(Ty* InitPtr):ptr(InitPtr)
		{}

		decltype(ptr->data)& operator*()
		{
			return ptr->data;
		}

		self& operator++()
		{
			if (ptr->next)
				ptr = ptr->next;
			return *this;
		}

		self operator++(int)
		{
			if (ptr->next)
				ptr = ptr->next;
			return *this;
		}

		self& operator--()
		{
			if (ptr->last)
				ptr = ptr->last;
			return *this;
		}

		self operator--(int)
		{
			if (ptr->last)
				ptr = ptr->last;
			return *this;
		}

		self& operator=(const self& obj)
		{
			this->ptr = obj.ptr;
			return *this;
		}

	private:
		friend bool operator!=(const self& Lhs , const self& Rhs)
		{
			return Lhs.ptr != Rhs.ptr;
		}
};


//const iterator for list
template<typename Ty>
struct const_List_iterator
{
	private:
		Ty* ptr = nullptr;

	public:
		using self = const_List_iterator<Ty>;

	public:
		const_List_iterator(const self& obj)
		{
			this->ptr = obj.ptr;
		}

		const_List_iterator(Ty* InitPtr) :ptr(InitPtr)
		{
		}

		decltype(ptr->data) operator*() const
		{
			return ptr->data;
		}

		self& operator++()
		{
			if (ptr->next)
				ptr = ptr->next;
			return *this;
		}

		self operator++(int)
		{
			auto temp = *this;

			if (ptr->next)
				ptr = ptr->next;

			return temp;
		}

		self& operator--()
		{
			if (ptr->last)
				ptr = ptr->last;
			return *this;
		}

		self operator--(int)
		{
			auto temp = *this;

			if (ptr->last)
				ptr = ptr->last;

			return temp;
		}

	private:
		friend bool operator!=(const self& Lhs , const self& Rhs)
		{
			return Lhs.ptr != Rhs.ptr;
		}
};



//iterator for RB_Tree
template<typename Ty>
struct RB_Tree_iterator
{
	private:
		Ty* ptr = nullptr;

		int step_count = 0;

	public:
		using self = RB_Tree_iterator<Ty>;

	public:
		RB_Tree_iterator() = default;

		RB_Tree_iterator(Ty* p):ptr(p)
		{}

		RB_Tree_iterator(Ty* p,int num):ptr(p),step_count(num)
		{ }

		decltype(ptr->data)& operator*()
		{
			return ptr->data;
		}

		int step()
		{
			return step_count;
		}

		self& operator+(int n)
		{
			for (int i = 0; i < n; ++i)
			{
				increment();
				step_count++;
			}

			return *this;
		}

		self& operator++()
		{
			increment();
			step_count++;

			return *this;
		}

		self operator++(int)
		{
			auto temp = *this;
			increment();
			step_count++;

			return temp;
		}

		self& operator--()
		{
			decrement();
			step_count--;

			return *this;
		}

		self operator--(int)
		{
			auto temp = *this;
			decrement();
			step_count--;

			return temp;
		}

		self& operator=(const self& obj)
		{
			this->ptr = obj.ptr;
			return *this;
		}

		bool operator<(const self& obj)
		{
			if (step_count < obj.step_count)
				return true;

			return false;
		}

		bool operator>(const self& obj)
		{
			if (step_count > obj.step_count)
				return true;

			return false;
		}

		bool operator<=(const self& obj)
		{
			if (step_count <= obj.step_count)
				return true;

			return false;
		}

		bool operator>=(const self& obj)
		{
			if (step_count >= obj.step_count)
				return true;

			return false;
		}

	private:
		void increment()
		{
			if (ptr->Rchild != nullptr)
			{
				ptr = ptr->Rchild;

				while (ptr->Lchild != nullptr)
				{
					ptr = ptr->Lchild;
				}
			}
			else
			{
				Ty* p = ptr->Father;

				while (ptr == p->Rchild)
				{
					ptr = p;
					p = p->Father;
				}
				if (ptr->Rchild != p)
				{
					ptr = p;
				}
			}
		}

		void decrement()
		{
			if (ptr->Color == 0 && ptr->Father->Father == ptr)
			{
				ptr = ptr->Rchild;
			}
			else if (ptr->Lchild != nullptr)
			{
				auto p = ptr->Lchild;

				while (p->Rchild != nullptr)
				{
					p = p->Rchild;
				}

				ptr = p;
			}
			else
			{
				Ty* p = ptr->Father;
				
				while (ptr == p->Lchild)
				{
					ptr = p;
					p = p->Father;
				}

				ptr = p;
			}
		}

	private:
		friend bool operator!=(const self& Lhs , const self& Rhs)
		{
			return Lhs.ptr != Rhs.ptr;
		}

		friend bool operator==(const self& Lhs , const self& Rhs)
		{
			return Lhs.ptr != Rhs.ptr;
		}
};

//const iterator for RB_Tree
template<typename Ty>
struct const_RB_Tree_iterator
{
	private:
		Ty* ptr = nullptr;

		int step_count = 0;

	public:
		using self = const_RB_Tree_iterator<Ty>;

	public:
		const_RB_Tree_iterator(const self& obj)
		{
			this->ptr = obj.ptr;
		}

		const_RB_Tree_iterator(Ty* p) :ptr(p)
		{}

		const_RB_Tree_iterator(Ty* p,int num):ptr(p),step_count(num)
		{ }

		decltype(ptr->data) operator*() const
		{
			return ptr->data;
		}

		int step()
		{
			return step_count;
		}

		self& operator+(int n)
		{
			for (int i = 0; i < n; ++i)
			{
				increment();
				step_count++;
			}

			return *this;
		}

		self& operator++()
		{
			increment();
			step_count++;

			return *this;
		}

		self operator++(int)
		{
			auto temp = *this;
			increment();
			step_count++;

			return temp;
		}

		self& operator--()
		{
			decrement();
			step_count--;

			return *this;
		}

		self operator--(int)
		{
			auto temp = *this;
			decrement();
			step_count--;

			return temp;
		}

		self& operator=(const self& obj)
		{
			this->ptr = obj.ptr;
			return *this;
		}

		bool operator<(const self& obj)
		{
			if (step_count < obj.step_count)
				return true;

			return false;
		}

		bool operator>(const self& obj)
		{
			if (step_count > obj.step_count)
				return true;

			return false;
		}

		bool operator<=(const self& obj)
		{
			if (step_count <= obj.step_count)
				return true;

			return false;
		}

		bool operator>=(const self& obj)
		{
			if (step_count >= obj.step_count)
				return true;

			return false;
		}

	private:
		void increment()
		{
			if (ptr->Rchild != nullptr)
			{
				ptr = ptr->Rchild;

				while (ptr->Lchild != nullptr)
				{
					ptr = ptr->Lchild;
				}
			}
			else
			{
				Ty* p = ptr->Father;

				while (ptr == p->Rchild)
				{
					ptr = p;
					p = p->Father;
				}
				if (ptr->Rchild != p)
				{
					ptr = p;
				}
			}
		}

		void decrement()
		{
			if (ptr->Color == 0 && ptr->Father->Father == ptr)
			{
				ptr = ptr->Rchild;
			}
			else if (ptr->Lchild != nullptr)
			{
				auto p = ptr->Lchild;

				while (p->Rchild != nullptr)
				{
					p = p->Rchild;
				}

				ptr = p;
			}
			else
			{
				Ty* p = ptr->Father;

				while (ptr == p->Lchild)
				{
					ptr = p;
					p = p->Father;
				}

				ptr = p;
			}
		}

	private:
		friend bool operator!=(const self& Lhs , const self& Rhs)
		{
			return Lhs.ptr != Rhs.ptr;
		}

		friend bool operator==(const self& Lhs , const self& Rhs)
		{
			return Lhs.ptr != Rhs.ptr;
		}
};



//iterator for hash table
template<typename Ty,typename Hash>//hash_node<Ty>*
struct hash_table_iterator
{
	private:
		//bucket node ptr
		Ty node;
		//hash_table ptr
		Hash* ptr;
		//bucket size
		int bucket_size = 0;
		//count
		int count = 0;

	public:
		using self = hash_table_iterator<Ty,Hash>;

	public:
		hash_table_iterator() = default;

		hash_table_iterator(Ty head , Hash* InitPtr , const int& size) :node(head) , ptr(InitPtr) , bucket_size(size)
		{
			if(node == nullptr)//head == nullptr
				bucket_jump();
		}

		decltype(node->val)& operator*()
		{
			return node->val;
		}

		self& operator=(const self& obj)
		{
			this->ptr = obj.ptr;
			return *this;
		}

		self& operator++()
		{
			node = node->next;

			if (node == nullptr)
			{
				bucket_jump();
			}

			return *this;
		}

		self operator++(int)
		{
			auto temp = *this;

			node = node->next;

			if (node == nullptr)
			{
				bucket_jump();
			}

			return temp;
		}

	private:
		void bucket_jump()
		{
			while (!node && ++count < bucket_size)
			{
				node = ptr->buckets[count];
			}
		}

		friend bool operator!=(const self& Lhs , const self& Rhs)
		{
			return Lhs.count != Rhs.bucket_size;
		}
};