#pragma once

namespace math
{
	template<typename Type>
	Type abs(Type x)
	{
		return((x < 0) ? -x : x);
	}

	double inline __declspec (naked) __fastcall sqrt(double n)
	{
		_asm fld qword ptr[esp + 4]
			_asm fsqrt
		_asm ret 8
	}
}