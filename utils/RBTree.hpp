
#include <iostream>
#include "stl.hpp"

// data structure that represents a node in the tree

template <
	typename T
>
struct Node
{
	typedef T value_type;
	typedef Node<T>* node_ptr;

	value_type data;	  // holds the key
	node_ptr parent; // pointer to the parent
	node_ptr left;	  // pointer to left child
	node_ptr right;  // pointer to right child
	int color;	  // 1 -> Red, 0 -> Black
};


// class RBTree implements the operations in Red Black Tree
template <
	typename T,
	class Compare = ft::less<T>,
    class Allocator = std::allocator<T>
>
class RBTree
{
	public:
		typedef T value_type;
		typedef Compare key_compare;
		typedef Node<T>	node_type;
		typedef typename node_type::node_ptr node_ptr;
        typedef Allocator allocator_type;
        typedef typename allocator_type::template rebind<node_type>::other allocator_node;

        RBTree(const key_compare &comp = key_compare()) :
                comp(comp),
                _alloc(allocator_node())
        {
            _nil = _alloc.allocate(1);
            _nil->color = 0;
            _nil->left = NULL;
            _nil->right = NULL;
            root = _nil;
        }

        ~RBTree()
        {
           if (root)
                destroy(root);
            _alloc.deallocate(_nil, 1);
        }

	private:
		node_ptr root;
		node_ptr _nil;
        key_compare comp;
        allocator_node _alloc;

    void destroy(node_ptr x)
    {
        if (x->left != _nil)
            destroy(x->left);
        if (x->right != _nil)
            destroy(x->right);
        _alloc.destroy(x);
        _alloc.deallocate(x, 1);
    }

	// initializes the nodes with appropirate values
	// all the pointers are set to point to the null pointer
    void initializeNULLNode(node_ptr node, node_ptr parent)
    {
        node->data = 0;
        node->parent = parent;
        node->left = NULL;
        node->right = NULL;
        node->color = 0;
    }

	void preOrderHelper(node_ptr node)
	{
		if (node != _nil)
		{
			std::cout << node->data << " ";
			preOrderHelper(node->left);
			preOrderHelper(node->right);
		}
	}

	void inOrderHelper(node_ptr node)
	{
		if (node != _nil)
		{
			inOrderHelper(node->left);
			std::cout << node->data << " ";
			inOrderHelper(node->right);
		}
	}

	void postOrderHelper(node_ptr node)
	{
		if (node != _nil)
		{
			postOrderHelper(node->left);
			postOrderHelper(node->right);
            std::cout << node->data << " ";
		}
	}

	node_ptr searchTreeHelper(node_ptr node, value_type key)
	{
		if (node == _nil || (!comp(key, node->data) && !comp(node->data, key)))
		{
			return node;
		}

		if (comp(key, node->data))
		{
			return searchTreeHelper(node->left, key);
		}
		return searchTreeHelper(node->right, key);
	}

	// fix the rb tree modified by the delete operation
	void fixDelete(node_ptr x)
	{
		node_ptr s;
		while (x != root && x->color == 0)
		{
			if (x == x->parent->left)
			{
				s = x->parent->right;
				if (s->color == 1)
				{
					// case 3.1
					s->color = 0;
					x->parent->color = 1;
					leftRotate(x->parent);
					s = x->parent->right;
				}

				if (s->left->color == 0 && s->right->color == 0)
				{
					// case 3.2
					s->color = 1;
					x = x->parent;
				}
				else
				{
					if (s->right->color == 0)
					{
						// case 3.3
						s->left->color = 0;
						s->color = 1;
						rightRotate(s);
						s = x->parent->right;
					}

					// case 3.4
					s->color = x->parent->color;
					x->parent->color = 0;
					s->right->color = 0;
					leftRotate(x->parent);
					x = root;
				}
			}
			else
			{
				s = x->parent->left;
				if (s->color == 1)
				{
					// case 3.1
					s->color = 0;
					x->parent->color = 1;
					rightRotate(x->parent);
					s = x->parent->left;
				}

				if (s->right->color == 0 && s->right->color == 0)
				{
					// case 3.2
					s->color = 1;
					x = x->parent;
				}
				else
				{
					if (s->left->color == 0)
					{
						// case 3.3
						s->right->color = 0;
						s->color = 1;
						leftRotate(s);
						s = x->parent->left;
					}

					// case 3.4
					s->color = x->parent->color;
					x->parent->color = 0;
					s->left->color = 0;
					rightRotate(x->parent);
					x = root;
				}
			}
		}
		x->color = 0;
	}

