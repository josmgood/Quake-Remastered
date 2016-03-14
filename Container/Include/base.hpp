#pragma once

/*
*==========================================================================
*
* NODES
*
* Pieces to node-dependent structures such as QList, QMap, and more.
* Can be singly-link, doubly-link, or irregular.
* Iterators of these classes point to the node, not the value held within.
*
*==========================================================================
*/
template<typename Type>
struct BaseNode
{
	BaseNode(const Type& dat)
		: data(dat) {}

	Type data;
};

template<typename Type>
struct ForwardListNode
	: public BaseNode<Type>
{
	ForwardListNode(const Type& dat)
		: BaseNode(dat), next(nullptr) {}

	ForwardListNode* next;
};

template<typename Type>
struct ListNode
	: public BaseNode<Type>
{
	ListNode(const Type& dat)
		: BaseNode(dat), next(nullptr), prev(nullptr) {}

	ListNode* next;
	ListNode* prev;
};

/*
*==========================================================================
*
* ITERATORS
*
* Used to generically and safely traverse a data structure.
* Universally overrides both operator++() and operator--().
* If an iterator of a node-dependent structure, _ptr points to the node.
*
*==========================================================================
*/

namespace iter
{
	struct ForwardTag {};
	struct BidirectionTag {};
	struct RandomAccessTag {};
}

/*
*==============================================
*
* ITERATOR
*
* A definition struct that allows for easy
* reference to typical iterator data types.
*
* /tparam - Range of motion of the iterator
* /tparam - Data type being redefined
*
*==============================================
*/
template<typename Tag, typename Type>
class IteratorDefs
{
public:
	typedef Type		Value;
	typedef Type&		Reference;
	typedef Type*		Pointer;
	typedef Tag			Direction;
};

/*
*===============================================
*
* BASE ITERATOR
*
* Base at which all iterators are built upon.
*
* /tparam - Range of motion of the iterator
* /tparam - Data type pointed to
*
*===============================================
*/
template<typename Tag, typename Type>
class BaseIterator
	: public IteratorDefs<Tag, Type>
{
public:
	BaseIterator(const Pointer ptr) 
		: _ptr(ptr) {}

	Reference operator*() { return(*_ptr); }

	void set(const Pointer ptr) { _ptr = ptr; }

	Pointer get() { return(_ptr); }

	bool operator==(const BaseIterator& other) 
	{ return _ptr == other._ptr; }

	bool operator!=(const BaseIterator& other) 
	{ return _ptr != other._ptr; }
protected:
	Pointer _ptr;
};

/*
*====================================================
*
* FOWARD ITERATOR
*
* Iterator that is constrained to only move forward.
*
* /tparam - Data type pointed to
*
*====================================================
*/
template<typename Type>
class ForwardIterator
	: public BaseIterator<iter::ForwardTag, Type>
{
public:
	ForwardIterator(const Pointer ptr)
		: BaseIterator(ptr) {}

	virtual ForwardIterator& operator++() = 0;
};

/*
*====================================================
*
* BIDIRECTIONAL ITERATOR
*
* Iterator that is able to move forward and backward.
*
* /tparam - Data type pointed to
*
*====================================================
*/
template<typename Type>
class BidirectionalIterator
	: public BaseIterator<iter::BidirectionTag, Type>
{
public:
	BidirectionalIterator(const Pointer ptr)
		: BaseIterator(ptr) {}

	virtual BidirectionalIterator& operator++() = 0;

	virtual BidirectionalIterator& operator--() = 0;
};

/*
*====================================================
*
* ARRAY ITERATOR
*
* Iterator used to traverse containers that are
* internally arrays. (QArray, QVector, etc...)
*
* /tparam - Data type pointed to
*
*====================================================
*/
template<typename Type>
class ArrayIterator
	: public BidirectionalIterator<Type>
{
public:
	ArrayIterator(const Pointer ptr = nullptr)
		: BidirectionalIterator(ptr) {}

	virtual ArrayIterator& operator++() override 
	{ ++_ptr; return(*this); }

	virtual ArrayIterator& operator--() override 
	{ --_ptr; return(*this); }
};

/*
*====================================================
*
* FORWARD LIST ITERATOR
*
* Iterator used to traverse a QForwardList.
* Constrained motion (only forward)
*
* /tparam - Data type pointed to
*
*====================================================
*/
template<typename Type>
class ForwardListIterator
	: public ForwardIterator<Type>
{
public:
	ForwardListIterator(const Pointer ptr)
		: ForwardIterator(ptr) {}

	virtual ForwardListIterator& operator++() override 
	{ _ptr = (!_ptr->next) ? _ptr : _ptr->next }
};

