#pragma once

#include <iostream>

#include "base.hpp"

#include "..\..\Auxiliary\Include\algorithm.h"

#include "..\..\Memory\Include\Allocator\mallocator.h"
#include "..\..\Memory\Include\Allocator\pool_allocator.hpp"

template<typename Type,
	typename TAllocator>
class Stack;

template<typename Type,
	typename TAllocator>
std::ostream& operator<<(std::ostream&, const Stack<Type, TAllocator>&);

template<typename Type,
	typename TAllocator = MAllocator>
class Stack
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

	static const Stack EMPTY_STACK;
	static const Node* NULL_NODE;
	static const Value EMPTY_VALUE;

	Stack(size_t maxSize = DEFAULT_CONTAINER_SIZE);
	Stack(const Pointer array_ptr, size_t size);
	Stack(const Stack& other);
	~Stack();

	void set(ConstReference reference);
	void push(ConstReference reference);
	void push(const Stack& other);
	void pop(size_t amount);
	void pop();
	Value take();
	ConstReference peek() const;

	Stack getReversed() const;
	void reverse();
	void clear();
	void copy(const Stack& other);
	void swap(Stack& other);
	void shrink(size_t maxSize);
	void resize(size_t maxSize);

	QBool equals(const Stack& other) const;

	QBool isEmpty() const;
	QBool isFull() const;

	Stack operator+(const Stack& other);
	Stack operator+=(const Stack& other);
	void operator=(const Stack& other);

	operator bool() const;
	QBool operator==(const Stack& other) const;
	QBool operator!=(const Stack& other) const;
	QBool operator<(const Stack& other) const;
	QBool operator<=(const Stack& other) const;
	QBool operator>(const Stack& other) const;
	QBool operator>=(const Stack& other) const;

	friend std::ostream& operator<< <>(std::ostream&, const Stack& stack);

	size_t getSize() const;
	size_t getMaxSize() const;
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
using Stk_Reference = typename Stack<Type, TAllocator>::Reference;

template<typename Type,
	typename TAllocator>
using Stk_ConstReference = typename Stack<Type, TAllocator>::ConstReference;

template<typename Type,
	typename TAllocator>
using Stk_Pointer = typename Stack<Type, TAllocator>::Pointer;

template<typename Type,
	typename TAllocator>
using Stk_Value = typename Stack<Type, TAllocator>::Value;

template<typename Type,
	typename TAllocator>
using Stk_Node = typename Stack<Type, TAllocator>::Node*;

#include "..\Source\stack.inl"