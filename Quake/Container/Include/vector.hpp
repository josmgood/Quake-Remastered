#pragma once

#include "base.hpp"
#include "iterator.hpp"

#include "ccontainers.h"

#include "..\..\Memory\Include\Allocator\pool_allocator.hpp"
#include "..\..\Memory\Include\Allocator\mallocator.h"

#define VECTOR_RESERVE_SIZE 5

template<typename T, typename A = MAllocator>
class Vector
	: public QAuxiliary<T, A>
{
public:
	typedef A Allocator;
	typedef BidirectionalArrayIterator<T> Iterator;
	typedef BidirectionalArrayIterator<const T> ConstIterator;
	typedef ReverseArrayIterator<T> ReverseIterator;
	typedef ReverseArrayIterator<const T> ConstReverseIterator;

	typedef Vector<T, A> Container;
	typedef CArray<T> cArray;
	typedef Pointer Array;

	static const Value EMPTY_VALUE;

	Vector(size_t maxSize = DEFAULT_CONTAINER_SIZE);
	Vector(const Container& container);
	~Vector();

	void pushBack(ConstReference reference);
	void popBack();

	Reference front() const;
	Reference back() const;

	Iterator find(ConstReference reference) const;
	QBool has(ConstReference reference) const;
	void erase(const Iterator iterator);
	void erase(const Iterator begin, const Iterator end);

	void copy(const Container& container);
	void swap(Container& container);
	void reserve(size_t maxSize);
	void shrink(size_t maxSize);
	void clear();

	QBool isEmpty() const;
	QBool isFull() const;

	Reference at(size_t index) const;
	Reference operator[](size_t index) const;

	void operator=(const Container& other);

	QBool equals(const Container& other) const;

	operator bool() const;
	QBool operator==(const Container& other) const;
	QBool operator!=(const Container& other) const;
	QBool operator<(const Container& other) const;
	QBool operator<=(const Container& other) const;
	QBool operator>(const Container& other) const;
	QBool operator>=(const Container& other) const;

	const Iterator begin() const;
	const Iterator end() const;
	const ConstIterator cbegin() const;
	const ConstIterator cend() const;
	const ReverseIterator rbegin() const;
	const ReverseIterator rend() const;
	const ConstReverseIterator crbegin() const;
	const ConstReverseIterator crend() const;

	size_t size() const;
	size_t maxSize() const;
	const Allocator& allocator() const;
	ALLOCATOR_ID allocatorID() const;
private:
	QBool _hasSpaceFor(size_t size) const;
	void _setMaxSize(size_t max);
	void _incrementSize();
	void _decrementSize();
	Array _allocateArray(size_t size);
	void _deallocateArray(Array array, size_t size);

	QBool _checkIndex(size_t index) const;

	Array _array;
	size_t _size;
	size_t _maxSize;
	Allocator _allocator;
};

template<typename T, typename A>
using Vec_Iterator = typename Vector<T, A>::Iterator;

template<typename T, typename A>
using Vec_ConstIterator = typename Vector<T, A>::ConstIterator;

template<typename T, typename A>
using Vec_ReverseIterator = typename Vector<T, A>::ReverseIterator;

template<typename T, typename A>
using Vec_ConstReverseIterator = typename Vector<T, A>::ConstReverseIterator;

template<typename T, typename A>
using Vec_Reference = typename Vector<T, A>::Reference;

template<typename T, typename A>
using Vec_ConstReference = typename Vector<T, A>::ConstReference;

template<typename T, typename A>
using Vec_Pointer = typename Vector<T, A>::Pointer;

template<typename T, typename A>
using Vec_Value = typename Vector<T, A>::Value;

template<typename T, typename A>
using Vec_Allocator = typename Vector<T, A>::Allocator;

template<typename T, typename A>
using Vec_Container = typename Vector<T, A>::Container;

template<typename T, typename A>
using Vec_CArray = typename Vector<T, A>::cArray;

template<typename T, typename A>
using Vec_Array = typename Vector<T, A>::Array;

#include "..\Source\vector.inl"