/* iterator implementation
 *
 * Copyright(c) 2021 Mashiro -1262159823@qq.com
 *
 * This File is part of CONTAINER LIBRARY project.
 *
 * version : 1.1.0
 *
 * author : Mashiro
 *
 * File name : iterator.hpp -iterator part.
 *
 * This library is free software;you can redistribute is and/or modify it
 * under the APACHE LICENSE 2.0 as published by the Free Software Foundation.
 * ------------------------------------------------------------------------
 */

#pragma once
#include"errors.hpp"

#if _LIB_DEBUG_LEVEL == 1

#include<assert.h>

#endif //_LIB_DEBUG_LEVEL


//compare struct
struct Compare_Method
{
	_NODISCARD static bool Compare() noexcept
	{
	}
};

struct Equal_Compare :public Compare_Method
{
	_NODISCARD static bool Compare() noexcept
	{
		return true;
	}
};

struct Unique_Compare :public Compare_Method
{
	_NODISCARD static bool Compare() noexcept
	{
		return false;
	}
};



//insert iterator
template<typename container>
class insert_iterator
{
	private:
		container* ptr = nullptr;

	public:
		using self = insert_iterator<container>;
		using value_type = typename container::value_type;

	public:
		insert_iterator() = delete;

		explicit insert_iterator(container& obj) :ptr(&obj)
		{
		}

		insert_iterator(const self& obj) :ptr(obj.ptr)
		{
		}

		~insert_iterator()
		{
			ptr = nullptr;
		}

		self& operator()(const value_type& elem)
		{
			ptr->insert(elem);
			return *this;
		}


		//opeartor ban
		self& operator=(self) = delete;
		self& operator++() = delete;
		self operator++(int n) = delete;
		self& operator--() = delete;
		self operator--(int n) = delete;
};

//back_insert_iterator
template<typename container>
class back_insert_iterator
{
	private:
		container* ptr = nullptr;

	public:
		using self = back_insert_iterator<container>;
		using value_type = typename container::value_type;

	public:
		back_insert_iterator() = delete;

		explicit back_insert_iterator(container& obj) :ptr(&obj)
		{
		}

		back_insert_iterator(const self& obj) :ptr(obj.ptr)
		{
		}

		~back_insert_iterator()
		{
			ptr = nullptr;
		}

		self& operator()(const value_type& elem)
		{
			ptr->push_back(elem);
			return *this;
		}

		//opeartor ban
		self& operator=(self) = delete;
		self& operator++() = delete;
		self operator++(int n) = delete;
		self& operator--() = delete;
		self operator--(int n) = delete;
};

//front_insert_iterator
template<typename container>
class front_insert_iterator
{
	private:
		container* ptr = nullptr;

	public:
		using self = front_insert_iterator<container>;
		using value_type = typename container::value_type;

	public:
		front_insert_iterator() = delete;

		explicit front_insert_iterator(container& obj) :ptr(&obj)
		{
		}

		front_insert_iterator(const self& obj) :ptr(obj.ptr)
		{
		}

		~front_insert_iterator()
		{
			ptr = nullptr;
		}

		self& operator()(const value_type& elem)
		{
			ptr->push_front(elem);
			return *this;
		}

		//opeartor ban
		self& operator=(self) = delete;
		self& operator++() = delete;
		self operator++(int n) = delete;
		self& operator--() = delete;
		self operator--(int n) = delete;
};

//reverse iterator
template<typename iterator_t>
class reverse_iterator
{
	private:
		iterator_t iter;

	public:
		using self = reverse_iterator<iterator_t>;
		using value_type = typename iterator_t::value_type;

	public:
		reverse_iterator() = delete;

		explicit reverse_iterator(iterator_t obj) :iter(obj)
		{
		}

		reverse_iterator(const self& obj) :iter(obj.iter)
		{
		}


		iterator_t base() const
		{
			return iter;
		}

		_NODISCARD decltype(auto) operator*() const noexcept
		{
			iterator_t temp = iter;
			return *--temp;
		}

		self& operator++() noexcept
		{
			--iter;
			return *this;
		}

		self operator++(int) noexcept
		{
			self temp = *this;

			--iter;
			return temp;
		}

		_NODISCARD self& operator+(int n) noexcept
		{
			for (int i = 0; i < n; ++i)
			{
				--iter;
			}

			return *this;
		}

		self& operator--() noexcept
		{
			++iter;
			return *this;
		}

		self operator--(int) noexcept
		{
			self temp = *this;

			++iter;
			return temp;
		}

		_NODISCARD self& operator-(int n) noexcept
		{
			for (int i = 0; i < n; ++i)
			{
				++iter;
			}

			return *this;
		}

	private:
		friend bool operator!=(const self& Lhs , const self& Rhs)
		{
			return Lhs.iter != Rhs.iter;
		}

		friend bool operator==(const self& Lhs , const self& Rhs)
		{
			return Lhs.iter == Rhs.iter;
		}
};


//helper function
template<typename container>
_NODISCARD inline insert_iterator<container> inserter(container& obj)
{
	return insert_iterator<container>(obj);
}

template<typename container>
_NODISCARD inline front_insert_iterator<container> front_inserter(container& obj)
{
	return front_insert_iterator<container>(obj);
}

template<typename container>
_NODISCARD inline back_insert_iterator<container> back_inserter(container& obj)
{
	return back_insert_iterator<container>(obj);
}

template<typename iterator_t>
_NODISCARD inline reverse_iterator<iterator_t> reverser(iterator_t obj)
{
	return reverse_iterator<iterator_t>(obj);
}





//iterator
template<typename Ty>
struct input_iterator
{
	private:
		Ty* ptr = nullptr;

	public:
		using self = input_iterator<Ty>;
		using value_type = Ty;

	public:
		input_iterator() = default;

		explicit input_iterator(Ty* InitPtr) :ptr(InitPtr)
		{}

		input_iterator(const self& obj):ptr(obj.ptr)
		{ }

		~input_iterator()
		{
			ptr = nullptr;
		}

		_NODISCARD Ty& operator*() noexcept
		{
			return *ptr;
		}

