#include "..\Include\vector4.hpp"

namespace math
{
	template<typename TIntegral>
	Vector4<TIntegral>::Vector4()
		: x(), y(), z(), w()
	{
	}

	template<typename TIntegral>
	Vector4<TIntegral>::Vector4(TIntegral _x, TIntegral _y, TIntegral _z, TIntegral _w)
		: x(_x), y(_y), z(_z), w(_w)
	{
	}

	template<typename TIntegral>
	Vector4<TIntegral>::Vector4(const Vector4& vector)
		: x(vector.x), y(vector.y), z(vector.z), w(vector.w)
	{
	}

	template<typename TIntegral>
	Vector4<TIntegral>::Vector4(Vector4&& vector)
		: x(vector.x), y(vector.y), z(vector.z), w(vector.w)
	{
	}

	template<typename TIntegral>
	TIntegral Vector4<TIntegral>::dot(const Vector4& one, const Vector4& two)
	{
		return(one ^ two);
	}

	template<typename TIntegral>
	Vector4<TIntegral> Vector4<TIntegral>::mScale(const Vector4& vector, TIntegral scalar)
	{
		return(vector * scalar);
	}

	template<typename TIntegral>
	Vector4<TIntegral> Vector4<TIntegral>::dScale(const Vector4& vector, TIntegral scalar)
	{
		return(vector / scalar);
	}

	template<typename TIntegral>
	Vector4<TIntegral> Vector4<TIntegral>::multiply(const Vector4& vector, const Vector4& multiplier)
	{
		return(vector * multiplier);
	}

	template<typename TIntegral>
	Vector4<TIntegral> Vector4<TIntegral>::divide(const Vector4& vector, const Vector4& divisor)
	{
		return(vector / divisor);
	}

	template<typename TIntegral>
	Vector4<TIntegral> Vector4<TIntegral>::add(const Vector4& vector, const Vector4& addend)
	{
		return(vector + addend);
	}

	template<typename TIntegral>
	Vector4<TIntegral> Vector4<TIntegral>::subtract(const Vector4& vector, const Vector4& subtrahend)
	{
		return(vector - subtrahend);
	}

	template<typename TIntegral>
	void Vector4<TIntegral>::set(Vector4& vector, TIntegral x, TIntegral y, TIntegral z, TIntegral w)
	{
		vector = Vector4<TIntegral>(x, y, z, w);
	}

	template<typename TIntegral>
	void Vector4<TIntegral>::setX(Vector4& vector, TIntegral x)
	{
		vector.x = x;
	}

	template<typename TIntegral>
	void Vector4<TIntegral>::setY(Vector4& vector, TIntegral y)
	{
		vector.y = y;
	}

	template<typename TIntegral>
	void Vector4<TIntegral>::setZ(Vector4& vector, TIntegral z)
	{
		vector.z = z;
	}

	template<typename TIntegral>
	void Vector4<TIntegral>::setW(Vector4& vector, TIntegral w)
	{
		vector.w = w;
	}

	template<typename TIntegral>
	TIntegral Vector4<TIntegral>::addX(const Vector4& vector, TIntegral addend)
	{
		return(vector.x + addend);
	}

	template<typename TIntegral>
	TIntegral Vector4<TIntegral>::subtractX(const Vector4& vector, TIntegral subtrahend)
	{
		return(vector.x - subtrahend);
	}

	template<typename TIntegral>
	TIntegral Vector4<TIntegral>::addY(const Vector4& vector, TIntegral addend)
	{
		return(vector.y + addend);
	}

	template<typename TIntegral>
	TIntegral Vector4<TIntegral>::subtractY(const Vector4& vector, TIntegral subtrahend)
	{
		return(vector.y - subtrahend);
	}

	template<typename TIntegral>
	TIntegral Vector4<TIntegral>::addZ(const Vector4& vector, TIntegral addend)
	{
		return(vector.z + addend);
	}

	template<typename TIntegral>
	TIntegral Vector4<TIntegral>::subtractZ(const Vector4& vector, TIntegral subtrahend)
	{
		return(vector.z - subtrahend);
	}

	template<typename TIntegral>
	TIntegral Vector4<TIntegral>::addW(const Vector4& vector, TIntegral addend)
	{
		return(vector.w + addend);
	}

	template<typename TIntegral>
	TIntegral Vector4<TIntegral>::subtractW(const Vector4& vector, TIntegral subtrahend)
	{
		return(vector.w - subtrahend);
	}

