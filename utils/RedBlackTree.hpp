#ifndef REDBLACKTREE_HPP
#define REDBLACKTREE_HPP
#include <iostream>

#include "../utils/function.hpp"

namespace ft
{
    template <typename T>
    struct Node
    {
        typedef T 					value_type;
        typedef Node				node_type;
        typedef node_type*			node_ptr;

        value_type					data;
        node_ptr					parent;
        node_ptr					left;
        node_ptr					right;
        int							color;

        Node(value_type key = value_type()) : data(key), parent(NULL), color(1) {}
    };
    template <typename T, class Compare = ft::less<typename T::first_type>, class Allocator = std::allocator<Node<T> > >
    class RedBlackTree
    {
    public:
        typedef T															value_type;
        typedef Compare														key_compare;
        typedef Allocator													allocator_type;
        typedef std::size_t													size_type;
        typedef Node<T>														node_type;
        typedef typename node_type::node_ptr								node_ptr;
        typedef typename allocator_type::template rebind<node_type>::other	allocator_node;
    private:
        node_ptr root;
        node_ptr TNULL;
        allocator_node _alloc;
        size_type _size;
        key_compare _comp;

        // Preorder
        void preOrderHelper(node_ptr node)
        {
            if (node != TNULL)
            {
                std::cout << node->data << " ";
                preOrderHelper(node->left);
                preOrderHelper(node->right);
            }
        }

        // Inorder
        void inOrderHelper(node_ptr node)
        {
            if (node != TNULL)
            {
                inOrderHelper(node->left);
                std::cout << node->data << " ";
                inOrderHelper(node->right);
            }
        }

        // Post order
        void postOrderHelper(node_ptr node)
        {
            if (node != TNULL)
            {
                postOrderHelper(node->left);
                postOrderHelper(node->right);
                std::cout << node->data << " ";
            }
        }
        node_ptr searchTreeHelper(node_ptr node, value_type key) const
        {
            if (node == TNULL || (!_comp(key.first, node->data.first) && !_comp(node->data.first, key.first)))
            {
                return node;
            }
            if (_comp(key.first, node->data.first))
            {
                return searchTreeHelper(node->left, key);
            }
            return searchTreeHelper(node->right, key);
        }

