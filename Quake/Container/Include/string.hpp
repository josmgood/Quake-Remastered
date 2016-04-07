#pragma once

#include <iostream>
#include <fstream>
#include <functional>
#include <string.h>

#include "base.hpp"
#include "iterator.hpp"

#include "..\..\Auxiliary\Include\string_aux.h"
#include "..\..\Auxiliary\Include\algorithm.h"

//#include "..\..\Math\Include\math.h"

#include "..\..\Memory\Include\Allocator\mallocator.h"

#define DEFAULT_STRING_SIZE	32
#define STRING_RESERVE_SIZE 8

enum class STRING_SEARCH_CASE_SENSITIVITY
	: int8
{
	SENSITIVE = 0,
	INSENSITIVE = 1
};

enum class STRING_SEARCH_DIRECTION
	: int8
{
	FORWARD = 0,
	BACKWARD = 1
};

#define STR_SENSITIVE STRING_SEARCH_CASE_SENSITIVITY::SENSITIVE
#define STR_INSENSITIVE STRING_SEARCH_CASE_SENSITIVITY::INSENSITIVE
#define STR_FORWARD STRING_SEARCH_DIRECTION::FORWARD
#define STR_BACKWARD STRING_SEARCH_DIRECTION::BACKWARD

typedef STRING_SEARCH_CASE_SENSITIVITY Sensitivity;
typedef STRING_SEARCH_DIRECTION Direction;

namespace
{
	QBool isSensitive(Sensitivity sensitivity)
	{
		return sensitivity == STR_SENSITIVE;
	}
	QBool isInsensitive(Sensitivity sensitivity)
	{
		return sensitivity == STR_INSENSITIVE;
	}
	QBool isForward(Direction direction)
	{
		return direction == STR_FORWARD;
	}
	QBool isBackward(Direction direction)
	{
		return direction == STR_BACKWARD;
	}
}

template<typename T, typename A>
class Basic_String;

template<typename T, typename A>
std::ostream& operator<<(std::ostream&, const Basic_String<T, A>&);

