#ifndef __Iterator_H__
#define __Iterator_H__

#include <iostream>

#include "../utils/function.hpp"


#ifndef REVERSE_INCLUDE
 #define REVERSE_INCLUDE
 #include "ReverseIterator.hpp"
#endif

namespace ft
{

	template <
		class T,
		bool B
	>
	struct ReverseIterator;

	template <
		class T,
		bool B
	>
	struct Iterator
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
			explicit Iterator(_ptr ptr = 0): m_ptr(ptr) {}
			Iterator(const Iterator<T, false> & rhs): m_ptr(rhs.base()) {}
			explicit Iterator(const ReverseIterator<T, false> & rhs): m_ptr(rhs.base()) {}


			reference operator *(void) const { return *m_ptr; }
			pointer operator->(void) const { return m_ptr; }

			Iterator operator+(difference_type __n) const { return Iterator(m_ptr + __n); }
			Iterator operator-(difference_type __n) const { return Iterator(m_ptr - __n); }
			difference_type operator-(const Iterator &it) const { return m_ptr - it.m_ptr; }
			difference_type operator+(const Iterator &it) const { return m_ptr + it.m_ptr; }

			Iterator& operator++(void) { m_ptr++; return *this; }
			Iterator operator++(int)
			{
				Iterator tmp(*this);
				operator++();
				return (tmp);
			}

			Iterator& operator--(void) { m_ptr--; return *this; }
			Iterator operator--(int)
			{
				Iterator tmp(*this);
				operator--();
				return (tmp);
			}

			Iterator & operator+=(difference_type __n) { m_ptr += __n; return *this; }
			Iterator & operator-=(difference_type __n) { m_ptr -= __n; return *this; }
			reference operator[](difference_type __n) const { return m_ptr[__n]; }

			Iterator& operator=(const Iterator& assign)
			{
				if (this != &assign)
					m_ptr = assign.m_ptr;
				return (*this);
			}

			T * base() const { return m_ptr; }

			bool operator==(const Iterator& it) const	{ return (it.m_ptr == m_ptr); }
			bool operator!=(const Iterator& it) const	{ return (it.m_ptr != m_ptr); }
			bool operator<(const Iterator& it) const	{ return (it.m_ptr > m_ptr); }
			bool operator>(const Iterator& it) const	{ return (it.m_ptr < m_ptr); }
			bool operator<=(const Iterator& it) const	{ return (it.m_ptr >= m_ptr); }
			bool operator>=(const Iterator& it) const	{ return (it.m_ptr <= m_ptr); }
	
			bool operator==(const pointer& ptr) const { return (m_ptr == ptr); }
	};
};

// OUTSIDE OVERLOAD

template<typename T> 
ft::Iterator<T, false> operator+(int offset, ft::Iterator<T, false> & rhs) { return (ft::Iterator<T, false>(rhs.base() + offset)); } 
template<typename T> 
ft::Iterator<T, false> operator-(int offset, ft::Iterator<T, false> & rhs) { return (ft::Iterator<T, false>(rhs.base() - offset)); } 



template <typename T>
bool operator!=(const ft::Iterator<T, false>& lhs, const ft::Iterator<T, true>& rhs) { return lhs.base() != rhs.base(); }
template <typename T>
bool operator==(const ft::Iterator<T, false>& lhs, const ft::Iterator<T, true>& rhs) { return lhs.base() == rhs.base(); }
template <typename T>
bool operator>(const ft::Iterator<T, false>& lhs, const ft::Iterator<T, true>& rhs) { return lhs.base() > rhs.base(); }
template <typename T>
bool operator<(const ft::Iterator<T, false>& lhs, const ft::Iterator<T, true>& rhs) { return lhs.base() < rhs.base(); }
template <typename T>
bool operator>=(const ft::Iterator<T, false>& lhs, const ft::Iterator<T, true>& rhs) { return lhs.base() >= rhs.base(); }
template <typename T>
bool operator<=(const ft::Iterator<T, false>& lhs, const ft::Iterator<T, true>& rhs) { return lhs.base() <= rhs.base(); }

#endif // __Iterator_H__