#pragma once

typedef int	PtrDiff;

template<typename PtrOne, typename PtrTwo>
PtrDiff ptrDistance(PtrOne one, PtrTwo two)
{
	return(one - two);
}