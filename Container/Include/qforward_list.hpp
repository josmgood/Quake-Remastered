#pragma once

/*Standard Library*/
#include <iostream>

/*Custom Library*/
#include "..\..\Memory\Allocators\Include\pool_allocator.hpp"

template<typename T>
class QForwardList
{
public:
	struct _Node
	{
		_Node(void);
		_Node(const T& data);

		_Node*	next;
		T		data;
	};
	QForwardList				(size_t capacity);
	QForwardList				(void);
	~QForwardList				(void);

	void pushFront				(const T& data);
	void pushBack				(const T& data);
	void popFront				(void);
	void popBack				(void);

	void insert					(const T& data, _Node* next);
	void append					(const T& data, _Node* prev);
	bool find					(const T& data);
	void erase					(_Node* node);
	void reserve				(size_t amount);
	void clear					(void);
	bool isEmpty				(void) const;

	const T& getFront			(void) const;
	const T& getBack			(void) const;
private:
	_Node* _create				(const T& data);
	Block _getBlock				(_Node* node);
	_Node* _getNext				(_Node* node);
	void _setNext				(_Node* curr, _Node* _next);
	void _incrementSize			(void);
	void _decrementSize			(void);

	_Node*								_front;
	_Node*								_back;
	size_t								_size;
	PoolAllocator<sizeof(_Node)>		_pool;
};

#include "..\Source\qforward_list.inl"