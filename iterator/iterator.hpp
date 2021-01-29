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
	protected:
		Ty* ptr = nullptr;

	public:
		using self = input_iterator<Ty>;

	public:
		input_iterator() = default;

		input_iterator(Ty* InitPtr) :ptr(InitPtr)
		{}

		virtual ~input_iterator()
		{}

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
struct forward_iterator :public input_iterator<Ty>
{
	protected:
		int CurrentNum = 0;
		int InitNum = 0;

	public:
		using self = forward_iterator<Ty>;

	public:
		forward_iterator() = default;

		forward_iterator(Ty* InitPtr , int num) :input_iterator<Ty>(InitPtr) , CurrentNum(num) , InitNum(num)
		{}

		virtual ~forward_iterator()
		{}

		self& operator++()
		{
			++input_iterator<Ty>::ptr;
			return *this;
		}

		self& operator++(int)
		{
			input_iterator<Ty>::ptr++;
			return *this;
		}
};

template<typename Ty>
struct Bid_iterator :public forward_iterator<Ty>
{
	public:
		using self = Bid_iterator<Ty>;

	public:
		Bid_iterator() = default;

		Bid_iterator(Ty* InitPtr , int num) :forward_iterator<Ty>(InitPtr , num)
		{}

		virtual ~Bid_iterator()
		{}

		self& operator--()
		{
			--forward_iterator<Ty>::ptr;
			return *this;
		}

		self* operator--(int)
		{
			forward_iterator<Ty>::ptr--;
			return *this;
		}
};

template<typename Ty>
struct Random_iterator :public Bid_iterator<Ty>
{
	public:
		using self = Random_iterator<Ty>;

	public:
		Random_iterator() = default;

		Random_iterator(Ty* IninPtr , int num) :Bid_iterator<Ty>(IninPtr , num)
		{}

		bool operator>(const self& obj)
		{
			if (Bid_iterator<Ty>::ptr > obj.ptr)
				return true;

			return false;
		}

		bool operator<(const self& obj)
		{
			if (Bid_iterator<Ty>::ptr < obj.ptr)
				return true;

			return false;
		}
};



//iterator for list
template<typename Ty>
struct List_iterator
{
	private:
		Ty* ptr;

	public:
		using self = List_iterator<Ty>;

	public:
		List_iterator() = default;

		List_iterator(Ty* InitPtr):ptr(InitPtr)
		{}

		decltype(ptr->data)& operator*() const
		{
			return ptr->data;
		}

		self& operator++()
		{
			if (ptr->next)
				ptr = ptr->next;
			return *this;
		}

		self& operator++(int)
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

		self& operator--(int)
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


//iterator for RB_Tree
template<typename Ty>
struct RB_Tree_iterator
{
	private:
		Ty* ptr;

	public:
		using self = RB_Tree_iterator<Ty>;

	public:
		RB_Tree_iterator() = default;

		RB_Tree_iterator(Ty* p):ptr(p)
		{}

		decltype(ptr->data) operator*() const
		{
			return ptr->data;
		}

		self& operator++()
		{
			increment();
			return *this;
		}

		self& operator++(int)
		{
			increment();
			return *this;
		}

		self& operator--()
		{
			decrement();
			return *this;
		}

		self& operator--(int)
		{
			decrement();
			return *this;
		}

		void operator=(const self& p)
		{
			this->ptr = p.ptr;
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

		decltype(node->val)& operator*() const
		{
			return node->val;
		}

		self& operator=(const Ty& NewPtr)
		{
			this->ptr = NewPtr;
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

		self& operator++(int)
		{
			node = node->next;

			if (node == nullptr)
			{
				bucket_jump();
			}

			return *this;
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