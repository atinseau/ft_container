
#include <memory>
#include <iostream>

int main(void)
{

	std::allocator<int> alloc;

	std::vector<int, std::allocator<std::string> > i;

	

	int *a = alloc.allocate(0);

	alloc.construct(a, 10);

	a[1] = 12;

	std::cout << a[1] << std::endl;

	return (0);
}