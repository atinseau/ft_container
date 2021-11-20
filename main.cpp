#include <stack>
#include <vector>
#include <map>
#include <iostream>

#include "utils/RBTree/runtime.hpp"


int main(void)
{


	ft::RBTree<int, int> tree;

	tree.insert(ft::make_pair(50, 1));
	tree.insert(ft::make_pair(75, 3));
	tree.insert(ft::make_pair(25, 2));


	tree.insert(ft::make_pair(12, 4));
	tree.insert(ft::make_pair(30, 5));

	tree.insert(ft::make_pair(60, 6));

	
	tree.insert(ft::make_pair(6, 7));

	tree.insert(ft::make_pair(70, 9));

	tree.delete_node(75);

	tree.draw();

	return (0);
} 