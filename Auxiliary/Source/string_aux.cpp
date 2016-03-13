#include "..\Include\string_aux.h"

size_t qStrLen(const char* string)
{
	size_t count = 0;
	const char* c = string;
	while (*c)
	{
		count++;
		c++;
	}
	return count;
}

size_t qStrLen(const char* string, size_t buffer)
{
	size_t count = 0;
	const char* c = string;
	while (*c && buffer--)
	{
		count++;
		c++;
	}
	return count;
}

void qStrCpy(const char* src, char* dest)
{
	while (*src)
	{
		*dest = *src;

		dest++;
		src++;
	}
	*dest++ = 0;
}

void qStrCpy(const char* src, char* dest, size_t buffer)
{
	while (*src && buffer--)
	{
		*dest = *src;

		dest++;
		src++;
	}
	if (buffer)
	{
		*dest++ = 0;
	}
}

QBool qStrCmp(const char* A, const char* B)
{
	while (true)
	{
		if (*A != *B)
		{
			return false;
		}
		else if (!*A)
		{
			return true;
		}
		else
		{
			A++;
			B++;
		}
	}
}

QBool qStrCmp(const char* A, const char* B, size_t buffer)
{
	while (true)
	{
		if (!buffer-- || *A != *B)
		{
			return false;
		}
		else if (!*A)
		{
			return true;
		}
		else
		{
			A++;
			B++;
		}
	}
}

QBool qStrFind(const char* string, char ch)
{
	for (const char* c = string; *c; c++)
	{
		if (*c == ch)
		{
			return true;
		}
	}
	return false;
}

QBool qStrFind(const char* string, char ch, size_t buffer)
{
	for (const char* c = string; *c && buffer--; c++)
	{
		if (*c == ch)
		{
			return true;
		}
	}
	return false;
}

const char* qStrConstChar(const char* string, char ch)
{
	for (const char* c = string; *c; c++)
	{
		if (*c == ch)
		{
			return c;
		}
	}
	return nullptr;
}

const char* qStrConstChar(const char* string, char ch, size_t buffer)
{
	for (const char* c = string; *c && buffer--; c++)
	{
		if (*c == ch)
		{
			return c;
		}
	}
	return nullptr;
}

char* qStrChr(char* string, char ch)
{
	for (char* c = string; *c; c++)
	{
		if (*c == ch)
		{
			return c;
		}
	}
	return nullptr;
}

char* qStrChr(char* string, char ch, size_t buffer)
{
	for (char* c = string; *c && buffer--; c++)
	{
		if (*c == ch)
		{
			return c;
		}
	}
	return nullptr;
}

void qStrPrint(const char* string)
{
	const char* c = string;
	while (*c)
	{
		std::cout << *c;
		c++;
	}
	std::cout << std::endl;
}