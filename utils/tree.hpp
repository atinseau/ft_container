#include <memory>

namespace ft
{
	template <
		class T
	>
	struct node
	{
		typedef node*	pointer;
		typedef T		value_type;

		value_type	data;
		pointer	left;
		pointer	right;
		pointer	parent;

		node (value_type v = value_type()): data(v), left(NULL), right(NULL), parent(NULL)
		{
			std::cout << "Creating node" << std::endl;
		}
		
	};

	template <
		class T,
		class Allocator = std::allocator<T>
	>
	struct tree
	{
		
		typedef T							value_type;
		typedef	node<T>						node_t;
		typedef typename Allocator::pointer	pointer;
		typedef typename node_t::pointer	node_ptr;

		tree(void): _root(new node_t()), _alloc(Allocator()) {}

		int	size()
		{
			return (_rsize(_root)); 
		}

		void insert_node(value_type v)
		{
			_rinsert_node(_root, new node_t(v));
		}

		void print(void)
		{
			_rprint(_root);
		}

		node_ptr data()
		{
			return _root;
		}

		private:
			node_ptr	_root;
			Allocator	_alloc;

			int _rsize(node_ptr _entry)
			{
				int i = 0;

				i++;
				if (_entry->left)
					i += _rsize(_entry->left);
				if (_entry->right)
					i += _rsize(_entry->right);
				return (i);
			}

			void _rinsert_node(node_ptr _entry, node_ptr next)
			{
				if (_entry->data < next->data)
				{
					if (_entry->right)
					{
						_rinsert_node(_entry->right, next);
						return;
					}
					_entry->right = next;
					next->parent = _entry;
				}
				if (_entry->data > next->data)
				{
					if (_entry->left)
					{
						_rinsert_node(_entry->left, next);
						return;
					}
					_entry->left = next;
					next->parent = _entry;
				}
			}

			void _rprint(node_ptr _entry)
			{
				std::cout << _entry->data << std::endl;

				if (_entry->left)
					_rprint(_entry->left);
				if (_entry->right)
					_rprint(_entry->right);
			}
	};
};