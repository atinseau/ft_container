
namespace ft
{
	template < class T1, class T2 >
	struct pair
	{
		typedef T1 first_type;
		typedef T2 second_type;

		first_type	first;
		second_type	second;

		pair(void): first(first_type()), second(second_type()) {}
		pair(const T1 & x, const T2 & y): first(x), second(y) {}
		pair(const pair & rhs): first(rhs.first), second(rhs.second) {}

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