	void rbTransplant(node_ptr u, node_ptr v)
	{
		if (u->parent == NULL)
		{
			root = v;
		}
		else if (u == u->parent->left)
		{
			u->parent->left = v;
		}
		else
		{
			u->parent->right = v;
		}
		v->parent = u->parent;
	}

	void deleteNodeHelper(node_ptr node, value_type key)
	{
		// find the node containing key
		node_ptr z = _nil;
		node_ptr x, y;
		while (node != _nil)
		{
			if ((!comp(key, node->data) && !comp(node->data, key)))
			{
				z = node;
			}

			if ((!comp(key, node->data) && !comp(node->data, key)) || comp(node->data, key))
			{
				node = node->right;
			}
			else
			{
				node = node->left;
			}
		}

		if (z == _nil)
		{
			std::cout << "Couldn't find key in the tree" << std::endl;
			return;
		}

        if (z->left == _nil && z->right == _nil && z == root) {
            _alloc.destroy(root);
            _alloc.deallocate(z, 1);
            root = NULL;
            return;
        }

		y = z;
		int y_original_color = y->color;
		if (z->left == _nil)
		{
			x = z->right;
			rbTransplant(z, z->right);
		}
		else if (z->right == _nil)
		{
			x = z->left;
			rbTransplant(z, z->left);
		}
		else
		{
			y = minimum(z->right);
			y_original_color = y->color;
			x = y->right;
			if (y->parent == z)
			{
				x->parent = y;
			}
			else
			{
				rbTransplant(y, y->right);
				y->right = z->right;
				y->right->parent = y;
			}

			rbTransplant(z, y);
			y->left = z->left;
			y->left->parent = y;
			y->color = z->color;
		}

        _alloc.destroy(z);
        _alloc.deallocate(z, 1);

		if (y_original_color == 0)
		{
			fixDelete(x);
		}
	}

	// fix the red-black tree
	void fixInsert(node_ptr k)
	{
		node_ptr u;
		while (k->parent->color == 1)
		{
			if (k->parent == k->parent->parent->right)
			{
				u = k->parent->parent->left; // uncle
				if (u->color == 1)
				{
					// case 3.1
					u->color = 0;
					k->parent->color = 0;
					k->parent->parent->color = 1;
					k = k->parent->parent;
				}
				else
				{
					if (k == k->parent->left)
					{
						// case 3.2.2
						k = k->parent;
						rightRotate(k);
					}
					// case 3.2.1
					k->parent->color = 0;
					k->parent->parent->color = 1;
					leftRotate(k->parent->parent);
				}
			}
			else
			{
				u = k->parent->parent->right; // uncle

				if (u->color == 1)
				{
					// mirror case 3.1
					u->color = 0;
					k->parent->color = 0;
					k->parent->parent->color = 1;
					k = k->parent->parent;
				}
				else
				{
					if (k == k->parent->right)
					{
						// mirror case 3.2.2
						k = k->parent;
						leftRotate(k);
					}
					// mirror case 3.2.1
					k->parent->color = 0;
					k->parent->parent->color = 1;
					rightRotate(k->parent->parent);
				}
			}
			if (k == root)
			{
				break;
			}
		}
		root->color = 0;
	}

	void printHelper(node_ptr entry, int space)
	{

        space += 10;

        if (entry->right)
            printHelper(entry->right, space);

        std::cout << std::endl;
        for (int i = 10; i < space; i++)
            std::cout<<" ";

        if (entry == _nil)
            std::cout << "(null)" << std::endl;
        else
            std::cout << entry->data << " " << (entry->color == 0 ? "Black" : "Red") << std::endl;

        if (entry->left)
            printHelper(entry->left, space);

	}

public:
	// Pre-Order traversal
	// Node->Left Subtree->Right Subtree
	void preorder()
	{
		preOrderHelper(this->root);
	}

