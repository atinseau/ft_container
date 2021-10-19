#include "../tester.hpp"
#include <criterion/criterion.h>

template <typename typeTest>
bool handle_not_found_pointer()
{
	ft::vector<typeTest> v1;

	typename ft::vector<typeTest>::size_type prev;

	for(int i = 0; i < 100; i++)
		v1.push_back(Generator<int>(i).get<typeTest>());

	prev = v1.size();
	v1.erase(v1.begin() - 1);
	if(prev != v1.size())
	{
		std::cout << "is warning..." << std::endl;
		return false;
	}
	prev = v1.size();
	v1.erase(v1.begin() - (v1.size() + 100));
	if(prev != v1.size())
	{
		std::cout << "is warning..." << std::endl;
		return false;
	}
	prev = v1.size();
	v1.erase(v1.begin() - (v1.size()));
	if(prev != v1.size())
	{
		std::cout << "is warning..." << std::endl;
		return false;
	}

	return (true);
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
