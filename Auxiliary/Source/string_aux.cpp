#include "..\Include\string_aux.h"

QBool isEmptyChar(char ch)
{
	return ch == EMPTY_CHAR;
}

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

char* qStrCat(const char* A, const char* B)
{
	size_t len = qStrLen(A) + qStrLen(B);
	char* str = new char[len];
	char* c = str;
	while (!*A)
	{
		*c = *A;

		A++;
		c++;
	}
	while (!*B)
	{
		*c = *B;

		B++;
		c++;
	}
	return str;
}

QBool qIsAlpha(char ch)
{
	return ch >= 65 && ch <= 122;
}

QBool qIsNumeric(char ch)
{
	return ch >= 48 && ch <= 57;
}

QBool qIsUpper(char ch)
{
	return ch >= 65 && ch <= 90;
}

QBool qIsLower(char ch)
{
	return ch >= 97 && ch <= 122;
}

char qToUpper(char ch)
{
	if (qIsLower(ch))
	{
		return ch - 32;
	}
	return EMPTY_CHAR;
}

char qToLower(char ch)
{
	if (qIsUpper(ch))
	{
		return ch + 32;
	}
	return EMPTY_CHAR;
}

int qToInt(char ch)
{
	if (qIsNumeric(ch))
	{
		return ch - '0';
	}
	return -1;
}

QBool qChrCmp(char A, char B)
{
	return A == B;
}

QBool qStrCmp(const char* A, const char* B)
{
	while (true)
	{
		if (*A != *B)
		{
			return false;
		}
		else if (!*A || !*B)
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
		else if (!*A || !*B)
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

QBool qChrCaseCmp(char A, char B)
{
	char equalA = qToLower(A);
	char equalB = qToLower(B);
	return equalA == equalB;
}

QBool qStrCaseCmp(const char* A, const char* B)
{
	while (true)
	{
		if (!*A || !*B )
		{
			return false;
		}
		else
		{
		}
	}
	return true;
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

const char* qStrConstChr(const char* string, char ch)
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

const char* qStrConstChr(const char* string, char ch, size_t buffer)
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