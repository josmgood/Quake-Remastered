#pragma once
#include <iterator>

//struct ForwardTag {};
//struct BidirectionalTag {};
//struct RandomAccessTag {};

//template<typename TIterator>
//struct IteratorTraits
//{
//	typedef TIterator::Type Value;
//	typedef TIterator::Reference Reference;
//	typedef TIterator::Pointer Pointer;
//}

template<typename Tag, 
	typename Type, 
	typename Reference = T&, 
	typename Pointer = T*,
	size_t distance = sizeof(Pointer)>
class Iterator
{
public:

};

//template<typename Type>
//class BaseIterator
//	: public IteratorTraits<Type>
//{
//public:
//	Reference operator*() const;
//	Reference get() const;
//protected:
//	Value		_value;
//	Distance	_distance;
//};
//
//template<typename Type>
//class ForwardIterator
//	: public BaseIterator<Type>
//{
//};

template<typename Type, typename TAllocator>
class QBaseContainer
{
public:
	virtual ~QBaseContainer() {}

	virtual void insert(const Type& dat) = 0;
	virtual void append(const Type& dat) = 0;
	virtual void reserve(size_t amount) = 0;
	//virtual void erase(Iterator iterator) = 0;
	virtual void resize(size_t newSize) = 0;
	//virtual void swap(Iterator iterator, Iterator iterator) = 0;
	virtual void sort() = 0;
	virtual void reverse() = 0;
	virtual void clear() = 0;
	virtual bool isEmpty() const = 0;

	//size_t getMaxSize() const;
	//size_t getSize() const;
protected:
	size_t			_size;
	TAllocator		_allocator;
};

template<typename Type, typename TAllocator>
class QLinearContainer
	: public QBaseContainer<Type, TAllocator>
{
public:
	virtual ~QLinearContainer() {}

	virtual void pushFront(const Type& dat) = 0;
	virtual void pushBack(const Type& dat) = 0;

	virtual void popFront() = 0;
	virtual void popBack() = 0;

	virtual void insert(const Type& dat) = 0;
	virtual void append(const Type& dat) = 0;
	virtual void reserve(size_t amount) = 0;
	virtual resize(size_t newSize) = 0;
	virtual void sort() = 0;
	virtual void reverse() = 0;
	virtual void clear() = 0;
	virtual bool isEmpty() const = 0;
};

template<typename Type, typename TAllocator>
class QBaseList
	: public QLinearContainer<Type, TAllocator>
{
public:

};