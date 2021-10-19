
#include "test/tester.hpp"

#define TESTED_TYPE foo<int>
#define TESTED_NAMESPACE ft


void	is_empty(TESTED_NAMESPACE::vector<TESTED_TYPE> const &vct)
{
	std::cout << "is_empty: " << vct.empty() << std::endl;
}

int		main(void)
{
	const int start_size = 7;
	TESTED_NAMESPACE::vector<TESTED_TYPE> vct(start_size, 20);
	TESTED_NAMESPACE::vector<TESTED_TYPE> vct2;
	TESTED_NAMESPACE::vector<TESTED_TYPE>::iterator it = vct.begin();

	for (int i = 2; i < start_size; ++i)
		it[i] = (start_size - i) * 3;
	vprint(vct);

	vct.resize(10, 42);
	vprint(vct);

	vct.resize(18, 43);
	vprint(vct);
	vct.resize(10);
	vprint(vct);
	vct.resize(23, 44);
	vprint(vct);
	vct.resize(5);
	vprint(vct);
	vct.reserve(5);
	vct.reserve(3);
	vprint(vct);
	vct.resize(87);
	vct.resize(5);
	vprint(vct);

	is_empty(vct2);
	vct2 = vct;
	is_empty(vct2);
	vct.reserve(vct.capacity() + 1);
	vprint(vct);
	vprint(vct2);

	vct2.resize(0);
	is_empty(vct2);
	vprint(vct2);
	return (0);
}