template<typename T = Char8, typename A = MAllocator>
class Basic_String
	: public QAuxiliary<T, A>
{
public:
	typedef A Allocator;
	typedef Basic_String<T, A> Container;
	typedef Value Character;
	typedef Pointer Index;
	typedef Pointer String;

	//typedef std::function<int(Character*, Character*, size_t)> CharChecker;
	typedef std::function<QBool(Character, Character)> CharChecker;
	typedef std::function<int(const Character*, const Character*, size_t)> StrChecker;

	typedef BidirectionalArrayIterator<Character> Iterator;
	typedef BidirectionalArrayIterator<const Character> ConstIterator;
	typedef ReverseArrayIterator<Character> ReverseIterator;
	typedef ReverseArrayIterator<const Character> ConstReverseIterator;

	static const Basic_String EMPTY_STRING;

	Basic_String(size_t length = DEFAULT_STRING_SIZE);
	Basic_String(const String string);
	Basic_String(const Index begin, const Index end);
	Basic_String(const Iterator begin, const Iterator end);
	Basic_String(const Basic_String& string);
	Basic_String(std::ifstream& istream);

	~Basic_String();

	void pushBack(Character ch);
	//void pushBack(const Character* string);
	//void pushBack(const Basic_String& string);
	Reference front() const;
	Reference back() const;

	void concat(const Character* string);
	void concat(const Basic_String& string);

	Basic_String substring(size_t start) const;
	Basic_String substring(size_t begin, size_t end) const;
	Basic_String substring(const Iterator iterator) const;
	Basic_String substring(const Iterator begin, const Iterator end) const;

	Iterator find(Character ch, Sensitivity sensitivty = STR_SENSITIVE) const;
	//Iterator find(const String string, Sensitivity sensitivty = STR_SENSITIVE) const;
	//Iterator find(const Basic_String& string, Sensitivity sensitivty = STR_SENSITIVE) const;

	QBool has(Character ch, Sensitivity sensitivity = STR_SENSITIVE) const;
	QBool has(const Character* string, Sensitivity sensitivity = STR_SENSITIVE) const;
	QBool has(const Basic_String& string, Sensitivity sensitivity = STR_SENSITIVE) const;

	QBool is(CharacterFilter filter, CharacterFilter exception = BLANK_FILTER) const;
	QBool is(size_t index, CharacterFilter filter, CharacterFilter exception = BLANK_FILTER) const;
	QBool is(size_t begin, size_t end, CharacterFilter filter, CharacterFilter exception = BLANK_FILTER) const;
	QBool is(const Iterator iterator, CharacterFilter filter, CharacterFilter exception = BLANK_FILTER) const;
	QBool is(const Iterator begin, const Iterator end, CharacterFilter filter, CharacterFilter exception = BLANK_FILTER) const;

	void to(CharacterConverter converter);
	void to(size_t index, CharacterConverter converter);
	void to(size_t begin, size_t end, CharacterConverter converter);

	//String reverse() const;
	//void revert();
	void copy(const String string);
	void copy(const Basic_String& string);
	void swap(String string);
	void swap(Basic_String& other);
	void reserve(size_t maxSize);
	void shrink(size_t maxSize);
	void clear();
	void pack();

	QBool equals(const String other) const;
	QBool equals(const Basic_String& other) const;

	QBool isEmpty() const;
	QBool isFull() const;

	int32 toInt32() const;
	//uint32 toUnsignedInt() const;
	//size_t toSize_t() const;
	//float32 toFloat32() const;
	float64 toFloat64() const;
	const String toCString() const;

	Reference at(size_t index) const;
	Reference operator[](size_t index) const;

	Basic_String operator+(const Character* string);
	Basic_String operator+(const Basic_String& string);
	Basic_String operator+=(const Character* string);
	Basic_String operator+=(const Basic_String& string);
	Basic_String operator*(size_t times);
	Basic_String operator*=(size_t times);
	void operator=(const String string);
	void operator=(const Container& other);

	operator bool() const;
	QBool operator==(const Character* other) const;
	QBool operator!=(const Character* other) const;
	QBool operator<(const Character* other) const;
	QBool operator<=(const Character* other) const;
	QBool operator>(const Character* other) const;
	QBool operator>=(const Character* other) const;

	QBool operator==(const Basic_String& other) const;
	QBool operator!=(const Basic_String& other) const;
	QBool operator<(const Basic_String& other) const;
	QBool operator<=(const Basic_String& other) const;
	QBool operator>(const Basic_String& other) const;
	QBool operator>=(const Basic_String& other) const;

	friend std::ostream& operator<< <>(std::ostream& os, const Basic_String& string);
	void operator<<(std::ifstream& input);

	const Iterator begin() const;
	const Iterator end() const;
	const ConstIterator cbegin() const;
	const ConstIterator cend() const;
	const ReverseIterator rbegin() const;
	const ReverseIterator rend() const;
	const ConstReverseIterator crbegin() const;
	const ConstReverseIterator crend() const;

	size_t length() const;
	size_t maxLength() const;
	size_t size() const;
	size_t maxSize() const;
	ALLOCATOR_ID allocatorID() const;
private:
	void _setLength(size_t len);
	void _setMaxLength(size_t max);
	void _incrementLength();
	void _decrementLength();
	void _addLength(size_t amount);
	void _subtractLength(size_t amount);

	QBool _hasSpaceFor(size_t num) const;
	void _setTerminatingZero(size_t index);

	QBool _checkIndex(size_t index) const;
	QBool _checkIndicies(size_t begin, size_t end) const;

	QBool _checkIterator(const Iterator iterator) const;
	QBool _checkIterators(const Iterator begin, const Iterator end) const;

	QBool _checkReverseIterator(const ReverseIterator iterator) const;
	QBool _checkReverseIterators(const ReverseIterator begin, const ReverseIterator end) const;

	Comparison _compare(const Character* A, const Character* B, size_t length, const CharChecker& checker) const;

	template<typename TIterator>
	QBool _comesBefore(TIterator begin, TIterator end) const;

	CharChecker _getCharChecker(Sensitivity sensitivity) const;
	StrChecker _getStrChecker(Sensitivity Sensitivity) const;
	size_t _getSearchBegin(Direction direction) const;
	size_t _getSearchEnd(Direction direction) const;
	QBool _endNotReached(size_t index, size_t end, Direction direction) const;
	size_t _increment(size_t traversed, Direction direction) const;

	/*Raw string*/
	String _string;
	/*String length*/
	size_t _length;
	/*Maximum length*/
	size_t _maxLength;
	/*Memory Allocator*/
	Allocator _allocator;
};

template<typename T, typename A>
using Str_Iterator = typename Basic_String<T, A>::Iterator;

template<typename T, typename A>
using Str_ConstIterator = typename Basic_String<T, A>::ConstIterator;

template<typename T, typename A>
using Str_ReverseIterator = typename Basic_String<T, A>::ReverseIterator;

template<typename T, typename A>
using Str_ConstReverseIterator = typename Basic_String<T, A>::ConstReverseIterator;

template<typename T, typename A>
using Str_Reference = typename Basic_String<T, A>::Reference;

template<typename T, typename A>
using Str_Pointer = typename Basic_String<T, A>::Pointer;

template<typename T, typename A>
using Str_Value = typename Basic_String<T, A>::Value;

template<typename T, typename A>
using Str_Character = typename Basic_String<T, A>::Character;

template<typename T, typename A>
using Str_String = typename Basic_String<T, A>::String;

template<typename T, typename A>
using Str_Index = typename Basic_String<T, A>::Index;

template<typename T, typename A>
using Str_CharChecker = typename Basic_String<T, A>::CharChecker;

template<typename T, typename A>
using Str_StrChecker = typename Basic_String<T, A>::StrChecker;

typedef Basic_String<Char8>		String;
typedef Basic_String<Char16>	String_16;
typedef Basic_String<Char32>	String_32;
typedef Basic_String<WChar>		WString;
typedef Basic_String<WChar>		TString;

#include "../Source/string.inl"