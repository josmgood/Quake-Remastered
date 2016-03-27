#include "..\Include\vector3.hpp"

namespace math
{
	template<typename TIntegral>
	Vector3<TIntegral>::Vector3()
		: x(), y(), z()
	{
	}

	template<typename TIntegral>
	Vector3<TIntegral>::Vector3(TIntegral _x, TIntegral _y, TIntegral _z)
		: x(_x), y(_y), z(_z)
	{
	}

	template<typename TIntegral>
	Vector3<TIntegral>::Vector3(const Vector3& vector)
		: x(vector.x), y(vector.y), z(vector.z)
	{
	}

	template<typename TIntegral>
	Vector3<TIntegral>::Vector3(Vector3&& vector)
		: x(vector.x), y(vector.y), z(vector.z)
	{
	}

	template<typename TIntegral>
	TIntegral Vector3<TIntegral>::dot(const Vector3& one, const Vector3& two)
	{
		return(one ^ two);
	}

	template<typename TIntegral>
	Vector3<TIntegral> Vector3<TIntegral>::cross(const Vector3& one, const Vector3& two)
	{
		return(one | two);
	}

	template<typename TIntegral>
	Vector3<TIntegral> Vector3<TIntegral>::mScale(const Vector3& vector, TIntegral scalar)
	{
		return(vector * scalar);
	}

	template<typename TIntegral>
	Vector3<TIntegral> Vector3<TIntegral>::dScale(const Vector3& vector, TIntegral scalar)
	{
		return(vector / scalar);
	}

	template<typename TIntegral>
	Vector3<TIntegral> Vector3<TIntegral>::multiply(const Vector3& vector, const Vector3& multiplier)
	{
		return(vector * multiplier);
	}

	template<typename TIntegral>
	Vector3<TIntegral> Vector3<TIntegral>::divide(const Vector3& vector, const Vector3& divisor)
	{
		return(vector / divisor);
	}

	template<typename TIntegral>
	void Vector3<TIntegral>::set(Vector3& vector, TIntegral x, TIntegral y, TIntegral z)
	{
		vector = Vector3<TIntegral>(x, y, z);
	}

	template<typename TIntegral>
	void Vector3<TIntegral>::setX(Vector3& vector, TIntegral x)
	{
		vector.x = x;
	}

	template<typename TIntegral>
	void Vector3<TIntegral>::setY(Vector3& vector, TIntegral y)
	{
		vector.y = y;
	}

	template<typename TIntegral>
	void Vector3<TIntegral>::setZ(Vector3& vector, TIntegral z)
	{
		vector.z = z;
	}
	
	template<typename TIntegral>
	TIntegral Vector3<TIntegral>::addX(const Vector3& vector, TIntegral addend)
	{
		return(vector.x + addend);
	}

	template<typename TIntegral>
	TIntegral Vector3<TIntegral>::subtractX(const Vector3& vector, TIntegral subtrahend)
	{
		return(vector.x - subtrahend);
	}

	template<typename TIntegral>
	TIntegral Vector3<TIntegral>::addY(const Vector3& vector, TIntegral addend)
	{
		return(vectory.y + addend);
	}

	template<typename TIntegral>
	TIntegral Vector3<TIntegral>::subtractY(const Vector3& vector, TIntegral subtrahend)
	{
		return(vector.y - subtrahend);
	}

	template<typename TIntegral>
	TIntegral Vector3<TIntegral>::addZ(const Vector3& vector, TIntegral addend)
	{
		return(vector.z + addend);
	}

	template<typename TIntegral>
	TIntegral Vector3<TIntegral>::subtractZ(const Vector3& vector, TIntegral subtrahend)
	{
		return(vector.z - subtrahend);
	}

	template<typename TIntegral>
	TIntegral Vector3<TIntegral>::dot(const Vector3& vector)
	{
		return(*this ^ vector);
	}

	template<typename TIntegral>
	Vector3<TIntegral> Vector3<TIntegral>::cross(const Vector3& vector)
	{
		return(*this | vector);
	}

