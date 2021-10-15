
#include "test/tester.hpp"

typedef std::string typeTest;

int main(void)
{
	std::vector<typeTest> v1;
	fd::vector<typeTest> v2;

	v1.erase(v1.begin());
	v2.erase(v2.begin());

	return (0);
}