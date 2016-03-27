#pragma once

#include "math.h"

namespace math
{
	template<typename TIntegral>
	class Vector4
	{
	public:
		Vector4();
		Vector4(TIntegral _x, TIntegral _y, TIntegral _z, TIntegral _w);
		Vector4(const Vector4& vector);
		Vector4(Vector4&& vector);

		static TIntegral dot(const Vector4& one, const Vector4& two);
		static Vector4 mScale(const Vector4& vector, TIntegral scalar);
		static Vector4 dScale(const Vector4& vector, TIntegral scalar);
		static Vector4 multiply(const Vector4& vector, const Vector4& multiplier);
		static Vector4 divide(const Vector4& vector, const Vector4& divisor);
		static Vector4 add(const Vector4& vector, const Vector4& addend);
		static Vector4 subtract(const Vector4& vector, const Vector4& subtrahend);
		static void set(Vector4& vector, TIntegral x, TIntegral y, TIntegral z, TIntegral w);
		static void setX(Vector4& vector, TIntegral x);
		static void setY(Vector4& vector, TIntegral y);
		static void setZ(Vector4& vector, TIntegral z);
		static void setW(Vector4& vector, TIntegral w);
		static TIntegral addX(const Vector4& vector, TIntegral addend);
		static TIntegral subtractX(const Vector4& vector, TIntegral subtrahend);
		static TIntegral addY(const Vector4& vector, TIntegral addend);
		static TIntegral subtractY(const Vector4& vector, TIntegral subtrahend);
		static TIntegral addZ(const Vector4& vector, TIntegral addend);
		static TIntegral subtractZ(const Vector4& vector, TIntegral subtrahend);
		static TIntegral addW(const Vector4& vector, TIntegral addend);
		static TIntegral subtractW(const Vector4& vector, TIntegral subtrahend);

		TIntegral dot(const Vector4& vector);
		void mScale(TIntegral scalar);
		void dScale(TIntegral scalar);
		void multiply(const Vector4& multiplier);
		void divide(const Vector4& divisor);
		void add(const Vector4& addend);
		void subtract(const Vector4& subtrahend);
		void set(TIntegral x, TIntegral y, TIntegral z, TIntegral w);
		void setX(TIntegral x);
		void setY(TIntegral y);
		void setZ(TIntegral z);
		void setW(TIntegral w);
		void addX(TIntegral addend);
		void subtractX(TIntegral subtrahend);
		void addY(TIntegral addend);
		void subtractY(TIntegral subtrahend);
		void addZ(TIntegral addend);
		void subtractZ(TIntegral subtrahend);
		void addW(TIntegral addend);
		void subtractW(TIntegral subtrahend);

		void invert();
		void normalize();
		float32 length();

		bool equals(const Vector4& other);
		
		TIntegral operator[](size_t index) const;

		TIntegral operator^(const Vector4& other);
		
		Vector4 operator*(TIntegral scalar);
		Vector4 operator*(const Vector4& multiplier);
		Vector4 operator/(TIntegral scalar);
		Vector4 operator/(const Vector4& divisor);
		Vector4 operator+(const Vector4& addend);
		Vector4 operator-(const Vector4& subtrahend);

		void operator*=(TIntegral scalar);
		void operator*=(const Vector4& multiplier);
		void operator/=(TIntegral scalar);
		void operator/=(const Vector4& divisor);
		void operator+=(const Vector4& addend);
		void operator-=(const Vector4& subtrahend);

		bool operator<(const Vector4& other);
		bool operator<=(const Vector4& other);

		bool operator>(const Vector4& other);
		bool operator>=(const Vector4& other);

		bool operator==(const Vector4& other);
		bool operator!=(const Vector4& other);

		TIntegral x;
		TIntegral y;
		TIntegral z;
		TIntegral w;
	};

	typedef Vector4<int32>		Vector4i;
	typedef Vector4<int64>		Vector4l;
	typedef Vector4<uint32>		Vector4ui;
	typedef Vector4<uint64>		Vector4ul;
	typedef Vector4<float32>	Vector4f;
	typedef Vector4<float64>	Vector4d;
}

#include "..\Source\vector4.inl"