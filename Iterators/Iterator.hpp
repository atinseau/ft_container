#ifndef __Iterator_H__
#define __Iterator_H__

#include <iostream>

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
		class Category,
		class Distance = std::ptrdiff_t,
		class Pointer = T*,
		class Reference = T&
	>
	struct Iterator
	{
		typedef Category iterator_category;
		typedef Distance difference_type;
		typedef T value_type;
		typedef T* pointer;
		typedef T& reference;

		private:
			pointer m_ptr;

		public:
			explicit Iterator(pointer ptr): m_ptr(ptr) {}
			Iterator(const Iterator & rhs): m_ptr(rhs.m_ptr) {}

			reference operator *(void) const { return *m_ptr; }
			pointer operator->(void) const { return m_ptr; }

			Iterator operator+(difference_type __n) { return Iterator(m_ptr + __n); }
			Iterator operator-(difference_type __n) { return Iterator(m_ptr - __n); }

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

			

			friend bool operator==(const Iterator &a, const Iterator &b) { return a.m_ptr == b.m_ptr; }
			friend bool operator!=(const Iterator &a, const Iterator &b) { return a.m_ptr != b.m_ptr; }
	};
};

#endif // __Iterator_H__