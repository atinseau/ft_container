#ifndef __TESTER_H__
#define __TESTER_H__

# define C11 1

#include <iostream>
#include <sys/time.h>
#include <vector>
#include <iostream>
#include <criterion/criterion.h>
#include "../Vector.hpp"



double mesure(int (*f)(void));

template <typename T>
bool compare(std::vector<T> &v1, fd::vector<T> &v2)
{
	if (v1.size() != v2.size())	
		return false;
	for (size_t i = 0; i < v1.size(); i++)
	{
		if (v1[i] != v2[i])
			return false;
	}
	return true;
}

template <typename T>
bool equal(std::vector<T> &v1, fd::vector<T> &v2)
{
	bool success = true;
	if (v1.empty() != v2.empty())
	{
		std::cout << "Your vector is empty at start..." << std::endl;
		success = false;
	}
	if(v1.size() != v2.size())
	{
		std::cout << "Your vector has not the good size..." << std::endl;
		success = false;
	}
	if(v1.capacity() != v2.capacity())
	{
		std::cout << "Your vector has not the good capacity..." << std::endl;
		success = false;
	}
	if (!compare(v1, v2))
	{
		std::cout << "Your vector is not the same with the real vector..." << std::endl;
		success = false;
	}
	return (success);
}


#endif // __TESTER_H__