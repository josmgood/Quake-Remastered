#pragma once

#include <iostream>

#include "base.hpp"
#include "iterator.hpp"

#include "..\..\Auxiliary\Include\string_aux.h"
#include "..\..\Auxiliary\Include\algorithm.h"

#include "..\..\Math\Include\math.h"

#include "..\..\Memory\Include\Allocator\pool_allocator.hpp"

#define DEFAULT_STRING_SIZE		32
#define EMPTY_STRING QString(nullptr);
#define BAD_INDEX 0

enum class STRING_SEARCH_CASE_SENSITIVITY
{
	SENSITIVE = 0,
	UNSENSITIVE = 1
};

enum class STRING_SEARCH_DIRECTION
{
	FORWARD = 0,
	BACKWARD = 1
};

#define STR_FORWARD STRING_SEARCH_DIRECTION::FORWARD
#define STR_BACKWARD STRING_SEARCH_DIRECTION::BACKWARD
#define STR_SENSITIVE STRING_SEARCH_CASE_SENSITIVITY::SENSITIVE
#define STR_UNSENSITIVE STRING_SEARCH_CASE_SENSITIVITY::UNSENSITIVE

typedef STRING_SEARCH_CASE_SENSITIVITY Sensitivity;
typedef STRING_SEARCH_DIRECTION Direction;

QBool isForward(Direction dir);
QBool isBackward(Direction dir);

QBool isSensitive(Sensitivity sensitivity);
QBool isUnsensitivity(Sensitivity sensitivity);

class QString
	: public QAuxiliary<char, int>
{
public:
	typedef Value Character;
	typedef Pointer Index;
	typedef Pointer String;

	typedef BidirectionalArrayIterator<Character> Iterator;
	typedef BidirectionalArrayIterator<const Character> ConstIterator;
	typedef ReverseArrayIterator<Character> ReverseIterator;
	typedef ReverseArrayIterator<const Character> ConstReverseIterator;

	QString(size_t length = DEFAULT_STRING_SIZE);
	QString(const char* string);
	QString(const QString& string);

	~QString();

	void pushFront(Character ch);
	void setFront(Character ch);
	Reference getFront() const;

	void pushBack(Character ch);
	void setBack(Character ch);
	Reference getBack() const;

	void concat(const char* string);
	void concat(const QString& string);
	void insert(size_t index, Character ch);
	void insert(size_t begin, size_t end, const QString& string);
	void append(size_t index, Character ch);
	void append(size_t begin, size_t end, const QString& string);
	void set(size_t index, Character ch);
	void set(size_t begin, size_t end, const char* string);

	QString substring(size_t begin);
	QString substring(size_t begin, size_t end);
	//QString substring();

	Iterator find(Character ch, Sensitivity sensitivty = STR_SENSITIVE, Direction dir = STR_FORWARD) const;
	Iterator find(const char* string, Sensitivity sensitivty = STR_SENSITIVE, Direction dir = STR_FORWARD) const;
	Iterator find(const QString& string, Sensitivity sensitivty = STR_SENSITIVE, Direction dir = STR_FORWARD) const;

	Iterator findLast(Character ch, Sensitivity sensitivity = STR_SENSITIVE, Direction dir = STR_FORWARD) const;
	Iterator findLast(const char* string, Sensitivity sensitivity = STR_SENSITIVE, Direction dir = STR_FORWARD) const;
	Iterator findLast(const QString& string, Sensitivity sensitivity = STR_SENSITIVE, Direction dir = STR_FORWARD) const;

	QBool has(Character ch, Sensitivity sensitivity = STR_SENSITIVE, Direction dir = STR_FORWARD) const;
	QBool has(const char* string, Sensitivity sensitivity = STR_SENSITIVE, Direction dir = STR_FORWARD) const;
	QBool has(const QString& string, Sensitivity sensitivity = STR_SENSITIVE, Direction dir = STR_FORWARD) const;

	size_t occurance(Character ch, Sensitivity sensitivity = STR_SENSITIVE, Direction dir = STR_FORWARD) const;
	size_t occurance(const char* string, Sensitivity sensitivity = STR_SENSITIVE, Direction dir = STR_FORWARD) const;
	size_t occurance(const QString& string, Sensitivity sensitivity = STR_SENSITIVE, Direction dir = STR_FORWARD) const;

	QBool isAlpha() const;
	QBool isAlpha(size_t index) const;
	QBool isAlpha(size_t begin, size_t end) const;
	QBool isAlpha(Iterator iterator) const;
	QBool isAlpha(Iterator begin, Iterator end) const;

	QBool isNumeric() const;
	QBool isNumeric(size_t index) const;
	QBool isNumeric(Iterator iterator) const;
	QBool isNumeric(size_t ibegin, size_t iend) const;
	QBool isNumeric(Iterator begin, Iterator end) const;

	QBool isSpace(size_t index) const;
	QBool isSpace(Iterator iterator) const;
	QBool isSpace(size_t ibegin, size_t iend) const;
	QBool isSpace(Iterator begin, Iterator end) const;

	QString toUpper() const;
	void setUpper();
	void setUpper(size_t index);
	void setUpper(Iterator iterator);
	void setUpper(size_t ibegin, size_t iend);
	void setUpper(Iterator begin, Iterator end);

	QString toLower() const;
	void setLower();
	void setLower(size_t index);
	void setLower(Iterator iterator);
	void setLower(size_t ibegin, size_t iend);
	void setLower(Iterator begin, Iterator end);

	void copy(const QString& string);

	void reserve(size_t size);
	void clear(size_t index);
	void clear(Iterator iterator);
	void clear(size_t ibegin, size_t iend);
	void clear(Iterator begin, Iterator end);
	void clear();
	QBool isEmpty() const;
	QBool isFull() const;
	void pack();
	void swap(QString& other);

	Reference at(size_t index) const;
	QString at(size_t begin, size_t end) const;
	Reference nAt(size_t index) const;
	QString nAt(size_t begin, size_t end) const;
	Reference operator[](size_t index) const;

	QString operator+(const char* string);
	QString operator+(const QString& string);
	QString operator+=(const char* string);
	void operator+=(const QString& string);
	QString operator*(size_t times);
	void operator*=(size_t times);
	void operator=(const char* string);
	void operator=(const QString& string);

	friend std::ostream& operator<<(std::ostream& os, const QString& string);

	const Iterator getBegin() const;
	const Iterator getEnd() const;
	const ReverseIterator getRBegin() const;
	const ReverseIterator getREnd() const;

	size_t getLength() const;
	size_t getMaxLength() const;
	size_t getSize() const;
	size_t getMaxSize() const;
private:
	void _setLength(size_t len);

	QBool _checkIndex(size_t index) const;
	QBool _checkIndicies(size_t begin, size_t end) const;

	QBool _checkIterator(Iterator iterator) const;
	QBool _checkIterators(Iterator begin, Iterator end) const;

	QBool _checkReverseIterator(ReverseIterator iterator) const;
	QBool _checkReverseIterators(ReverseIterator begin, ReverseIterator end) const;

	template<typename TIterator>
	QBool _comesBefore(TIterator begin, TIterator end) const
	{
		return begin <= end;
	}

	void _incrementLength();
	void _decrementLength();

	/*Raw string*/
	String _string;
	/*String length*/
	size_t _length;
	/*Maximum length*/
	size_t _maxLength;
	/*Memory Allocator*/
	//Allocator _allocator;
};