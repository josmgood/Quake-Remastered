#pragma once

namespace internal
{
	typedef unsigned char Byte;

	template<typename SizeType = size_t>
	inline constexpr SizeType align_8_byte(SizeType value)
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

	template<typename PtrType = Byte>
	constexpr bool isAlignedTo(PtrType* value, size_t alignment)
	{
		return(reinterpret_cast<Byte>(value) & (alignment - 1)) == 0;
	}

	template<typename SizeType = size_t>
	inline constexpr bool isPowerOfTwo(SizeType value)
	{
		return(value && (value & (value - 1)) == 0);
	}
}