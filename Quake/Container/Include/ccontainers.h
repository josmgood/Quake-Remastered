#pragma once

struct CString
{
	char* string;
	size_t size;
};

template<typename Type>
struct CArray
{
	Type* array;
	size_t size;
};