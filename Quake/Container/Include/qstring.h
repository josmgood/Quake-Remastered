#pragma once

#include <iostream>
#include <functional>
#include <string.h>

#include "base.hpp"
#include "iterator.hpp"

#include "..\..\Auxiliary\Include\string_aux.h"
#include "..\..\Auxiliary\Include\algorithm.h"

#include "..\..\Math\Include\math.h"

#define DEFAULT_STRING_SIZE	32

enum class STRING_SEARCH_CASE_SENSITIVITY
{
	SENSITIVE = 0,
	INSENSITIVE = 1
};

#define STR_SENSITIVE STRING_SEARCH_CASE_SENSITIVITY::SENSITIVE
#define STR_INSENSITIVE STRING_SEARCH_CASE_SENSITIVITY::INSENSITIVE

typedef STRING_SEARCH_CASE_SENSITIVITY Sensitivity;

QBool isSensitive(Sensitivity sensitivity);
QBool isInsensitive(Sensitivity sensitivity);

/*
class QWString
	: public QAuxiliary<wchar_t, void>*/

class QString
	: public QAuxiliary<char, void>
{
public:
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

	QString(size_t length = DEFAULT_STRING_SIZE);
	QString(const Character* string);
	QString(const Character* begin, const Character* end);
	QString(const Iterator begin, const Iterator end);
	QString(const QString& string);

	~QString();

	void pushFront(Character ch);
	void pushFront(const Character* string);
	void pushFront(const QString& string);
	void setFront(Character ch);
	void setFront(const Character* string);
	void setFront(const QString& string);
	Reference getFront() const;

	void pushBack(Character ch);
	void pushBack(const Character* string);
	void pushBack(const QString& string);
	void setBack(Character ch);
	void setBack(const Character* string);
	void setBack(const QString& string);
	Reference getBack() const;

	void concat(const Character* string);
	void concat(const QString& string);

	void insert(size_t index, Character ch);
	void insert(size_t egin, size_t end, const Character* string);
	void insert(size_t begin, size_t end, const QString& string);

	void insert(const Iterator iterator, Character ch);
	void insert(const Iterator begin, const Iterator end, const Character* string);
	void insert(const Iterator begin, const Iterator end, const QString& string);

	void append(size_t index, Character ch);
	void append(size_t begin, size_t end, const QString& string);

	void set(size_t index, Character ch);
	void set(size_t begin, size_t end, const Character* string);
	void set(size_t begin, size_t end, const QString& string);
	void set(Iterator iterator, Character ch);
	void set(Iterator begin, Iterator end, const Character* string);
	void set(Iterator begin, Iterator end, const QString& string);

	QString substring(size_t index) const;
	QString substring(size_t begin, size_t end) const;
	QString substring(const Iterator iterator) const;
	QString substring(const Iterator begin, const Iterator end) const;

	Iterator find(Character ch, size_t buffer = 1, Sensitivity sensitivty = STR_SENSITIVE) const;
	Iterator find(const Character* string, size_t buffer = 1, Sensitivity sensitivty = STR_SENSITIVE) const;
	Iterator find(const QString& string, size_t buffer = 1, Sensitivity sensitivty = STR_SENSITIVE) const;

	ReverseIterator rfind(Character ch, Sensitivity sensitivity = STR_SENSITIVE) const;
	ReverseIterator rfind(const Character* string, Sensitivity sensitivity = STR_SENSITIVE) const;
	ReverseIterator rfind(const QString& string, Sensitivity sensitivity = STR_SENSITIVE) const;

	/*Iterator findnth(Character ch, size_t buffer, Sensitivity sensitivity = STR_SENSITIVE) const;
	Iterator findnth(const Character* string, size_t buffer, Sensitivity sensitivity = STR_SENSITIVE) const;
	Iterator findnth(const QString& string, size_t buffer, Sensitivity sensitivity = STR_SENSITIVE) const;*/

	/*ReverseIterator rfindnth(Character ch, size_t buffer, Sensitivity sensitivity = STR_SENSITIVE) const;
	ReverseIterator rfindnth(const Character* string, size_t buffer, Sensitivity sensitivity = STR_SENSITIVE) const;
	ReverseIterator rfindnth(const QString& string, size_t buffer, Sensitivity sensitivity = STR_SENSITIVE) const;*/

	Iterator findLast(Character ch, Sensitivity sensitivity = STR_SENSITIVE) const;
	Iterator findLast(const Character* string, Sensitivity sensitivity = STR_SENSITIVE) const;
	Iterator findLast(const QString& string, Sensitivity sensitivity = STR_SENSITIVE) const;

	QBool has(Character ch, Sensitivity sensitivity = STR_SENSITIVE) const;
	QBool has(const Character* string, Sensitivity sensitivity = STR_SENSITIVE) const;
	QBool has(const QString& string, Sensitivity sensitivity = STR_SENSITIVE) const;

	QBool rhas(Character ch, Sensitivity sensitivity = STR_SENSITIVE) const;
	QBool rhas(const Character* string, Sensitivity sensitivity = STR_SENSITIVE) const;
	QBool rhas(const QString& stirng, Sensitivity sensitivity = STR_SENSITIVE) const;

	size_t occurances(Character ch, Sensitivity sensitivity = STR_SENSITIVE) const;
	size_t occurances(const Character* string, Sensitivity sensitivity = STR_SENSITIVE) const;
	size_t occurances(const QString& string, Sensitivity sensitivity = STR_SENSITIVE) const;

	QBool is(CharacterFilter filter, CharacterFilter exception = BLANK_FILTER) const;
	QBool is(size_t index, CharacterFilter filter, CharacterFilter exception = BLANK_FILTER) const;
	QBool is(size_t begin, size_t end, CharacterFilter filter, CharacterFilter exception = BLANK_FILTER) const;
	QBool is(const Iterator iterator, CharacterFilter filter, CharacterFilter exception = BLANK_FILTER) const;
	QBool is(const Iterator begin, const Iterator end, CharacterFilter filter, CharacterFilter exception = BLANK_FILTER) const;

	QBool ris(size_t index, CharacterFilter filter, CharacterFilter exception = BLANK_FILTER) const;
	QBool ris(size_t begin, size_t end, CharacterFilter filter, CharacterFilter exception = BLANK_FILTER) const;
	QBool ris(const ReverseIterator iterator, CharacterFilter filter, CharacterFilter exception = BLANK_FILTER) const;
	QBool ris(const ReverseIterator begin, const ReverseIterator end, CharacterFilter filter, CharacterFilter exception = BLANK_FILTER) const;

	void to(CharacterConverter converter);
	void to(size_t index, CharacterConverter converter);
	void to(size_t begin, size_t end, CharacterConverter converter);
	void to(const Iterator iterator, CharacterConverter converter);
	void to(const Iterator begin, const Iterator end, CharacterConverter converter);

	void rto(size_t index, CharacterConverter converter);
	void rto(size_t begin, size_t end, CharacterConverter converter);
	void rto(const ReverseIterator iterator, CharacterConverter converter);
	void rto(const ReverseIterator begin, const ReverseIterator end, CharacterConverter converter);

	void copy(const Character* string);
	void copy(const QString& string);
	void reserve(size_t size);
	void clear();

	QBool equals(const Character* other) const;
	QBool equals(const QString& other) const;

	QBool isEmpty() const;
	QBool isFull() const;
	void pack();
	void swap(QString& other);

	int32 toInt32() const;
	//uint32 toUnsignedInt() const;
	//size_t toSize_t() const;
	//float32 toFloat32() const;
	float64 toFloat64() const;
	const Character* toCString() const;

	Reference at(size_t index) const;
	Reference operator[](size_t index) const;

	//void operator=(const char* string);
	//void operator(const QString& string);
	QString operator+(const Character* string);
	QString operator+(const QString& string);
	QString operator+=(const Character* string);
	void operator+=(const QString& string);
	QString operator*(size_t times);
	void operator*=(size_t times);
	void operator=(const Character* string);
	void operator=(const QString& string);

	operator bool() const;
	QBool operator==(const Character* other) const;
	QBool operator!=(const Character* other) const;
	QBool operator<(const Character* other) const;
	QBool operator<=(const Character* other) const;
	QBool operator>(const Character* other) const;
	QBool operator>=(const Character* other) const;

	QBool operator==(const QString& other) const;
	QBool operator!=(const QString& other) const;
	QBool operator<(const QString& other) const;
	QBool operator<=(const QString& other) const;
	QBool operator>(const QString& other) const;
	QBool operator>=(const QString& other) const;

	friend std::ostream& operator<<(std::ostream& os, const QString& string);

	const Iterator getBegin() const;
	const Iterator getEnd() const;
	const ConstIterator getCBegin() const;
	const ConstIterator getCEnd() const;
	const ReverseIterator getRBegin() const;
	const ReverseIterator getREnd() const;
	const ConstReverseIterator getCRBegin() const;
	const ConstReverseIterator getCREnd() const;

	size_t getLength() const;
	size_t getMaxLength() const;
	size_t getSize() const;
	size_t getMaxSize() const;
private:
	struct Comparison
	{
		Comparison(size_t trav, QBool equal);
		size_t traversed;
		QBool isEqual;
	};

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
	QBool _comesBefore(TIterator begin, TIterator end) const
	{
		return begin <= end;
	}

	CharChecker _getCharChecker(Sensitivity sensitivity) const;
	StrChecker _getStrChecker(Sensitivity Sensitivity) const;

	/*Raw string*/
	String _string;
	/*String length*/
	size_t _length;
	/*Maximum length*/
	size_t _maxLength;
	/*Memory Allocator*/
	//Allocator _allocator;
};

static const QString EMPTY_STRING((size_t)0);