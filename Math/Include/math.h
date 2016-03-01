#pragma once

#include "..\..\Core\common.h"

namespace math
{
	inline float64 abs(float64 x)
	{
		return((x < 0) ? -x : x);
	}

	inline float64 pow(float64 x, int32 p)
	{
		float64 n = x;
		for (int32 i = 1; i < math::abs(p); i++)
		{
			n *= x;
		}
		return(n);
	}

	inline float64 squared(float64 x)
	{
		return(x * x);
	}

	inline float64 __declspec (naked) __fastcall sqrt(float64 n)
	{
		_asm fld qword ptr[esp + 4]
			_asm fsqrt
		_asm ret 8
	}
}