#ifndef VECTOR_INCLUDE
#define VECTOR_INCLUDE


#include <memory>
#include <iostream>
#include <limits>
#include <exception>
#include <stdexcept>
#include <algorithm>

#ifndef ITERATOR_INCLUDE
 #define ITERATOR_INCLUDE
 #include "Iterators/Iterator.hpp"
#endif

#ifndef REVERSE_INCLUDE
 #define REVERSE_INCLUDE
 #include "Iterators/ReverseIterator.hpp"
#endif


namespace ft
{
	template <
		typename T,
		typename Allocator = std::allocator<T>
	>
	class vector
	{
		public:
			typedef T							value_type;
			typedef Allocator					allocator_type;
			typedef std::size_t					size_type;
			typedef std::ptrdiff_t				difference_type;
			typedef value_type&					reference;
			typedef const value_type&			const_reference;
			typedef typename Allocator::pointer	pointer;

			typedef Iterator<T, false>			iterator;
			typedef Iterator<T, true>			const_iterator;
			typedef ReverseIterator<T, false>	reverse_iterator;
			typedef ReverseIterator<T, true>	const_reverse_iterator;

			vector(void):  _c(NULL), _capacity(0), _size(0) {}

			# ifdef C11
				vector(std::initializer_list<value_type> lst, const allocator_type& alloc = allocator_type()): _c(NULL), _alloc(alloc), _capacity(0), _size(0)
				{
					reserve(lst.size());
					for(typename std::initializer_list<value_type>::const_iterator it = lst.begin(); it != lst.end(); it++)
					{
						_alloc.construct(&_c[_size], *it);
						_size++;
					}
				}
			#endif 

			explicit vector(size_type count, const value_type& value = value_type(), const allocator_type& alloc = allocator_type()): _c(NULL), _alloc(alloc), _capacity(0), _size(0)
			{
				assign(count, value);
			}

			vector(const vector & rhs):  _c(NULL), _capacity(0), _size(0)
			{
				_copy(rhs);
			}

		
			template< class InputIt >
			vector(InputIt first, InputIt last, const Allocator& alloc = Allocator(), typename enable_if<!is_integral<InputIt>::value>::type* = 0):  _c(NULL), _alloc(alloc), _capacity(0), _size(0)
			{
				size_type range = std::distance(first, last);
				reserve(range);

				for (; first != last; first++)
				{
					_alloc.construct(_c + _size, *first);
					_size++;
				}
			}

			~vector(void)
			{
				clear();
				_alloc.deallocate(_c,  _capacity);
			}

			// MEMORY
			/**************************************************/

			void			reserve(size_type new_cap)
			{
				pointer _tmp;
				if (new_cap > max_size() || new_cap < 0)
					throw std::length_error("invalid size");
				if (new_cap > _capacity)
				{
					_tmp = _alloc.allocate(new_cap);
					if (_c && _size)
					{
						for (size_type i = 0; i < _size; i++)
						{
							_alloc.construct(&_tmp[i], _c[i]);
							_alloc.destroy(&_c[i]);
						}
						_alloc.deallocate(_c, _capacity);
					}
					_c = _tmp;
					_capacity = new_cap;
				}
			}


			// SETTER
			/**************************************************/

			void			assign(size_type count, const value_type& value)
			{
				_clear_capacity(count);
				for(; _size < count; _size++)
					_alloc.construct(&_c[_size], value);
			}

			template< class InputIt >
			void			assign( InputIt first, InputIt last, typename ft::enable_if<!ft::is_integral<InputIt>::value >::type* = 0)
			{
				_clear_capacity(std::distance(first, last));
				for (; first != last; first++)
				{
					_alloc.construct(&_c[_size], *first);
					_size++;
				}
			}

			void			push_back(const value_type &value)
			{
				if (_size + 1 > _capacity)
					reserve(!_capacity ? 1 : _capacity * 2);
				_size += 1;
				_alloc.construct(&_c[_size - 1], value);
			}

			void			pop_back(void)
			{
				if (_size - 1 >= 0 && _c)
				{
					_alloc.destroy(&_c[_size - 1]);
					_size -= 1;
				}
			}

