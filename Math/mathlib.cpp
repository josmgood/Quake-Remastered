#include "mathlib.h"

bool isPowerOfTwo(size_t value)
{
	return(value && (value & (value - 1)) == 0);
}