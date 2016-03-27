#include "..\..\Quake\Auxiliary\Include\string_aux.h"

#include <GTest\gtest.h>

#define NAME DISABLED_STRING

TEST(NAME, IS_EMPTY_CHAR)
{
	EXPECT_EQ(true, isEmptyChar(' '));
	EXPECT_EQ(false, isEmptyChar('a'));
}

TEST(NAME, LENGTH)
{
	char* str1 = "Hello";
	EXPECT_EQ(5, Q_strLen(str1));

	char* str2 = new char[11];
	//std::memset(str2, 0, sizeof(*str2) + 10);
	for (size_t i = 0; i < Q_strLen(str1); ++i)
	{
		str2[i] = str1[i];
	}
	str2[Q_strLen(str1)] = '\0';
	EXPECT_EQ(5, Q_strLen(str2));
}

TEST(NAME, LENGTH_BUFFER)
{
	char* str1 = "Hello World";
	EXPECT_EQ(5, Q_strLen(str1, 5));

	char* str2 = new char[12];
	std::memset(str2, 0, sizeof(*str2) + 12);
	for (size_t i = 0; i < Q_strLen(str1); ++i)
	{
		str2[i] = str1[i];
	}
	EXPECT_EQ(7, Q_strLen(str2, 7));
}

TEST(NAME, COPY)
{
	char* src = "Hello World";
	char* dest = new char[100];
	Q_strCpy(src, dest);
	EXPECT_EQ(true, Q_strCmp(src, dest));
	EXPECT_EQ(true, Q_strLen(src) == Q_strLen(dest));
}

TEST(NAME, COPY_BUFFER)
{
	char* src = "Hello World";
	char* dest = new char[100];
	Q_strCpy(src, dest, 12);
	EXPECT_EQ(true, Q_strCmp(src, dest));
	EXPECT_EQ(true, Q_strLen(src) == Q_strLen(dest));
}

TEST(NAME, CONCAT)
{
	char* A = "Hello ";
	char* B = "World!";
	char* together = "Hello World!";
	char* cated = new char[12];
	Q_strCpy(A, cated);
	Q_strCat(B, cated);
	EXPECT_EQ(true, Q_strCmp(together, cated));
}

TEST(NAME, CONCAT_BUFFER)
{
	char* A = "Hello ";
	char* B = "World";
	char* together = "Hello Wor";
	char* cated = new char[12];
	Q_strCpy(A, cated);
	Q_strCat(B, cated, 3);
	EXPECT_EQ(true, Q_strCmp(together, cated));
}

TEST(NAME, CHAR_TO_INT32)
{
	char ch = '5';
	EXPECT_EQ(5, Q_toInt32(ch));
}

TEST(NAME, STRING_TO_INT32)
{
	char* integer = "12345adf23";
	EXPECT_EQ(12345, Q_toInt32(integer));

	char* hex1 = "0x394B4";
	EXPECT_EQ(234676, Q_toInt32(hex1));

	char* hex2 = "0x7FFFFFFF";
	EXPECT_EQ(2147483647, Q_toInt32(hex2));
}

//TEST(NAME, TO_FLOAT64)
//{
//	char* flo = "123.23322932";
//	EXPECT_EQ(123.233, Q_toFloat64(flo));
//
//	char* hex = "0x42F676C8";
//	EXPECT_EQ(123.233, Q_toFloat64(hex));
//}

TEST(NAME, CHAR_CMP)
{
	EXPECT_EQ(true, Q_chrCmp('h', 'h'));
	EXPECT_EQ(false, Q_chrCmp('a', 'z'));
}

TEST(NAME, STRING_CMP)
{
	char* str1 = "Hello";
	char* str2 = "World";
	char* str3 = "Hello World";

	EXPECT_EQ(false, Q_strCmp(str1, str2));
	EXPECT_EQ(true, Q_strCmp(str1, str3, 5));
	EXPECT_EQ(false, Q_strCmp(str2, str3, 5));
}

TEST(NAME, STRING_CASE_CMP)
{
	char* str1 = "HELLO";
	char* str2 = "HeLlO";
	char* str3 = "SJFLasfsKSJDFLSKHJFlkjkasjfdl";

	EXPECT_EQ(true, Q_strCaseCmp(str1, str2));
	EXPECT_EQ(false, Q_strCaseCmp(str1, str3, 5));
	EXPECT_EQ(false, Q_strCaseCmp(str2, str3, 5));
}

TEST(NAME, FIND)
{
	char* string = "This is a test string.";
	EXPECT_EQ(true, Q_strFind(string, 't'));
	EXPECT_EQ(false, Q_strFind(string, 'z'));
}

TEST(NAME, FIND_BUFFER)
{
	char* string = "This is a test string.";
	EXPECT_EQ(true, Q_strFind(string, 't', 12));
	EXPECT_EQ(false, Q_strFind(string, 'z', 1000));
}

TEST(NAME, CONST_CHR)
{
	char* string = "This is a test string.";
	const char* ch = &string[2];
	EXPECT_EQ(ch, Q_strConstChr(string, 'i'));
	EXPECT_EQ(nullptr, Q_strConstChr(string, 'z'));
}

TEST(NAME, CONST_CHR_BUFFER)
{
	char* string = "This is a test string.";
	const char* ch = &string[10];
	EXPECT_EQ(ch, Q_strConstChr(string, 't', 11));
	EXPECT_EQ(nullptr, Q_strConstChr(string, 'z', 1000));
}

TEST(NAME, CHR)
{
	char* string = "This is a test string.";
	char* ch = &string[2];
	EXPECT_EQ(ch, Q_strConstChr(string, 'i'));
	EXPECT_EQ(nullptr, Q_strConstChr(string, 'z'));
}

TEST(NAME, CHR_BUFFER)
{
	char* string = "This is a test string.";
	const char* ch = &string[10];
	EXPECT_EQ(ch, Q_strConstChr(string, 't', 11));
	EXPECT_EQ(nullptr, Q_strConstChr(string, 'z', 1000));
}