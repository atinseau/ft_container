#ifndef __MAP_H__
#define __MAP_H__

#include <iostream>
#include "utils/pair.hpp"
#include "utils/tree.hpp"

namespace ft
{
	template<
		class Key,
		class T,
		class Compare = less<Key>,
		class Allocator = std::allocator<pair<const Key, T> >
	> class map
	{
		
		typedef Key							key_type;
		typedef T							mapped_type;
		typedef pair<Key, T>				value_type;
		typedef std::size_t					size_type;
		typedef std::ptrdiff_t				difference_type;
		typedef Compare						key_compare;
		typedef Allocator					allocator_type;
		typedef value_type&					reference;
		typedef	const value_type&			const_reference;
		typedef	typename Allocator::pointer	pointer;

		public:
			explicit map( const key_compare& comp =  key_compare() , const Allocator& alloc = Allocator()) :
				_comp(comp),
				_alloc(alloc),
				_sub()
			{}

			map(const map& other) :
				_comp(other._comp),
				_alloc(other._alloc),
				_sub(other._sub)
			{}

			void insert( const value_type& value)
			{
				_sub.insert(value);
			}

			size_type size() const { return (_sub.size()); }


			reference at(const key_type & k)
			{ return (_sub.findByKey(make_pair(k, mapped_type()))); }

			const_reference at(const key_type & k) const
			{ return (_sub.findByKey(make_pair(k, mapped_type()))); }

			bool empty(void) const
			{ return (_sub.size() == 0); }


			// OVERLOAD

			reference operator[](const key_type & k)
			{ return (at(k)); }

			const_reference operator[](const key_type & k) const 
			{ return (at(k)); }
			

		private:
			key_compare	_comp;
			allocator_type _alloc;



		public:
			tree<value_type, Compare> _sub;
			
	};
};

#endif // __MAP_H__