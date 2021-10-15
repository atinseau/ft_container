#include "../tester.hpp"
#include <criterion/criterion.h>
template <typename typeTest>
bool insert_on_vector()
{
	bool test_1 = false;
	bool test_2 = false;
	{
		std::vector<typeTest> v1;
		fd::vector<typeTest> v2;

		for (int i = 0; i < 100; i++)
		{
			v1.insert(v1.begin() + (v1.size() / 2), Generator<int>(i).get<typeTest>());
			v2.insert(v2.begin() + (v2.size() / 2), Generator<int>(i).get<typeTest>());
		}

		test_1 = equal(v1, v2);
	}
	{
		std::vector<typeTest> v1 (100);
		fd::vector<typeTest> v2 (100);

		for (int i = 0; i < 100; i++)
		{
			v1.insert(v1.end() - 1, Generator<int>(i).get<typeTest>());
			v2.insert(v2.end() - 1, Generator<int>(i).get<typeTest>());
		}

		test_2 = equal(v1, v2);
	}
	return (test_1 && test_2);
}

Test(vector, insert_on_vector)
{
	cr_assert(insert_on_vector<int>(), "Vector differ on int....!");
	cr_assert(insert_on_vector<float>(), "Vector differ on float....!");
	cr_assert(insert_on_vector<std::string>(), "Vector differ on std::string....!");
	cr_assert(insert_on_vector<char *>(), "Vector differ on char *....!");
	cr_assert(insert_on_vector<foo<int>* >(), "Vector differ on int....!");
	cr_assert(insert_on_vector<long>(), "Vector differ on bool....!");
}