		_NODISCARD const Ty& operator*() const noexcept
		{
			return *ptr;
		}

		self& operator=(const self& obj)
		{
			auto temp = obj.ptr;
			ptr = temp;

			return *this;
		}

	protected:
		friend bool operator!=(const self& Lhs , const self& Rhs)
		{
			return Lhs.ptr != Rhs.ptr;
		}

		friend bool operator==(const self& Lhs , const self& Rhs)
		{
			return Lhs.ptr == Rhs.ptr;
		}
};

template<typename Ty>
struct forward_iterator
{
	private:
		Ty* ptr = nullptr;

	public:
		using self = forward_iterator<Ty>;
		using value_type = Ty;

	public:
		forward_iterator() = default;

		explicit forward_iterator(Ty* InitPtr) :ptr(InitPtr)
		{}

		forward_iterator(const self& obj):ptr(obj.ptr)
		{ }

		~forward_iterator()
		{
			ptr = nullptr;
		}


		_NODISCARD Ty& operator*() noexcept
		{
			return *ptr;
		}

		_NODISCARD const Ty& operator*() const noexcept
		{
			return *ptr;
		}

		_NODISCARD self operator+(int n) const noexcept
		{
			return self(ptr + n);
		}

		self& operator++() noexcept
		{
			++ptr;
			return *this;
		}

		self operator++(int) noexcept
		{
			auto temp = *this;
			++ptr;

			return temp;
		}

		self& operator=(const self& obj)
		{
			auto temp = obj.ptr;
			ptr = temp;

			return *this;
		}

	protected:
		friend bool operator!=(const self& Lhs , const self& Rhs)
		{
			return Lhs.ptr != Rhs.ptr;
		}

		friend bool operator==(const self& Lhs , const self& Rhs)
		{
			return Lhs.ptr == Rhs.ptr;
		}
};

template<typename Ty>
struct Bid_iterator
{
	private:
		Ty* ptr = nullptr;

	public:
		using self = Bid_iterator<Ty>;
		using value_type = Ty;

	public:
		Bid_iterator() = default;

		explicit Bid_iterator(Ty* InitPtr) :ptr(InitPtr)
		{}

		Bid_iterator(const self& obj):ptr(obj.ptr)
		{ }

		~Bid_iterator()
		{
			ptr = nullptr;
		}

		_NODISCARD Ty& operator*() noexcept
		{
			return *ptr;
		}

		_NODISCARD const Ty& operator*() const noexcept
		{
			return *ptr;
		}

		_NODISCARD self operator+(int n) const noexcept
		{
			return self(ptr + n);
		}

		_NODISCARD self operator-(int n) const noexcept
		{
			return self(ptr - n);
		}

		self& operator--() noexcept
		{
			--ptr;
			return *this;
		}

		self operator--(int) noexcept
		{
			auto temp = *this;
			--ptr;

			return temp;
		}

		self& operator++() noexcept
		{
			++ptr;
			return *this;
		}

		self operator++(int) noexcept
		{
			auto temp = *this;
			++ptr;

			return temp;
		}

		self& operator=(const self& obj)
		{
			auto temp = obj.ptr;
			ptr = temp;

			return *this;
		}

	protected:
		friend bool operator!=(const self& Lhs , const self& Rhs)
		{
			return Lhs.ptr != Rhs.ptr;
		}

		friend bool operator==(const self& Lhs , const self& Rhs)
		{
			return Lhs.ptr == Rhs.ptr;
		}
};

template<typename Ty>
struct Random_iterator
{
	private:
		Ty* ptr = nullptr;

		int step_count = 0;
		size_t limit = 0;

	public:
		using self = Random_iterator<Ty>;
		using value_type = Ty;

	public:
		Random_iterator() = default;

		explicit Random_iterator(Ty* InitPtr , size_t size) :ptr(InitPtr) , limit(size)
		{}

		explicit Random_iterator(Ty* InitPtr , int num , size_t size) :ptr(InitPtr) , step_count(num) , limit(size)
		{}

		Random_iterator(const self& obj) :ptr(obj.ptr),step_count(obj.step_count),limit(obj.limit)
		{ }

		~Random_iterator() noexcept
		{
			ptr = nullptr;
		}

		_NODISCARD Ty& operator*() noexcept
		{
		#if _LIB_DEBUG_LEVEL == 1

			_BUG_VERIFY((step_count < limit) , "out of range");
			assert(step_count < limit);

		#endif // _LIB_DEBUG_LEVEL == 1

			return *ptr;
		}

		_NODISCARD const Ty& operator*() const noexcept
		{
		#if _LIB_DEBUG_LEVEL == 1

			_BUG_VERIFY((step_count < limit) , "out of range");
			assert(step_count < limit);

		#endif // _LIB_DEBUG_LEVEL == 1

			return *ptr;
		}

		_NODISCARD int step() const noexcept
		{
			return step_count;
		}

		_NODISCARD self operator+(int n) const noexcept
		{
			return self(ptr + n , step_count + n , limit);
		}

		_NODISCARD self operator-(int n) const noexcept
		{
			return self(ptr - n , step_count - n , limit);
		}

		self& operator--() noexcept
		{
			--ptr;
			step_count--;

			return *this;
		}

		self operator--(int) noexcept
		{
			auto temp = *this;
			--ptr;
			step_count--;

			return temp;
		}

		self& operator++() noexcept
		{
			++ptr;
			step_count++;

			return *this;
		}

		self operator++(int) noexcept
		{
			auto temp = *this;
			++ptr;
			step_count++;

			return temp;
		}

		self& operator=(const self& obj)
		{
			auto temp = obj.ptr;
			ptr = temp;
			step_count = obj.step_count;
			limit = obj.limit;

			return *this;
		}

		bool operator>(const self& obj) const
		{
			if (step_count > obj.step_count)
				return true;

			return false;
		}

		bool operator<(const self& obj) const
		{
			if (step_count < obj.step_count)
				return true;

			return false;
		}

		bool operator>=(const self& obj) const
		{
			if (step_count >= obj.step_count)
				return true;

			return false;
		}

