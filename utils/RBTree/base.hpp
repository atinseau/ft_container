#ifndef __BASE_H__
#define __BASE_H__

#include "../pair.hpp"
#include "../stl.hpp"

#define RED true
#define BLACK false
#define LEAF NULL

namespace ft
{

	template <
		typename T
	>
	struct Node
	{
		typedef T					value_type;
		typedef value_type*			pointer;
		typedef value_type& 		reference;
		typedef Node*				node_pointer;

		value_type		data;

		private:
			node_pointer	parent;
			node_pointer	left;
			node_pointer	right;
			bool			color;

		public:
			Node(
				const value_type v = value_type(),
				bool c = BLACK,
				node_pointer p = LEAF,
				node_pointer l = LEAF,
				node_pointer r = LEAF
			) : data(v),  parent(p), left(l), right(r), color(c) 
			{}

		
			bool 			getColor() const { return color; }
			node_pointer 	getParent() const { return parent; }
			node_pointer 	getLeft() const { return left; }
			node_pointer 	getRight() const { return right; }

			void 			setColor(bool c) { color = c; }
			void 			setParent(node_pointer p) { parent = p; }
			void 			setLeft(node_pointer l) { left = l; }
			void 			setRight(node_pointer r) { right = r; }

	};

	template<
		class Key, 
		class T, 
		class Compare = less<Key>
	>
	class RBTreeBase
	{
		public:
			typedef Node<pair<Key, T> >						node_type;
			typedef typename node_type::node_pointer	node_pointer;
			typedef typename node_type::value_type		value_type;
			typedef typename node_type::pointer			pointer;
			typedef typename node_type::reference		reference;

			RBTreeBase(void):_comp(Compare())
			{
				_nil = new node_type();
				_nil->setColor(BLACK);
				_root = _nil;
			}

			virtual ~RBTreeBase(void) {}

		protected:
			node_pointer	_root;
			node_pointer	_nil;
			Compare			_comp;

			virtual node_pointer _create_node(const value_type v, bool color, node_pointer parent = LEAF) const = 0;
			virtual node_pointer _rinsert(node_pointer node, const value_type v) = 0;
			virtual void _balancing(node_pointer inserted_node) = 0;

			void _rdraw(node_pointer _entry, int space)
			{
				space += 10;
			
				if (_entry->getRight())
					_rdraw(_entry->getRight(), space);

				std::cout << std::endl;
				for (int i = 10; i < space; i++)
					std::cout<<" ";

				if (_entry == _nil)
					std::cout << "(null)" << std::endl;
				else
					std::cout << _entry->data << " " << (_entry->getColor() == BLACK ? "Black" : "Red") << std::endl;
			
				if (_entry->getLeft())
					_rdraw(_entry->getLeft(), space);
			}


			/**
			 * @brief Rotate the tree to the left
			 * 
			 */
			void _rotate_left(node_pointer x)
			{
				node_pointer y = x->getRight();

				x->setRight(y->getLeft());

				// RESTORE BRANCH HERITAGE
				if (y->getLeft() != _nil)
					y->getLeft()->setParent(x);

				// CONNECT X PARENT WITH Y PARENT
				y->setParent(_parent(x));

				// REPARE ROOT
				if (_parent(x) == NULL)
					_root = y;
				else if (x == _parent(x)->getLeft())
					_parent(x)->setLeft(y);
				else
					_parent(x)->setRight(y);

				y->setLeft(x);
				x->setParent(y);
			}

			/**
			 * @brief Rotate the tree to the right
			 * 
			 */
			void _rotate_right(node_pointer x)
			{
				node_pointer y = x->getLeft();

				x->setLeft(y->getRight());

				// RESTORE BRANCH HERITAGE
				if (y->getRight() != _nil)
					y->getRight()->setParent(x);

				// CONNECT X PARENT WITH Y PARENT
				y->setParent(_parent(x));

				// REPARE ROOT
				if (_parent(x) == NULL)
					_root = y;
				else if (x == _parent(x)->getRight())
					_parent(x)->setRight(y);
				else
					_parent(x)->setLeft(y);

				y->setRight(x);
				x->setParent(y);
			}

			/**
			 * @brief get the parent of a node
			 * 
			 * @param Node<Key, T>* node 
			 * @return Node<Key, T>* 
			 */
			node_pointer _parent(node_pointer node)
			{
				return node->getParent();
			}

			/**
			 * @brief get the uncle of a node
			 * 
			 * @param Node<Key, T>* node
			 * @return Node<Key, T>*
			 */
			node_pointer _uncle(node_pointer node)
			{
				return _sibling(_parent(node));
			}

			/**
			 * @brief get the sibling of a node
			 * 
			 * @param Node<Key, T>* node
			 * @return Node<Key, T>*
			 */
			node_pointer _sibling(node_pointer node)
			{
				node_pointer parent = _parent(node);
				
				if (parent->getLeft() == node)
					return parent->getRight();
				else
					return parent->getLeft();
			}
			
			/**
			 * @brief get the grandparent of a node
			 * 
			 * @param Node<Key, T>* node 
			 * @return Node<Key, T>*
			 */
			node_pointer _grandparent(node_pointer node)
			{
				return _parent(_parent(node));	
			}


			/**
			 * @brief find node with the given key, only if tree is equilibrated
			 * 
			 * @param Node<Key, T>* node
			 * @param Key key
			 * @return Node<Key, T>* 
			 */
			node_pointer _find_node(node_pointer node, const Key & key)
			{
				if (node->data.first == key || node == _nil)
					return node;

				if (_comp(node->data.first, key))
					return _find_node(node->getRight(), key);
				else
					return _find_node(node->getLeft(), key);
			}

			node_pointer _minimum(node_pointer node)
			{
				while (node->getLeft() != _nil)
					node = node->getLeft();
				return node;
			}
	};
};

#endif // __BASE_H__