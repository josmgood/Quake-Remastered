#pragma once

#include "math.h"

namespace math
{
	template<typename TIntegral>
	class Vector3
	{
	public:
		Vector3();
		Vector3(TIntegral _x, TIntegral _y, TIntegral _z);
		Vector3(const Vector3& vector);
		Vector3(Vector3&& vector);

		static TIntegral dot(const Vector3& one, const Vector3& two);
		static Vector3 cross(const Vector3& one, const Vector3& two);
		static Vector3 mScale(const Vector3& vector, TIntegral scalar);
		static Vector3 dScale(const Vector3& vector, TIntegral scalar);
		static Vector3 multiply(const Vector3& vector, const Vector3& multiplier);
		static Vector3 divide(const Vector3& vector, const Vector3& divisor);
		static void set(Vector3& vector, TIntegral x, TIntegral y, TIntegral z);
		static void setX(Vector3& vector, TIntegral x);
		static void setY(Vector3& vector, TIntegral y);
		static void setZ(Vector3& vector, TIntegral z);
		static TIntegral addX(const Vector3& vector, TIntegral addend);
		static TIntegral subtractX(const Vector3& vector, TIntegral subtrahend);
		static TIntegral addY(const Vector3& vector, TIntegral addend);
		static TIntegral subtractY(const Vector3& vector, TIntegral subtrahend);
		static TIntegral addZ(const Vector3& vector, TIntegral addend);
		static TIntegral subtractZ(const Vector3& vector, TIntegral subtrahend);

		TIntegral dot(const Vector3& vector);
		Vector3 cross(const Vector3& vector);
		void mScale(TIntegral scalar);
		void dScale(TIntegral scalar);
		void multiply(const Vector3& multiplier);
		void divide(const Vector3& divisor);
		void add(const Vector3& addend);
		void subtract(const Vector3& subtrahend);
		void set(TIntegral x, TIntegral y, TIntegral z);
		void setX(TIntegral _x);
		void setY(TIntegral _y);
		void setZ(TIntegral _z);
		void addX(TIntegral addend);
		void subtractX(TIntegral subtrahend);
		void addY(TIntegral addend);
		void subtractY(TIntegral subtrahend);
		void addZ(TIntegral addend);
		void subtractZ(TIntegral subtrahend);

		void invert();
		void normalize();
		float32 length();

		bool equals(const Vector3& other);
		TIntegral operator[](size_t index) const;

		TIntegral operator^(const Vector3& other);
		Vector3 operator|(const Vector3& other);

		Vector3 operator*(TIntegral scalar);
		Vector3 operator*(const Vector3& multiplier);
		Vector3 operator/(TIntegral scalar);
		Vector3 operator/(const Vector3& divisor);
		Vector3 operator+(const Vector3& addend);
		Vector3 operator-(const Vector3& subtrahend);

		void operator*=(TIntegral scalar);
		void operator*=(const Vector3& multiplier);
		void operator/=(TIntegral scalar);
		void operator/=(const Vector3& divisor);
		void operator+=(const Vector3& addend);
		void operator-=(const Vector3& subtrahend);

		bool operator<(const Vector3& other);
		bool operator<=(const Vector3& other);

		bool operator>(const Vector3& other);
		bool operator>=(const Vector3& other);

		bool operator==(const Vector3& other);
		bool operator!=(const Vector3& other);

		TIntegral x;
		TIntegral y;
		TIntegral z;
	};

	typedef Vector3<int32>		Vector3i;
	typedef Vector3<int64>		Vector3l;
	typedef Vector3<uint32>		Vector3ui;
	typedef Vector3<uint64>		Vector3ul;
	typedef Vector3<float32>	Vector3f;
	typedef Vector3<float64>	Vector3d;
}

#include "..\Source\vector3.inl"