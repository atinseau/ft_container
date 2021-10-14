#ifndef __Iterator_H__
#define __Iterator_H__

#include <iostream>
#include "../utils/stl.hpp"
#include "../utils/function.hpp"


namespace fd
{
	template< class Iter>
	struct iterator_traits
	{
		typedef typename Iter::difference_type difference_type;
		typedef typename Iter::value_type value_type;
		typedef typename Iter::pointer pointer;
		typedef typename Iter::reference reference;
		typedef typename Iter::iterator_category iterator_category;
	};

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
			Iterator(_ptr ptr = 0): m_ptr(ptr) {}
			Iterator(const Iterator<T, false> & rhs): m_ptr(rhs.getInterval()) {}

			reference operator *(void) const { return *m_ptr; }
			pointer operator->(void) const { return m_ptr; }

			Iterator operator+(difference_type __n) { return Iterator(m_ptr + __n); }
			Iterator operator-(difference_type __n) { return Iterator(m_ptr - __n); }
			difference_type operator-(const Iterator &it) { return m_ptr - it.m_ptr; }
			difference_type operator+(const Iterator &it) { return m_ptr + it.m_ptr; }

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

			T * getInterval() const { return m_ptr; }

			bool operator==(const Iterator& it) const	{ return (it.m_ptr == m_ptr); }
			bool operator!=(const Iterator& it) const	{ return (it.m_ptr != m_ptr); }
			bool operator<(const Iterator& it) const	{ return (it.m_ptr > m_ptr); }
			bool operator>(const Iterator& it) const	{ return (it.m_ptr < m_ptr); }
			bool operator<=(const Iterator& it) const	{ return (it.m_ptr >= m_ptr); }
			bool operator>=(const Iterator& it) const	{ return (it.m_ptr <= m_ptr); }
	};
};

#endif // __Iterator_H__