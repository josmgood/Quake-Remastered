#pragma once

#include <functional>
#include <string.h>

#include "..\..\Container\Include\qbool.h"
#include "..\..\common.h"

#define TZERO '\0';
#define FIRST_INDEX 0

static char EMPTY_CHAR = ' ';

QBool hasTerminatingZero(const char* string);
QBool hasTerminatingZero(const char* string, size_t length);

QBool chricmp(char one, char two);
QBool chrcmp(char one, char two);

typedef std::function<bool(char ch)> CharacterFilter;
typedef std::function<int(char)> CharacterConverter;

#define BLANK_FILTER CharacterFilter()
#define BLANK_CONVERTER CharacterConverter()

#define IS_ALPHA CharacterFilter(isalpha)
#define IS_DIGIT CharacterFilter(isdigit)
#define IS_SPACE CharacterFilter(isspace)
#define IS_UPPER CharacterFilter(isupper)
#define IS_LOWER CharacterFilter(islower)
#define IS_CONTROL CharacterFilter(iscntrl);
#define IS_PUNCTUATION CharacterFilter(ispunct)
#define IS_HEXADECIMAL CharacterFilter(isxdigit)

#define TO_UPPER CharacterConverter(toupper)
#define TO_LOWER CharacterConverter(tolower)

QBool filterMatch(bool result);
QBool filterNotMatch(bool result);

QBool exceptionApply(bool result);
QBool exceptionNotApply(bool result);