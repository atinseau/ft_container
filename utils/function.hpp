#ifndef __FUNCTION_H__
#define __FUNCTION_H__

namespace fd
{
	template <typename T>
	bool range_address(T* array, long size, const T* search)
	{
		if (!array || !search)
			return (false);
		if (search - array <= size && search - array >= 0)
			return (true);
		return (false);
	}
};

#endif // __FUNCTION_H__