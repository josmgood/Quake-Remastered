#pragma once

#include <iostream>

#include "base.hpp"

#include "..\..\Auxiliary\Include\algorithm.h"

#include "..\..\Memory\Include\Allocator\mallocator.h"
#include "..\..\Memory\Include\Allocator\pool_allocator.hpp"

template<typename Type,
	typename TAllocator>
class QStack;

template<typename Type,
	typename TAllocator>
std::ostream& operator<<(std::ostream&, const QStack<Type, TAllocator>&);

template<typename Type,
	typename TAllocator = MAllocator>
class QStack
	: public QAuxiliary<Type, TAllocator>
{
public:
	struct Node
	{
		Node(ConstReference dat);
		void set(ConstReference dat);

		Node* getNext() const;
		Node* getPrev() const;

		void setNext(Node* nxt);
		void setPrev(Node* prv);

		Type data;
		Node* next;
		Node* prev;
	};

	QStack(size_t maxSize = DEFAULT_CONTAINER_SIZE);
	QStack(const Pointer array_ptr, size_t size);
	QStack(const QStack& other);
	~QStack();

	void set(ConstReference reference);
	void push(ConstReference reference);
	void push(const Pointer array_ptr, size_t size);
	void push(const QStack& other);
	void pop(size_t amount);
	void pop();
	Value take();
	ConstReference peek() const;

	QStack reversed() const;
	void reverse();
	void clear();
	void copy(const QStack& other);
	void swap(QStack& other);
	void resize(size_t maxSize);

	QBool equals(const QStack& other) const;

	QBool isEmpty() const;
	QBool isFull() const;

	QStack operator+(const QStack& other);
	QStack operator+=(const QStack& other);
	void operator=(const QStack& other);

	operator bool() const;
	QBool operator==(const QStack& other) const;
	QBool operator!=(const QStack& other) const;
	QBool operator<(const QStack& other) const;
	QBool operator<=(const QStack& other) const;
	QBool operator>(const QStack& other) const;
	QBool operator>=(const QStack& other) const;

	friend std::ostream& operator<< <>(std::ostream&, const QStack& stack);

	size_t getSize() const;
	size_t getMaxSize() const;

	static const QStack<Type, TAllocator> EMPTY_STACK;
private:
	void _setSize(size_t size);
	void _setMaxSize(size_t max);
	void _incrementSize();
	void _decrementSize();
	void _addSize(size_t amount);
	void _subtractSize(size_t amount);

	QBool _hasSpaceFor(size_t num) const;
	void _initBounds(ConstReference reference);

	Node* _top;
	Node* _bottom;
	size_t _size;
	size_t _maxSize;
	Allocator _allocator;
};

template<typename Type,
	typename TAllocator>
using Stk_Reference = typename QStack<Type, TAllocator>::Reference;

template<typename Type,
	typename TAllocator>
using Stk_ConstReference = typename QStack<Type, TAllocator>::ConstReference;

template<typename Type,
	typename TAllocator>
using Stk_Pointer = typename QStack<Type, TAllocator>::Pointer;

template<typename Type,
	typename TAllocator>
using Stk_Value = typename QStack<Type, TAllocator>::Value;

template<typename Type,
	typename TAllocator>
using Stk_Node = typename QStack<Type, TAllocator>::Node*;

#include "..\Source\qstack.inl"