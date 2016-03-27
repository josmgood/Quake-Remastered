#pragma once

#include "..\..\common.h"

#define PI = 3.14159265358979323846

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

	inline int32 log2(int32 val)
	{
		int32 answer = 0;
		while (val >>= 1)
		{
			answer++;
		}
		return(answer);
	}

	inline int32 GCD(int32 one, int32 two)
	{
		if (one > two)
		{
			return((two == 0) ? one : GCD(two, one % two));
		}
		else
		{
			return((one == 0) ? two : GCD(one, two % one));
		}
	}

	inline float64 __declspec (naked) __fastcall sqrt(float64 n)
	{
		_asm fld qword ptr[esp + 4]
			_asm fsqrt
		_asm ret 8
	}
}