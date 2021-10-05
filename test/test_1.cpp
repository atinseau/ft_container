
#include "tester.hpp"


Test(vector_init, is_empty_at_start)
{
	std::vector<int> v1;
	fd::vector<int> v2;

	cr_assert(v1.empty() == v2.empty(), "Your vector is not empty at start...");
	cr_assert(v1.size() == v2.size(), "Your vector has a size...");
	cr_assert(v1.capacity() == v2.capacity(), "Your vector has a capacity");
}

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

Test(vector_init, right_constructor)
{
	std::vector<int> v1 (10);
	fd::vector<int> v2 (10);

	cr_assert(equal(v1, v2), "Vector differ....!");
}

Test(vector_init, initialization_list)
{
	std::vector<int> v1 ({1, 2, 3, 4, 5, 6, 7});
	fd::vector<int> v2 ({1, 2, 3, 4, 5, 6, 7});

	cr_assert(equal(v1, v2), "Vector differ....!");
}

Test(vector_init, insert_on_filled_vector)
{
	std::vector<int> v1;
	fd::vector<int> v2;

	for(int i = 0; i < 100; i++)
	{
		v1.push_back(i);
		v2.push_back(i);
	}

	for (int i = 0; i < 100; i++)
	{
		v1.insert(v1.begin() + (v1.size() / 2), i);
		v2.insert(v2.begin() + (v2.size() / 2), i);
	}

	cr_assert(equal(v1, v2), "Vector differ....!");
}


Test(vector_init, insert_on_empty_vector)
{
	std::vector<int> v1;
	fd::vector<int> v2;

	for (int i = 0; i < 100; i++)
	{
		v1.insert(v1.begin() + (v1.size() / 2), i);
		v2.insert(v2.begin() + (v2.size() / 2), i);
	}

	cr_assert(equal(v1, v2), "Vector differ....!");
}

