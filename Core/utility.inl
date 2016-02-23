#include "utility.h"

template<typename t_integral>
t_integral alignTo(t_integral value, size_t alignment)
{
	return(static_cast<t_integral>((static_cast<size_t>(value) + (alignment - 1)) & ~(alignment - 1)));
}

template<typename t_ptr>
t_ptr* alignTo(t_ptr* value, size_t alignment)
{
	return(reinterpret_cast<t_ptr*>(alignTo(reinterpret_cast<uintptr32>(value), alignment)));
}

template<typename t_integral>
bool isAlignedTo(t_integral value, size_t alignment)
{
	return(!(value & (alignment - 1)));
}

template<typename t_ptr>
bool isAlignedTo(t_ptr* value, size_t alignment)
{
	return(!(reinterpret_cast<uintptr32>(value) & (alignment - 1)));
}

bool isPowerOfTwo(size_t value)
{
	return(value != 0 && (value & (value - 1)) == 0);
}

template<typename T1, typename T2>
bool areSameType(void)
{

}