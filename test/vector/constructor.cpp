#include <criterion/criterion.h>
#include "../tester.hpp"

template <typename typeTest>
bool empty_basic() 
{
	std::vector<typeTest> v1;
	fd::vector<typeTest> v2;

	return equal(v1, v2);
}

template <typename typeTest>
bool filled_basic() 
{
	std::vector<typeTest> v1_1 (10);
	fd::vector<typeTest> v2_1 (10);

	std::vector<typeTest> v1_2 (10, Generator<int>(150660).get<typeTest>());
	fd::vector<typeTest> v2_2 (10, Generator<int>(150660).get<typeTest>());

	return equal(v1_1, v2_1) && equal(v1_2, v2_2);
}


/*** TEST 1 ***/
Test(vector_constructor, empty_basic_int)
{ cr_assert(empty_basic<int>(), "Vector differ on int....!"); }
Test(vector_constructor, empty_basic_float)
{ cr_assert(empty_basic<float>(), "Vector differ on float....!"); }
Test(vector_constructor, empty_basic_std_string)
{ cr_assert(empty_basic<std::string>(), "Vector differ on std::string....!"); }
Test(vector_constructor, empty_basic_char_ptr)
{ cr_assert(empty_basic<char *>(), "Vector differ on char *....!"); }
Test(vector_constructor, empty_basic_foo_int_ptr)
{ cr_assert(empty_basic<foo<int>* >(), "Vector differ on int....!"); }
Test(vector_constructor, empty_basic_long)
{ cr_assert(empty_basic<long>(), "Vector differ on bool....!"); }


/*** TEST 2 ***/
Test(vector_constructor, filled_basic_int)
{ cr_assert(empty_basic<int>(), "Vector differ on int....!"); }
Test(vector_constructor, filled_basic_float)
{ cr_assert(empty_basic<float>(), "Vector differ on float....!"); }
Test(vector_constructor, filled_basic_std_string)
{ cr_assert(empty_basic<std::string>(), "Vector differ on std::string....!"); }
Test(vector_constructor, filled_basic_char_ptr)
{ cr_assert(empty_basic<char *>(), "Vector differ on char *....!"); }
Test(vector_constructor, filled_basic_foo_int_ptr)
{ cr_assert(empty_basic<foo<int>* >(), "Vector differ on int....!"); }
Test(vector_constructor, filled_basic_long)
{ cr_assert(empty_basic<long>(), "Vector differ on bool....!"); }
