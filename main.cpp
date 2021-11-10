#include <stack>
#include <vector>
#include <map>
#include <iostream>

#include "utils/pair.hpp"
#include "utils/tree.hpp"

int main(void)
{
	ft::tree<int> t1;

	t1.insert_node(10);
	t1.insert_node(11);
	t1.insert_node(15)
	t1.insert_node(5);

	std::cout << t1.size() << std::endl;

	// t1.print();

	std::cout << t1.data()->data << std::endl;

	return (0);
} 