#pragma once

#include "math.h"

namespace math
{
	template<typename TIntegral>
	class Vector2
	{
	public:
		Vector2();
		Vector2(TIntegral _x, TIntegral _y);
		Vector2(const Vector2& vector);
		Vector2(Vector2&& vector);

		static TIntegral dot(const Vector2& one, const Vector2& two);
		static Vector2 mScale(const Vector2& vector, TIntegral scalar);
		static Vector2 dScale(const Vector2& vector, TIntegral scalar);
		static Vector2 multiply(const Vector2& vector, const Vector2& multiplier);
		static Vector2 divide(const Vector2& vector, const Vector2& divisor);
		static Vector2 add(const Vector2& vector, const Vector2& addend);
		static Vector2 subtract(const Vector2& vector, const Vector2& subtrahend);
		static void set(Vector2& vector, TIntegral x, TIntegral y);
		static void setX(Vector2& vector, TIntegral x);
		static void setY(Vector2& vector, TIntegral y);
		static TIntegral addX(const Vector2& vector, TIntegral addend);
		static TIntegral subtractX(const Vector2& vector, TIntegral subtrahend);
		static TIntegral addY(const Vector2& vector, TIntegral addend);
		static TIntegral subtractY(const Vector2& vector, TIntegral subtrahend);

		TIntegral dot(const Vector2& vector);
		void mScale(TIntegral scalar);
		void dScale(TIntegral scalar);
		void multiply(const Vector2& multiplier);
		void divide(const Vector2& divisor);
		void add(const Vector2& addend);
		void subtract(const Vector2& subtrahend);
		void set(TIntegral x, TIntegral y);
		void setX(TIntegral x);
		void setY(TIntegral y);
		void addX(TIntegral addend);
		void subtractX(TIntegral subtrahend);
		void addY(TIntegral addend);
		void subtractY(TIntegral subtrahend);

		void invert();
		void normalize();
		float32 length();

		bool equals(const Vector2& other);

		TIntegral operator[](size_t index) const;

		TIntegral operator^(const Vector2& vector);

		Vector2 operator*(TIntegral scalar);
		Vector2 operator*(const Vector2& multiplier);
		Vector2 operator/(TIntegral scalar);
		Vector2 operator/(const Vector2& divisor);
		Vector2 operator+(const Vector2& addend);
		Vector2 operator-(const Vector2& subtrahend);

		void operator*=(TIntegral scalar);
		void operator*=(const Vector2& multiplier);
		void operator/=(TIntegral scalar);
		void operator/=(const Vector2& divisor);
		void operator+=(const Vector2& addend);
		void operator-=(const Vector2& subtrahend);

		bool operator<(const Vector2& other);
		bool operator<=(const Vector2& other);

		bool operator>(const Vector2& other);
		bool operator>=(const Vector2& other);

		bool operator==(const Vector2& other);
		bool operator!=(const Vector2& other);

		TIntegral x;
		TIntegral y;
	};

	typedef Vector2<int32>		Vector2i;
	typedef Vector2<int64>		Vector2l;
	typedef Vector2<uint32>		Vector2ui;
	typedef Vector2<uint64>		Vector2ul;
	typedef Vector2<float32>	Vector2f;
	typedef Vector2<float64>	Vector2d;
}

#include "..\Source\vector2.inl"