		bool operator<=(const self& obj) const
		{
			if (step_count <= obj.step_count)
				return true;

			return false;
		}

	protected:
		friend bool operator!=(const self& Lhs , const self& Rhs)
		{
			return Lhs.ptr != Rhs.ptr;
		}

		friend bool operator==(const self& Lhs , const self& Rhs)
		{
			return Lhs.ptr == Rhs.ptr;
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
		using value_type = Ty;

	public:
		const_input_iterator(const self& obj)
		{
			this->ptr = obj.ptr;
		}

		explicit const_input_iterator(Ty* InitPtr) :ptr(InitPtr)
		{}

		~const_input_iterator()
		{
			ptr = nullptr;
		}


		_NODISCARD const Ty& operator*() const noexcept
		{
			return *ptr;
		}

	protected:
		friend bool operator!=(const self& Lhs , const self& Rhs)
		{
			return Lhs.ptr != Rhs.ptr;
		}

		friend bool operator==(const self& Lhs , const self& Rhs)
		{
			return Lhs.ptr == Rhs.ptr;
		}
};

template<typename Ty>
struct const_forward_iterator
{
	private:
		Ty* ptr = nullptr;

	public:
		using self = const_forward_iterator<Ty>;
		using value_type = Ty;

	public:
		const_forward_iterator(const self& obj)
		{
			this->ptr = obj.ptr;
		}

		explicit const_forward_iterator(Ty* InitPtr) :ptr(InitPtr)
		{}

		~const_forward_iterator()
		{
			ptr = nullptr;
		}


		_NODISCARD const Ty& operator*() const noexcept
		{
			return *ptr;
		}

		_NODISCARD self operator+(int n) const noexcept
		{
			return self(ptr + n);
		}

		self& operator++() noexcept
		{
			++ptr;
			return *this;
		}

		self operator++(int) noexcept
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

		friend bool operator==(const self& Lhs , const self& Rhs)
		{
			return Lhs.ptr == Rhs.ptr;
		}
};

template<typename Ty>
struct const_Bid_iterator
{
	private:
		Ty* ptr = nullptr;

	public:
		using self = const_Bid_iterator<Ty>;
		using value_type = Ty;

	public:
		const_Bid_iterator(const self& obj)
		{
			this->ptr = obj.ptr;
		}

		explicit const_Bid_iterator(Ty* InitPtr) :ptr(InitPtr)
		{}

		~const_Bid_iterator()
		{
			ptr = nullptr;
		}


		_NODISCARD const Ty& operator*() const noexcept
		{
			return *ptr;
		}

		_NODISCARD self operator+(int n) const noexcept
		{
			return self(ptr + n);
		}

		_NODISCARD self operator-(int n) const noexcept
		{
			return self(ptr - n);
		}

		self& operator--() noexcept
		{
			--ptr;
			return *this;
		}

		self operator--(int) noexcept
		{
			auto temp = *this;
			--ptr;

			return temp;
		}

		self& operator++() noexcept
		{
			++ptr;
			return *this;
		}

		self operator++(int) noexcept
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

		friend bool operator==(const self& Lhs , const self& Rhs)
		{
			return Lhs.ptr == Rhs.ptr;
		}
};

template<typename Ty>
struct const_Random_iterator
{
	private:
		Ty* ptr = nullptr;

		int step_count = 0;
		size_t limit = 0;

	public:
		using self = const_Random_iterator<Ty>;
		using value_type = Ty;

	public:
		const_Random_iterator(const self& obj)
		{
			this->ptr = obj.ptr;
			this->step_count = obj.step_count;
			this->limit = obj.limit;
		}

		explicit const_Random_iterator(Ty* InitPtr , size_t size) :ptr(InitPtr) , limit(size)
		{}

		explicit const_Random_iterator(Ty* InitPtr , int num , size_t size) :ptr(InitPtr) , step_count(num) , limit(size)
		{}

		~const_Random_iterator()
		{
			ptr = nullptr;
		}

		_NODISCARD const Ty& operator*() const noexcept
		{
		#if _LIB_DEBUG_LEVEL == 1

			_BUG_VERIFY((step_count < limit) , "out of range");
			assert(step_count < limit);

		#endif // _LIB_DEBUG_LEVEL == 1

			return *ptr;
		}

		_NODISCARD self operator+(int n) const noexcept
		{
			return self(ptr + n , step_count + n , limit);
		}

		_NODISCARD self operator-(int n) const noexcept
		{
			return self(ptr - n , step_count - n , limit);
		}

		self& operator--() noexcept
		{
			--ptr;
			step_count--;

			return *this;
		}

		self operator--(int) noexcept
		{
			auto temp = *this;
			--ptr;
			step_count--;

			return temp;
		}

		self& operator++() noexcept
		{
			++ptr;
			step_count++;

			return *this;
		}

		self operator++(int) noexcept
		{
			auto temp = *this;
			++ptr;
			step_count++;

			return temp;
		}

		bool operator>(const self& obj) const
		{
			if (step_count > obj.step_count)
				return true;

			return false;
		}

		bool operator<(const self& obj) const
		{
			if (step_count < obj.step_count)
				return true;

			return false;
		}

		bool operator>=(const self& obj) const
		{
			if (step_count >= obj.step_count)
				return true;

			return false;
		}

		bool operator<=(const self& obj) const
		{
			if (step_count <= obj.step_count)
				return true;

			return false;
		}

	protected:
		friend bool operator!=(const self& Lhs , const self& Rhs)
		{
			return Lhs.ptr != Rhs.ptr;
		}

		friend bool operator==(const self& Lhs , const self& Rhs)
		{
			return Lhs.ptr == Rhs.ptr;
		}
};



//iterator for list
template<typename Ty>
struct List_iterator
{
	private:
		Ty* ptr = nullptr;

		int step_count = 0;
		size_t limit = 0;

	public:
		using self = List_iterator<Ty>;
		using value_type = typename Ty::value_type;

	public:
		List_iterator() = default;

		explicit List_iterator(Ty* InitPtr , size_t size) :ptr(InitPtr) , limit(size)
		{}

