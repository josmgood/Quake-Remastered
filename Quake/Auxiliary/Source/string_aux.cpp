#include "..\Include\string_aux.h"

cString::cString(char* str, size_t len)
	: string(str), length(len)
{
}

QBool isEmptyChar(char ch)
{
	return ch == EMPTY_CHAR;
}

size_t Q_strLen(const char* string)
{
	size_t count = 0;
	while (string[count])
	{
		count++;
	}

	return count;
}

size_t Q_strLen(const char* string, size_t buffer)
{
	size_t count = 0;
	while (string[count] && buffer--)
	{
		count++;
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

char* Q_strCat(const char* src, char* dest)
{
	size_t len = 0;
	char* ch = dest;
	while (*ch++)
	{
		len++;
	}

	size_t i;
	for (i = 0; src[i] != '\0'; ++i)
	{
		dest[len + i] = src[i];
	}
	dest[len + i] = '\0';
	return dest;
}

char* Q_strCat(const char* src, char* dest, size_t buffer)
{
	size_t len = 0;
	char* ch = dest;
	while (*ch++)
	{
		len++;
	}

	size_t i;
	for (i = 0; buffer-- && src[i]; ++i)
	{
		dest[len + i] = src[i];
	}
	dest[len + i] = '\0';
	return dest;
}

QBool Q_isAlpha(char ch)
{
	return ch >= 'A' && ch <= 'z';
}

QBool Q_isSpace(char ch)
{
	return ch == ' ';
}

QBool Q_isNumeric(char ch)
{
	return ch >= '0' && ch <= '9';
}

QBool Q_isUpper(char ch)
{
	return ch >= 'A' && ch <= 'Z';
}

QBool Q_isLower(char ch)
{
	return ch >= 'a' && ch <= 'z';
}

QBool Q_isHexU(char ch)
{
	return ch >= 'A' && ch <= 'F';
}

QBool Q_isHexL(char ch)
{
	return ch >= 'a' && ch <= 'f';
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

int32 Q_toInt32(char ch)
{
	if (Q_isNumeric(ch))
	{
		return ch - '0';
	}
	return -1;
}

int32 Q_toInt32(char* string)
{
	int32 value = 0;
	int32 sign = 1;
	char ch = 0;

	/*Determine if integer is negative.*/
	if (*string == '-')
	{
		sign = -1;
		string++;
	}
	
	/*Is it in hexadecimal format?*/
	if (string[0] == '0' && (string[1] == 'x' || string[1] == 'X'))
	{
		string += 2;
		while (true)
		{
			ch = *string++;
			if (Q_isNumeric(ch))
			{
				value = (value << 4) + ch - '0';
			}
			else if (Q_isHexU(ch))
			{
				value = (value << 4) + ch - 'A' + 10;
			}
			else if (Q_isHexL(ch))
			{
				value = (value << 4) + ch - 'a' + 10;
			}
			else
			{
				return sign * value;
			}
		}
	}

	/*Is it a character?*/
	if (string[0] == '\'')
	{
		return sign * string[1];
	}

	/*It must be a normal integer*/
	while (true)
	{
		ch = *string++;
		if (!Q_isNumeric(ch))
		{
			return sign * value;
		}
		value = value * 10 + ch - '0';
	}
	return 0;
}

float64 Q_toFloat64(char* string)
{
	float64 value = 0;
	int sign = 1;
	char ch = 0;
	int decimal = -1;
	int total = 0;

	/*Determine the sign of the float.*/
	if (*string == '-')
	{
		sign = -1;
		string++;
	}

	/*Is it in hexadecimal format?*/
	if (string[0] == '0' && (string[1] == 'x' || string[1] == 'X'))
	{
		string += 2;
		while (true)
		{
			ch = *string++;
			if (Q_isNumeric(ch))
			{
				value = (value * 16) + ch - '0';
			}
			else if (Q_isHexU(ch))
			{
				value = (value * 16) + ch - 'A' + 10;
			}
			else if (Q_isHexL(ch))
			{
				value = (value * 16) + ch - 'a' + 10;
			}
			else
			{
				return sign * value;
			}
		}
	}

	/*Is it a character?*/
	if (string[0] == '\'')
	{
		return sign * string[1];
	}

	/*It must be a normal float. Calculate.*/
	while (true)
	{
		ch = *string++;
		if (ch == '.')
		{
			decimal = total;
			continue;
		}
		if (!Q_isNumeric(ch))
		{
			break;
		}
		value = value * 10 + ch - '0';
		total++;
	}
	
	/*If it is not a float, return integer result.*/
	if (decimal == -1)
	{
		return sign * value;
	}
	/*Divide until an accurate decimal*/
	while (total > decimal)
	{
		value /= 10;
		total--;
	}
	return sign * value;
}

QBool Q_chrCmp(char A, char B)
{
	return A == B;
}

QBool Q_strCmp(const char* A, const char* B)
{
	while (*A && *B)
	{
		if (!Q_chrCmp(*A, *B))
		{
			return false;
		}
		A++;
		B++;
	}
	return true;
}

QBool Q_strCmp(const char* A, const char* B, size_t buffer)
{
	while (*A && *B && buffer--)
	{
		if (!Q_chrCmp(*A, *B))
		{
			return false;
		}
		A++;
		B++;
	}
	return true;
}

QBool Q_chrCaseCmp(char A, char B)
{
	char equalA = Q_toLower(A);
	char equalB = Q_toLower(B);
	return equalA == equalB;
}

QBool Q_strCaseCmp(const char* A, const char* B)
{
	while (*A || *B)
	{
		if (!Q_chrCaseCmp(*A, *B))
		{
			return false;
		}
		A++;
		B++;
	}
	return true;
}

QBool Q_strCaseCmp(const char* A, const char* B, size_t buffer)
{
	while (*A && *B && buffer--)
	{
		if (!Q_chrCaseCmp(*A, *B))
		{
			return false;
		}
		A++;
		B++;
	}
	return false;
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

void Q_strPrint(const char* string)
{
	std::cout << string;
}