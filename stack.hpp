#ifndef __STACK_H__
#define __STACK_H__

#include "vector.hpp"

namespace ft
{
	template <
		class T,
		class Container = ft::vector<T>
	>
	class stack
	{	
		public:
			typedef Container							container_type;
			typedef typename Container::value_type		value_type;
			typedef typename Container::size_type		size_type;
			typedef typename Container::reference		reference;
			typedef typename Container::const_reference	const_reference;

			stack(void) : c() { }
			stack(const stack& __q) : c(__q.c) {}
			explicit stack( const Container& cont ): c(cont) {};
			stack& operator=(const stack& __q) {c = __q.c; return *this;}
			~stack() {}

			bool			empty() const { return (c.empty()); }
			size_type		size() const { return c.size(); }
			reference		top() { return (c.back()); }
			const_reference	top() const { return (c.back()); }
 
			void			pop() { c.pop_back(); }
			void			push( const value_type& value ) { c.push_back(value); }


			bool	operator==(const stack & rhs) const { return c == rhs.c; }
			bool	operator!=(const stack & rhs) const { return c != rhs.c; }
			bool	operator<(const stack & rhs) const { return c < rhs.c; }
			bool	operator>(const stack & rhs) const { return c > rhs.c; }
			bool	operator<=(const stack & rhs) const { return c <= rhs.c; }
			bool	operator>=(const stack & rhs) const { return c >= rhs.c; }

		protected:
			Container c;
	};

	
};

#endif // __STACK_H__