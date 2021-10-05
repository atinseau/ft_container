
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

	std::vector<int> v1;
	fd::vector<int> v2;

	for (int i = 0; i < 100; i++)
	{
		v1.push_back(i);
		v2.push_back(i);
	}

	v1.insert(v1.begin(), v2.begin(), v2.end());

	vdebug(v1);
	vprint(v1);

	return (0);
}