		explicit List_iterator(Ty* InitPtr , int num , size_t size) :ptr(InitPtr) , step_count(num) , limit(size)
		{}

		List_iterator(const self& obj) :ptr(obj.ptr) , step_count(obj.step_count) , limit(obj.limit)
		{ }

		~List_iterator()
		{
			ptr = nullptr;
		}

		_NODISCARD value_type& operator*() noexcept
		{
		#if _LIB_DEBUG_LEVEL == 1

			_BUG_VERIFY((step_count < limit) , "out of range");
			assert(step_count < limit);

		#endif // _LIB_DEBUG_LEVEL == 1

			return ptr->data;
		}

		_NODISCARD const value_type& operator*() const noexcept
		{
		#if _LIB_DEBUG_LEVEL == 1

			_BUG_VERIFY((step_count < limit) , "out of range");
			assert(step_count < limit);

		#endif // _LIB_DEBUG_LEVEL == 1

			return ptr->data;
		}

		_NODISCARD int step() const noexcept
		{
			return step_count;
		}

		_NODISCARD self operator+(int n) const noexcept
		{
			Ty* temp = ptr;

			int count = 0;
			for (int i = 0; i < n; ++i)
			{
				if (temp->next != nullptr)
				{
					temp = temp->next;
					count++;
				}
			}

			return self(temp , step_count + count , limit);
		}

		_NODISCARD self operator-(int n) const noexcept
		{
			Ty* temp = ptr;

			int count = 0;
			for (int i = 0; i < n; ++i)
			{
				if (temp->last != nullptr)
				{
					temp = temp->last;
					count++;
				}
			}

			return self(temp , step_count - count , limit);
		}

		self& operator++() noexcept
		{
			if (ptr->next)
			{
				ptr = ptr->next;
			}step_count++;

			return *this;
		}

		self operator++(int) noexcept
		{
			auto temp = *this;

			if (ptr->next)
			{
				ptr = ptr->next;
			}step_count++;

			return temp;
		}

		self& operator--() noexcept
		{
			if (ptr->last)
			{
				ptr = ptr->last;
			}step_count--;

			return *this;
		}

		self operator--(int) noexcept
		{
			auto temp = *this;

			if (ptr->last)
			{
				ptr = ptr->last;
			}step_count--;

			return temp;
		}

		self& operator=(const self& obj)
		{
			auto temp = obj.ptr;

			this->ptr = temp;
			step_count = obj.step_count;
			limit = obj.limit;

			return *this;
		}

		bool operator>(const self& obj) const
		{
			if (step_count > obj.step_count)
				return true;

			return false;
		}

		bool operator<(const self& obj) const
		{
			if (step_count < obj.step_count)
				return true;

			return false;
		}

		bool operator>=(const self& obj) const
		{
			if (step_count >= obj.step_count)
				return true;

			return false;
		}

		bool operator<=(const self& obj) const
		{
			if (step_count <= obj.step_count)
				return true;

			return false;
		}

	private:
		friend bool operator!=(const self& Lhs , const self& Rhs)
		{
			return Lhs.step_count != Rhs.step_count;
		}

		friend bool operator==(const self& Lhs , const self& Rhs)
		{
			return Lhs.step_count == Rhs.step_count;
		}
};

//const iterator for list
template<typename Ty>
struct const_List_iterator
{
	private:
		Ty* ptr = nullptr;

		int step_count = 0;
		size_t limit = 0;

	public:
		using self = const_List_iterator<Ty>;
		using value_type = typename Ty::value_type;

	public:
		const_List_iterator(const self& obj)
		{
			this->ptr = obj.ptr;
			this->step_count = obj.step_count;
			this->limit = obj.limit;
		}

		explicit const_List_iterator(Ty* InitPtr , size_t size) :ptr(InitPtr) , limit(size)
		{}

		explicit const_List_iterator(Ty* InitPtr , int num , size_t size) :ptr(InitPtr) , step_count(num) , limit(size)
		{}

		~const_List_iterator()
		{
			ptr = nullptr;
		}


		_NODISCARD const value_type& operator*() const noexcept
		{
		#if _LIB_DEBUG_LEVEL == 1

			_BUG_VERIFY((step_count < limit) , "out of range");
			assert(step_count < limit);

		#endif // _LIB_DEBUG_LEVEL == 1

			return ptr->data;
		}

		_NODISCARD int step() const noexcept
		{
			return step_count;
		}

		_NODISCARD self operator+(int n) const noexcept
		{
			Ty* temp = ptr;

			int count = 0;
			for (int i = 0; i < n; ++i)
			{
				if (temp->next != nullptr)
				{
					temp = temp->next;
					count++;
				}
			}

			return self(temp , step_count + count , limit);
		}

		_NODISCARD self operator-(int n) const noexcept
		{
			Ty* temp = ptr;

			int count = 0;
			for (int i = 0; i < n; ++i)
			{
				if (temp->last != nullptr)
				{
					temp = temp->last;
					count++;
				}
			}

			return self(temp , step_count - count , limit);
		}

		self& operator++() noexcept
		{
			if (ptr->next)
			{
				ptr = ptr->next;
			}step_count++;

			return *this;
		}

		self operator++(int) noexcept
		{
			auto temp = *this;

			if (ptr->next)
			{
				ptr = ptr->next;
			}step_count++;

			return temp;
		}

		self& operator--() noexcept
		{
			if (ptr->last)
			{
				ptr = ptr->last;
			}step_count--;

			return *this;
		}

		self operator--(int) noexcept
		{
			auto temp = *this;

			if (ptr->last)
			{
				ptr = ptr->last;
			}step_count--;

			return temp;
		}

		bool operator>(const self& obj) const
		{
			if (step_count > obj.step_count)
				return true;

			return false;
		}

		bool operator<(const self& obj) const
		{
			if (step_count < obj.step_count)
				return true;

			return false;
		}

		bool operator>=(const self& obj) const
		{
			if (step_count >= obj.step_count)
				return true;

			return false;
		}

