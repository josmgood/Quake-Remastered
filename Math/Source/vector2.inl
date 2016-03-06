#include "../Include/vector2.hpp"

namespace math
{
	template<typename TIntegral>
	Vector2<TIntegral>::Vector2()
		: x(), y()
	{
	}

	template<typename TIntegral>
	Vector2<TIntegral>::Vector2(TIntegral _x, TIntegral _y)
		: x(_x), y(_y)
	{
	}

	template<typename TIntegral>
	Vector2<TIntegral>::Vector2(const Vector2& vector)
		: x(vector.x), y(vector.y)
	{
	}

	template<typename TIntegral>
	Vector2<TIntegral>::Vector2(Vector2&& vector)
		: x(vector.x), y(vector.y)
	{
	}

	template<typename TIntegral>
	TIntegral Vector2<TIntegral>::dot(const Vector2& one, const Vector2& two)
	{
		return(one ^ two);
	}

	template<typename TIntegral>
	Vector2<TIntegral> Vector2<TIntegral>::mScale(const Vector2& vector, TIntegral scalar)
	{
		return(vector * scalar);
	}

	template<typename TIntegral>
	Vector2<TIntegral> Vector2<TIntegral>::dScale(const Vector2& vector, TIntegral scalar)
	{
		return(vector / scalar);
	}

	template<typename TIntegral>
	Vector2<TIntegral> Vector2<TIntegral>::multiply(const Vector2& vector, const Vector2& multiplier)
	{
		return(vector * multiplier);
	}

	template<typename TIntegral>
	Vector2<TIntegral> Vector2<TIntegral>::divide(const Vector2& vector, const Vector2& divisor)
	{
		return(vector / divisor);
	}

	template<typename TIntegral>
	Vector2<TIntegral> Vector2<TIntegral>::add(const Vector2& vector, const Vector2& addend)
	{
		return(vector + addend);
	}

	template<typename TIntegral>
	Vector2<TIntegral> Vector2<TIntegral>::subtract(const Vector2& vector, const Vector2& subtrahend)
	{
		return(vector - subtrahend);
	}

	template<typename TIntegral>
	void Vector2<TIntegral>::set(Vector2& vector, TIntegral x, TIntegral y)
	{
		vector = Vector2<TIntegral>(x, y);
	}

	template<typename TIntegral>
	void Vector2<TIntegral>::setX(Vector2& vector, TIntegral x)
	{
		vector.x = x;
	}

	template<typename TIntegral>
	void Vector2<TIntegral>::setY(Vector2& vector, TIntegral y)
	{
		vector.y = y;
	}

	template<typename TIntegral>
	TIntegral Vector2<TIntegral>::addX(const Vector2& vector, TIntegral addend)
	{
		return(vector.x + addend);
	}

	template<typename TIntegral>
	TIntegral Vector2<TIntegral>::subtractX(const Vector2& vector, TIntegral subtrahend)
	{
		return(vector.x - subtrahend);
	}

	template<typename TIntegral>
	TIntegral Vector2<TIntegral>::addY(const Vector2& vector, TIntegral addend)
	{
		return(vector.x + addend);
	}

	template<typename TIntegral>
	TIntegral Vector2<TIntegral>::subtractY(const Vector2& vector, TIntegral subtrahend)
	{
		return(vector.y - subtrahend);
	}

	template<typename TIntegral>
	TIntegral Vector2<TIntegral>::dot(const Vector2& other)
	{
		return(*this ^ other);
	}

	template<typename TIntegral>
	void Vector2<TIntegral>::mScale(TIntegral scalar)
	{
		*this *= scalar;
	}

	template<typename TIntegral>
	void Vector2<TIntegral>::dScale(TIntegral scalar)
	{
		*this /= scalar;
	}

	template<typename TIntegral>
	void Vector2<TIntegral>::multiply(const Vector2& multiplier)
	{
		*this *= multiplier;
	}

	template<typename TIntegral>
	void Vector2<TIntegral>::divide(const Vector2& divisor)
	{
		*this /= divisor;
	}

	template<typename TIntegral>
	void Vector2<TIntegral>::add(const Vector2& addend)
	{
		*this += addend;
	}

	template<typename TIntegral>
	void Vector2<TIntegral>::subtract(const Vector2& subtrahend)
	{
		*this -= subtrahend;
	}

	template<typename TIntegral>
	void Vector2<TIntegral>::set(TIntegral x, TIntegral y)
	{
		*this = Vector3<TIntegral>(x, y);
	}

	template<typename TIntegral>
	void Vector2<TIntegral>::setX(TIntegral x)
	{
		this->x = x;
	}

	template<typename TIntegral>
	void Vector2<TIntegral>::setY(TIntegral y)
	{
		this->y = y;
	}

	template<typename TIntegral>
	void Vector2<TIntegral>::addX(TIntegral addend)
	{
		this->x += addend;
	}

	template<typename TIntegral>
	void Vector2<TIntegral>::subtractX(TIntegral subtrahend)
	{
		this->x -= subtrahend;
	}

