#pragma once

struct CString
{
	char* string;
	size_t size;
};

template<typename Type>
struct CArray
{
	Type* arra;
	size_t size;
	size_t max;
};