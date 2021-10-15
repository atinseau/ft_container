#include "../tester.hpp"
#include <criterion/criterion.h>

template <typename typeTest>
bool empty_basic()
{
	std::vector<typeTest>	v1;
	fd::vector<typeTest>	v2;

	v1.clear();
	v2.clear();

	return equal(v1, v2);
}

template <typename typeTest>
bool not_empty_basic()
{
	bool diff_1 = false, diff_2 = false;

	std::vector<typeTest>	v1 (100);
	fd::vector<typeTest>	v2 (100);
	v1.clear();
	v2.clear();
	diff_1 = equal(v1, v2);
	for (int i = 0; i < 200; i++)
	{
		v1.push_back(Generator<int>(i).get<typeTest>());
		v2.push_back(Generator<int>(i).get<typeTest>());
	}
	v1.clear();
	v2.clear();
	diff_2 = equal(v1, v2);
	return diff_1 && diff_2;
}


/*** TEST 1 ***/
Test(vector_clear, empty_basic_int)
{ cr_assert(empty_basic<int>(), "Vector differ on int....!"); }
Test(vector_clear, empty_basic_float)
{ cr_assert(empty_basic<float>(), "Vector differ on float....!"); }
Test(vector_clear, empty_basic_std_string)
{ cr_assert(empty_basic<std::string>(), "Vector differ on std::string....!"); }
Test(vector_clear, empty_basic_char_ptr)
{ cr_assert(empty_basic<char *>(), "Vector differ on char *....!"); }
Test(vector_clear, empty_basic_foo_int_ptr)
{ cr_assert(empty_basic<foo<int>* >(), "Vector differ on int....!"); }
Test(vector_clear, empty_basic_long)
{ cr_assert(empty_basic<long>(), "Vector differ on bool....!"); }


/*** TEST 2 ***/
Test(vector_clear, not_empty_basic_int)
{ cr_assert(empty_basic<int>(), "Vector differ on int....!"); }
Test(vector_clear, not_empty_basic_float)
{ cr_assert(empty_basic<float>(), "Vector differ on float....!"); }
Test(vector_clear, not_empty_basic_std_string)
{ cr_assert(empty_basic<std::string>(), "Vector differ on std::string....!"); }
Test(vector_clear, not_empty_basic_char_ptr)
{ cr_assert(empty_basic<char *>(), "Vector differ on char *....!"); }
Test(vector_clear, not_empty_basic_foo_int_ptr)
{ cr_assert(empty_basic<foo<int>* >(), "Vector differ on int....!"); }
Test(vector_clear, not_empty_basic_long)
{ cr_assert(empty_basic<long>(), "Vector differ on bool....!"); }