		bool operator<=(const self& obj) const
		{
			if (step_count <= obj.step_count)
				return true;

			return false;
		}

	private:
		friend bool operator!=(const self& Lhs , const self& Rhs)
		{
			return Lhs.step_count != Rhs.step_count;
		}

		friend bool operator==(const self& Lhs , const self& Rhs)
		{
			return Lhs.step_count == Rhs.step_count;
		}
};



//iterator for RB_Tree
template<typename Ty>
struct RB_Tree_iterator
{
	private:
		Ty* ptr = nullptr;

		int step_count = 0;
		size_t limit = 0;

	public:
		using self = RB_Tree_iterator<Ty>;
		using value_type = typename Ty::value_type;

	public:
		RB_Tree_iterator() = default;

		explicit RB_Tree_iterator(Ty* p , size_t size) :ptr(p) , limit(size)
		{}

		explicit RB_Tree_iterator(Ty* p , int num , size_t size) :ptr(p) , step_count(num) , limit(size)
		{}

		RB_Tree_iterator(const self& obj) :ptr(obj.ptr) , step_count(obj.step_count) , limit(obj.limit)
		{}

		~RB_Tree_iterator()
		{
			ptr = nullptr;
		}

		_NODISCARD value_type& operator*() noexcept
		{
		#if _LIB_DEBUG_LEVEL == 1

			_BUG_VERIFY((step_count < limit) , "out of range");
			assert(step_count < limit);

		#endif // _LIB_DEBUG_LEVEL == 1

			return ptr->data;
		}

		_NODISCARD const value_type& operator*() const noexcept
		{
		#if _LIB_DEBUG_LEVEL == 1

			_BUG_VERIFY((step_count < limit) , "out of range");
			assert(step_count < limit);

		#endif // _LIB_DEBUG_LEVEL == 1

			return ptr->data;
		}

		_NODISCARD int step() const noexcept
		{
			return step_count;
		}

		_NODISCARD self operator+(int n) noexcept
		{
			auto cur_ptr_save = ptr;

			for (int i = 0; i < n; ++i)
			{
				increment();
			}

			auto return_ptr = ptr;
			ptr = cur_ptr_save;

			return self(return_ptr , step_count + n , limit);
		}

		_NODISCARD self operator-(int n) noexcept
		{
			auto cur_ptr_save = ptr;

			for (int i = 0; i < n; ++i)
			{
				decrement();
			}

			auto return_ptr = ptr;
			ptr = cur_ptr_save;

			return self(return_ptr , step_count - n , limit);
		}

		self& operator++() noexcept
		{
			increment();
			step_count++;

			return *this;
		}

		self operator++(int) noexcept
		{
			auto temp = *this;
			increment();
			step_count++;

			return temp;
		}

		self& operator--() noexcept
		{
			decrement();
			step_count--;

			return *this;
		}

		self operator--(int) noexcept
		{
			auto temp = *this;
			decrement();
			step_count--;

			return temp;
		}

		self& operator=(const self& obj)
		{
			auto temp = obj.ptr;
			this->ptr = temp;
			step_count = obj.step_count;
			limit = obj.limit;

			return *this;
		}

		bool operator<(const self& obj) const
		{
			if (step_count < obj.step_count)
				return true;

			return false;
		}

		bool operator>(const self& obj) const
		{
			if (step_count > obj.step_count)
				return true;

			return false;
		}

		bool operator<=(const self& obj) const
		{
			if (step_count <= obj.step_count)
				return true;

			return false;
		}

		bool operator>=(const self& obj) const
		{
			if (step_count >= obj.step_count)
				return true;

			return false;
		}

	private:
		void increment() noexcept
		{	
			//find next min val which bigger than cur val

			if (ptr->Rchild != nullptr)//non-leaf node
			{
				ptr = ptr->Rchild;

				while (ptr->Lchild != nullptr)
				{
					ptr = ptr->Lchild;
				}
			}
			else//leaf node
			{
				Ty* p = ptr->Father;

				while (ptr == p->Rchild)//this level is visited(from left to right)
				{						//if here is end of RB_Tree,it's never goes over.
					ptr = p;
					p = p->Father;
				}
				if (ptr->Rchild != p)
				{
					ptr = p;
				}
			}
		}

		void decrement() noexcept
		{
			if (ptr->Color == 0 && ptr->Father->Father == ptr)//ptr is header(end)
			{
				ptr = ptr->Rchild;//max val of RB_Tree
			}
			else if (ptr->Lchild != nullptr) //increment's reverse
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
			return Lhs.step_count != Rhs.step_count;
		}

		friend bool operator==(const self& Lhs , const self& Rhs)
		{
			return Lhs.step_count == Rhs.step_count;
		}
};

//const iterator for RB_Tree
template<typename Ty>
struct const_RB_Tree_iterator
{
	private:
		Ty* ptr = nullptr;

		int step_count = 0;
		size_t limit = 0;

	public:
		using self = const_RB_Tree_iterator<Ty>;
		using value_type = typename Ty::value_type;

	public:
		const_RB_Tree_iterator(const self& obj)
		{
			this->ptr = obj.ptr;
			this->step_count = obj.step_count;
			this->limit = obj.limit;
		}

		explicit const_RB_Tree_iterator(Ty* p , size_t size) :ptr(p) , limit(size)
		{}

		explicit const_RB_Tree_iterator(Ty* p , int num , size_t size) :ptr(p) , step_count(num) , limit(size)
		{}

		~const_RB_Tree_iterator()
		{
			ptr = nullptr;
		}

		_NODISCARD const value_type& operator*() const noexcept
		{
		#if _LIB_DEBUG_LEVEL == 1

			_BUG_VERIFY((step_count < limit) , "out of range");
			assert(step_count < limit);

		#endif // _LIB_DEBUG_LEVEL == 1

			return ptr->data;
		}

		_NODISCARD int step() const noexcept
		{
			return step_count;
		}

		_NODISCARD self operator+(int n) noexcept
		{
			auto cur_ptr_save = ptr;

			for (int i = 0; i < n; ++i)
			{
				increment();
			}

			auto return_ptr = ptr;
			ptr = cur_ptr_save;

			return self(return_ptr , step_count + n , limit);
		}

