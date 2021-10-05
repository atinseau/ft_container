#ifndef __TESTER_H__
#define __TESTER_H__

# define C11 1

#include <iostream>
#include <sys/time.h>
#include <vector>
#include <iostream>
#include <criterion/criterion.h>
#include "../Vector.hpp"



double mesure(int (*f)(void));

#endif // __TESTER_H__