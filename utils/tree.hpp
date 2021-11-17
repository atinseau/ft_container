#include <memory>
#include "stl.hpp"

namespace ft
{
	template <
		class T
	>
	struct node
	{
		typedef node*	node_ptr;
		typedef T		value_type;

		value_type	data;
		node_ptr	left;
		node_ptr	right;
		node_ptr	parent;

		explicit node (const value_type & v = value_type()) :
			data(v),
			left(NULL),
			right(NULL),
			parent(NULL)
		{
			std::cout << "Creating node" << std::endl;
		}

		~node(void)
		{
			std::cout << "Destruting node" << std::endl;
		}

		bool	operator<(const node & rhs) const
		{
			if (data < rhs.data)
				return true;
			return false;
		}

		bool	operator>(const node & rhs) const { return !(*this < rhs); }

	};

	template <
		class T,
		class Compare = less<T>
	>
	struct tree
	{
		
		typedef T									value_type;
		typedef value_type &						reference;
		typedef const value_type &					const_reference;
		typedef value_type*							pointer;
		typedef	node<value_type>					node_t;
		typedef std::allocator<node_t>				allocator_type;
		typedef typename allocator_type::pointer	node_ptr;

		explicit tree(const Compare & comp = Compare()): _root(NULL), _comp(comp), _alloc(allocator_type()) {}
		tree(const tree & other) : _root(_rclone(other._root)), _comp(other._comp), _alloc(other._alloc) {}
		~tree(void) { _rfree(_root); }

		int	size() const { return (_rsize(_root)); }
		int height() const { return (_rheight(_root)); }

		
		void insert(const_reference v)
		{
			try
			{
				findByKey(v);
			} catch (std::exception & e)
			{
				node_ptr tmp = _create_node(v);
				if (!_root)
				{
					_root = tmp;
					return;
				}
				_rinsert(_root, tmp);
			}
		}

		void print(void) const { _rprint(_root); }

		void draw(void) const
		{
			if (!_root)
				return;
			std::cout << "################################################" << std::endl;
			_rdraw(_root, 0);
			std::cout << "################################################" << std::endl;
		}

		node_ptr data() { return _root; }

		template <typename Key, typename Value>
		reference findByKey(const pair<Key, Value> & v)
		{
			node_ptr tmp = _rfindByKey(_root, v);
			if (!tmp)
				throw std::out_of_range("No such key");
			return (tmp->data);
		}

		private:
			node_ptr		_root;
			Compare			_comp;
			allocator_type	_alloc;

			// RECURSIVE FUNCTIONS 

			int _rsize(node_ptr _entry) const
			{
				int i = 0;

				if (!_entry)
					return (i);

				i++;
				if (_entry->left)
					i += _rsize(_entry->left);
				if (_entry->right)
					i += _rsize(_entry->right);
				return (i);
			}

			void _rinsert(node_ptr _entry, node_ptr next)
			{
				if (_entry->data < next->data)
				{
					if (_entry->right)
					{
						_rinsert(_entry->right, next);
						return;
					}
					_entry->right = next;
					next->parent = _entry;
				}
				if (_entry->data > next->data)
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
				std::cout << _entry->data << std::endl;
			
				if (_entry->left)
					_rdraw(_entry->left, space);
			}

			void _rfree(node_ptr _entry)
			{
				if (!_entry)
					return;

				if (_entry->left)
					_rfree(_entry->left);
				if (_entry->right)
					_rfree(_entry->right);
				
				delete _entry;
			}

			template <typename Key, typename Value>
			node_ptr _rfindByKey(node_ptr _entry, const pair<Key, Value> & v)
			{
				if (!_entry)
					return (NULL);
				if (_entry->data.first == v.first)
					return (_entry);
				if (_comp(v.first, _entry->data.first))
				{
					if (_entry->left)
						return (_rfindByKey(_entry->left, v));
				}
				else
				{
					if (_entry->right)
						return (_rfindByKey(_entry->right, v));
				}
				return (NULL);
			}

			node_ptr _rclone(node_ptr _entry)
			{
				if (!_entry)
					return (NULL);
				node_ptr tmp = _create_node(_entry->data);
				tmp->left = _rclone(_entry->left);
				tmp->right = _rclone(_entry->right);
				return (tmp);
			}

			// ITERATIVE FUNCTIONS

			node_ptr _create_node(const_reference v)
			{
				return (new node_t(v));
			}
	};
};