		_NODISCARD self operator-(int n) noexcept
		{
			auto cur_ptr_save = ptr;

			for (int i = 0; i < n; ++i)
			{
				decrement();
			}

			auto return_ptr = ptr;
			ptr = cur_ptr_save;

			return self(return_ptr , step_count - n , limit);
		}

		self& operator++() noexcept
		{
			increment();
			step_count++;

			return *this;
		}

		self operator++(int) noexcept
		{
			auto temp = *this;
			increment();
			step_count++;

			return temp;
		}

		self& operator--() noexcept
		{
			decrement();
			step_count--;

			return *this;
		}

		self operator--(int) noexcept
		{
			auto temp = *this;
			decrement();
			step_count--;

			return temp;
		}

		self& operator=(const self& obj)
		{
			auto temp = obj.ptr;
			this->ptr = temp;
			step_count = obj.step_count;
			limit = obj.limit;

			return *this;
		}

		bool operator<(const self& obj) const
		{
			if (step_count < obj.step_count)
				return true;

			return false;
		}

		bool operator>(const self& obj) const
		{
			if (step_count > obj.step_count)
				return true;

			return false;
		}

		bool operator<=(const self& obj) const
		{
			if (step_count <= obj.step_count)
				return true;

			return false;
		}

		bool operator>=(const self& obj) const
		{
			if (step_count >= obj.step_count)
				return true;

			return false;
		}

	private:
		void increment() noexcept
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

		void decrement() noexcept
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
			return Lhs.step_count != Rhs.step_count;
		}

		friend bool operator==(const self& Lhs , const self& Rhs)
		{
			return Lhs.step_count == Rhs.step_count;
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
		int step_count = 0;

		size_t limit = 0;

	public:
		using self = hash_table_iterator<Ty,Hash>;
		using value_type = typename Hash::value_type;

	public:
		hash_table_iterator() = default;

		explicit hash_table_iterator(Ty head , Hash* InitPtr , int size,int step,size_t elem_count,int jump_count = 0) :
			node(head) , ptr(InitPtr) , bucket_size(size),step_count(step),count(jump_count),limit(elem_count)
		{
			if(node == nullptr && step == 0)//head == nullptr
				bucket_jump();
		}

		hash_table_iterator(const self& obj)
		{
			node = obj.node;
			ptr = obj.ptr;
			bucket_size = obj.bucket_size;
			count = obj.count;
			step_count = obj.step_count;
			limit = obj.limit;
		}

		~hash_table_iterator()
		{
			ptr = nullptr;
			node = nullptr;
		}

		_NODISCARD int step() const noexcept
		{
			return step_count;
		}

		_NODISCARD value_type& operator*() noexcept
		{
		#if _LIB_DEBUG_LEVEL == 1

			_BUG_VERIFY((step_count < limit) , "out of range");
			assert(step_count < limit);

		#endif // _LIB_DEBUG_LEVEL == 1

			return node->val;
		}

		_NODISCARD const value_type& operator*() const noexcept
		{
		#if _LIB_DEBUG_LEVEL == 1

			_BUG_VERIFY((step_count < limit) , "out of range");
			assert(step_count < limit);

		#endif // _LIB_DEBUG_LEVEL == 1

			return node->val;
		}

		self& operator=(const self& obj)
		{
			this->ptr = obj.ptr;
			this->node = obj.node;
			this->bucket_size = obj.bucket_size;
			this->count = obj.count;
			this->step_count = obj.step_count;
			this->limit = obj.limit;

			return *this;
		}

		self& operator++() noexcept
		{
			node = node->next;

			if (node == nullptr)
			{
				bucket_jump();
			}

			step_count++;
			return *this;
		}

		_NODISCARD self operator+(int n) noexcept
		{
			auto cur_node_save = node;

			for (int i = 0; i < n; ++i)
			{
				node = node->next;

				if (node == nullptr)
				{
					bucket_jump();
				}
			}

			auto return_node = node;
			node = cur_node_save;

			return self(return_node,ptr,bucket_size,step_count+n,limit,count);
		}

		self operator++(int) noexcept
		{
			auto temp = *this;

			node = node->next;

			if (node == nullptr)
			{
				bucket_jump();
			}

			step_count++;
			return temp;
		}

		bool operator>(const self& obj) const
		{
			if (this->step_count > obj.step_count)
				return true;

			return false;
		}

		bool operator<(const self& obj) const
		{
			if (this->step_count < obj.step_count)
				return true;

			return false;
		}

		bool operator>=(const self& obj) const
		{
			if (this->step_count >= obj.step_count)
				return true;

			return false;
		}

		bool operator<=(const self& obj) const
		{
			if (this->step_count <= obj.step_count)
				return true;

			return false;
		}

	private:
		void bucket_jump() noexcept
		{
			while (!node && ++count < bucket_size)
			{
				node = ptr->buckets[count];
			}
		}

		friend bool operator!=(const self& Lhs , const self& Rhs)
		{
			return Lhs.step_count != Rhs.step_count;
		}

		friend bool operator==(const self& Lhs , const self& Rhs)
		{
			return Lhs.step_count == Rhs.step_count;
		}
};

//const iterator for hash table
template<typename Ty , typename Hash>//hash_node<Ty>*
struct const_hash_table_iterator
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
		int step_count = 0;

		size_t limit = 0;

	public:
		using self = const_hash_table_iterator<Ty , Hash>;
		using value_type = typename Hash::value_type;

	public:
		const_hash_table_iterator() = delete;

		explicit const_hash_table_iterator(Ty head , Hash* InitPtr , int size , int step,size_t elem_count ,int jump_count = 0) :
			node(head) , ptr(InitPtr) , bucket_size(size) , step_count(step),count(jump_count),limit(elem_count)
		{
			if (node == nullptr && step == 0)//head == nullptr
				bucket_jump();
		}

		const_hash_table_iterator(const self& obj)
		{
			node = obj.node;
			ptr = obj.ptr;
			bucket_size = obj.bucket_size;
			count = obj.count;
			step_count = obj.step_count;
			limit = obj.limit;
		}

