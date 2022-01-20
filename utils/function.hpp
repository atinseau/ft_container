#ifndef __STL_H__
#define __STL_H__

#include <iostream>

namespace ft 
{
	/*
	** enable_if comportement usefully for choose right function template during 
	** the compilation, it take a "boolean response template" like is_integral or is_same
	** return typdef with the wanted type
	*/
	template<bool B>
	struct enable_if {};	
	template<>
	struct enable_if<true> { typedef int type; };

    template< class Iter>
    struct iterator_traits
    {
        typedef typename Iter::difference_type difference_type;
        typedef typename Iter::value_type value_type;
        typedef typename Iter::pointer pointer;
        typedef typename Iter::reference reference;
        typedef typename Iter::iterator_category iterator_category;
    };

	/*
	** boolean response template can used with enable_if or any logical condition
	** during the execution for describe a comportement depending on the template type
	** who is passed 
	*/
	template<class T, class U>
	struct is_same { static const bool value = false; };
	template<class T>
	struct is_same<T, T> { static const bool value = true; };
	
	template <bool isConst, typename isFalse, typename isTrue>
	struct is_const {};

	template <typename isFalse, typename isTrue>
	struct is_const<false, isFalse, isTrue> {
        typedef isFalse type;
    };

	template <typename isFalse, typename isTrue>
	struct is_const<true, isFalse, isTrue> {
        typedef isTrue type;
    };


    template <bool isConstant, typename const_type, typename notConst_type>
    struct is_constant {};

    template <typename const_type, typename notConst_type>
    struct is_constant<true, const_type, notConst_type> {
        typedef const_type		type;
    };

    template <typename const_type, typename notConst_type>
    struct is_constant<false, const_type, notConst_type> {
        typedef notConst_type	type;
    };


    template<typename T>
	struct is_pointer { static const bool value = false; };
	template<typename T>
	struct is_pointer<T*> { static const bool value = true; };
	template<typename T>
	struct is_pointer<const T> { static const bool value = false; };
	template<typename T>
	struct is_pointer<const T*> { static const bool value = true; };


	/*
	**
	** is integral determine if the template type is regular type like
	** int, long, short, unsigned char etc....
	** if isn't , static value in struct initlized to false are accesible and can be used to 
	** enable_if a specific template
	*/
	template <typename T>
	struct is_integral { static const bool value = false; };
	template <>
	struct is_integral<bool> { static const bool value = true; };
	template <>
	struct is_integral<char> { static const bool value = true; };
	template <>
	struct is_integral<float> { static const bool value = true; };
	template <>
	struct is_integral<short> { static const bool value = true; };
	template <>
	struct is_integral<int> { static const bool value = true; };
	template <>
	struct is_integral<long> { static const bool value = true; };
	template <>
	struct is_integral<long long> { static const bool value = true; };
	template <>
	struct is_integral<unsigned char> { static const bool value = true; };
	template <>
	struct is_integral<unsigned short> { static const bool value = true; };
	template <>
	struct is_integral<unsigned int> { static const bool value = true; };
	template <>
	struct is_integral<unsigned long> { static const bool value = true; };
	template <>
	struct is_integral<unsigned long long> { static const bool value = true; };

	template <class Arg1, class Arg2, class Result>
	struct binary_function
	{
		/* The first argument type */
		typedef Arg1 first_argument_type;

		/* The second arguement type */
		typedef Arg2 second_argument_type;

		/* The result type */
		typedef Result result_type;
	};

	template <class T>
	struct less : binary_function<T, T, bool>
	{
		bool operator() (const T& x, const T& y) const { return (x < y); }
	};

    struct random_access_iterator_tag {};
    struct bidirectional_iterator_tag {};


    template <typename T>
    bool range_address(T* array, long size, const T* search)
    {
        if (!array || !search)
            return (false);
        if (search - array <= size && search - array >= 0)
            return (true);
        return (false);
    }
    template<class InputIt1, class InputIt2>
    bool lexicographical_compare(InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2)
    {
        for ( ; (first1 != last1) && (first2 != last2); ++first1, (void) ++first2 ) {
            if (*first1 < *first2) return true;
            if (*first2 < *first1) return false;
        }
        return (first1 == last1) && (first2 != last2);
    }

    template<class InputIterator1, class InputIterator2>
    bool equal(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2)
    {
        while (first1 != last1)
        {
            if (!(*first1 == *first2)) // or: if (!pred(*first1,*first2)), for version 2
                return false;
            ++first1;
            ++first2;
        }
        return true;
    }

    template<class T1, class T2>
    struct pair
    {
        typedef T1 first_type;
        typedef T2 second_type;

        T1 first;
        T2 second;

        pair() : first(), second() {};

        pair( const T1& x, const T2& y ) : first(x), second(y) {};

        template< class U1, class U2 >
        pair( const pair<U1, U2>& p ) : first(p.first), second(p.second) {};

        pair& operator=( const pair& other ) {
            if (this == &other)
                return *this;
            first = other.first;
            second = other.second;
            return *this;
        };
    };

    template <class T1, class T2>
    std::ostream & operator<<(std::ostream &o, ft::pair<T1, T2>& rhs)
    {
        o << "[" << rhs.first << ":" << rhs.second << "]";
        return o;
    }


    template <class T1, class T2>
    std::ostream & operator<<(std::ostream &o, const ft::pair<T1, T2>& rhs)
    {
        o << "[" << rhs.first << ":" << rhs.second << "]";
        return o;
    }

    template< class T1, class T2 >
    bool operator==( const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs ) { return lhs.first == rhs.first && lhs.second == rhs.second; }

    template< class T1, class T2 >
    bool operator!=( const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs ) { return !(lhs == rhs); }

    template< class T1, class T2 >
    bool operator<( const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs ) {

        if (lhs.first < rhs.first)
            return true;
        else if (rhs.first < lhs.first)
            return false;
        else if (lhs.second < rhs.second)
            return true;
        return false;
    };

    template< class T1, class T2 >
    bool operator<=( const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs ) { return !(rhs < lhs); }

    template< class T1, class T2 >
    bool operator>( const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs ) { return rhs < lhs; }

    template< class T1, class T2 >
    bool operator>=( const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs ) { return !(rhs < lhs); }
    template< class T1, class T2 >
    ft::pair<T1,T2> make_pair( T1 t, T2 u ) { return ft::pair<T1, T2>(t, u); };


}

#endif // __STL_H__