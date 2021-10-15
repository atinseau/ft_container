
#include <memory>
#include <iostream>
#include <limits>
#include <exception>
#include <stdexcept>
#include <algorithm>

#include "Iterators/Iterator.hpp"


namespace fd
{

	/*	Custom vector implementation for 42 project
	*	High level array for any type
	*	Automatic memory gesture for non pointer T type else delete manually on exit
	*	memory allocation overflow work like:
	*		1 - if the size increase with one and old capacity is lower then
	*			multiplie the capacity by two 
	*		2 - sereval methods change the capacity at specific value like
				assign who set the capacity to X parameter or some overload of insert who
				change the capacity with growth continuoulsy 
			3 - push_back increase to one at end
	*/
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

			explicit vector (size_type count, const value_type& value = value_type(), const allocator_type& alloc = allocator_type()): _c(NULL), _alloc(alloc), _capacity(0), _size(0)
			{
				assign(count, value);
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
			void			assign( InputIt first, InputIt last, typename fd::enable_if<!fd::is_integral<InputIt>::value >::type* = 0)
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
				if (fd::range_address(_c, _size, &(*pos)) || (!_c && !_size && !_capacity))
				{
					int index = &(*pos) - &_c[0];
					if (_size + 1 > _capacity)
						reserve((!_capacity) ? 1 : _capacity * 2);
					
					for (int i = _size - 1; i >= index; i--)
						_alloc.construct(&_c[i + 1], _c[i]);

					_alloc.construct(&_c[index], value);
					_size += 1;
					return (iterator(&_c[index]));
				}
				else
					throw std::logic_error("Invalid iterator for insertion....!");
			}

			void			insert( iterator pos, size_type count, const T& value )
			{
				int	index = 0;
				int last = _size - 1;

				index = (!_capacity ? 0 : static_cast<int>(&(*pos) - &_c[0]));
				if (_size + count > _capacity)
					reserve(_size + count);
				_size += count;

				for (int i = last; i >= index; i--)
					_c[i + count] = _c[i];
				for (int i = index; i < count; i++)
					_c[i] = value;
			}

			template< class InputIt >
			iterator insert(const_iterator pos, InputIt first, InputIt last )
			{
				int			index = 0;
				size_type	count = std::distance(first, last);

				index = (!_capacity ? 0 : static_cast<int>(&(*pos) - &_c[0]));
				if (_size + count > _capacity)
					reserve(_size + count);
				_size += count;

				for (int i = _size - 1; i >= index; i--)
					_c[i + count] = _c[i];
				
				for (; first != last; first++)
					_c[index++] = *first;
				return iterator(&_c[(_size - (_size - index)) - count]);
			}

			void resize(size_type count)
			{
				if (count < 0)
					throw std::length_error("Invalid resize value");
				if (count > _size)
					reserve(count);
				_size = count;
			}

			template <class InputIt>
			iterator erase(InputIt pos, 
				typename fd::enable_if
				<	fd::is_same<InputIt, iterator>::value ||
					fd::is_same<InputIt, const_iterator>::value >::type* = 0)
			{
				if (fd::range_address(_c, _size, &(*pos)))
				{
					size_type coord = &(*pos) - _c;

					for (; coord < _size - 1; coord++)
						_c[coord] = _c[coord + 1];
					_size -= 1;
				}
				return (iterator(pos.getInterval()));
			}

			iterator erase(iterator first, iterator last)
			{
				if (fd::range_address(_c, _size, &(*first)) && fd::range_address(_c, _size, &(*last)))
				{
					const size_type range = std::distance(first, last);
					const size_type start = &(*first) - _c;
					if (!range)
						return (iterator(&(*last)));
					for (size_type i = 0; i < _size - range; i++)
						_c[start + i] = _c[start + range + i];
					_size -= range;
				}
				return (iterator(last.getInterval()));
			}

			iterator erase(const_iterator first, const_iterator last)
			{
				if (fd::range_address(_c, _size, &(*first)) && fd::range_address(_c, _size, &(*last)))
				{
					const size_type range = std::distance(first, last);
					const size_type start = &(*first) - _c;
					if (!range)
						return (iterator(last.getInterval()));
					for (size_type i = 0; i < _size - range; i++)
						_c[start + i] = _c[start + range + i];
					_size -= range;
				}
				return (iterator(last.getInterval()));
			}

			// GETTER
			/**************************************************/

			size_type			capacity(void)		const	{ return (_capacity); }
			size_type			size(void)			const	{ return (_size); }
			size_type			max_size(void)		const	{ return (std::numeric_limits<difference_type>::max()); }
			reference			at(size_type pos)			{ return (_c[pos]); }
			const_reference		at(size_type pos)	const	{ return (_c[pos]); }
			reference			front(void)					{ return _c[0]; }
			const_reference		front(void)			const	{ return _c[0]; }
			reference			back(void)					{ return _c[_size - 1]; }
			const_reference		back(void)			const	{ return _c[_size - 1]; }
			pointer				data(void)					{ return (_c); }
			const pointer		data(void)			const	{ return (_c); }

			// ITERATOR
			/**************************************************/

			iterator			begin(void) 				{ return iterator(&_c[0]); }
			const_iterator		begin(void) 		const	{ return const_iterator(&_c[0]); }

			iterator			end(void) 					{ return iterator(&_c[_size]); }
			const_iterator		end(void) 			const	{ return const_iterator(&_c[_size]); }


			// OVERLOAD
			/**************************************************/

			reference		operator[](int N) { return (_c[N]); }


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

			void _erase_range()
			{
				
			}
	};
};