		~const_hash_table_iterator()
		{
			ptr = nullptr;
			node = nullptr;
		}

		_NODISCARD int step() const noexcept
		{
			return step_count;
		}

		_NODISCARD const value_type& operator*() const noexcept
		{
		#if _LIB_DEBUG_LEVEL == 1

			_BUG_VERIFY((step_count < limit) , "out of range");
			assert(step_count < limit);

		#endif // _LIB_DEBUG_LEVEL == 1

			return node->val;
		}

		self& operator=(const self& obj)
		{
			this->ptr = obj.ptr;
			this->node = obj.node;
			this->bucket_size = obj.bucket_size;
			this->count = obj.count;
			this->step_count = obj.step_count;
			this->limit = obj.limit;

			return *this;
		}

		self& operator++() noexcept
		{
			node = node->next;

			if (node == nullptr)
			{
				bucket_jump();
			}

			step_count++;
			return *this;
		}

		_NODISCARD self operator+(int n) noexcept
		{
			auto cur_node_save = node;

			for (int i = 0; i < n; ++i)
			{
				node = node->next;

				if (node == nullptr)
				{
					bucket_jump();
				}
			}

			auto return_node = node;
			node = cur_node_save;

			return self(return_node , ptr , bucket_size , step_count + n , limit , count);
		}

		self operator++(int) noexcept
		{
			auto temp = *this;

			node = node->next;

			if (node == nullptr)
			{
				bucket_jump();
			}

			step_count++;
			return temp;
		}

		bool operator>(const self& obj) const
		{
			if (this->step_count > obj.step_count)
				return true;

			return false;
		}

		bool operator<(const self& obj) const
		{
			if (this->step_count < obj.step_count)
				return true;

			return false;
		}

		bool operator>=(const self& obj) const
		{
			if (this->step_count >= obj.step_count)
				return true;

			return false;
		}

		bool operator<=(const self& obj) const
		{
			if (this->step_count <= obj.step_count)
				return true;

			return false;
		}

	private:
		void bucket_jump() noexcept
		{
			while (!node && ++count < bucket_size)
			{
				node = ptr->buckets[count];
			}
		}

		friend bool operator!=(const self& Lhs , const self& Rhs)
		{
			return Lhs.step_count != Rhs.step_count;
		}

		friend bool operator==(const self& Lhs , const self& Rhs)
		{
			return Lhs.step_count == Rhs.step_count;
		}
};



//iterator for deque
template<typename Ty>
class deque_iterator
{
	private:
		Ty** ptr = nullptr;

		int insert_count = 0;
		int buffer_count = 0;
		int body_size = 0;
		int step_count = 0;
		size_t limit = 0;

	public:
		using self = deque_iterator<Ty>;
		using value_type = Ty;

	public:
		deque_iterator() = delete;

		explicit deque_iterator(Ty** init_ptr , int insert , int buffer , int body , int count , size_t size) :
			ptr(init_ptr) , insert_count(insert) , buffer_count(buffer) , body_size(body) , step_count(count) , limit(size)
		{}

		deque_iterator(const self& obj)
		{
			ptr = obj.ptr;
			insert_count = obj.insert_count;
			buffer_count = obj.buffer_count;
			body_size = obj.body_size;
			step_count = obj.step_count;
			limit = obj.limit;
		}

		~deque_iterator()
		{
			ptr = nullptr;
		}


		_NODISCARD int step() const noexcept
		{
			return step_count;
		}

		_NODISCARD int buffer() const noexcept
		{
			return buffer_count;
		}

		_NODISCARD int insert_flag() const noexcept
		{
			return insert_count;
		}

		_NODISCARD Ty& operator*() noexcept
		{
		#if _LIB_DEBUG_LEVEL == 1

			_BUG_VERIFY((step_count < limit) , "out of range");
			assert(step_count < limit);

		#endif // _LIB_DEBUG_LEVEL == 1

			return ptr[buffer_count][insert_count];
		}

		_NODISCARD const Ty& operator*() const noexcept
		{
		#if _LIB_DEBUG_LEVEL == 1

			_BUG_VERIFY((step_count < limit) , "out of range");
			assert(step_count < limit);

		#endif // _LIB_DEBUG_LEVEL == 1

			return ptr[buffer_count][insert_count];
		}

		self& operator=(const self& obj)
		{
			this->ptr = obj.ptr;
			this->body_size = obj.body_size;
			this->buffer_count = obj.buffer_count;
			this->insert_count = obj.insert_count;
			this->step_count = obj.step_count;
			this->limit = obj.limit;

			return *this;
		}

		self& operator++() noexcept
		{
			if (insert_count == body_size - 1)
			{
				buffer_count++;
				insert_count = 0;
			}
			else
			{
				insert_count++;
			}

			step_count++;
			return *this;
		}

		_NODISCARD self operator+(int n) noexcept
		{
			int insert_count_save = insert_count;
			int buffer_count_save = buffer_count;

			for (int i = 0; i < n; ++i)
			{
				if (insert_count == body_size - 1)
				{
					buffer_count++;
					insert_count = 0;
				}
				else
				{
					insert_count++;
				}
			}

			int return_insert_count = insert_count;
			int return_buffer_count = buffer_count;

			buffer_count = buffer_count_save;
			insert_count = insert_count_save;

			return self(ptr , return_insert_count , return_buffer_count , body_size , step_count + n , limit);
		}

		self operator++(int) noexcept
		{
			auto temp = *this;

			if (insert_count == body_size - 1)
			{
				buffer_count++;
				insert_count = 0;
			}
			else
			{
				insert_count++;
			}

			step_count++;
			return temp;
		}

		self& operator--() noexcept
		{
			if (insert_count == 0)
			{
				buffer_count--;
				insert_count = body_size - 1;
			}
			else
			{
				insert_count--;
			}

			step_count--;
			return *this;
		}

