#pragma once

struct ContigiousIterator;
struct LinkedIterator;

#define DEFAULT_CONTAINER_SIZE 16

template<typename Type,
	typename TAllocator>
class QAuxiliary
{
public:
	typedef Type					Value;
	typedef Type&					Reference;
	typedef const Type&				ConstReference;
	typedef Type*					Pointer;
	typedef TAllocator				Allocator;
};

#include "..\Source\base.inl"