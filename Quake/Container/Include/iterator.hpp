#pragma once

#include <iostream>

#include "qbool.h"

#include "..\..\common.h"

typedef size_t Distance;

template<typename T,
	template<typename> typename I>
class IteratorBase
{
public:
	typedef T Value;
	typedef T& Reference;
	typedef T* Pointer;
	typedef I<T> Iterator;

	IteratorBase();
	IteratorBase(const Pointer ptr);
	IteratorBase(const Reference ref);

	virtual Reference operator*() const = 0;
	virtual Pointer ptr() const = 0;
	virtual Reference get() const = 0;

	virtual QBool operator==(Iterator other) const;
	virtual QBool operator!=(Iterator other) const;
	virtual QBool operator<(Iterator other) const;
	virtual QBool operator<=(Iterator other) const;
	virtual QBool operator>(Iterator other) const;
	virtual QBool operator>=(Iterator other) const;

	void set(const Pointer ptr);
	void set(const Reference ref);
protected:
	Pointer _ptr;
};

//=======================================================================================

template<typename T, 
	template<typename> typename I>
class ForwardIterator
	: public IteratorBase<T, I>
{
public:
	ForwardIterator();
	ForwardIterator(const Pointer ptr);
	ForwardIterator(const Reference ref);

	virtual Iterator next() const = 0;
	virtual Reference operator*() const = 0;
	virtual Pointer ptr() const = 0;
	virtual Reference get() const = 0;

	virtual Iterator operator+(int itrs) = 0;
	virtual void operator+=(int itrs) = 0;
	virtual Iterator operator++() = 0;
};

template<typename T>
class ForwardNodeIterator
	: public ForwardIterator<T, ForwardNodeIterator>
{
public:
	ForwardNodeIterator();
	ForwardNodeIterator(const Pointer ptr);
	ForwardNodeIterator(const Reference ref);

	Iterator next() const override;
	Reference operator*() const override;
	Pointer ptr() const override;
	Reference get() const override;

	Iterator operator+(int itrs) override;
	void operator+=(int itrs) override;
	Iterator operator++() override;
};

template<typename T>
class ForwardArrayIterator
	: public ForwardIterator<T, ForwardArrayIterator>
{
public:
	ForwardArrayIterator();
	ForwardArrayIterator(const Pointer ptr);
	ForwardArrayIterator(const Reference ref);

	Iterator next() const override;
	Reference operator*() const override;
	Pointer ptr() const override;
	Reference get() const override;

	Iterator operator+(int itrs) override;
	void operator+=(int itrs) override;
	Iterator operator++() override;
};

//template<typename T, template<typename T> typename I>
//using FValue = typename ForwardIterator<T, I>::Value;
//
//template<typename T, template<typename T> typename I>
//using FReference = typename ForwardIterator<T, I>::Reference;
//
//template<typename T, template<typename T> typename I>
//using FPointer = typename ForwardIterator<T, I>::Pointer;
//
//template<typename T, template<typename T> typename I>
//using FIterator = typename ForwardIterator<T, I>::Iterator;

//=======================================================================================

template<typename T,
	template<typename T> typename I>
class BidirectionalIterator
	: public IteratorBase<T, I>
{
public:
	BidirectionalIterator();
	BidirectionalIterator(const Pointer ptr);
	BidirectionalIterator(const Reference ref);

	virtual Iterator next() const = 0;
	virtual Iterator prev() const = 0;
	virtual Reference operator*() const = 0;
	virtual Pointer ptr() const = 0;
	virtual Reference get() const = 0;

	virtual Iterator operator+(int itrs) = 0;
	virtual void operator+=(int itrs) = 0;
	virtual Iterator operator++() = 0;

	virtual Iterator operator-(int itrs) = 0;
	virtual void operator-=(int itrs) = 0;
	virtual Iterator operator--() = 0;
};

template<typename T>
class BidirectionalNodeIterator
	: public BidirectionalIterator<T, BidirectionalNodeIterator>
{
public:
	BidirectionalNodeIterator();
	BidirectionalNodeIterator(const Pointer ptr);
	BidirectionalNodeIterator(const Reference ref);

	Iterator next() const override;
	Iterator prev() const override;
	Reference operator*() const override;
	Pointer ptr() const override;
	Reference get() const override;

	Iterator operator+(int itrs) override;
	void operator+=(int itrs) override;
	Iterator operator++() override;

	Iterator operator-(int itrs) override;
	void operator-=(int itrs) override;
	Iterator operator--() override;
};

