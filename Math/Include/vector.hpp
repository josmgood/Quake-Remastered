#pragma once

#include "..\..\Core\common.h"

namespace math
{
	template<typename Type>
	struct VectorBase
	{
		typedef Type Value;
		typedef Type& Reference;
		typedef const Type& ConstReference;
		typedef float32 Length;

		virtual Reference operator[](size_t i) = 0;
		virtual Length length() = 0;
	};

	template<typename Type = int32>
	struct Vector2
		: public VectorBase<Type>
	{

		virtual Reference operator[](size_t i) override
		{
			switch (i)
			{
			case 0:
				return(x);
			case 1:
				return(y);
			default:
				return(Value());
			}
		}
		virtual Length length() override
		{
			static float32 length;

		}

		Value x;
		Value y;
	};

	template<typename Type = int32>
	struct Vector3
		: public VectorBase<Type>
	{

		virtual operator[](size_t i) override;
		virtual Length length() override;

		Value x;
		Value y;
		Value z;
	};

	template<typename Type = int32>
	struct Vector4
		: public VectorBase<Type>
	{
		
		virtual operator[](size_t i) override;
		virtual Length length() override;

		Value x;
		Value y;
		Value z;
		Value w;
	};

	typedef int32			 Scalari;
	typedef Vector2<int32>	 Vector2i;
	typedef Vector3<int32>	 Vector3i;
	typedef Vector4<int32>	 Vector4i;

	typedef uint32			 Scalarui;
	typedef Vector2<uint32>  Vector2ui;
	typedef Vector3<uint32>	 Vector3ui;
	typedef Vector4<uint32>  Vector4ui;

	typedef int64			 Scalarl;
	typedef Vector2<int64>	 Vector2l;
	typedef Vector3<int64>	 Vector3l;
	typedef Vector4<int64>	 Vector4l;

	typedef uint64			 Scalarul;
	typedef Vector2<uint64>  Vector2ul;
	typedef Vector3<uint64>  Vector3ul;
	typedef Vector4<uint64>  Vector4ul;

	typedef float32			 Scalarf;
	typedef Vector2<float32> Vector2f;
	typedef Vector3<float32> Vector3f;
	typedef Vector4<float32> Vector4f;

	typedef float64			 Scalard;
	typedef Vector2<float64> Vector2d;
	typedef Vector3<float64> Vector3d;
	typedef Vector3<float64> Vector4d;
}