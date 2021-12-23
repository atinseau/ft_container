
#include <ostream>

namespace ft
{
	template < class T1, class T2 >
	struct pair
	{
		typedef T1 first_type;
		typedef T2 second_type;

		first_type	first;
		second_type	second;

		pair(): first(first_type()), second(second_type()) {}
		pair(const T1 & x, const T2 & y): first(x), second(y) {}
		pair(const pair & rhs): first(rhs.first), second(rhs.second) {}

        template< class U1, class U2 >
        pair( const pair<U1, U2>& p ) : first(p.first), second(p.second) {};


        pair & operator=(const pair & rhs)
		{
			first = rhs.first;
			second = rhs.second;
			return (*this);
		}

		void swap(pair & rhs)
		{
			const first_type tmp_1 = first;
			const second_type tmp_2 = second;

			first = rhs.first;
			second = rhs.second;
			rhs.first = tmp_1;
			rhs.second = tmp_2;
		}
	};

	template< class T1, class T2 >
	bool operator==( const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs )
	{
		return (lhs.first == rhs.first && lhs.second == rhs.second);
	}

	template< class T1, class T2 >
	bool operator!=( const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs )
	{
		return (!(lhs == rhs));
	}

	template< class T1, class T2 >
	bool operator<( const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs )
	{
		return (lhs.first < rhs.first || (!(rhs.first < lhs.first) && lhs.second < rhs.second)); 
	}

	template <class T1, class T2>
	bool operator<= (const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs)
	{
		return !(rhs < lhs);
	}

	template <class T1, class T2>
	bool operator>  (const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs)
	{
		return (rhs < lhs);
	}

	template <class T1, class T2>
	bool operator>= (const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs)
	{
		return !(lhs < rhs);
	}

	template <class T1, class T2>
	std::ostream & operator<<(std::ostream &o, ft::pair<T1, T2>& rhs)
	{
		o << "[" << rhs.first << ":" << rhs.second << "]";
		return o;
	}

	template < class T1, class T2>
	T2 & get(pair<T1, T2> & p)
	{
		return p.second;
	}

	template< class T1, class T2 >
	pair<T1,T2> make_pair( T1 t, T2 u )
	{
		pair<T1, T2> p(t, u);
		return (p);
	}
};