	// In-Order traversal
	// Left Subtree -> Node -> Right Subtree
	void inorder()
	{
		inOrderHelper(this->root);
	}

	// Post-Order traversal
	// Left Subtree -> Right Subtree -> Node
	void postorder()
	{
		postOrderHelper(this->root);
	}

	// search the tree for the key k
	// and return the corresponding node
	node_ptr searchTree(value_type k)
	{
		return searchTreeHelper(this->root, k);
	}

	// find the node with the minimum key
	node_ptr minimum(node_ptr node)
	{
		while (node && node->left != _nil)
		{
			node = node->left;
		}
		return node;
	}

	// find the node with the maximum key
	node_ptr maximum(node_ptr node)
	{
		while (node->right != _nil)
		{
			node = node->right;
		}
		return node;
	}

	// find the successor of a given node
	node_ptr successor(node_ptr x)
	{
        if (!root)
            return NULL;

        if (x == maximum(root))
            return NULL;
		// if the right subtree is not null,
		// the successor is the leftmost node in the
		// right subtree
		if (x->right != _nil)
		{
			return minimum(x->right);
		}

		// else it is the lowest ancestor of x whose
		// left child is also an ancestor of x.
		node_ptr y = x->parent;
		while (y != _nil && x == y->right)
		{
			x = y;
			y = y->parent;
		}
		return y;
	}

	// find the predecessor of a given node
	node_ptr predecessor(node_ptr x)
	{
		// if the left subtree is not null,
		// the predecessor is the rightmost node in the
		// left subtree
		if (x->left != _nil)
		{
			return maximum(x->left);
		}

		node_ptr y = x->parent;
		while (y != _nil && x == y->left)
		{
			x = y;
			y = y->parent;
		}

		return y;
	}

	// rotate left at node x
	void leftRotate(node_ptr x)
	{
		node_ptr y = x->right;
		x->right = y->left;
		if (y->left != _nil)
		{
			y->left->parent = x;
		}
		y->parent = x->parent;
		if (x->parent == NULL)
		{
			this->root = y;
		}
		else if (x == x->parent->left)
		{
			x->parent->left = y;
		}
		else
		{
			x->parent->right = y;
		}
		y->left = x;
		x->parent = y;
	}

	// rotate right at node x
	void rightRotate(node_ptr x)
	{
		node_ptr y = x->left;
		x->left = y->right;
		if (y->right != _nil)
		{
			y->right->parent = x;
		}
		y->parent = x->parent;
		if (x->parent == NULL)
		{
			this->root = y;
		}
		else if (x == x->parent->right)
		{
			x->parent->right = y;
		}
		else
		{
			x->parent->left = y;
		}
		y->right = x;
		x->parent = y;
	}

	// insert the key to the tree in its appropriate position
	// and fix the tree
	void insert(value_type key)
	{
		// Ordinary Binary Search Insertion
		node_ptr node = _alloc.allocate(1);
		node->parent = NULL;
		node->data = key;
		node->left = _nil;
		node->right = _nil;
		node->color = 1; // new node must be red

        if (!root)
        {
            root = node;
            return;
        }

		node_ptr y = NULL;
		node_ptr x = this->root;

		while (x != _nil)
		{
			y = x;
			if (comp(node->data, x->data))
			{
				x = x->left;
			}
			else
			{
				x = x->right;
			}
		}

		// y is parent of x
		node->parent = y;
		if (y == NULL)
		{
			root = node;
		}
		else if (comp(node->data, y->data))
		{
			y->left = node;
		}
		else
		{
			y->right = node;
		}

		// if new node is a root node, simply return
		if (node->parent == NULL)
		{
			node->color = 0;
			return;
		}

		// if the grandparent is null, simply return
		if (node->parent->parent == NULL)
		{
			return;
		}

		// Fix the tree
		fixInsert(node);
	}

	node_ptr getRoot()
	{
		return this->root;
	}

    node_ptr getEnd()
    {
        return this->_nil;
    }

	// delete the node from the tree
	void deleteNode(value_type data)
	{
		deleteNodeHelper(this->root, data);
	}

	// print the tree structure on the screen
	void prettyPrint()
	{
		if (root)
		{
			printHelper(this->root, 10);
		}
	}
};