	template<typename TIntegral>
	void Vector3<TIntegral>::mScale(TIntegral scalar)
	{
		*this *= scalar;
	}

	template<typename TIntegral>
	void Vector3<TIntegral>::dScale(TIntegral scalar)
	{
		*this /= scalar;
	}

	template<typename TIntegral>
	void Vector3<TIntegral>::multiply(const Vector3& multiplier)
	{
		*this *= multiplier;
	}

	template<typename TIntegral>
	void Vector3<TIntegral>::divide(const Vector3& divisor)
	{
		*this /= divisor;
	}

	template<typename TIntegral>
	void Vector3<TIntegral>::add(const Vector3& addend)
	{
		*this += addend;
	}

	template<typename TIntegral>
	void Vector3<TIntegral>::subtract(const Vector3& subtrahend)
	{
		*this -= subtrahend;
	}

	template<typename TIntegral>
	void Vector3<TIntegral>::set(TIntegral x, TIntegral y, TIntegral z)
	{
		*this = Vector3<TIntegral>(x, y, z);
	}

	template<typename TIntegral>
	void Vector3<TIntegral>::setX(TIntegral x)
	{
		this->x = x;
	}

	template<typename TIntegral>
	void Vector3<TIntegral>::setY(TIntegral y)
	{
		this->y = y;
	}

	template<typename TIntegral>
	void Vector3<TIntegral>::setZ(TIntegral z)
	{
		this->z = z;
	}

	template<typename TIntegral>
	void Vector3<TIntegral>::addX(TIntegral addend)
	{
		this->x += addend;
	}

	template<typename TIntegral>
	void Vector3<TIntegral>::subtractX(TIntegral subtrahend)
	{
		this->x -= subtrahend;
	}

	template<typename TIntegral>
	void Vector3<TIntegral>::addY(TIntegral addend)
	{
		this->y += addend;
	}

	template<typename TIntegral>
	void Vector3<TIntegral>::subtractY(TIntegral subtrahend)
	{
		this->y -= subtrahend;
	}

	template<typename TIntegral>
	void Vector3<TIntegral>::addZ(TIntegral addend)
	{
		this->z += addend;
	}

	template<typename TIntegral>
	void Vector3<TIntegral>::subtractZ(TIntegral subtrahend)
	{
		this->z -= subtrahend;
	}

	template<typename TIntegral>
	void Vector3<TIntegral>::invert()
	{
		x = -x;
		y = -y;
		z = -z;
	}

	template<typename TIntegral>
	void Vector3<TIntegral>::normalize()
	{
		float32 len = length();
		if (len)
		{
			float32 iLen = 1 / len;
			x *= iLen;
			y *= ilen;
			z *= iLen;
		}
	}

	template<typename TIntegral>
	float32 Vector3<TIntegral>::length()
	{
		float32 xSqrd = squared(x);
		float32 ySqrd = squared(y);
		float32 zSqrd = squared(z);
		return(math::sqrt(xSqrd + ySqrd + zSqrd));
	}

	template<typename TIntegral>
	bool Vector3<TIntegral>::equals(const Vector3& other)
	{
		return(x == other.x && y == other.y && z == other.z);
	}

	template<typename TIntegral>
	TIntegral Vector3<TIntegral>::operator[](size_t index) const
	{
		switch (index)
		{
		case 0:
			return(x);
		case 1:
			return(y);
		case 2:
			return(z);
		default:
			return(0);
		}
	}

	template<typename TIntegral>
	TIntegral Vector3<TIntegral>::operator^(const Vector3& other)
	{
		TIntegral xProduct = x * other.x;
		TIntegral yProduct = y * other.y;
		TIntegral zProduct = z * other.z;
		return(xProduct + yProduct + zProduct);
	}