        // For balancing the tree after deletion
        void deleteFix(node_ptr x)
        {
            node_ptr s;
            while (x != root && x->color == 0)
            {
                if (x == x->parent->left)
                {
                    s = x->parent->right;
                    if (s->color == 1)
                    {
                        s->color = 0;
                        x->parent->color = 1;
                        leftRotate(x->parent);
                        s = x->parent->right;
                    }

                    if (s->left->color == 0 && s->right->color == 0)
                    {
                        s->color = 1;
                        x = x->parent;
                    }
                    else
                    {
                        if (s->right->color == 0)
                        {
                            s->left->color = 0;
                            s->color = 1;
                            rightRotate(s);
                            s = x->parent->right;
                        }

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
                        s->color = 0;
                        x->parent->color = 1;
                        rightRotate(x->parent);
                        s = x->parent->left;
                    }

                    if (s->right->color == 0 && s->right->color == 0)
                    {
                        s->color = 1;
                        x = x->parent;
                    }
                    else
                    {
                        if (s->left->color == 0)
                        {
                            s->right->color = 0;
                            s->color = 1;
                            leftRotate(s);
                            s = x->parent->left;
                        }

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
            node_ptr z = TNULL;
            node_ptr x, y;
            while (node != TNULL)
            {
                if ((!_comp(key.first, node->data.first) && !_comp(node->data.first, key.first)))
                {
                    z = node;
                }

                if ((!_comp(key.first, node->data.first) && !_comp(node->data.first, key.first)) || _comp(node->data.first, key.first))
                {
                    node = node->right;
                }
                else
                {
                    node = node->left;
                }
            }
            if (z == TNULL)
            {
                return;
            }

            TNULL->parent = maximum(root);
            this->_size--;

            if (z->left == TNULL && z->right == TNULL && z == root)
            {
                _alloc.destroy(z);
                _alloc.deallocate(z, 1);
                root = TNULL;
                return;
            }
            y = z;
            int y_original_color = y->color;
            if (z->left == TNULL)
            {
                x = z->right;
                rbTransplant(z, z->right);
            }
            else if (z->right == TNULL)
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
                deleteFix(x);
            }
        }

        // For balancing the tree after insertion
        void insertFix(node_ptr k)
        {
            node_ptr u;
            while (k->parent->color == 1)
            {
                if (k->parent == k->parent->parent->right)
                {
                    u = k->parent->parent->left;
                    if (u->color == 1)
                    {
                        u->color = 0;
                        k->parent->color = 0;
                        k->parent->parent->color = 1;
                        k = k->parent->parent;
                    }
                    else
                    {
                        if (k == k->parent->left)
                        {
                            k = k->parent;
                            rightRotate(k);
                        }
                        k->parent->color = 0;
                        k->parent->parent->color = 1;
                        leftRotate(k->parent->parent);
                    }
                }
                else
                {
                    u = k->parent->parent->right;

                    if (u->color == 1)
                    {
                        u->color = 0;
                        k->parent->color = 0;
                        k->parent->parent->color = 1;
                        k = k->parent->parent;
                    }
                    else
                    {
                        if (k == k->parent->right)
                        {
                            k = k->parent;
                            leftRotate(k);
                        }
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

        void printHelper(node_ptr root, std::string indent, bool last)
        {
            if (root != TNULL)
            {
                std::cout << indent;
                if (last)
                {
                    std::cout << "R----";
                    indent += "   ";
                }
                else
                {
                    std::cout << "L----";
                    indent += "|  ";
                }

                std::string sColor = root->color ? "RED" : "BLACK";
                std::cout << " [ " << root->data.first << ", " << root->data.second << " ] "
                          << "(" << sColor << ")" << std::endl;
                printHelper(root->left, indent, false);
                printHelper(root->right, indent, true);
            }
        }
    public:
        RedBlackTree(const key_compare &comp = key_compare()) : _alloc(allocator_node()), _comp(comp)
        {
            TNULL = _alloc.allocate(1);
            TNULL->color = 0;
            TNULL->left = NULL;
            TNULL->right = NULL;
            root = TNULL;
            _size = 0;
        }
        RedBlackTree(const RedBlackTree &x) : _alloc(x._alloc), _comp(x._comp)
        {
            TNULL = _alloc.allocate(1);
            TNULL->color = 0;
            TNULL->left = NULL;
            TNULL->right = NULL;
            root = TNULL;
            _size = 0;
            node_ptr min = x.minimum(x.getRoot());
            while (min != x.getEnd())
            {
                insert(min->data);
                min = x.successor(min);
            }
            _size = x.getSize();
        }
        ~RedBlackTree()
        {
            if (_size > 0)
                clear();
            _alloc.deallocate(TNULL, 1);
        }
        void		clear()
        {
            if (root && root != TNULL)
                destroy(root);
            root = TNULL;
            // _alloc.deallocate(TNULL, 1);
            _size = 0;

        }
        RedBlackTree &operator=(RedBlackTree const &src)
        {
            if (this == &src)
                return *this;
            clear();
            node_ptr min = src.minimum(src.getRoot());
            while (min != src.getEnd())
            {
                this->insert(min->data);
                min = src.successor(min);
            }
            return *this;
        };

        void swap(RedBlackTree& x)
        {
            if (&x == this)
                return ;

            node_ptr root_tmp = this->root;
            node_ptr end_tmp = this->TNULL;
            size_t tmp_size = this->_size;
            this->TNULL = x.TNULL;
            this->root = x.root;
            this->_size = x._size;
            x.TNULL = end_tmp;
            x.root = root_tmp;
            x._size = tmp_size;
        }

        void destroy(node_ptr x)
        {
            if (x && x->left != TNULL)
            {
                destroy(x->left);
            }
            if (x && x->right != TNULL)
            {
                destroy(x->right);
            }
            _alloc.deallocate(x, 1);
            x = TNULL;
        }

        void preorder()
        {
            preOrderHelper(this->root);
        }

        void inorder()
        {
            inOrderHelper(this->root);
        }

        void postorder()
        {
            postOrderHelper(this->root);
        }

        node_ptr searchTree(value_type k) const
        {
            return searchTreeHelper(this->root, k);
        }

        ft::pair<node_ptr, bool> search_node(value_type k) const
        {
            node_ptr elem = searchTree(k);
            bool found = elem != TNULL;
            return ft::make_pair(elem, found);
        }
        size_type max_size() const { return _alloc.max_size(); };

        void leftRotate(node_ptr x)
        {
            node_ptr y = x->right;
            x->right = y->left;
            if (y->left != TNULL)
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

        void rightRotate(node_ptr x)
        {
            node_ptr y = x->left;
            x->left = y->right;
            if (y->right != TNULL)
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

        // Inserting a node
        node_ptr insert(const value_type key)
        {
            node_ptr node = _alloc.allocate(1);
            _alloc.construct(node, node_type(key));
            node->left = TNULL;
            node->right = TNULL;
            node->color = 1;
            this->_size++;
            node_ptr y = NULL;
            node_ptr x = this->root;

            while (x != TNULL)
            {
                y = x;
                if (_comp(node->data.first, x->data.first))
                    x = x->left;
                else
                    x = x->right;
            }

            node->parent = y;
            if (y == NULL)
            {
                root = node;
            }
            else if (_comp(node->data.first, y->data.first))
            {
                y->left = node;
            }
            else
            {
                y->right = node;
            }
            this->TNULL->parent = maximum(this->root);

            if (node->parent == NULL)
            {
                node->color = 0;
                return node;
            }

            if (node->parent->parent == NULL)
            {
                return node;
            }
            insertFix(node);
            return node;
        }

        node_ptr getRoot() const
        {
            return this->root;
        }

        void deleteNode(value_type data)
        {
            deleteNodeHelper(this->root, data);
        }

        void deleteNodePtr(node_ptr pos, value_type data)
        {
            deleteNodeHelper(pos, data);
        }
        void printTree()
        {
            if (root)
                printHelper(this->root, "", true);
        }

        node_ptr minimum(node_ptr node) const {
            while (node && node->left != TNULL)
                node = node->left;
            return !node ? TNULL : node;
        }

        node_ptr maximum(node_ptr node) const {
            if (node == TNULL)
                return node;
            while (node->right != TNULL)
                node = node->right;
            return node;
        }

        node_ptr successor(node_ptr x) const {
            if (x == TNULL)
                return (minimum(this->root));
            if (x->right != TNULL) {
                return minimum(x->right);
            }

            node_ptr y = x->parent;
            while (y && x && y != TNULL && x == y->right) {
                x = y;
                y = y->parent;
            }
            return !y ? TNULL : y ;
        }

        node_ptr predecessor(node_ptr x) const {

            if (x == TNULL)
                return (maximum(this->root));

            if (x->left != TNULL) {
                return maximum(x->left);
            }

            node_ptr y = x->parent;
            while (y != TNULL && x == y->left) {
                x = y;
                if (y->parent == NULL)
                    return NULL;
                y = y->parent;
            }

            return y;
        }

        node_ptr getEnd() const {
            return this->TNULL;
        }

        size_type getSize() const {
            return this->_size;
        }
    };
}
#endif
