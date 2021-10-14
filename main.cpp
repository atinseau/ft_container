
#include "test/tester.hpp"



int main(void)
{
	std::vector<int>v1;
	fd::vector<int>v2;
	
	for(int i = 0; i < 5; i++)
	{
		v1.push_back(i);
		v2.push_back(i);
	}

	std::cout << *(v1.end() - 1) << std::endl;
	std::cout << *(v2.end() - 1) << std::endl;

	std::cout << std::endl;

	std::vector<int>::iterator res_it_1 = v1.erase(v1.end() - 1);
	fd::vector<int>::iterator res_it_2 = v2.erase(v2.end() - 1);

	std::cout << v1[4] << std::endl;
	std::cout << v2[3] << std::endl;


	return (0);
}