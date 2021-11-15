#include <memory>
#include "stl.hpp"

namespace ft
{
	template <
		class T,
		class Allocator = std::allocator<T>
	>
	struct node
	{
		typedef node*								node_ptr;
		typedef T									value_type;
		typedef Allocator							allocator_type;
		typedef typename allocator_type::pointer	pointer;

		pointer		data;
		node_ptr	left;
		node_ptr	right;
		node_ptr	parent;

		node (const value_type & v = value_type()) :
			data(NULL),
			left(NULL),
			right(NULL),
			parent(NULL),
			_alloc(allocator_type())
		{
			data = _alloc.allocate(1);
			_alloc.construct(data, v);
			std::cout << "Creating node" << std::endl;
		}

		~node(void)
		{
			_alloc.destroy(data);
			_alloc.deallocate(data, 1);
			std::cout << "Destruting node" << std::endl;
		}

		bool	operator<(const node & rhs) const
		{
			if (*data < *rhs.data)
				return true;
			return false;
		}

		bool	operator>(const node & rhs) const { return !(*this < rhs); }
		value_type value() const { return (*data); }

		private:
			allocator_type _alloc;

	};

	template <
		class T,
		class Compare = less<T>
	>
	struct tree
	{
		
		typedef T							value_type;
		typedef value_type &				reference;
		typedef const value_type &			const_reference;
		typedef T*							pointer;
		typedef	node<T>						node_t;
		typedef typename node_t::node_ptr	node_ptr;

		tree(const Compare & comp = Compare()): _root(NULL), _comp(comp) {}
		~tree(void) { _rfree(_root); }

		int	size() const { return (_rsize(_root)); }
		int height() const { return (_rheight(_root)); }

		
		void insert(const_reference v)
		{
			node_ptr tmp = new node_t(v);
			if (!_root)
			{
				_root = tmp;
				return;
			}
			_rinsert(_root, tmp);
		}

		void print(void) const { _rprint(_root); }

		void draw(void) const
		{
			std::cout << "################################################" << std::endl;
			_rdraw(_root, 0);
			std::cout << "################################################" << std::endl;
		}

		node_ptr data() { return _root; }

		private:
			node_ptr	_root;
			Compare		_comp;

			int _rsize(node_ptr _entry) const
			{
				int i = 0;

				i++;
				if (_entry->left)
					i += _rsize(_entry->left);
				if (_entry->right)
					i += _rsize(_entry->right);
				return (i);
			}

			void _rinsert(node_ptr _entry, node_ptr next)
			{
				if (*_entry < *next)
				{
					if (_entry->right)
					{
						_rinsert(_entry->right, next);
						return;
					}
					_entry->right = next;
					next->parent = _entry;
				}
				if (*_entry > *next)
				{
					if (_entry->left)
					{
						_rinsert(_entry->left, next);
						return;
					}
					_entry->left = next;
					next->parent = _entry;
				}
			}

			int _rheight(node_ptr _entry) const
			{
				if (_entry == NULL)
					return (0);
				else
				{
					int lheight = _rheight(_entry->left);
					int rheight = _rheight(_entry->right);
					if (lheight > rheight) 
						return (lheight + 1);
					else
						return (rheight + 1);
				}
			}

			void _rprint(node_ptr _entry) const
			{
				std::cout << _entry->data << std::endl;

				if (_entry->left)
					_rprint(_entry->left);
				if (_entry->right)
					_rprint(_entry->right);
			}

			void _rdraw (node_ptr _entry, int space) const
			{
				space += 10;
			
				if (_entry->right)
					_rdraw(_entry->right, space);

				std::cout << std::endl;
				for (int i = 10; i < space; i++)
					std::cout<<" ";
				std::cout << *_entry->data << std::endl;
			
				if (_entry->left)
					_rdraw(_entry->left, space);
			}

			void _rfree(node_ptr _entry)
			{
				if (_entry->left)
					_rfree(_entry->left);
				if (_entry->right)
					_rfree(_entry->right);
				delete _entry;
			}
	};
};