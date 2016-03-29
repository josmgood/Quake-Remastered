#pragma once

#include <iostream>

#include "qbool.h"

#include "..\..\common.h"

template<typename Type,
	template<typename T> typename TIterator>
class IteratorBase
{
public:
	typedef Type Value;
	typedef Type& Reference;
	typedef Type* Pointer;
	typedef TIterator<Type> Iterator;

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

template<typename Type, 
	template<typename T> typename TIterator>
class ForwardIterator
	: public IteratorBase<Type, TIterator>
{
public:
	ForwardIterator();
	ForwardIterator(const Pointer ptr);
	ForwardIterator(const Reference ref);

	virtual Iterator next() = 0;
	virtual Reference operator*() const = 0;
	virtual Pointer ptr() const = 0;
	virtual Reference get() const = 0;

	virtual Iterator operator+(int itrs) = 0;
	virtual void operator+=(int itrs) = 0;
	virtual Iterator operator++() = 0;
};

template<typename Type>
class ForwardNodeIterator
	: public ForwardIterator<Type, ForwardNodeIterator>
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

template<typename Type>
class ForwardArrayIterator
	: public ForwardIterator<Type, ForwardArrayIterator>
{
public:
	ForwardArrayIterator();
	ForwardArrayIterator(const Pointer ptr);
	ForwardArrayIterator(const Reference ref);

	Iterator next() override;
	Reference operator*() const override;
	Pointer ptr() const override;
	Reference get() const override;

	Iterator operator+(int itrs) override;
	void operator+=(int itrs) override;
	Iterator operator++() override;
};

//template<typename Type, template<typename T> typename TIterator>
//using FValue = typename ForwardIterator<Type, TIterator>::Value;
//
//template<typename Type, template<typename T> typename TIterator>
//using FReference = typename ForwardIterator<Type, TIterator>::Reference;
//
//template<typename Type, template<typename T> typename TIterator>
//using FPointer = typename ForwardIterator<Type, TIterator>::Pointer;
//
//template<typename Type, template<typename T> typename TIterator>
//using FIterator = typename ForwardIterator<Type, TIterator>::Iterator;

//=======================================================================================

template<typename Type,
	template<typename T> typename TIterator>
class BidirectionalIterator
	: public IteratorBase<Type, TIterator>
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

template<typename Type>
class BidirectionalNodeIterator
	: public BidirectionalIterator<Type, BidirectionalNodeIterator>
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

template<typename Type>
class BidirectionalArrayIterator
	: public BidirectionalIterator<Type, BidirectionalArrayIterator>
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

//template<typename TIterator, typename Type>
//using BValue = typename BidirectionalIterator<TIterator, Type>::Value;
//
//template<typename TIterator, typename Type>
//using BReference = typename BidirectionalIterator<TIterator, Type>::Reference;
//
//template<typename TIterator, typename Type>
//using BPointer = typename BidirectionalIterator<TIterator, Type>::Pointer;
//
//template<typename TIterator, typename Type>
//using BIterator = typename BidirectionalIterator<TIterator, Type>::Iterator;

//=======================================================================================

template<typename Type, 
	template<typename T> typename TIterator>
class ReverseIterator
	: public IteratorBase<Type, TIterator>
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

template<typename Type>
class ReverseNodeIterator
	: public ReverseIterator<Type, ReverseNodeIterator>
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

template<typename Type>
class ReverseArrayIterator
	: public ReverseIterator<Type, ReverseArrayIterator>
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