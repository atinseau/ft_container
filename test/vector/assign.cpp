#include "../tester.hpp"
#include <criterion/criterion.h>

template <typename typeTest>
bool empty_basic ()
{
	std::vector<typeTest> v1;
	fd::vector<typeTest> v2;

	bool fail_1 = false, fail_2 = false;

	try { v1.assign(-10, Generator<int>(145).get<typeTest>()); }
	catch (...) { fail_1 = true; }

	try { v2.assign(-10, Generator<int>(145).get<typeTest>()); }
	catch (...) { fail_2 = true; } 

	v1.assign(145, Generator<int>(145).get<typeTest>());
	v2.assign(145, Generator<int>(145).get<typeTest>());

	return equal(v1, v2) && fail_1 && fail_2;
}


template <typename typeTest>
bool not_empty_basic ()
{
	std::vector<typeTest> v1 (10);
	fd::vector<typeTest> v2 (10);

	for(int i = 0; i < 100; i++)
	{
		v1.push_back(Generator<int>(i).get<typeTest>());
		v2.push_back(Generator<int>(i).get<typeTest>());
	}
	
	v1.assign(145, Generator<int>(145).get<typeTest>());
	v2.assign(145, Generator<int>(145).get<typeTest>());

	return equal(v1, v2);
}

template <typename typeTest>
bool empty_with_iterator()
{
	std::vector<typeTest> db1;
	std::vector<typeTest> db2;

	for(int i = 0; i < 100; i++)
	{
		db1.push_back(Generator<int>(i).get<typeTest>());
		db2.push_back(Generator<int>(i).get<typeTest>());
	}
	std::vector<typeTest>	v1;
	fd::vector<typeTest>	v2;

	v1.assign(db1.begin(), db1.end() - 10);
	v2.assign(db2.begin(), db2.end() - 10);

	return equal(v1, v2);
}



template <typename typeTest>
bool not_empty_with_iterator()
{
	std::vector<typeTest> db1;
	std::vector<typeTest> db2;

	for(int i = 0; i < 100; i++)
	{
		db1.push_back(Generator<int>(i).get<typeTest>());
		db2.push_back(Generator<int>(i).get<typeTest>());
	}

	std::vector<typeTest>	v1 (140);
	fd::vector<typeTest>	v2 (140);

	v1.assign(db1.begin(), db1.end() - 10);
	v2.assign(db2.begin(), db2.end() - 10);

	return equal(v1, v2);
}


/*** TEST 1 ***/
Test(vector_assign, empty_basic_int)
{ cr_assert(empty_basic<int>(), "Vector differ on int....!"); }
Test(vector_assign, empty_basic_float)
{ cr_assert(empty_basic<float>(), "Vector differ on float....!"); }
Test(vector_assign, empty_basic_std_string)
{ cr_assert(empty_basic<std::string>(), "Vector differ on std::string....!"); }
Test(vector_assign, empty_basic_char_ptr)
{ cr_assert(empty_basic<char *>(), "Vector differ on char *....!"); }
Test(vector_assign, empty_basic_foo_int_ptr)
{ cr_assert(empty_basic<foo<int>* >(), "Vector differ on int....!"); }
Test(vector_assign, empty_basic_long)
{ cr_assert(empty_basic<long>(), "Vector differ on bool....!"); }


/*** TEST 2 ***/
Test(vector_assign, not_empty_basic_int)
{ cr_assert(not_empty_basic<int>(), "Vector differ on int....!"); }
Test(vector_assign, not_empty_basic_float)
{ cr_assert(not_empty_basic<float>(), "Vector differ on float....!"); }
Test(vector_assign, not_empty_basic_std_string)
{ cr_assert(not_empty_basic<std::string>(), "Vector differ on std::string....!"); }
Test(vector_assign, not_empty_basic_char_ptr)
{ cr_assert(not_empty_basic<char *>(), "Vector differ on char *....!"); }
Test(vector_assign, not_empty_basic_foo_int_ptr)
{ cr_assert(not_empty_basic<foo<int>* >(), "Vector differ on int....!"); }
Test(vector_assign, not_empty_basic_long)
{ cr_assert(not_empty_basic<long>(), "Vector differ on bool....!"); }

/*** TEST 3 ***/
Test(vector_assign, empty_with_iterator_int)
{ cr_assert(empty_with_iterator<int>(), "Vector differ on int....!"); }
Test(vector_assign, empty_with_iterator_float)
{ cr_assert(empty_with_iterator<float>(), "Vector differ on float....!"); }
Test(vector_assign, empty_with_iterator_std_string)
{ cr_assert(empty_with_iterator<std::string>(), "Vector differ on std::string....!"); }
Test(vector_assign, empty_with_iterator_char_ptr)
{ cr_assert(empty_with_iterator<char *>(), "Vector differ on char *....!"); }
Test(vector_assign, empty_with_iterator_foo_int_ptr)
{ cr_assert(empty_with_iterator<foo<int>* >(), "Vector differ on int....!"); }
Test(vector_assign, empty_with_iterator_long)
{ cr_assert(empty_with_iterator<long>(), "Vector differ on bool....!"); }
	
/*** TEST 4 ***/
Test(vector_assign, not_empty_with_iterator_int)
{ cr_assert(not_empty_with_iterator<int>(), "Vector differ on int....!"); }
Test(vector_assign, not_empty_with_iterator_float)
{ cr_assert(not_empty_with_iterator<float>(), "Vector differ on float....!"); }
Test(vector_assign, not_empty_with_iterator_std_string)
{ cr_assert(not_empty_with_iterator<std::string>(), "Vector differ on std::string....!"); }
Test(vector_assign, not_empty_with_iterator_char_ptr)
{ cr_assert(not_empty_with_iterator<char *>(), "Vector differ on char *....!"); }
Test(vector_assign, not_empty_with_iterator_foo_int_ptr)
{ cr_assert(not_empty_with_iterator<foo<int>* >(), "Vector differ on int....!"); }
Test(vector_assign, not_empty_with_iterator_long)
{ cr_assert(not_empty_with_iterator<long>(), "Vector differ on bool....!"); }
