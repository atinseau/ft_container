#ifndef REVERSE_ITERATOR_H
# define REVERSE_ITERATOR_H

# include <iostream>
# include <cstddef>
#ifndef LEGACY_ITERATOR_INCLUDE
#define LEGACY_ITERATOR_INCLUDE
#include "LegacyBidirectionalIterator.hpp"
#endif

#include "../utils/RedBlackTree.hpp"
# include "../utils/function.hpp"

namespace ft {
    template <typename T, bool B, class C>
    class LegacyBidirectionalIterator ;

    template <typename T>
    class LegacyReverseBidirectionalIterator
    {
    public:
        typedef T																iterator_type;
        typedef typename ft::iterator_traits<iterator_type>::difference_type	difference_type;
        typedef typename ft::iterator_traits<iterator_type>::pointer			pointer;
        typedef typename ft::iterator_traits<iterator_type>::reference			reference;
        typedef typename ft::iterator_traits<T>::iterator_category				iterator_category;
        typedef typename ft::iterator_traits<iterator_type>::value_type			value_type;
        /* Constructor */
        LegacyReverseBidirectionalIterator(void): current() {};
        explicit LegacyReverseBidirectionalIterator( iterator_type x ): current(x) {};
        /* Destructor */
        ~LegacyReverseBidirectionalIterator(void) {};
        /* Copy constructor */
        template< class U >
        LegacyReverseBidirectionalIterator( const LegacyReverseBidirectionalIterator<U>& other ): current(other.base()) {};
        /* Copy Assignation constructor */
        LegacyReverseBidirectionalIterator&		operator=(const LegacyReverseBidirectionalIterator& rhs)
        {
            if (this != &rhs)
                this->current = rhs.base();
            return (*this);
        }
        /* Increment Decrement Part */
        LegacyReverseBidirectionalIterator&		operator--(void) { ++current; return *this; }
        LegacyReverseBidirectionalIterator		operator--(int) { LegacyReverseBidirectionalIterator old = *this; operator--(); return old; }
        LegacyReverseBidirectionalIterator&		operator++(void) { --current; return *this; }
        LegacyReverseBidirectionalIterator		operator++(int) { LegacyReverseBidirectionalIterator old = *this; operator++(); return old; }
        typename T::pair_type&								operator*(void) const { iterator_type tmp = current; return *(--tmp); }
        typename T::pair_type*									operator->(void) const { return &(operator*()); }
        /* Arithmetic operations */
        // LegacyReverseBidirectionalIterator		operator+(difference_type rhs) const { return LegacyReverseBidirectionalIterator(current - rhs); }
        // LegacyReverseBidirectionalIterator		operator-(difference_type rhs) const { return LegacyReverseBidirectionalIterator(base() + rhs); }
        // difference_type							operator-(LegacyReverseBidirectionalIterator const &r) { return r.base() - this->base(); }
        // /* Compound assignement arithmetics operations */
        // LegacyReverseBidirectionalIterator&		operator+=(difference_type rhs) { current -= rhs; return *(this); }
        // LegacyReverseBidirectionalIterator&		operator-=(difference_type rhs) { current += rhs; return *this; }
        /* Offset dereference operator */
        reference								operator[](difference_type rhs) const { return *(current - rhs - 1); }
        iterator_type							base(void) const { return current; };
    protected:
        iterator_type							current;
    };

    template< class Iterator1, class Iterator2 >
    bool	operator==(const LegacyReverseBidirectionalIterator<Iterator1>& lhs, const LegacyReverseBidirectionalIterator<Iterator2>& rhs) { return (lhs.base() == rhs.base()); };
    template< class Iterator >
    bool	operator==(const LegacyReverseBidirectionalIterator<Iterator>& lhs, const LegacyReverseBidirectionalIterator<Iterator>& rhs) { return (lhs.base() == rhs.base()); };
    template< class Iterator1, class Iterator2 >
    bool 	operator!=(const LegacyReverseBidirectionalIterator<Iterator1>& lhs, const LegacyReverseBidirectionalIterator<Iterator2>& rhs) { return (lhs.base() != rhs.base()); }
    template< class Iterator >
    bool 	operator!=(const LegacyReverseBidirectionalIterator<Iterator>& lhs, const LegacyReverseBidirectionalIterator<Iterator>& rhs) { return (lhs.base() != rhs.base()); }
    template< class Iterator1, class Iterator2 >
    bool	operator<(const LegacyReverseBidirectionalIterator<Iterator1>& lhs, const LegacyReverseBidirectionalIterator<Iterator2>& rhs) { return (lhs.base() > rhs.base()); };
    template< class Iterator>
    bool	operator<(const LegacyReverseBidirectionalIterator<Iterator>& lhs, const LegacyReverseBidirectionalIterator<Iterator>& rhs) { return (lhs.base() > rhs.base()); };
    template< class Iterator1, class Iterator2 >
    bool	operator>(const LegacyReverseBidirectionalIterator<Iterator1>& lhs, const LegacyReverseBidirectionalIterator<Iterator2>& rhs) { return (lhs.base() < rhs.base()); };
    template< class Iterator >
    bool	operator>(const LegacyReverseBidirectionalIterator<Iterator>& lhs, const LegacyReverseBidirectionalIterator<Iterator>& rhs) { return (lhs.base() < rhs.base()); };
    template< class Iterator1, class Iterator2 >
    bool	operator<=(const LegacyReverseBidirectionalIterator<Iterator1>& lhs, const LegacyReverseBidirectionalIterator<Iterator2>& rhs) { return (lhs.base() >= rhs.base()); };
    template< class Iterator >
    bool	operator<=(const LegacyReverseBidirectionalIterator<Iterator>& lhs, const LegacyReverseBidirectionalIterator<Iterator>& rhs) { return (lhs.base() >= rhs.base()); };
    template< class Iterator1, class Iterator2 >
    bool	operator>=(const LegacyReverseBidirectionalIterator<Iterator1>& lhs, const LegacyReverseBidirectionalIterator<Iterator2>& rhs) { return (lhs.base() <= rhs.base()); };
    template< class Iterator >
    bool	operator>=(const LegacyReverseBidirectionalIterator<Iterator>& lhs, const LegacyReverseBidirectionalIterator<Iterator>& rhs) { return (lhs.base() <= rhs.base()); };
}

#endif
