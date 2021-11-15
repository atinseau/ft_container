#ifndef __STL_H__
#define __STL_H__

namespace ft 
{
	/*
	** enable_if comportement usefully for choose right function template during 
	** the compilation, it take a "boolean response template" like is_integral or is_same
	** return typdef with the wanted type
	*/
	template<bool B>
	struct enable_if {};	
	template<>
	struct enable_if<true> { typedef int type; };


	/*
	** boolean response template can used with enable_if or any logical condition
	** during the execution for describe a comportement depending on the template type
	** who is passed 
	*/
	template<class T, class U>
	struct is_same { static const bool value = false; };
	template<class T>
	struct is_same<T, T> { static const bool value = true; };
	
	template <bool isConst, typename isFalse, typename isTrue>
	struct is_const {};
	template <typename isFalse, typename isTrue>
	struct is_const<false, isFalse, isTrue> { typedef isFalse type; };
	template <typename isFalse, typename isTrue>
	struct is_const<true, isFalse, isTrue> { typedef isTrue type; };

	template<typename T>
	struct is_pointer { static const bool value = false; };
	template<typename T>
	struct is_pointer<T*> { static const bool value = true; };
	template<typename T>
	struct is_pointer<const T> { static const bool value = false; };
	template<typename T>
	struct is_pointer<const T*> { static const bool value = true; };


	/*
	**
	** is integral determine if the template type is regular type like
	** int, long, short, unsigned char etc....
	** if isn't , static value in struct initlized to false are accesible and can be used to 
	** enable_if a specific template
	*/
	template <typename T>
	struct is_integral { static const bool value = false; };
	template <>
	struct is_integral<bool> { static const bool value = true; };
	template <>
	struct is_integral<char> { static const bool value = true; };
	template <>
	struct is_integral<float> { static const bool value = true; };
	template <>
	struct is_integral<short> { static const bool value = true; };
	template <>
	struct is_integral<int> { static const bool value = true; };
	template <>
	struct is_integral<long> { static const bool value = true; };
	template <>
	struct is_integral<long long> { static const bool value = true; };
	template <>
	struct is_integral<unsigned char> { static const bool value = true; };
	template <>
	struct is_integral<unsigned short> { static const bool value = true; };
	template <>
	struct is_integral<unsigned int> { static const bool value = true; };
	template <>
	struct is_integral<unsigned long> { static const bool value = true; };
	template <>
	struct is_integral<unsigned long long> { static const bool value = true; };

	template <class Arg1, class Arg2, class Result>
	struct binary_function
	{
		/* The first argument type */
		typedef Arg1 first_argument_type;

		/* The second arguement type */
		typedef Arg2 second_argument_type;

		/* The result type */
		typedef Result result_type;
	};

	template <class T>
	struct less : binary_function<T, T, bool>
	{
		bool operator() (const T& x, const T& y) const { return (x < y); }
	};

	

}

#endif // __STL_H__