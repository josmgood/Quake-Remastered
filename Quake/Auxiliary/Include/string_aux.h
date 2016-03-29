#pragma once

#include <functional>
#include <string.h>

#include "..\..\Container\Include\qbool.h"
#include "..\..\common.h"

#define TZERO '\0';

static char EMPTY_CHAR = ' ';

QBool chricmp(char one, char two);
QBool chrcmp(char one, char two);

typedef std::function<QBool(char ch)> CharacterFilter;
typedef std::function<char(char)> CharacterConverter;

#define BLANK_FILTER CharacterFilter()
#define BLANK_CONVERTER CharacterConverter()

#define IS_ALPHA CharacterFilter(isalpha)
#define IS_DIGIT CharacterFilter(isdigit)
#define IS_SPACE CharacterFilter(isspace)
#define IS_UPPER CharacterFilter(isupper)
#define IS_LOWER CharacterFilter(islower)
#define IS_CONTROL CharacterFilter(iscntrl);
#define IS_PUNCTUATION CharacterFilter(ispunct);
#define IS_HEXADECIMAL CharacterFilter(isxdigit);

#define TO_UPPER CharacterConverter(toupper)
#define TO_SPACE CharacterConverter(tolower)