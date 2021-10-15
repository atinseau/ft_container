#include "../tester.hpp"
#include <criterion/criterion.h>

template <typename typeTest>
bool handle_not_found_pointer()
{
	fd::vector<typeTest> v1;

	typename fd::vector<typeTest>::size_type prev;

	for(int i = 0; i < 100; i++)
		v1.push_back(Generator<int>(i).get<typeTest>());

	prev = v1.size();
	v1.erase(v1.begin() - 1);
	if(prev != v1.size())
		return false;

	prev = v1.size();
	v1.erase(v1.begin() - (v1.size() + 100));
	if(prev != v1.size())
		return false;

	prev = v1.size();
	v1.erase(v1.begin() - (v1.size()));
	if(prev != v1.size())
		return false;

	return (true);
}

template <typename typeTest>
bool complex_basic()
{
	std::vector<typeTest> v1;
	fd::vector<typeTest> v2;

	bool diff_1 = false, diff_2 = false;

	for (int i = 0; i < 100; i++)
	{
		v1.push_back(Generator<int>(i).get<typeTest>());
		v2.push_back(Generator<int>(i).get<typeTest>());
	}

	v1.erase(v1.begin() + (v1.size() / 2));
	v2.erase(v2.begin() + (v2.size() / 2));

	diff_1 = equal(v1, v2);

	while(v1.size() > 0)
		v1.erase(v1.end() - 1);
	while(v2.size() > 0)
		v2.erase(v2.end() - 1);

	diff_2 = equal(v1, v2);

	return diff_1 && diff_2;
}

template <typename typeTest>
bool complexe_range_basic()
{
	
}


/*** TEST 1 ***/
Test(vector_erase, handle_not_found_pointer_int)
{ cr_assert(handle_not_found_pointer<int>(), "Vector differ on int....!"); }
Test(vector_erase, handle_not_found_pointer_float)
{ cr_assert(handle_not_found_pointer<float>(), "Vector differ on float....!"); }
Test(vector_erase, handle_not_found_pointer_string)
{ cr_assert(handle_not_found_pointer<std::string>(), "Vector differ on std::string....!"); }
Test(vector_erase, handle_not_found_pointer_char_ptr)
{ cr_assert(handle_not_found_pointer<char *>(), "Vector differ on char *....!"); }
Test(vector_erase, handle_not_found_pointer_foo_int_ptr)
{ cr_assert(handle_not_found_pointer<foo<int>* >(), "Vector differ on int....!"); }
Test(vector_erase, handle_not_found_pointer_long)
{ cr_assert(handle_not_found_pointer<long>(), "Vector differ on bool....!"); }


/*** TEST 2 ***/
Test(vector_erase, complex_basic_int)
{ cr_assert(complex_basic<int>(), "Vector differ on int....!"); }
Test(vector_erase, complex_basic_float)
{ cr_assert(complex_basic<float>(), "Vector differ on float....!"); }
Test(vector_erase, complex_basic_std_string)
{ cr_assert(complex_basic<std::string>(), "Vector differ on std::string....!"); }
Test(vector_erase, complex_basic_char_ptr)
{ cr_assert(complex_basic<char *>(), "Vector differ on char *....!"); }
Test(vector_erase, complex_basic_foo_int_ptr)
{ cr_assert(complex_basic<foo<int>* >(), "Vector differ on int....!"); }
Test(vector_erase, complex_basic_long)
{ cr_assert(complex_basic<long>(), "Vector differ on bool....!"); }

