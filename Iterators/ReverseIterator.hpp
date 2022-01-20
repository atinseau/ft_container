#ifndef __ReverseIterator_H__
#define __ReverseIterator_H__

#include <iostream>
#include "../utils/function.hpp"
#include "../utils/function.hpp"

#ifndef ITERATOR_INCLUDE
 #define ITERATOR_INCLUDE
 #include "Iterator.hpp"
#endif


namespace ft
{
	template <
		class T,
		bool B
	>
	struct Iterator ;

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

			template <bool Any>
			ReverseIterator(const Iterator<T, Any> & rhs): m_ptr(rhs.base()) {}

			template <bool Any>
			ReverseIterator(const ReverseIterator<T, Any> & rhs): m_ptr(rhs.base()) {}
			
			~ReverseIterator() {}
		
			reference operator *(void) const
			{
				_ptr tmp = m_ptr;
				return *(--tmp);
			}
			pointer operator->(void) { return &(operator*()); }

			// DECREMENTATION OR INCREMENTATION

			ReverseIterator& operator++(void)
			{ --m_ptr; return (*this); }
			ReverseIterator operator++(int)
			{ ReverseIterator tmp(*this); ++(*this); return (tmp); }

			ReverseIterator& operator--(void)
			{ ++m_ptr; return (*this); }
			ReverseIterator operator--(int)
			{ ReverseIterator tmp(*this); --(*this); return (tmp); }

			ReverseIterator& operator+= (int offset)
			{ m_ptr -= offset; return *this; }

			ReverseIterator& operator-= (int offset)
			{ m_ptr += offset; return *this; }

			ReverseIterator operator-(int offset) const
			{
				return (ReverseIterator(m_ptr + offset ));
			}

			ReverseIterator operator+(int offset) const
			{
				return (ReverseIterator(m_ptr - offset));
			}

			// BASIC OVERLOAD

			reference operator[] (int offset) const
			{
				return m_ptr[-offset - 1];
			}

			ReverseIterator& operator=(const ReverseIterator& assign)
			{
				if (this != &assign)
					m_ptr = assign.m_ptr;
				return (*this);
			}

			T * base() const { return m_ptr; }

			bool operator==(const ReverseIterator& it) const	{ return (it.m_ptr == m_ptr); }
			bool operator!=(const ReverseIterator& it) const	{ return (it.m_ptr != m_ptr); }
			bool operator<(const ReverseIterator& it) const		{ return (it.m_ptr < m_ptr); }
			bool operator>(const ReverseIterator& it) const		{ return (it.m_ptr > m_ptr); }
			bool operator<=(const ReverseIterator& it) const	{ return (it.m_ptr <= m_ptr); }
			bool operator>=(const ReverseIterator& it) const	{ return (it.m_ptr >= m_ptr); }

			friend ReverseIterator operator+(int offset, const ReverseIterator & rhs)
			{
				return ReverseIterator(rhs.m_ptr - offset);
			}
	};
};



template <typename T>
typename ft::ReverseIterator<T, true>::difference_type operator-(
	const ft::ReverseIterator<T, true>& lhs,
	const ft::ReverseIterator<T, false>& rhs
)
{
	return (rhs.base() - lhs.base());
}

template <typename T>
bool operator!=(const ft::ReverseIterator<T, false>& lhs, const ft::ReverseIterator<T, true>& rhs) { return lhs.base() != rhs.base(); }
template <typename T>
bool operator==(const ft::ReverseIterator<T, false>& lhs, const ft::ReverseIterator<T, true>& rhs) { return lhs.base() == rhs.base(); }
template <typename T>
bool operator>(const ft::ReverseIterator<T, false>& lhs, const ft::ReverseIterator<T, true>& rhs) { return lhs.base() < rhs.base(); }
template <typename T>
bool operator<(const ft::ReverseIterator<T, false>& lhs, const ft::ReverseIterator<T, true>& rhs) { return lhs.base() > rhs.base(); }
template <typename T>
bool operator>=(const ft::ReverseIterator<T, false>& lhs, const ft::ReverseIterator<T, true>& rhs) { return lhs.base() <= rhs.base(); }
template <typename T>
bool operator<=(const ft::ReverseIterator<T, false>& lhs, const ft::ReverseIterator<T, true>& rhs) { return lhs.base() >= rhs.base(); }


#endif // __ReverseIterator_H__