#include "..\Include\qstring.hpp"

template<typename TAllocator>
QString<TAllocator>::QString(size_t length)
	: _allocator(sizeof(Character) * length), _maxLength(length), _length(length)
{
	_string = _allocator.allocate(sizeof(Character) * length);
}