	template<typename TIntegral>
	TIntegral Vector4<TIntegral>::dot(const Vector4& vector)
	{
		return(*this ^ vector);
	}

	template<typename TIntegral>
	void Vector4<TIntegral>::mScale(TIntegral scalar)
	{
		*this *= scalar;
	}

	template<typename TIntegral>
	void Vector4<TIntegral>::dScale(TIntegral scalar)
	{
		*this /= scalar;
	}

	template<typename TIntegral>
	void Vector4<TIntegral>::multiply(const Vector4& multiplier)
	{
		*this *= multiplier;
	}

	template<typename TIntegral>
	void Vector4<TIntegral>::divide(const Vector4& divisor)
	{
		*this /= divisor;
	}

	template<typename TIntegral>
	void Vector4<TIntegral>::add(const Vector4& addend)
	{
		*this += addend;
	}

	template<typename TIntegral>
	void Vector4<TIntegral>::subtract(const Vector4& subtrahend)
	{
		*this -= subtrahend;
	}

	template<typename TIntegral>
	void Vector4<TIntegral>::set(TIntegral x, TIntegral y, TIntegral z, TIntegral w)
	{
		*this = Vector4<TIntegral>(x, y, z, w);
	}

	template<typename TIntegral>
	void Vector4<TIntegral>::setX(TIntegral x)
	{
		this->x = x;
	}

	template<typename TIntegral>
	void Vector4<TIntegral>::setY(TIntegral y)
	{
		this->y = y;
	}

	template<typename TIntegral>
	void Vector4<TIntegral>::setZ(TIntegral z)
	{
		this->z = z;
	}

	template<typename TIntegral>
	void Vector4<TIntegral>::setW(TIntegral w)
	{
		this->w = w;
	}

	template<typename TIntegral>
	void Vector4<TIntegral>::addX(TIntegral addend)
	{
		this->x += addend;
	}

	template<typename TIntegral>
	void Vector4<TIntegral>::subtractX(TIntegral subtrahend)
	{
		this->x -= subtrahend;
	}

	template<typename TIntegral>
	void Vector4<TIntegral>::addY(TIntegral addend)
	{
		this->y += addend;
	}

	template<typename TIntegral>
	void Vector4<TIntegral>::subtractY(TIntegral subtrahend)
	{
		this->y -= subtrahend;
	}

	template<typename TIntegral>
	void Vector4<TIntegral>::addZ(TIntegral addend)
	{
		this->z += addend;
	}

	template<typename TIntegral>
	void Vector4<TIntegral>::subtractZ(TIntegral subtrahend)
	{
		this->z -= subtrahend;
	}

	template<typename TIntegral>
	void Vector4<TIntegral>::addW(TIntegral addend)
	{
		this->w += addend;
	}

	template<typename TIntegral>
	void Vector4<TIntegral>::subtractW(TIntegral subtrahend)
	{
		this->w -= subtrahend;
	}

	template<typename TIntegral>
	void Vector4<TIntegral>::invert()
	{
		x = -x;
		y = -y;
		z = -z;
		w = -w;
	}

	template<typename TIntegral>
	void Vector4<TIntegral>::normalize()
	{
		float32 len = length();
		if (len)
		{
			float32 iLen = 1 / len;
			x *= iLen;
			y *= iLen;
			z *= iLen;
			w *= iLen;
		}
	}

	template<typename TIntegral>
	float32 Vector4<TIntegral>::length()
	{
		float32 xSqrd = squared(x);
		float32 ySqrd = squared(y);
		float32 zSqrd = squared(z);
		float32 wSqrd = squared(w);
		return(math::sqrt(xSqrd + ySqrd + zSqrd + wSqrd));
	}

	template<typename TIntegral>
	bool Vector4<TIntegral>::equals(const Vector4& other)
	{
		return(*this == other);
	}

	template<typename TIntegral>
	TIntegral Vector4<TIntegral>::operator[](size_t index) const
	{
		switch (index)
		{
		case 0:
			return(x);
		case 1:
			return(y);
		case 2:
			return(z);
		case 3:
			return(w);
		default:
			return(0);
		}
	}

	template<typename TIntegral>
	TIntegral Vector4<TIntegral>::operator^(const Vector4& other)
	{
		TIntegral xProduct = x * other.x;
		TIntegral yProduct = y * other.y;
		TIntegral zProduct = z * other.z;
		TIntegral wProduct = w * other.w;
		return(xProduct + yProduct + zProduct + wProduct);
	}