/*
*====================================================
*
* LIST ITERATOR
*
* Iterator used to traverse a QList. 
* Full range of motion (forward and backward)
*
* /tparam - Data type pointed to
*
*====================================================
*/
template<typename Type>
class ListIterator
	: public BidirectionalIterator<Type>
{
public:
	ListIterator(const Pointer ptr)
		: BidirectionalIterator(ptr) {}

	virtual BidirectionalIterator& operator++() override 
	{ _ptr = (!_ptr->next) ? _ptr : _ptr->next; }

	virtual BidirectionalIterator& operator--() override 
	{ _ptr = (!_ptr->prev) ? _ptr : _ptr->prev; }
};

#define DEFAULT_CONTAINER_SIZE 16

template<typename Type,
	typename TAllocator>
//	typename TIterator>
class QAuxiliary
{
public:
	typedef Type					Value;
	typedef Type&					Reference;
	typedef const Type&				ConstReference;
	typedef Type*					Pointer;
	typedef TAllocator				Allocator;
	//typedef TIterator				Iterator;
	//typedef TIterator				ConstIterator;
};

template<typename Type,
	typename TAllocator,
	typename TIterator,
	typename Container>
class QBaseContainer
{
public:
	typedef Type			Value;
	typedef const Type&		ConstReference;
	typedef Type&			Reference;
	typedef Type*			Pointer;
	typedef TAllocator		Allocator;
	typedef TIterator		Iterator;

	QBaseContainer(size_t size = DEFAULT_CONTAINER_SIZE)
		: _allocator(sizeof(Type) * size), _size(size){}
	virtual ~QBaseContainer() {}
	virtual void clear() = 0;
	virtual void swap(Container& other) = 0;
	virtual bool has(ConstReference value) = 0;

	const Iterator& begin() const { return(_begin); }
	const Iterator& end() const { return(_end); }

	bool isEmpty() const { return(!_size); };
	const Allocator& getAllocator() const { return(_allocator); }
	size_t getCapacity() const { return(_allocator.getCapacity()); }
	size_t getSize() const { return(_size); }
protected:
	void _incrementSize() { _size++; }
	void _decrementSize() { _size--; }
	void _setSize(size_t size) { _size = size; };
	void _clearSize() { _size = 0; }
	void _setAllocator(const Allocator& alloc) { _allocator = alloc; }

	Allocator		_allocator;
	size_t			_size;
	Iterator		_begin;
	Iterator		_end;
};

template<typename Type, 
	typename TIterator, 
	typename ConstReference = const Type&>
class Insertable
{
public:
	virtual void insert(ConstReference value, TIterator& next) = 0;
	virtual void append(ConstReference value, TIterator& prev) = 0;
};

template<typename Type,
	typename TIterator,
	typename ConstReference = const Type&>
class Searchable
{
public:
	virtual TIterator& find(ConstReference value) = 0;
};

template<typename Type, 
	typename Index = size_t,
	typename Reference = Type&,
	typename Pointer = Type*>
class Arrayable
{
public:
	typedef Pointer Array;

	Arrayable(size_t size = DEFAULT_CONTAINER_SIZE)
		: _array(new Value[size]) {}

	virtual Reference operator[](Index index) = 0;
	virtual Reference at(Index index) = 0;
protected:
	Array _array;
};

template<typename TNode>
class Listable
{
public:
	typedef TNode	Node;
	typedef TNode&	NodeRef;
	typedef TNode*	NodePtr;
};

template<typename Type,
	typename ConstReference = const Type&>
class FrontAccessible
{
public:
	virtual void pushFront(ConstReference value) = 0;
	virtual void popFront() = 0;
	virtual ConstReference getFront() const = 0;
};

template<typename Type,
	typename ConstReference = const Type&>
class BackAccessible
{
public:
	virtual void pushBack(ConstReference value) = 0;
	virtual void popBack() = 0;
	virtual ConstReference getBack() const = 0;
};

template<typename Type,
	typename Value = Type,
	typename Reference = Type&,
	typename Pointer = Type*,
	typename ConstReference = const Type&>
class Stackable
{
public:
	typedef Pointer Stack;

	Stackable()
		: _stack() {}
	virtual ConstReference getTop() const = 0;
	virtual void push(ConstReference value) = 0;
	virtual void pop() = 0;
protected:
	void _setStack(Pointer stack) { _stack = stack; }

	Stack _stack;
};

template<typename Type>
class Resizable
{
public:
	virtual void resize(size_t amount) = 0;
	virtual void reserve(size_t amount) = 0;
};

#include "..\Source\base.inl"