#ifndef __ReverseIterator_H__
#define __ReverseIterator_H__

#include <iostream>
#include "../utils/stl.hpp"
#include "../utils/function.hpp"


namespace ft
{
	template <
		class T,
		bool B
	>
	struct ReverseIterator
	{
		typedef std::random_access_iterator_tag				iterator_category;
		typedef std::ptrdiff_t								difference_type;
		typedef T											value_type;
		typedef typename is_const<B, T&, const T&>::type	reference;
		typedef typename is_const<B, T*, const T*>::type	pointer;
		typedef T*											_ptr;

		private:
			_ptr m_ptr;

		public:
			explicit ReverseIterator(_ptr ptr = 0): m_ptr(ptr) {}
			ReverseIterator(const ReverseIterator<T, false> & rhs): m_ptr(rhs.base()) {}
			ReverseIterator(const Iterator<T, false> & rhs): m_ptr(rhs.base()) {}

			ReverseIterator<T, true>(const Iterator<T, true> & rhs): m_ptr(rhs.base()) {}

			reference operator *(void) const { return *m_ptr; }
			pointer operator->(void) const { return m_ptr; }

			ReverseIterator operator+(difference_type __n) const { return ReverseIterator(m_ptr - __n); }
			ReverseIterator operator-(difference_type __n) const { return ReverseIterator(m_ptr + __n); }
			difference_type operator-(const ReverseIterator &it) const { return m_ptr + it.m_ptr; }
			difference_type operator+(const ReverseIterator &it) const { return m_ptr - it.m_ptr; }


			ReverseIterator& operator++(void) { m_ptr--; return *this; }
			ReverseIterator operator++(int)
			{
				ReverseIterator tmp(*this);
				++(*this);
				return (tmp);
			}

			ReverseIterator& operator--(void) { m_ptr++; return *this; }
			ReverseIterator operator--(int)
			{
				ReverseIterator tmp(*this);
				--(*this);
				return (tmp);
			}

			ReverseIterator & operator+=(difference_type __n) { m_ptr -= __n; return *this; }
			ReverseIterator & operator-=(difference_type __n) { m_ptr += __n; return *this; }
			reference operator[](difference_type __n) const { return m_ptr[__n]; }

			ReverseIterator& operator=(const ReverseIterator& assign)
			{
				if (this != &assign)
					m_ptr = assign.m_ptr;
				return (*this);
			}

			T * base() const { return m_ptr; }

			bool operator==(const ReverseIterator& it) const	{ return (it.m_ptr == m_ptr); }
			bool operator!=(const ReverseIterator& it) const	{ return (it.m_ptr != m_ptr); }
			bool operator<(const ReverseIterator& it) const	{ return (it.m_ptr > m_ptr); }
			bool operator>(const ReverseIterator& it) const	{ return (it.m_ptr < m_ptr); }
			bool operator<=(const ReverseIterator& it) const	{ return (it.m_ptr >= m_ptr); }
			bool operator>=(const ReverseIterator& it) const	{ return (it.m_ptr <= m_ptr); }
	};
};

// OUTSIDE OVERLOAD

template<typename T> 
ft::ReverseIterator<T, false> operator+(int offset, const ft::ReverseIterator<T, false> & rhs) { return (ft::ReverseIterator<T, false>(rhs.base() + offset)); } 
template<typename T> 
ft::ReverseIterator<T, false> operator-(int offset, const ft::ReverseIterator<T, false> & rhs) { return (ft::ReverseIterator<T, false>(rhs.base() - offset)); } 

template<typename T> 
typename ft::ReverseIterator<T, false>::difference_type operator+(const ft::ReverseIterator<T, true> & lhs, const ft::ReverseIterator<T, false> & rhs) 
{
	return lhs.base() + rhs.base(); 
}
template<typename T> 
typename ft::ReverseIterator<T, false>::difference_type operator-(const ft::ReverseIterator<T, true> & lhs, const ft::ReverseIterator<T, false> & rhs)
{
	return lhs.base() - rhs.base();
} 




template <typename T>
bool operator!=(const ft::ReverseIterator<T, false>& lhs, const ft::ReverseIterator<T, true>& rhs) { return lhs.base() != rhs.base(); }
template <typename T>
bool operator==(const ft::ReverseIterator<T, false>& lhs, const ft::ReverseIterator<T, true>& rhs) { return lhs.base() == rhs.base(); }
template <typename T>
bool operator>(const ft::ReverseIterator<T, false>& lhs, const ft::ReverseIterator<T, true>& rhs) { return lhs.base() > rhs.base(); }
template <typename T>
bool operator<(const ft::ReverseIterator<T, false>& lhs, const ft::ReverseIterator<T, true>& rhs) { return lhs.base() < rhs.base(); }
template <typename T>
bool operator>=(const ft::ReverseIterator<T, false>& lhs, const ft::ReverseIterator<T, true>& rhs) { return lhs.base() >= rhs.base(); }
template <typename T>
bool operator<=(const ft::ReverseIterator<T, false>& lhs, const ft::ReverseIterator<T, true>& rhs) { return lhs.base() <= rhs.base(); }

#endif // __ReverseIterator_H__