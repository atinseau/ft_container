#include "../tester.hpp"
#include <criterion/criterion.h>

template <typename typeTest>
bool empty_basic()
{
	std::vector<typeTest> v1;
	ft::vector<typeTest> v2;

	for(int i = 0; i < 100; i++)
	{
		v1.push_back(Generator<int>(i).get<typeTest>());
		v2.push_back(Generator<int>(i).get<typeTest>());
	}

	return (equal(v1, v2));
}

Test(vector_push_back, empty_basic)
{
	cr_assert(empty_basic<int>(), "Vector differ on int....!");
	cr_assert(empty_basic<float>(), "Vector differ on float....!");
	cr_assert(empty_basic<std::string>(), "Vector differ on std::string....!");
	cr_assert(empty_basic<char *>(), "Vector differ on char *....!");
	cr_assert(empty_basic<foo<int>* >(), "Vector differ on int....!");
	cr_assert(empty_basic<long>(), "Vector differ on bool....!");	
}


template <typename typeTest>
bool not_empty_basic()
{
	std::vector<typeTest> v1 (1000);
	ft::vector<typeTest> v2 (1000);

	for(int i = 0; i < 100; i++)
	{
		v1.push_back(Generator<int>(i).get<typeTest>());
		v2.push_back(Generator<int>(i).get<typeTest>());
	}

	return (equal(v1, v2));
}


Test(vector_push_back, not_empty_basic)
{
	cr_assert(not_empty_basic<int>(), "Vector differ on int....!");
	cr_assert(not_empty_basic<float>(), "Vector differ on float....!");
	cr_assert(not_empty_basic<std::string>(), "Vector differ on std::string....!");
	cr_assert(not_empty_basic<char *>(), "Vector differ on char *....!");
	cr_assert(not_empty_basic<foo<int>* >(), "Vector differ on int....!");
	cr_assert(not_empty_basic<long>(), "Vector differ on bool....!");	
}
