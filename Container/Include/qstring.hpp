#pragma once

#include <iostream>

#include "..\..\Memory\Include\Allocator\pool_allocator.hpp"

#define DEFAULT_STRING_CAPACITY		32

template<typename TAllocator = PoolAllocator<char>>
class QString
{
public:
	QString(void) {};
	QString(const char* string);
	QString(char* string);
	QString(const QString& string);

	~QString(void) {};

private:
	enum SEARCH_CASE_SENSITIVITY
	{
		/*Characters must have exact casing*/
		SENSITIVE,
		/*Character casing is irrelevant.*/
		UNSENSITIVE
	};
	enum SEARCH_STARTING_POINT
	{
		/*Start searching the string at the beginning (forward)*/
		BEGINNING,
		/*Start searching the string at the end (backward)*/
		END
	};

	void _copy(const char* src, char* dest, size_t buffer);

	/*Raw string*/
	char*								_string;
	/*String length*/
	size_t								_length;
	/*Memory pool*/
	//PoolAllocator<char>	_pool;
};

#include "..\Source\qstring.inl"