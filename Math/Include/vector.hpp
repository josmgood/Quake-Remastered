#pragma once

#include "math.h"

namespace math
{
	class Vector2
	{
	public:
		inline Vector2();
		inline Vector2(float32 x, float32 y);
		inline Vector2(const Vector2& vec);

		inline void operator+(const Vector2& vec);
		inline void operator-(const Vector2& vec);
		inline void operator==(const Vector2& vec);
		inline void operator!=(const Vector2& vec);

		inline bool equals(const Vector2& other);

	private:
		float32 _x;
		float32 _y;
	};
}