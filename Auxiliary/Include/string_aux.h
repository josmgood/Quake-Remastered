#pragma once

#include "..\..\Container\Include\qbool.h"

static char EMPTY_CHAR = ' ';

struct cString
{
	char* string;
	size_t length;
};

QBool isEmptyChar(char ch);

size_t Q_strLen(const char* string);
size_t Q_strLen(const char* string, size_t buffer);

void Q_strCpy(const char* src, char* dest);
void Q_strCpy(const char* src, char* dest, size_t buffer);

//char* qStrCat(const char* A, const char* B);

QBool Q_isAlpha(char ch);
QBool Q_isNumeric(char ch);
QBool Q_isUpper(char ch);
QBool Q_isLower(char ch);

char Q_toUpper(char ch);
char Q_toLower(char ch);

int Q_toInt(char ch);
int Q_toInt(char* string);

QBool Q_chrCmp(char A, char B);
QBool Q_strCmp(const char* A, const char* B);
QBool Q_strCmp(const char* A, const char* B, size_t buffer);
QBool Q_chrCaseCmp(char A, char B);
QBool Q_strCaseCmp(const char* A, const char* B);
//QBool qStrCaseCmp(const char* A, const char* B, size_t buffer);

QBool Q_strFind(const char* string, char ch);
QBool Q_strFind(const char* string, char ch, size_t buffer);

const char* Q_strConstChr(const char* string, char ch);
const char* Q_strConstChr(const char* string, char ch, size_t buffer);

char* Q_strChr(char* string, char ch);
char* Q_strChr(char* string, char ch, size_t buffer);

void Q_strDelete(char* string, size_t length);

void Q_strPrint(const char* string);