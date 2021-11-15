#include <stack>
#include <vector>
#include <map>
#include <iostream>

#include "map.hpp"

int main(void)
{
	ft::map<int, int> m1; 

	m1.insert(ft::make_pair(1, 12));
	m1.insert(ft::make_pair(1, 2));
	m1.insert(ft::make_pair(1, 3));
	m1.insert(ft::make_pair(1, 5));
	m1.insert(ft::make_pair(1, 7));
	m1.insert(ft::make_pair(1, 4));

	m1._sub.draw();

	std::cout << m1.size() << std::endl;

	return (0);
} 