			void			clear(void)
			{
				if (_size)
				{
					for(size_type i = 0; i < _size; i++)
						_alloc.destroy(&_c[i]);
					_size = 0;
				}
			}

			iterator		insert( iterator pos, const value_type value )
			{
				if (ft::range_address(_c, _size, &(*pos)) || (!_c && !_size && !_capacity))
				{
					int index = &(*pos) - &_c[0];
					if (_size + 1 > _capacity)
						reserve((!_capacity) ? 1 : _capacity * 2);
					_move_to_right(1, index);
					_alloc.construct(_c + index, value);
					_size += 1;
					return (iterator(&_c[index]));
				}
				else
					throw std::logic_error("Invalid iterator for insertion....!");
			}

			void			insert( iterator pos, size_type count, const T& value )
			{
				if (ft::range_address(_c, _size, &(*pos)) || (!_c && !_size && !_capacity))
				{
					int index = &(*pos) - &_c[0];
					if (_size + count > _capacity)
						reserve(_size + count);
					_move_to_right(count, index);
					for (size_type i = index; i < index + count; i++)
						_alloc.construct(_c + i, value);
					_size += count;
				}
				else
					throw std::logic_error("Invalid iterator for insertion....!");
			}

			template< class InputIt >
			iterator insert(const_iterator pos, InputIt first, InputIt last,
				typename enable_if<!is_integral<InputIt>::value>::type* = 0
			)
			{
				if (ft::range_address(_c, _size, &(*pos)) || (!_c && !_size && !_capacity))
				{
					size_type	count = std::distance(first, last);
					int index = &(*pos) - &_c[0];
					if (_size + count > _capacity)
						reserve(_size + count);
					_move_to_right(count, index);
					for (; first != last; first++)
					{
						_alloc.construct(_c + index, *first);
						index++;
					}
					_size += count;
					return iterator(&_c[(_size - (_size - index)) - count]);
				}
				else
					throw std::logic_error("Invalid iterator for insertion....!");
			}

			void resize(size_type count)
			{
				if (count < 0)
					throw std::length_error("Invalid resize value");
				if (count > _size)
					reserve(count);
				_size = count;
			}

			void resize(size_type count, const value_type& value )
			{
				size_type old_size = _size;
				resize(count);
				if (count > old_size)
				{
					for (; old_size < count; old_size++)
						_alloc.construct(_c + old_size, value);
				}
			}

			template <class InputIt>
			iterator erase(InputIt pos, 
				typename ft::enable_if
				<	ft::is_same<InputIt, iterator>::value ||
					ft::is_same<InputIt, const_iterator>::value >::type* = 0)
			{
				if (ft::range_address(_c, _size, &(*pos)))
				{
					size_type coord = &(*pos) - _c;

					for (; coord < _size - 1; coord++)
						_c[coord] = _c[coord + 1];
					_size -= 1;
				}
				return (iterator(pos.base()));
			}

			iterator erase(iterator first, iterator last) { return _erase_range(first, last); }
			iterator erase(const_iterator first, const_iterator last) { return _erase_range(first, last); }

			void swap( vector& other )
			{
				swap(_c, other._c);
				swap(_alloc, other._alloc);
				swap(_capacity, other._capacity);
				swap(_size, other._size);
			}

			// GETTER
			/**************************************************/

			size_type			capacity(void)		const	{ return (_capacity); }
			size_type			size(void)			const	{ return (_size); }
			size_type			max_size(void)		const	{ return (_alloc.max_size()); }
			reference			front(void)					{ return _c[0]; }
			const_reference		front(void)			const	{ return _c[0]; }
			reference			back(void)					{ return _c[_size - 1]; }
			const_reference		back(void)			const	{ return _c[_size - 1]; }
			pointer				data(void)					{ return (_c); }
			const pointer		data(void)			const	{ return (_c); }

			reference			at(size_type pos)			
			{
				if (pos >= _size)
					throw std::out_of_range("out of bound");
				return (_c[pos]);
			}
			const_reference		at(size_type pos)	const
			{
				if (pos >= _size)
					throw std::out_of_range("out of bound");
				return (_c[pos]);
			}

