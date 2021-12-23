#include <stack>
#include <vector>
#include <map>
#include <iostream>

#include "utils/RBTree.hpp"
#include "utils/pair.hpp"

int main()
{
	RBTree<ft::pair<int, int> > bst;
	bst.insert(ft::make_pair(1, 1));
    bst.insert(ft::make_pair(2, 2));
    bst.insert(ft::make_pair(3, 3));
    bst.insert(ft::make_pair(4, 4));
    bst.insert(ft::make_pair(5, 5));
    bst.insert(ft::make_pair(6, 6));
    bst.insert(ft::make_pair(7, 7));
    bst.insert(ft::make_pair(8, 8));

    bst.deleteNode(ft::make_pair(3, 3));
    bst.deleteNode(ft::make_pair(4, 4));
    bst.deleteNode(ft::make_pair(5, 5));
    bst.deleteNode(ft::make_pair(6, 6));
    bst.deleteNode(ft::make_pair(7, 7));
    bst.deleteNode(ft::make_pair(8, 8));
    bst.deleteNode(ft::make_pair(1, 1));



    bst.prettyPrint();

    RBTree<ft::pair<int, int> >::node_ptr min = bst.minimum(bst.getRoot());

    while (min != NULL)
    {
        std::cout << min->data << std::endl;
        min = bst.successor(min);
    }

	return 0;
}