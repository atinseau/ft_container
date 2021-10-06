
#include <iostream>
#include <sys/time.h>
#include <vector>
#include "Vector.hpp"
# define MAX_SIZE 100000000



template <typename T>
void vdebug(T & v)
{
	std::cout << "Empty: " << (v.empty() ? "True" : "False") << std::endl;
	std::cout << "Size: " << v.size() << std::endl;
	std::cout << "Capacity: " << v.capacity() << std::endl;
}

template <typename T>
void vprint(T & v)
{
	for(typename T::iterator it = v.begin(); it != v.end(); it++)
		std::cout << *it << std::endl;
}


template <typename T>
int push_bench(void)
{
	T v1 ;

	for(int i = 0; i < MAX_SIZE; i++)
		v1.push_back("salut tout le monde");
	return (1);
}

template<typename T>
int insert_bench(void)
{
	T v1 (MAX_SIZE, 10);

	std::vector<int> needed;

	for(int i = 0; i < 10; i++)
		needed.push_back(i);

	while(needed.size() != 0)
	{
		v1.insert(v1.begin() + (v1.size() / 2), 3, needed.back());
		needed.pop_back();
	}
	return (1);
}


int main(void)
{
	std::vector<std::string> db1 (10, "salut les gars");

	

	fd::vector<std::string> v1;
	// fd::vector<std::string> v2;

	v1.assign(db1.begin(), db1.end());
	// v2.assign(db1.begin(), db1.end());

	vprint(v1);

	// v1.assign(db2.begin(), db2.end());
	// v2.assign(db2.begin(), db2.end());

	// std::cout << std::endl;


	return (0);
}