			// ITERATOR
			/**************************************************/

			iterator				begin(void) 				{ return iterator(_c); }
			const_iterator			begin(void) 	const	{ return const_iterator(_c); }

			iterator				end(void) 				{ return iterator(_c+ _size); }
			const_iterator			end(void) 		const	{ return const_iterator(_c + _size); }

			reverse_iterator		rbegin(void)			{ return reverse_iterator(_c + (_size)); }
			const_reverse_iterator	rbegin(void)	const	{ return const_reverse_iterator(_c + (_size)); }

			reverse_iterator		rend(void)				{ return reverse_iterator(_c); }
			reverse_iterator		rend(void)		const	{ return const_reverse_iterator(_c); }


			// OVERLOAD
			/**************************************************/

			reference		operator[](size_type pos) { return (_c[pos]); }
			const_reference operator[]( size_type pos ) const { return (_c[pos]); }
			void		operator=(const vector & rhs)
			{
				clear();
				_copy(rhs);
			}

			// STATE FUNCTION
			/**************************************************/

			bool			empty(void) const { return (begin() == end()); }


		private:
			pointer			_c;
			allocator_type	_alloc;
			size_type		_capacity;
			size_type		_size;

			void _clear_capacity(size_type count)
			{
				clear();
				reserve(count);
			}

			template <typename InputIt>
			iterator _erase_range(InputIt first, InputIt last,
				typename enable_if<is_same<InputIt, iterator>::value || is_same<InputIt, const_iterator>::value>::type* = 0
			)
			{
				
				if (ft::range_address(_c, _size, &(*first)) && ft::range_address(_c, _size, &(*last)))
				{
					const size_type range = std::distance(first, last);
					const size_type start = &(*first) - _c;
					size_type i = 0;
					if (!range)
						return (iterator(last.base()));
					for (; i < _size - range; i++)
						_c[start + i] = _c[start + range + i];
					_size -= range;
					return (iterator(&_c[start]));
				}
				return (end());
			}

			void _move_to_right (int step, int to)
			{
				for (int i = _size - 1; i >= to; i--)
				{
					_alloc.construct(&_c[i + step], _c[i]);
					_alloc.destroy(_c + i);
				}
			}

			void _copy(const vector & rhs)
			{
				reserve(rhs.capacity());
				
				for (typename vector<T>::const_iterator it = rhs.begin(); it != rhs.end(); it++)
				{
					_alloc.construct(_c + _size, *it);
					_size++;
				}
			}

			template <typename Any>
			void swap(Any & a, Any & b)
			{
				Any tmp = a;
				a = b;
				b = tmp;
			}

			friend void swap (vector& x, vector& y) { x.swap(y); }
	};

	template <typename T, class Alloc >
	bool operator==(const vector<T, Alloc> & lhs, const vector<T, Alloc> & rhs)
	{
		typename vector<T, Alloc>::const_iterator it_1 = lhs.begin();
		typename vector<T, Alloc>::const_iterator it_2 = rhs.begin();
		
		if (lhs.size() != rhs.size())
			return (false);

		while(it_1 != lhs.end() && it_2 != rhs.end())
		{
			if (*it_1 != *it_2)
				return (false);
			it_1++;
			it_2++;
		}
		return (true);
	}

	template <typename T, class Alloc >
	bool operator<(const vector<T, Alloc> & lhs, const vector<T, Alloc> & rhs)
	{
		return lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	}

	template <typename T, class Alloc >
	bool operator>(const vector<T, Alloc> & lhs, const vector<T, Alloc> & rhs)
	{
		return rhs < lhs;
	}

	template <typename T, class Alloc >
	bool operator<=(const vector<T, Alloc> & lhs, const vector<T, Alloc> & rhs)
	{
		
		return !(rhs < lhs);
	}

	template <typename T, class Alloc >
	bool operator>=(const vector<T, Alloc> & lhs, const vector<T, Alloc> & rhs)
	{
		return !(lhs < rhs);
	}

		template <typename T, class Alloc >
	bool operator!=(const vector<T, Alloc> & lhs, const vector<T, Alloc> & rhs)
	{
		return !(lhs == rhs);
	}
};

#endif