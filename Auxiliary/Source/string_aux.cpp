#include "..\Include\string_aux.h"

QBool isEmptyChar(char ch)
{
	return ch == EMPTY_CHAR;
}

size_t Q_strLen(const char* string)
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

size_t Q_strLen(const char* string, size_t buffer)
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

void Q_strCpy(const char* src, char* dest)
{
	while (*src)
	{
		*dest = *src;

		dest++;
		src++;
	}
	*dest++ = 0;
}

void Q_strCpy(const char* src, char* dest, size_t buffer)
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

char* Q_strCat(const char* A, const char* B)
{
	size_t len = Q_strLen(A) + Q_strLen(B);
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

QBool Q_isAlpha(char ch)
{
	return ch >= 65 && ch <= 122;
}

QBool Q_isSpace(char ch)
{
	return ch == 32;
}

QBool Q_isNumeric(char ch)
{
	return ch >= 48 && ch <= 57;
}

QBool Q_isUpper(char ch)
{
	return ch >= 65 && ch <= 90;
}

QBool Q_isLower(char ch)
{
	return ch >= 97 && ch <= 122;
}

char Q_toUpper(char ch)
{
	if (Q_isLower(ch))
	{
		return ch - 32;
	}
	return ch;
}

char Q_toLower(char ch)
{
	if (Q_isUpper(ch))
	{
		return ch + 32;
	}
	return ch;
}

int Q_toInt(char ch)
{
	if (Q_isNumeric(ch))
	{
		return ch - '0';
	}
	return -1;
}

int Q_toInt(char* string)
{
	int num = 0;
	while (!*string)
	{
		if (Q_isNumeric(*string))
		{
			num += *string;
		}
		else
		{
			return -1;
		}
		string++;
	}
	return num;
}

QBool Q_chrCmp(char A, char B)
{
	return A == B;
}

QBool Q_strCmp(const char* A, const char* B)
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

QBool Q_strCmp(const char* A, const char* B, size_t buffer)
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

QBool Q_chrCaseCmp(char A, char B)
{
	char equalA = Q_toLower(A);
	char equalB = Q_toLower(B);
	return equalA == equalB;
}

QBool Q_strCaseCmp(const char* A, const char* B)
{
	while (!*A || !*B)
	{
		if (!Q_chrCaseCmp(*A, *B))
		{
			return false;
		}
	}
	return true;
}

QBool Q_strFind(const char* string, char ch)
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

QBool Q_strFind(const char* string, char ch, size_t buffer)
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

const char* Q_strConstChr(const char* string, char ch)
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

const char* Q_strConstChr(const char* string, char ch, size_t buffer)
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

char* Q_strChr(char* string, char ch)
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

char* Q_strChr(char* string, char ch, size_t buffer)
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

void Q_strDelete(char* string, size_t length)
{
	if (length == 1)
	{
		delete string;
	}
	else
	{
		delete[] string;
	}
}

void Q_strPrint(const char* string)
{
	const char* c = string;
	while (*c)
	{
		std::cout << *c;
		c++;
	}
	std::cout << std::endl;
}