	template<typename TIntegral>
	void Vector2<TIntegral>::addY(TIntegral addend)
	{
		this->x += addend;
	}

	template<typename TIntegral>
	void Vector2<TIntegral>::subtractY(TIntegral subtrahend)
	{
		this->y -= subtrahend;
	}

	template<typename TIntegral>
	void Vector2<TIntegral>::invert()
	{
		x = -x;
		y = -y;
	}

	template<typename TIntegral>
	void Vector2<TIntegral>::normalize()
	{
		TIntegral len = length();
		if (len)
		{
			float32 iLen = 1 / len;
			x *= iLen;
			y *= iLen;
		}
	}

	template<typename TIntegral>
	float32 Vector2<TIntegral>::length()
	{
		float32 xSqrd = squared(x);
		float32 ySqrd = squared(y);
		return(math::sqrt(xSqrd + ySqrd));
	}

	template<typename TIntegral>
	bool Vector2<TIntegral>::equals(const Vector2& other)
	{
		return(*this == other);
	}

	template<typename TIntegral>
	TIntegral Vector2<TIntegral>::operator[](size_t index) const
	{
		switch (index)
		{
		case 0:
			return(x);
		case 1:
			return(y);
		default:
			return(0);
		}
	}

	template<typename TIntegral>
	TIntegral Vector2<TIntegral>::operator^(const Vector2& other)
	{
		TIntegral xProduct = x * other.x;
		TIntegral yProduct = y * other.y;
		return(xProduct + yProduct);
	}

	template<typename TIntegral>
	Vector2<TIntegral> Vector2<TIntegral>::operator*(TIntegral scalar)
	{
		Vector2<TIntegral> vec;
		vec.x = x * scalar;
		vec.y = y * scalar;
		return(vec);
	}

	template<typename TIntegral>
	Vector2<TIntegral> Vector2<TIntegral>::operator*(const Vector2& multiplier)
	{
		Vector2<TIntegral> vec;
		vec.x = x * multiplier.x;
		vec.y = y * multiplier.y;
		return(vec);
	}

	template<typename TIntegral>
	Vector2<TIntegral> Vector2<TIntegral>::operator/(TIntegral scalar)
	{
		Vector2<TIntegral> vec;
		vec.x = x * scalar;
		vec.y = y * scalar;
		return(vec);
	}

	template<typename TIntegral>
	Vector2<TIntegral> Vector2<TIntegral>::operator/(const Vector2& divisor)
	{
		Vector2<TInteral> vec;
		vec.x = x / divisor.x;
		vec.y = y / divisor.y;
		return(vec);
	}

	template<typename TIntegral>
	Vector2<TIntegral> Vector2<TIntegral>::operator+(const Vector2& addend)
	{
		Vector2<TIntegral> vec;
		vec.x = x + addend.x;
		vec.y = y + addend.y;
		return(vec);
	}

	template<typename TIntegral>
	Vector2<TIntegral> Vector2<TIntegral>::operator-(const Vector2& subtrahend)
	{
		Vector2<TIntegral> vec;
		vec.x = x - addend.x;
		vec.y = y - addend.y;
		return(vec);
	}

	template<typename TIntegral>
	void Vector2<TIntegral>::operator*=(TIntegral scalar)
	{
		x *= scalar;
		y *= scalar;
	}

	template<typename TIntegral>
	void Vector2<TIntegral>::operator*=(const Vector2& multiplier)
	{
		x *= multiplier.x;
		y *= multiplier.y;
	}

	template<typename TIntegral>
	void Vector2<TIntegral>::operator/=(TIntegral scalar)
	{
		x /= scalar;
		y /= scalar;
	}

	template<typename TIntegral>
	void Vector2<TIntegral>::operator/=(const Vector2& divisor)
	{
		x /= divisor.x;
		y /= divisor.y;
	}

	template<typename TIntegral>
	void Vector2<TIntegral>::operator+=(const Vector2& addend)
	{
		x += addend.x;
		y += addend.y;
	}

	template<typename TIntegral>
	void Vector2<TIntegral>::operator-=(const Vector2& subtrahend)
	{
		x -= subtrahend.x;
		y -= subtrahend.y;
	}

	template<typename TIntegral>
	bool Vector2<TIntegral>::operator<(const Vector2& other)
	{
		return(x < other.x && y < other.y);
	}

	template<typename TIntegral>
	bool Vector2<TIntegral>::operator<=(const Vector2& other)
	{
		return(x <= other.x && y <= other.y);
	}

	template<typename TIntegral>
	bool Vector2<TIntegral>::operator>(const Vector2& other)
	{
		return(x > other.x && y > other.y);
	}

	template<typename TIntegral>
	bool Vector2<TIntegral>::operator>=(const Vector2& other)
	{
		return(x >= other.x && y >= other.y);
	}

	template<typename TIntegral>
	bool Vector2<TIntegral>::operator==(const Vector2& other)
	{
		return(x == other.x && y == other.y);
	}

	template<typename TIntegral>
	bool Vector2<TIntegral>::operator!=(const Vector2& other)
	{
		return(x != other.x && y != other.y);
	}
}