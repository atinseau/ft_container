#ifndef __MAP_H__
#define __MAP_H__

#include <iostream>
#include "utils/pair.hpp"
#include "utils/stl.hpp"

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
				_alloc(alloc) {}

			map(const map& other) :
				_comp(other._comp),
				_alloc(other._alloc) {}

	
		private:
			key_compare	_comp;
			allocator_type _alloc;
			
	};
};

#endif // __MAP_H__