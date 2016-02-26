#pragma once

/*Standard Library*/
#include <iostream>
#include <string.h>

/*Custom Library*/
#include "..\..\Memory\Allocators\Include\pool_allocator.hpp"

namespace aux
{
	size_t qStrLen			(const char* string);
	size_t qStrLen			(const char* string, size_t buffer);
	void qStrCpy			(const char* src, char* dest, size_t buffer);
	bool qStrCmp			(const char* s1, const char* s2);
	bool qStrCmp			(const char* s1, const char* s2, size_t buffer);
}

#define STRING_CHUNK_SIZE			sizeof(char*)
#define DEFAULT_STRING_CAPACITY		32

class QString
{
public:
	QString(void);
	QString(const char* string);
	QString(char* string);
	QString(const QString& string);

	~QString(void);

private:
	enum SEARCH_CASE_SENSITIVITY
	{
		/*Characters must have eact casing*/
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
	PoolAllocator<STRING_CHUNK_SIZE>	_pool;
};