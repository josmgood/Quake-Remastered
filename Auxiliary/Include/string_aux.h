#pragma once

#include "..\..\Container\Include\qbool.h"

size_t qStrLen(const char* string);
size_t qStrLen(const char* string, size_t buffer);

void qStrCpy(const char* src, char* dest);
void qStrCpy(const char* src, char* dest, size_t buffer);

//char* qStrCat(const char* A, const char* B);

QBool qStrCmp(const char* A, const char* B);
QBool qStrCmp(const char* A, const char* B, size_t buffer);
//QBool qStrCaseCmp(const char* A, const char* B);
//QBool qStrCaseCmp(const char* A, const char* B, size_t buffer);

QBool qStrFind(const char* string, char ch);
QBool qStrFind(const char* string, char ch, size_t buffer);

const char* qStrConstChr(const char* string, char ch);
const char* qStrConstChr(const char* string, char ch, size_t buffer);

char* qStrChr(char* string, char ch);
char* qStrChr(char* string, char ch, size_t buffer);

void qStrPrint(const char* string);