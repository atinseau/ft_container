#ifndef __TESTER_H__
#define __TESTER_H__

#include <iostream>
#include <sys/time.h>
#include <vector>
#include <sstream>
#include <iostream>
#include "../Vector.hpp"
#define MAX_SIZE 100000000

double mesure(int (*f)(void));

template < typename T >
struct foo
{
	std::string str;
	foo (void): str("salut tout le monde"), _dynamic(T()) {}
	foo (T dyn): str("salut tout le monde"), _dynamic(dyn) {}
	~foo(void) {}

	T getDynamic(void) const { return _dynamic; }

	bool operator!=(const foo &rhs) const
	{
		if (str == rhs.str && _dynamic == _dynamic)
			return (false);
		return (true);
	}

	private:
		T _dynamic;
};

template < typename T >
std::ostream & operator<<(std::ostream &o , const foo<T> & rhs)
{
	o << rhs.str << ", " << rhs.getDynamic();
	return o;
}

template < typename T >
std::string to_string(const T& n)
{
	std::ostringstream stm ;
	stm << n ;
	return stm.str();
}

template < typename T >
char * to_str(const T& n)
{
	std::allocator<char> alloc;
	std::string tmp = to_string(n);
	char *str = alloc.allocate(tmp.length() + 1);
	for(size_t i = 0; i < tmp.length(); i++)
		str[i] = tmp[i];
	str[tmp.length()] = '\0';

	return (str);
}

template <typename Va, typename Vb>
bool compare(Va &v1, Vb &v2, 
		typename fd::enable_if<fd::is_same<typename Va::value_type, typename Vb::value_type>::value>::type* = 0,
		typename fd::enable_if<fd::is_pointer<typename Va::value_type>::value>::type* = 0
	) 
{
	if (v1.size() != v2.size())
		return false;
	for (size_t i = 0; i < v1.size(); i++)
	{
		if (!v1[i] && !v2[i])
			return (true);

		if (*v1[i] != *v2[i])
			return false;
	}
	return true;
}


template <typename Va, typename Vb>
bool compare(Va &v1, Vb &v2,
		typename fd::enable_if<fd::is_same<typename Va::value_type, typename Vb::value_type>::value>::type* = 0,
		typename fd::enable_if<!fd::is_pointer<typename Va::value_type>::value>::type* = 0
	) 
{
	if (v1.size() != v2.size())
		return false;
	for (size_t i = 0; i < v1.size(); i++)
	{
		if (v1[i] != v2[i])
			return false;
	}
	return true;
}

template <typename Va, typename Vb>
bool equal(Va &v1, Vb &v2)
{
	bool success = true;
	if (v1.empty() != v2.empty())
	{
		std::cerr << "Your vector is empty at start..." << std::endl;
		success = false;
	}
	if(v1.size() != v2.size())
	{
		std::cerr << "Your vector has not the good size..." << std::endl;
		success = false;
	}
	if(v1.capacity() != v2.capacity())
	{
		std::cerr << "Your vector has not the good capacity..." << std::endl;
		success = false;
	}
	if (!compare(v1, v2))
	{
		std::cerr << "Your vector is not the same with the real vector..." << std::endl;
		success = false;
	}
	return (success);
}


template <typename T>
void vdebug(T & v)
{
	std::cout << "Empty: " << (v.empty() ? "True" : "False") << std::endl;
	std::cout << "Size: " << v.size() << std::endl;
	std::cout << "Capacity: " << v.capacity() << std::endl;
}


template <typename T>
void vprint(T & v, typename fd::enable_if<fd::is_pointer<typename T::value_type>::value >::type* = 0)
{
	for(typename T::iterator it = v.begin(); it != v.end(); it++)
	{
		typename T::value_type tmp = *it;
		if (tmp)
			std::cout << *tmp << std::endl;
		else
			std::cout << "(null)" << std::endl;
	}
}

template <typename T>
void vprint(T & v, typename fd::enable_if<!fd::is_pointer<typename T::value_type>::value >::type* = 0)
{
	for(typename T::iterator it = v.begin(); it != v.end(); it++)
	{
		std::cout << *it << std::endl;
	}
}


// VALUE GENERATOR

template <typename InputType>
class Generator
{
	private:
		InputType _input;
	
	public:
		Generator(InputType V): _input(V) {}
		Generator(void): _input(InputType()) {}

		template <typename T>
		T get (typename fd::enable_if<fd::is_same<InputType, int>::value && fd::is_same<T, std::string>::value >::type = 0)
		{
			return (to_string(_input) + " voici un vrai valeur...");
		}

		template <typename T>
		T get (typename fd::enable_if<fd::is_same<InputType, int>::value && fd::is_same<T, char *>::value >::type = 0)
		{
			return (to_str(_input));
		}

		template <typename T>
		T get (typename fd::enable_if<fd::is_same<InputType, int>::value && fd::is_same<T, foo<int> *>::value >::type = 0)
		{
			return (new foo<int>(_input));
		}


		template <typename T>
		T get (typename fd::enable_if<fd::is_integral<T>::value && fd::is_same<InputType, int>::value >::type = 0)
		{
			return (static_cast<T>(_input));
		}
};



#endif // __TESTER_H__