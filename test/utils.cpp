#include "tester.hpp"

double mesure(int (*f)(void))
{
	struct timeval now;
	struct timeval after;
	gettimeofday(&now, NULL);
	f();
	gettimeofday(&after, NULL);
	return (((after.tv_sec * 1000) + (after.tv_usec / 1000)) - ((now.tv_sec * 1000) + (now.tv_usec / 1000)));
}
