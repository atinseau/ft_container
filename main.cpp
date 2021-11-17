#include <stack>
#include <vector>
#include <map>
#include <iostream>

#include "map.hpp"

template <class Map>
void mdebug(Map & m)
{
	std::cout << "Empty: " << (m.empty() ? "True": "False") << std::endl;
	std::cout << "Size: " << m.size() << std::endl;
}

int main(void)
{
	ft::map<int, int> m1; 
;
	// mdebug(m1);

	m1.insert(ft::make_pair(1, 13));
	m1.insert(ft::make_pair(1, 13));

	std::cout << m1[1] << std::endl;
	
	mdebug(m1);

	return (0);
} 