		_NODISCARD self operator-(int n) noexcept
		{
			int insert_count_save = insert_count;
			int buffer_count_save = buffer_count;

			for (int i = 0; i < n; ++i)
			{
				if (insert_count == 0)
				{
					buffer_count--;
					insert_count = body_size - 1;
				}
				else
				{
					insert_count--;
				}
			}

			int return_insert_count = insert_count;
			int return_buffer_count = buffer_count;

			buffer_count = buffer_count_save;
			insert_count = insert_count_save;

			return self(ptr , return_insert_count , return_buffer_count , body_size , step_count - n , limit);
		}

		self operator--(int) noexcept
		{
			auto temp = *this;

			if (insert_count == 0)
			{
				buffer_count--;
				insert_count = body_size - 1;
			}
			else
			{
				insert_count--;
			}

			step_count--;
			return temp;
		}

		bool operator>(const self& obj) const
		{
			if (this->step_count > obj.step_count)
				return true;

			return false;
		}

		bool operator<(const self& obj) const
		{
			if (this->step_count < obj.step_count)
				return true;

			return false;
		}

		bool operator>=(const self& obj) const
		{
			if (this->step_count >= obj.step_count)
				return true;

			return false;
		}

		bool operator<=(const self& obj) const
		{
			if (this->step_count <= obj.step_count)
				return true;

			return false;
		}

	private:
		friend bool operator==(const self& Lhs , const self& Rhs)
		{
			return Lhs.step_count == Rhs.step_count;
		}

		friend bool operator!=(const self& Lhs , const self& Rhs)
		{
			return Lhs.step_count != Rhs.step_count;
		}
};

//const iterator for deque
template<typename Ty>
class const_deque_iterator
{
	private:
		Ty** ptr = nullptr;

		int insert_count = 0;
		int buffer_count = 0;
		int body_size = 0;
		int step_count = 0;
		size_t limit = 0;

	public:
		using self = const_deque_iterator<Ty>;
		using value_type = Ty;

	public:
		const_deque_iterator() = delete;

		explicit const_deque_iterator(Ty** init_ptr , int insert , int buffer , int body , int count , size_t size) :
			ptr(init_ptr) , insert_count(insert) , buffer_count(buffer) , body_size(body) , step_count(count) , limit(size)
		{}

		const_deque_iterator(const self& obj)
		{
			ptr = obj.ptr;
			insert_count = obj.insert_count;
			buffer_count = obj.buffer_count;
			body_size = obj.body_size;
			step_count = obj.step_count;
			limit = obj.limit;
		}

		~const_deque_iterator()
		{
			ptr = nullptr;
		}


		_NODISCARD int step() const noexcept
		{
			return step_count;
		}

		_NODISCARD const Ty& operator*() const noexcept
		{
		#if _LIB_DEBUG_LEVEL == 1

			_BUG_VERIFY((step_count < limit) , "out of range");
			assert(step_count < limit);

		#endif // _LIB_DEBUG_LEVEL == 1

			return ptr[buffer_count][insert_count];
		}

		self& operator=(const self& obj)
		{
			this->ptr = obj.ptr;
			this->body_size = obj.body_size;
			this->buffer_count = obj.buffer_count;
			this->insert_count = obj.insert_count;
			this->step_count = obj.step_count;
			this->limit = obj.limit;

			return *this;
		}

		self& operator++() noexcept
		{
			if (insert_count == body_size - 1)
			{
				buffer_count++;
				insert_count = 0;
			}
			else
			{
				insert_count++;
			}

			step_count++;
			return *this;
		}

		_NODISCARD self operator+(int n) noexcept
		{
			int insert_count_save = insert_count;
			int buffer_count_save = buffer_count;

			for (int i = 0; i < n; ++i)
			{
				if (insert_count == body_size - 1)
				{
					buffer_count++;
					insert_count = 0;
				}
				else
				{
					insert_count++;
				}
			}

			int return_insert_count = insert_count;
			int return_buffer_count = buffer_count;

			buffer_count = buffer_count_save;
			insert_count = insert_count_save;

			return self(ptr , return_insert_count , return_buffer_count , body_size , step_count + n , limit);
		}

		self operator++(int) noexcept
		{
			auto temp = *this;

			if (insert_count == body_size - 1)
			{
				buffer_count++;
				insert_count = 0;
			}
			else
			{
				insert_count++;
			}

			step_count++;
			return temp;
		}

		self& operator--() noexcept
		{
			if (insert_count == 0)
			{
				buffer_count--;
				insert_count = body_size - 1;
			}
			else
			{
				insert_count--;
			}

			step_count--;
			return *this;
		}

		_NODISCARD self operator-(int n) noexcept
		{
			int insert_count_save = insert_count;
			int buffer_count_save = buffer_count;

			for (int i = 0; i < n; ++i)
			{
				if (insert_count == 0)
				{
					buffer_count--;
					insert_count = body_size - 1;
				}
				else
				{
					insert_count--;
				}
			}

			int return_insert_count = insert_count;
			int return_buffer_count = buffer_count;

			buffer_count = buffer_count_save;
			insert_count = insert_count_save;

			return self(ptr , return_insert_count , return_buffer_count , body_size , step_count - n , limit);
		}

		self operator--(int) noexcept
		{
			auto temp = *this;

			if (insert_count == 0)
			{
				buffer_count--;
				insert_count = body_size - 1;
			}
			else
			{
				insert_count--;
			}

			step_count--;
			return temp;
		}

		bool operator>(const self& obj) const
		{
			if (this->step_count > obj.step_count)
				return true;

			return false;
		}

		bool operator<(const self& obj) const
		{
			if (this->step_count < obj.step_count)
				return true;

			return false;
		}

		bool operator>=(const self& obj) const
		{
			if (this->step_count >= obj.step_count)
				return true;

			return false;
		}

		bool operator<=(const self& obj) const
		{
			if (this->step_count <= obj.step_count)
				return true;

			return false;
		}

	private:
		friend bool operator==(const self& Lhs , const self& Rhs)
		{
			return Lhs.step_count == Rhs.step_count;
		}

		friend bool operator!=(const self& Lhs , const self& Rhs)
		{
			return Lhs.step_count != Rhs.step_count;
		}
};