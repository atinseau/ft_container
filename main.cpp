#include <stack>
#include <vector>
#include <map>
#include <iostream>

#include "utils/RBTree/runtime.hpp"


int main(void)
{


	ft::RBTree<ft::pair<int, int> > tree;

	for (int i = 0; i < 1000000; i++)
		tree.insert(ft::make_pair<int, int>(i, i));

	tree.delete_node(ft::make_pair<int, int>(1000000, 1000000));

	return (0);
} 