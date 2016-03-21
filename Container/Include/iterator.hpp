#pragma once

#include <iostream>

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
	virtual Reference operator*() const = 0;
	virtual Pointer ptr() const = 0;
	virtual Reference get() const = 0;

	QBool operator==(Iterator other) const;
	QBool operator!=(Iterator other) const;
	QBool operator<(Iterator other) const;
	QBool operator<=(Iterator other) const;
	QBool operator>(Iterator other) const;
	QBool operator>=(Iterator other) const;

	void set(const Pointer ptr);
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
	: public BidirectionalIterator<Type, BidirectionalNodeIterator>
{
public:
	BidirectionalArrayIterator();
	BidirectionalArrayIterator(const Pointer ptr);

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
//
////=======================================================================================
//
//template<typename TIterator, 
//	typename Type>
//class ReverseIterator
//	: public IteratorBase<, Type>
//{
//public:
//	ReverseIterator();
//	ReverseIterator(const Pointer ptr);
//
//	virtual Iterator next() const = 0;
//	virtual Iterator prev() const = 0;
//	virtual Reference operator*() const = 0;
//	virtual Pointer ptr() const = 0;
//	virtual Reference get() const = 0;
//
//	virtual Iterator operator+(int itrs) = 0;
//	virtual void operator+=(int itrs) = 0;
//	virtual Iterator operator++() = 0;
//
//	virtual Iterator operator-(int itrs) = 0;
//	virtual void operator-=(int itrs) = 0;
//	virtual Iterator operator--() = 0;
//};
//
//template<typename TIterator, 
//	typename Type>
//class ReverseNodeIterator
//	: public ReverseIterator<TIterator, Type>
//{
//public:
//	ReverseNodeIterator();
//	ReverseNodeIterator(const Pointer ptr);
//
//	Iterator next() const override;
//	Iterator prev() const override;
//	Reference operator*() const override;
//	Pointer ptr() const override;
//	Reference get() const override;
//
//	Iterator operator+(int itrs) override;
//	void operator+=(int itrs) override;
//	Iterator operator++() override;
//
//	Iterator operator-(int itrs) override;
//	void operator-=(int itrs) override;
//	Iterator operator--() override;
//};
//
//template<typename TIterator, 
//	typename Type>
//class ReverseArrayIterator
//	: public ReverseIterator<TIterator, Type>
//{
//public:
//	ReverseArrayIterator();
//	ReverseArrayIterator(const Pointer ptr);
//
//	Iterator next() const override;
//	Iterator prev() const override;
//	Reference operator*() const override;
//	Pointer ptr() const override;
//	Reference get() const override;
//
//	Iterator operator+(int itrs) override;
//	void operator+=(int itrs) override;
//	Iterator operator++() override;
//
//	Iterator operator-(int itrs) override;
//	void operator-=(int itrs) override;
//	Iterator operator--() override;
//};

//typedef BidirectionalIterator<int> IntIterator;

#include "..\Source\iterator.inl"