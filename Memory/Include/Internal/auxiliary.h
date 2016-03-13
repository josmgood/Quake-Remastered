#pragma once

namespace internal
{
	typedef unsigned char Byte;

	template<typename SizeType = size_t>
	inline constexpr SizeType byteAlign(SizeType value)
	{
		return((value + 7) & ~7);
	}

	template<typename SizeType = size_t>
	inline constexpr SizeType alignTo(SizeType value, size_t alignment)
	{
		return(static_cast<SizeType>
			((static_cast<size_t>(value) + (alignment - 1)) & ~(alignment - 1)));
	}

	template<typename PtrType = Byte>
	inline constexpr PtrType* alignTo(PtrType* value, size_t alignment)
	{
		return(reinterpret_cast<PtrType*>
			(alignTo(reinterpret_cast<Byte>(value), alignment)));
	}

	template<typename SizeType = size_t>
	inline constexpr bool isAlignedTo(SizeType value, size_t alignment)
	{
		return((value & (alignment - 1)) == 0);
	}

	template<typename PtrType = internal::Byte*>
	constexpr bool isAlignedTo(PtrType* value, size_t alignment)
	{
		return(reinterpret_cast<PtrType>(value) & (alignment - 1)) == 0;
	}

	template<typename SizeType = size_t>
	inline constexpr bool isPowerOfTwo(SizeType value)
	{
		return(value && (value & (value - 1)) == 0);
	}

	template<typename SizeType = size_t>
	inline SizeType alignToPowerOfTwo(SizeType n)
	{
		n--;
		n |= n >> 1;
		n |= n >> 2;
		n |= n >> 4;
		n |= n >> 8;
		n |= n >> 31;
		n++;
		return(n);
	}

	inline constexpr bool addressMatch(void* one, void* two)
	{
		return(one == two);
	}

	template<typename Ptr>
	inline void copy(Ptr base, size_t buffer, Ptr dest)
	{
		for (size_t i = 0; i < buffer; i++)
		{
			dest[i] = base[i];
		}
	}
}