template<typename T>
class BidirectionalArrayIterator
	: public BidirectionalIterator<T, BidirectionalArrayIterator>
{
public:
	BidirectionalArrayIterator();
	BidirectionalArrayIterator(const Pointer ptr);
	BidirectionalArrayIterator(const Reference ref);

	Iterator next() const override;
	Iterator prev() const override;
	Reference operator*() const override;
	Pointer ptr() const override;
	Reference get() const override;

	Iterator operator+(int itrs) override;
	void operator+=(int itrs) override;
	Iterator operator++() override;

	Iterator operator-(int itrs) override;
	void operator-=(int itrs) override;
	Iterator operator--() override;
};

//template<typename I, typename T>
//using BValue = typename BidirectionalIterator<I, T>::Value;
//
//template<typename I, typename T>
//using BReference = typename BidirectionalIterator<I, T>::Reference;
//
//template<typename I, typename T>
//using BPointer = typename BidirectionalIterator<I, T>::Pointer;
//
//template<typename I, typename T>
//using BIterator = typename BidirectionalIterator<I, T>::Iterator;

//=======================================================================================

template<typename T, 
	template<typename T> typename I>
class ReverseIterator
	: public IteratorBase<T, I>
{
public:
	ReverseIterator();
	ReverseIterator(const Pointer ptr);
	ReverseIterator(const Reference ref);

	virtual Iterator next() const = 0;
	virtual Iterator prev() const = 0;
	virtual Reference operator*() const = 0;
	virtual Pointer ptr() const = 0;
	virtual Reference get() const = 0;

	virtual Iterator operator+(int itrs) = 0;
	virtual void operator+=(int itrs) = 0;
	virtual Iterator operator++() = 0;

	virtual Iterator operator-(int itrs) = 0;
	virtual void operator-=(int itrs) = 0;
	virtual Iterator operator--() = 0;

	QBool operator<(Iterator other) const override;
	QBool operator<=(Iterator other) const override;
	QBool operator>(Iterator other) const override;
	QBool operator>=(Iterator other) const override;
};

template<typename T>
class ReverseNodeIterator
	: public ReverseIterator<T, ReverseNodeIterator>
{
public:
	ReverseNodeIterator();
	ReverseNodeIterator(const Pointer ptr);
	ReverseNodeIterator(const Reference ref);

	Iterator next() const override;
	Iterator prev() const override;
	Reference operator*() const override;
	Pointer ptr() const override;
	Reference get() const override;

	Iterator operator+(int itrs) override;
	void operator+=(int itrs) override;
	Iterator operator++() override;

	Iterator operator-(int itrs) override;
	void operator-=(int itrs) override;
	Iterator operator--() override;

	/*QBool operator<(Iterator other) const override;
	QBool operator<=(Iterator other) const override;
	QBool operator>(Iterator other) const override;
	QBool operator>=(Iterator other) const override;*/
};

template<typename T>
class ReverseArrayIterator
	: public ReverseIterator<T, ReverseArrayIterator>
{
public:
	ReverseArrayIterator();
	ReverseArrayIterator(const Pointer ptr);
	ReverseArrayIterator(const Reference ref);

	Iterator next() const override;
	Iterator prev() const override;
	Reference operator*() const override;
	Pointer ptr() const override;
	Reference get() const override;

	Iterator operator+(int itrs) override;
	void operator+=(int itrs) override;
	Iterator operator++() override;

	Iterator operator-(int itrs) override;
	void operator-=(int itrs) override;
	Iterator operator--() override;

	QBool operator<(Iterator other) const override;
	QBool operator<=(Iterator other) const override;
	QBool operator>(Iterator other) const override;
	QBool operator>=(Iterator other) const override;
};

typedef BidirectionalArrayIterator<int> IntegerIterator;
typedef BidirectionalArrayIterator<float32> FloatIterator;
typedef BidirectionalArrayIterator<float64> DoubleIterator;
typedef BidirectionalArrayIterator<char> CharacterIterator;
typedef BidirectionalArrayIterator<unsigned char> UnsignedCharacterIterator;

#include "..\Source\iterator.inl"