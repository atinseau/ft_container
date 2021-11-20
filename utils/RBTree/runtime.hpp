#ifndef __TREE_H__
#define __TREE_H__

// create class RBTree

#include "base.hpp"

namespace ft
{
	template <
		class Key,
		class T,
		class Compare = less<Key>
	>
	class RBTree : public RBTreeBase<Key, T, Compare>
	{
		typedef RBTreeBase<Key, T, Compare> Base;

		// Type definitions
		using typename Base::node_pointer;
		using typename Base::node_type;
		using typename Base::pointer;
		using typename Base::reference;
		using typename Base::value_type;

		// Function using
		using Base::_find_node;
		using Base::_minimum;

		// Function node family
		using Base::_grandparent;
		using Base::_parent;
		using Base::_sibling;
		using Base::_uncle;

		// State
		using Base::_nil;
		using Base::_root;
		using Base::_comp;

	public:
		/**
		 * @brief Construct a new RBTree object
		 * @param void
		 */
		RBTree(void) : Base() {}

		/**
		 * @brief Insert a new node into the tree
		 * @param ft::pair<Key,T> v
		 */
		void insert(const value_type v)
		{

			if (_root == _nil)
				_root = _create_node(v, BLACK);
			else
			{
				node_pointer next_node = NULL;
				next_node = _rinsert(_root, v);
				_balancing(next_node);
			}
		}

		/**
		 * @brief find one node by key and delete it
		 * 
		 * @param Key key
		 */
		void delete_node(const Key & key)
		{
			node_pointer node = _find_node(_root, key);

			_delete(node);
		}

		void draw()
		{
			this->_rdraw(_root, 0);
		}

	private:
		/**
		 * @brief Create a new node
		 * 
		 * @param const ft::pair<Key,T> v
		 * @return Node<Key, T>* 
		 */
		node_pointer _create_node(const value_type v, bool color, node_pointer parent = LEAF) const
		{
			node_pointer node = new node_type(v, color, parent, _nil, _nil);
			return node;
		}

		/**
		 * @brief Recursive insert a new node into the tree
		 * 
		 * @param Node<Key,T>* node 
		 * @param const ft::pair<Key,T> v
		 * @return Node<Key,T>*
		 */
		node_pointer _rinsert(node_pointer node, const value_type v)
		{
			if (_comp(node->data.first, v.first))
			{
				if (node->getRight() != _nil)
					return _rinsert(node->getRight(), v);
				node->setRight(_create_node(v, RED, node));
				return node->getRight();
			}
			else
			{
				if (node->getLeft() != _nil)
					return _rinsert(node->getLeft(), v);
				node->setLeft(_create_node(v, RED, node));
				return node->getLeft();
			}
		}

		/**
		 * @brief Restore the RBTree after insertion
		 * 
		 * @param Node<Key,T>* node
		 */
		void _balancing(node_pointer k)
		{
			if (k == _root || _parent(k)->getColor() == BLACK)
			{
				_root->setColor(BLACK);
				return;
			}

			if (_uncle(k)->getColor() == RED)
			{
				_uncle(k)->setColor(BLACK);
				_parent(k)->setColor(BLACK);
				_grandparent(k)->setColor(RED);
				_balancing(_grandparent(k));
			}
			else
			{
				if (_parent(k) == _grandparent(k)->getRight())
				{
					if (k == _parent(k)->getLeft())
					{
						// case 3.2.2
						k = _parent(k);
						this->_rotate_right(k);
					}
					// case 3.2.1
					_parent(k)->setColor(BLACK);
					_grandparent(k)->setColor(RED);
					this->_rotate_left(_grandparent(k));
				}
				else
				{
					if (k == _parent(k)->getRight())
					{
						// mirror case 3.2.2
						k = _parent(k);
						this->_rotate_left(k);
					}
					// mirror case 3.2.1
					_parent(k)->setColor(BLACK);
					_grandparent(k)->setColor(RED);
					this->_rotate_right(_grandparent(k));
				}
				_balancing(k);
			}
		}

		void _delete(node_pointer k)
		{
			if (k->getLeft() == _nil && k->getRight() == _nil)
			{
				if (k == _root)
					_root = _nil;
				else
				{
					if (_parent(k)->getLeft() == k)
						_parent(k)->setLeft(_nil);
					else
						_parent(k)->setRight(_nil);
				}
				delete k;
			}
			else if (k->getLeft() != _nil && k->getRight() != _nil)
			{
				node_pointer node = _minimum(k->getRight());
				value_type cpy = node->data;
				_delete(node);
				k->data = cpy;
			}
			else
			{
				node_pointer node = (k->getLeft() != _nil) ? k->getLeft() : k->getRight();

				if (k != _root)
				{
					if (_parent(k)->getLeft() == k)
						_parent(k)->setLeft(node);
					else
						_parent(k)->setRight(node);
				}
				else
					_root = node;
				delete k;
			}
		}
	};

};

#endif // __TREE_H__