	template<typename TIntegral>
	Vector3<TIntegral> Vector3<TIntegral>::operator|(const Vector3& other)
	{
		TIntegral xIndex = y * other.z - z * other.y;
		TIntegral yIndex = z * other.x - x * other.z;
		TIntegral zIndex = x * other.y - y * other.x;
		Vector3<TIntegral> vec(xIndex, yIndex, zIndex);
		return(vec);
	}

	template<typename TIntegral>
	Vector3<TIntegral> Vector3<TIntegral>::operator*(TIntegral scalar)
	{
		Vector3<TIntegral> vec;
		vec.x = x * scalar;
		vec.y = y * scalar;
		return(vec);
	}

	template<typename TIntegral>
	Vector3<TIntegral> Vector3<TIntegral>::operator*(const Vector3& multiplier)
	{
		Vector3<TIntegral> vec;
		vec.x = x * multiplier.x;
		vec.y = y * multiplier.y;
		return(vec);
	}

	template<typename TIntegral>
	Vector3<TIntegral> Vector3<TIntegral>::operator/(TIntegral scalar)
	{
		Vector3<TIntegral> vec;
		vec.x = x / scalar;
		vec.y = y / scalar;
		return(vec);
	}

	template<typename TIntegral>
	Vector3<TIntegral> Vector3<TIntegral>::operator/(const Vector3& divisor)
	{
		Vector3<TIntegral> vec;
		vec.x = x / divisor.x;
		vec.y = y / divisor.y;
		return(vec);
	}

	template<typename TIntegral>
	Vector3<TIntegral> Vector3<TIntegral>::operator+(const Vector3& addend)
	{
		Vector3<TIntegral> vec;
		vec.x = x + addend.x;
		vec.y = y + addend.y;
		return(vec);
	}

	template<typename TIntegral>
	Vector3<TIntegral> Vector3<TIntegral>::operator-(const Vector3& subtrahend)
	{
		Vector3<TIntegral> vec;
		vec.x = x - subtrahend.x;
		vec.y = y - subtrahend.y;
		return(vec);
	}

	template<typename TIntegral>
	void Vector3<TIntegral>::operator*=(TIntegral scalar)
	{
		x *= scalar;
		y *= scalar;
	}

	template<typename TIntegral>
	void Vector3<TIntegral>::operator*=(const Vector3& multiplier)
	{
		x *= multiplier.x;
		y *= multiplier.y;
	}

	template<typename TIntegral>
	void Vector3<TIntegral>::operator/=(TIntegral scalar)
	{
		x /= scalar;
		y /= scalar;
	}

	template<typename TIntegral>
	void Vector3<TIntegral>::operator/=(const Vector3& divisor)
	{
		x /= divisor.x;
		y /= divisor.y;
	}

	template<typename TIntegral>
	void Vector3<TIntegral>::operator+=(const Vector3& addend)
	{
		x += addend.x;
		y += addend.y;
	}

	template<typename TIntegral>
	void Vector3<TIntegral>::operator-=(const Vector3& subtrahend)
	{
		x -= subtrahend.x;
		y -= subtrahend.y;
	}

	template<typename TIntegral>
	bool Vector3<TIntegral>::operator<(const Vector3& other)
	{
		return(x < other.x && y < other.y && z < other.z);
	}

	template<typename TIntegral>
	bool Vector3<TIntegral>::operator<=(const Vector3& other)
	{
		return(x <= other.x && y <= other.y && z <= other.z);
	}

	template<typename TIntegral>
	bool Vector3<TIntegral>::operator>(const Vector3& other)
	{
		return(x > other.x && y > other.y && z > other.z);
	}

	template<typename TIntegral>
	bool Vector3<TIntegral>::operator>=(const Vector3& other)
	{
		return(x >= other.x && y >= other.y && z >= other.z);
	}

	template<typename TIntegral>
	bool Vector3<TIntegral>::operator==(const Vector3& other)
	{
		return(x == other.x && y == other.y && z == other.z);
	}

	template<typename TIntegral>
	bool Vector3<TIntegral>::operator!=(const Vector3& other)
	{
		return(x != other.x && y != other.y && z != other.z);
	}
}