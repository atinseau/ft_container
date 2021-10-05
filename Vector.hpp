
#include <memory>
#include <iostream>
#include <limits>
#include <exception>
#include <stdexcept>

#include "Iterators/Iterator.hpp"


namespace fd
{
	template <
		typename T,
		typename Allocator = std::allocator<T>
	>
	class vector
	{
		public:
			typedef T														value_type;
			typedef Allocator												allocator_type;
			typedef std::size_t												size_type;
			typedef std::ptrdiff_t											difference_type;
			typedef value_type&												reference;
			typedef const value_type&										const_reference;
			typedef typename Allocator::pointer								pointer;
			typedef Iterator<value_type, std::random_access_iterator_tag>	iterator;

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
				if (new_cap > max_size())
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
				clear();
				_alloc.deallocate(_c, _capacity);
				reserve(count);
				for(; _size < count; _size++)
					_alloc.construct(&_c[_size], value);
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

			// GETTER
			/**************************************************/

			size_type			capacity(void) const { return (_capacity); }
			size_type			size(void) const { return (_size); }
			size_type			max_size(void) const { return (std::numeric_limits<difference_type>::max()); }
			reference			at(size_type pos) { return (_c[pos]); }
			const_reference		at(size_type pos) const { return (_c[pos]); }
			reference			front(void) { return _c[0]; }
			const_reference		front(void) const { return _c[0]; }
			reference			back(void) { return _c[_size - 1]; }
			const_reference		back(void) const { return _c[_size - 1]; }
			pointer				data(void) { return (_c); }
			const pointer		data(void) const { return (_c); }

			// ITERATOR
			/**************************************************/

			iterator		begin(void) const { return iterator(&_c[0]); }

			iterator		end(void) const { return iterator(&_c[_size]); }

			iterator		insert( iterator pos, const value_type value )
			{
				int	index = 0;
				int i = _size;

				index = (!_capacity ? 0 : static_cast<int>(&(*pos) - &_c[0]));
				if (_size + 1 > _capacity)
					reserve(!_capacity ? 1 : _capacity * 2);
				_size += 1;
			
				while(i >= index)
				{
					_c[i + 1] = _c[i];
					i--;
				}
				_c[index] = value;
				return (iterator(&_c[index]));
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
		
				// for (size_type e = index; e < count + index; e++)
				// 	_c[e] = value;
			}


			// OVERLOAD
			/**************************************************/

			reference &		operator[](int N) { return (_c[N]); }


			// STATE FUNCTION
			/**************************************************/

			bool			empty(void) const { return (begin() == end()); }


			private:
				pointer			_c;
				allocator_type	_alloc;
				size_type		_capacity;
				size_type		_size;
	};
};