#pragma once

#include <functional>

#include "..\..\Container\Include\qbool.h"
#include "..\..\common.h"

static char EMPTY_CHAR = ' ';

struct cString
{
	cString(char* str, size_t len);

	char* string;
	size_t length;
};

QBool isEmptyChar(char ch);
QBool isTerminatingZero(char ch);

size_t Q_strLen(const char* string);
size_t Q_strLen(const char* string, size_t buffer);

void Q_strCpy(const char* src, char* dest);
void Q_strCpy(const char* src, char* dest, size_t buffer);

char* Q_strCat(const char* src, char* dest);
char* Q_strCat(const char* src, char* dest, size_t buffer);

QBool Q_isAlpha(char ch);
QBool Q_isSpace(char ch);
QBool Q_isNumeric(char ch);
QBool Q_isUpper(char ch);
QBool Q_isLower(char ch);
QBool Q_isHexU(char ch);
QBool Q_isHexL(char ch);

char Q_toUpper(char ch);
char Q_toLower(char ch);

int32 Q_toInt32(char ch);
int32 Q_toInt32(char* string);
float64 Q_toFloat64(char* string);

QBool Q_chrCmp(char A, char B);
QBool Q_strCmp(const char* A, const char* B);
QBool Q_strCmp(const char* A, const char* B, size_t buffer);
QBool Q_chrCaseCmp(char A, char B);
QBool Q_strCaseCmp(const char* A, const char* B);
QBool Q_strCaseCmp(const char* A, const char* B, size_t buffer);

QBool Q_strFind(const char* string, char ch);
QBool Q_strFind(const char* string, char ch, size_t buffer);

const char* Q_strConstChr(const char* string, char ch);
const char* Q_strConstChr(const char* string, char ch, size_t buffer);

char* Q_strChr(char* string, char ch);
char* Q_strChr(char* string, char ch, size_t buffer);

void Q_strPrint(const char* string);

typedef std::function<QBool(char ch)> CharacterFilter;
typedef std::function<char(char)> CharacterConverter;

#define BLANK_FILTER CharacterFilter()
#define BLANK_CONVERTER CharacterConverter()

#define IS_ALPHA CharacterFilter(Q_isAlpha)
#define IS_NUMERIC CharacterFilter(Q_isNumeric)
#define IS_SPACE CharacterFilter(Q_isSpace)
#define IS_UPPER CharacterFilter(Q_isSpace)
#define IS_LOWER CharacterFilter(Q_isLower)

#define TO_UPPER CharacterConverter(Q_toUpper)
#define TO_SPACE CharacterConverter(Q_toLower)