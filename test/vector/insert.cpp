#include "../tester.hpp"
#include <criterion/criterion.h>

template <typename typeTest>
bool insert_on_vector()
{
	bool test_1 = false, test_2 = false;
	{
		std::vector<typeTest> v1;
		ft::vector<typeTest> v2;

		for (int i = 0; i < 100; i++)
		{
			v1.insert(v1.begin() + (v1.size() / 2), Generator<int>(i).get<typeTest>());
			v2.insert(v2.begin() + (v2.size() / 2), Generator<int>(i).get<typeTest>());
		}

		test_1 = equal(v1, v2);
	}
	{
		std::vector<typeTest> v1 (100);
		ft::vector<typeTest> v2 (100);

		for (int i = 0; i < 100; i++)
		{
			v1.insert(v1.end() - 1, Generator<int>(i).get<typeTest>());
			v2.insert(v2.end() - 1, Generator<int>(i).get<typeTest>());
		}

		test_2 = equal(v1, v2);
	}
	return (test_1 && test_2);
}

/*** TEST 1 ***/
Test(vector_insert, insert_on_vector_int)
{ cr_assert(insert_on_vector<int>(), "Vector differ on int....!"); }
Test(vector_insert, insert_on_vector_float)
{ cr_assert(insert_on_vector<float>(), "Vector differ on float....!"); }
Test(vector_insert, insert_on_vector_string)
{ cr_assert(insert_on_vector<std::string>(), "Vector differ on std::string....!"); }
Test(vector_insert, insert_on_vector_char_ptr)
{ cr_assert(insert_on_vector<char *>(), "Vector differ on char *....!"); }
Test(vector_insert, insert_on_vector_foo_int_ptr)
{ cr_assert(insert_on_vector<foo<int>* >(), "Vector differ on int....!"); }
Test(vector_insert, insert_on_vector_long)
{ cr_assert(insert_on_vector<long>(), "Vector differ on bool....!"); }