	template<typename TIntegral>
	Vector4<TIntegral> Vector4<TIntegral>::operator*(TIntegral scalar)
	{
		Vector4<TIntegral> vec;
		vec.x = x * scalar;
		vec.y = y * scalar;
		vec.z = z * scalar;
		vec.w = w * scalar;
		return(vec);
	}

	template<typename TIntegral>
	Vector4<TIntegral> Vector4<TIntegral>::operator*(const Vector4& multiplier)
	{
		Vector4<TIntegral> vec;
		vec.x = x * multiplier.x;
		vec.y = y * multiplier.y;
		vec.z = z * multiplier.z;
		vec.w = w * multiplier.w;
		return(vec);
	}

	template<typename TIntegral>
	Vector4<TIntegral> Vector4<TIntegral>::operator/(TIntegral scalar)
	{
		Vector4<TIntegral> vec;
		vec.x = x / scalar;
		vec.y = y / scalar;
		vec.z = z / scalar;
		vec.w = w / scalar;
		return(vec);
	}

	template<typename TIntegral>
	Vector4<TIntegral> Vector4<TIntegral>::operator/(const Vector4& divisor)
	{
		Vector4<TIntegral> vec;
		vec.x = x / divisor.x;
		vec.y = y / divisor.y;
		vec.z = z / divisor.z;
		vec.w = w / divisor.w;
		return(vec);
	}

	template<typename TIntegral>
	Vector4<TIntegral> Vector4<TIntegral>::operator+(const Vector4& vector)
	{
		Vector4<TIntegral> vec;
		vec.x = x + vector.x;
		vec.y = y + vector.y;
		vec.z = z + vector.z;
		vec.w = w + vector.w;
		return(vec);
	}

	template<typename TIntegral>
	Vector4<TIntegral> Vector4<TIntegral>::operator-(const Vector4& vector)
	{
		Vector4<TIntegral> vec;
		vec.x = x - vector.x;
		vec.y = y - vector.y;
		vec.z = z - vector.z;
		vec.w = w - vector.w;
		return(vec);
	}

	template<typename TIntegral>
	void Vector4<TIntegral>::operator*=(TIntegral scalar)
	{
		x *= scalar;
		y *= scalar;
	}

	template<typename TIntegral>
	void Vector4<TIntegral>::operator*=(const Vector4& multiplier)
	{
		x *= multiplier.x;
		y *= multiplier.y;
		z *= multiplier.z;
		w *= multiplier.w;
	}

	template<typename TIntegral>
	void Vector4<TIntegral>::operator/=(TIntegral scalar)
	{
		x /= scalar;
		y /= scalar;
		z /= scalar;
		w /= scalar;
	}

	template<typename TIntegral>
	void Vector4<TIntegral>::operator/=(const Vector4& divisor)
	{
		x /= divisor.x;
		y /= divisor.y;
		z /= divisor.y;
		w /= divisor.w;
	}

	template<typename TIntegral>
	void Vector4<TIntegral>::operator+=(const Vector4& addend)
	{
		x += addend.x;
		y += addend.y;
		z += addend.z;
		w += addend.w;
	}

	template<typename TIntegral>
	void Vector4<TIntegral>::operator-=(const Vector4& subtrahend)
	{
		x -= subtrahend.x;
		y -= subtrahend.y;
		z -= subtrahend.z;
		w -= subtrahend.w;
	}

	template<typename TIntegral>
	bool Vector4<TIntegral>::operator<(const Vector4& other)
	{
		return(x < other.x && y < other.y && z < other.z && w < other.w);
	}

	template<typename TIntegral>
	bool Vector4<TIntegral>::operator<=(const Vector4& other)
	{
		return(x <= other.x && y <= other.y && z <= other.z && w <= other.w);
	}

	template<typename TIntegral>
	bool Vector4<TIntegral>::operator>(const Vector4& other)
	{
		return(x > other.x && y > other.y && z > other.z && w > other.w);
	}

	template<typename TIntegral>
	bool Vector4<TIntegral>::operator>=(const Vector4& other)
	{
		return(x >= other.x && y >= other.y && z >= other.z && w >= other.w);
	}

	template<typename TIntegral>
	bool Vector4<TIntegral>::operator==(const Vector4& other)
	{
		return(x == other.x && y == other.y && z == other.z && w == other.w);
	}

	template<typename TIntegral>
	bool Vector4<TIntegral>::operator!=(const Vector4& other)
	{
		return(x != other.x && y != other.y && z != other.z && w != other.w);
	}
}