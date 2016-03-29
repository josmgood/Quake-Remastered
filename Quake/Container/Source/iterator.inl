#include "..\Include\iterator.hpp"

template<typename Type,
	template<typename T> typename TIterator>
IteratorBase<Type, TIterator>::IteratorBase()
	: _ptr(nullptr)
{
}

template<typename Type,
	template<typename T> typename TIterator>
IteratorBase<Type, TIterator>::IteratorBase(const Pointer ptr)
	: _ptr(ptr)
{
}

template<typename Type,
	template<typename T> typename TIterator>
IteratorBase<Type, TIterator>::IteratorBase(const Reference ref)
	: _ptr(&ref)
{
}

template<typename Type,
	template<typename T> typename TIterator>
QBool IteratorBase<Type, TIterator>::operator==(Iterator other) const
{
	return _ptr == other._ptr;
}

template< typename Type,
	template<typename T> typename TIterator>
QBool IteratorBase<Type, TIterator>::operator!=(Iterator other) const
{
	return _ptr != other._ptr;
}

template<typename Type,
	template<typename T> typename TIterator>
QBool IteratorBase<Type, TIterator>::operator<(Iterator other) const
{
	return _ptr < other._ptr;
}

template<typename Type,
	template<typename T> typename TIterator>
QBool IteratorBase<Type, TIterator>::operator<=(Iterator other) const
{
	return _ptr <= other._ptr;
}

template< typename Type,
	template<typename T> typename TIterator>
QBool IteratorBase<Type, TIterator>::operator>(Iterator other) const
{
	return _ptr > other._ptr;
}

template<typename Type,
	template<typename T> typename TIterator>
QBool IteratorBase<Type, TIterator>::operator>=(Iterator other) const
{
	return _ptr >= other._ptr;
}

template<typename Type,
	template<typename T> typename TIterator>
void IteratorBase<Type, TIterator>::set(const Pointer ptr)
{
	_ptr = ptr;
}

template<typename Type,
	template<typename T> typename TIterator>
void IteratorBase<Type, TIterator>::set(const Reference ref)
{
	*_ptr = ref;
}

//=======================================================================================

template<typename Type, 
	template <typename T> typename TIterator>
ForwardIterator<Type, TIterator>::ForwardIterator()
	: IteratorBase()
{
}

template<typename Type, 
	template<typename T> typename TIterator>
ForwardIterator<Type, TIterator>::ForwardIterator(const Pointer ptr)
	: IteratorBase(ptr)
{
}

template<typename Type,
	template<typename T> typename TIterator>
ForwardIterator<Type, TIterator>::ForwardIterator(const Reference ref)
	: IteratorBase(ref)
{
}

template<typename Type>
ForwardNodeIterator<Type>::ForwardNodeIterator()
	: ForwardIterator()
{
}

template<typename Type>
ForwardNodeIterator<Type>::ForwardNodeIterator(const Pointer ptr)
	: ForwardIterator(ptr)
{
}

template<typename Type>
ForwardNodeIterator<Type>::ForwardNodeIterator(const Reference ref)
	: ForwardIterator(ref)
{
}

template<typename Type>
typename ForwardNodeIterator<Type>::Iterator
ForwardNodeIterator<Type>::next() const
{
	return Iterator(_ptr->next);
}

template<typename Type>
typename ForwardNodeIterator<Type>::Reference
ForwardNodeIterator<Type>::operator*() const
{
	return *_ptr;
}

template<typename Type>
typename ForwardNodeIterator<Type>::Pointer
ForwardNodeIterator<Type>::ptr() const
{
	return _ptr;
}

template<typename Type>
typename ForwardNodeIterator<Type>::Reference
ForwardNodeIterator<Type>::get() const
{
	return *_ptr;
}

template<typename Type>
typename ForwardNodeIterator<Type>::Iterator
ForwardNodeIterator<Type>::operator+(int itrs)
{
	Iterator itr(_ptr);
	while (!itrs--)
	{
		itr._ptr = itr._ptr->next;
	}
	return itr;
}

template<typename Type>
void ForwardNodeIterator<Type>::operator+=(int itrs)
{
	while (!itrs--)
	{
		_ptr = ptr->next;
	}
}

template<typename Type>
typename ForwardNodeIterator<Type>::Iterator
ForwardNodeIterator<Type>::operator++()
{
	_ptr = _ptr->next;
	return *this;
}

template<typename Type>
ForwardArrayIterator<Type>::ForwardArrayIterator()
	: ForwardIterator()
{
}

template<typename Type>
ForwardArrayIterator<Type>::ForwardArrayIterator(const Pointer ptr)
	: ForwardIterator(ptr)
{
}

template<typename Type>
ForwardArrayIterator<Type>::ForwardArrayIterator(const Reference ref)
	: ForwardIterator(ref)
{
}

template<typename Type>
typename ForwardArrayIterator<Type>::Iterator 
ForwardArrayIterator<Type>::next()
{
	return Iterator(_ptr + 1);
}

template<typename Type>
typename ForwardArrayIterator<Type>::Reference
ForwardArrayIterator<Type>::operator*() const
{
	return *_ptr;
}

template<typename Type>
typename ForwardArrayIterator<Type>::Pointer
ForwardArrayIterator<Type>::ptr() const
{
	return _ptr;
}

template<typename Type>
typename ForwardArrayIterator<Type>::Reference 
ForwardArrayIterator<Type>::get() const
{
	return *_ptr;
}

template<typename Type>
typename ForwardArrayIterator<Type>::Iterator
ForwardArrayIterator<Type>::operator+(int itrs)
{
	return Iterator(_ptr + sizeof(Type) * itrs);
}

template<typename Type>
void ForwardArrayIterator<Type>::operator+=(int itrs)
{
	_ptr += itrs;
}

template<typename Type>
typename ForwardArrayIterator<Type>::Iterator
ForwardArrayIterator<Type>::operator++()
{
	++_ptr;
	return *this;
}

//=======================================================================================

template<typename Type,
	template<typename T> typename TIterator>
BidirectionalIterator<Type, TIterator>::BidirectionalIterator()
	: IteratorBase()
{
}

template<typename Type,
	template<typename T> typename TIterator>
BidirectionalIterator<Type, TIterator>::BidirectionalIterator(const Pointer ptr)
	: IteratorBase(ptr)
{
}

template<typename Type,
	template<typename T> typename TIterator>
BidirectionalIterator<Type, TIterator>::BidirectionalIterator(const Reference ref)
	: IteratorBase(ref)
{
}

template<typename Type>
BidirectionalNodeIterator<Type>::BidirectionalNodeIterator()
	: BidirectionalIterator()
{
}

template<typename Type>
BidirectionalNodeIterator<Type>::BidirectionalNodeIterator(const Pointer ptr)
	: BidirectionalIterator(ptr)
{
}

template<typename Type>
BidirectionalNodeIterator<Type>::BidirectionalNodeIterator(const Reference ref)
	: BidirectionalIterator(ref)
{
}

template<typename Type>
typename BidirectionalNodeIterator<Type>::Iterator
BidirectionalNodeIterator<Type>::next() const
{
	return Iterator(_ptr->next);
}

template<typename Type>
typename BidirectionalNodeIterator<Type>::Iterator
BidirectionalNodeIterator<Type>::prev() const
{
	return Iterator(_ptr->prev);
}

template<typename Type>
typename BidirectionalNodeIterator<Type>::Reference 
BidirectionalNodeIterator<Type>::operator*() const
{
	return *_ptr;
}

template<typename Type>
typename BidirectionalNodeIterator<Type>::Pointer
BidirectionalNodeIterator<Type>::ptr() const
{
	return _ptr;
}

template<typename Type>
typename BidirectionalNodeIterator<Type>::Reference
BidirectionalNodeIterator<Type>::get() const
{
	return *_ptr;
}

template<typename Type>
typename BidirectionalNodeIterator<Type>::Iterator
BidirectionalNodeIterator<Type>::operator+(int itrs)
{
	Iterator itr(_ptr);
	while (!itrs--)
	{
		itr._ptr = itr._ptr->next;
	}
	return itr;
}

template<typename Type>
void BidirectionalNodeIterator< Type>::operator+=(int itrs)
{
	while (!itrs--)
	{
		_ptr = _ptr->next;
	}
}

template<typename Type>
typename BidirectionalNodeIterator<Type>::Iterator
BidirectionalNodeIterator<Type>::operator++()
{
	_ptr = _ptr->next;
	return *this;
}

template<typename Type>
typename BidirectionalNodeIterator<Type>::Iterator
BidirectionalNodeIterator<Type>::operator-(int itrs)
{
	Iterator itr(_ptr);
	while (!itrs--)
	{
		itr._ptr = itr._ptr->next;
	}
	return itr;
}

template<typename Type>
void BidirectionalNodeIterator<Type>::operator-=(int itrs)
{
	while (!itrs--)
	{
		_ptr = _ptr->prev;
	}
}

template<typename Type>
typename BidirectionalNodeIterator<Type>::Iterator
BidirectionalNodeIterator<Type>::operator--()
{
	_ptr = _ptr->prev;
	return *this;
}

template< typename Type>
BidirectionalArrayIterator<Type>::BidirectionalArrayIterator()
	: BidirectionalIterator()
{
}

template<typename Type>
BidirectionalArrayIterator<Type>::BidirectionalArrayIterator(const Pointer ptr)
	: BidirectionalIterator(ptr)
{
}

template<typename Type>
BidirectionalArrayIterator<Type>::BidirectionalArrayIterator(const Reference ref)
	: BidirectionalIterator(ref)
{
}

template<typename Type>
typename BidirectionalArrayIterator<Type>::Iterator
BidirectionalArrayIterator<Type>::next() const
{
	return Iterator(_ptr + 1);
}

template<typename Type>
typename BidirectionalArrayIterator<Type>::Iterator
BidirectionalArrayIterator< Type>::prev() const
{
	return Iterator(_ptr - 1);
}

template<typename Type>
typename BidirectionalArrayIterator<Type>::Reference
BidirectionalArrayIterator<Type>::operator*() const
{
	return *_ptr;
}

template<typename Type>
typename BidirectionalArrayIterator<Type>::Pointer
BidirectionalArrayIterator<Type>::ptr() const
{
	return _ptr;
}

template<typename Type>
typename BidirectionalArrayIterator<Type>::Reference
BidirectionalArrayIterator<Type>::get() const
{
	return *_ptr;
}

template<typename Type>
typename BidirectionalArrayIterator<Type>::Iterator
BidirectionalArrayIterator<Type>::operator+(int itrs)
{
	return Iterator(_ptr + 1 * itrs);
}

template<typename Type>
void BidirectionalArrayIterator<Type>::operator+=(int itrs)
{
	_ptr += 1 * itrs;
}

template<typename Type>
typename BidirectionalArrayIterator<Type>::Iterator
BidirectionalArrayIterator<Type>::operator++()
{
	++_ptr;
	return *this;
}

template<typename Type>
typename BidirectionalArrayIterator<Type>::Iterator
BidirectionalArrayIterator<Type>::operator-(int itrs)
{
	return Iterator(_ptr - 1 * itrs);
}

template<typename Type>
void BidirectionalArrayIterator<Type>::operator-=(int itrs)
{
	_ptr -= 1 * itrs;
}

template<typename Type>
typename BidirectionalArrayIterator<Type>::Iterator
BidirectionalArrayIterator<Type>::operator--()
{
	--_ptr;
	return *this;
}

//=======================================================================================

template<typename Type,
	template<typename T> typename TIterator>
ReverseIterator<Type, TIterator>::ReverseIterator()
	: IteratorBase()
{
}

template<typename Type,
	template<typename T> typename TIterator>
ReverseIterator<Type, TIterator>::ReverseIterator(const Pointer ptr)
	: IteratorBase(ptr)
{
}

template<typename Type,
	template<typename T> typename TIterator>
ReverseIterator<Type, TIterator>::ReverseIterator(const Reference ref)
	: IteratorBase(ref)
{
}

template<typename Type,
	template<typename T> typename TIterator>
QBool ReverseIterator<Type, TIterator>::operator<(Iterator other) const
{
	return _ptr > other._ptr;
}

template<typename Type,
	template<typename T> typename TIterator>
QBool ReverseIterator<Type, TIterator>::operator<=(Iterator other) const
{
	return _ptr >= other._ptr;
}

template<typename Type,
	template<typename T> typename TIterator>
QBool ReverseIterator<Type, TIterator>::operator>(Iterator other) const
{
	return _ptr < other._ptr;
}

template<typename Type,
	template<typename T> typename TIterator>
QBool ReverseIterator<Type, TIterator>::operator>=(Iterator other) const
{
	return _ptr <= other._ptr;
}

template<typename Type>
ReverseNodeIterator<Type>::ReverseNodeIterator()
	: ReverseIterator()
{
}

template<typename Type>
ReverseNodeIterator<Type>::ReverseNodeIterator(const Pointer ptr)
	: ReverseIterator(ptr)
{
}

template<typename Type>
ReverseNodeIterator<Type>::ReverseNodeIterator(const Reference ref)
	: ReverseIterator(ref)
{
}

template<typename Type>
typename ReverseNodeIterator<Type>::Iterator
ReverseNodeIterator<Type>::next() const
{
	return Iterator(_ptr->prev);
}

template<typename Type>
typename ReverseNodeIterator<Type>::Iterator
ReverseNodeIterator<Type>::prev() const
{
	return Iterator(_ptr->next);
}

template<typename Type>
typename ReverseNodeIterator<Type>::Reference
ReverseNodeIterator<Type>::operator*() const
{
	return _ptr;
}

template<typename Type>
typename ReverseNodeIterator<Type>::Pointer
ReverseNodeIterator<Type>::ptr() const
{
	return _ptr;
}

template<typename Type>
typename ReverseNodeIterator<Type>::Reference 
ReverseNodeIterator<Type>::get() const
{
	return _ptr;
}

template<typename Type>
typename ReverseNodeIterator<Type>::Iterator
ReverseNodeIterator<Type>::operator+(int itrs)
{
	Pointer node = _ptr;
	while (!itrs--)
	{
		node = node->prev;
	}
	return Iterator(node);
}

template<typename Type>
void ReverseNodeIterator<Type>::operator+=(int itrs)
{
	while (!itrs--)
	{
		_ptr = _ptr->prev;
	}
}

template<typename Type>
typename ReverseNodeIterator<Type>::Iterator
ReverseNodeIterator<Type>::operator++()
{
	_ptr = _ptr->prev;
	return *this;
}

template<typename Type>
typename ReverseNodeIterator<Type>::Iterator
ReverseNodeIterator<Type>::operator-(int itrs)
{
	Pointer node = _ptr;
	while (!itrs--)
	{
		node = node->next;
	}
	return Iterator(node);
}

template<typename Type>
void ReverseNodeIterator<Type>::operator-=(int itrs)
{
	while (!itrs--)
	{
		_ptr = ptr->next;
	}
}

template<typename Type>
typename ReverseNodeIterator<Type>::Iterator
ReverseNodeIterator<Type>::operator--()
{
	_ptr = _ptr->next;
	return *this;
}

template<typename Type>
ReverseArrayIterator<Type>::ReverseArrayIterator()
	: ReverseIterator()
{
}

template<typename Type>
ReverseArrayIterator<Type>::ReverseArrayIterator(const Pointer ptr)
	: ReverseIterator(ptr)
{
}

template<typename Type>
ReverseArrayIterator<Type>::ReverseArrayIterator(const Reference ref)
	: ReverseIterator(ref)
{
}

template<typename Type>
typename ReverseArrayIterator<Type>::Iterator
ReverseArrayIterator<Type>::next() const
{
	return _ptr - 1;
}

template<typename Type>
typename ReverseArrayIterator<Type>::Iterator
ReverseArrayIterator<Type>::prev() const
{
	return _ptr + 1;
}

template<typename Type>
typename ReverseArrayIterator<Type>::Reference
ReverseArrayIterator<Type>::operator*() const
{
	return *_ptr;
}

template<typename Type>
typename ReverseArrayIterator<Type>::Pointer
ReverseArrayIterator<Type>::ptr() const
{
	return _ptr;
}

template<typename Type>
typename ReverseArrayIterator<Type>::Reference
ReverseArrayIterator<Type>::get() const
{
	return *_ptr;
}

template<typename Type>
typename ReverseArrayIterator<Type>::Iterator
ReverseArrayIterator<Type>::operator+(int itrs)
{
	return Iterator(_ptr - 1 * itrs);
}

template<typename Type>
void ReverseArrayIterator<Type>::operator+=(int itrs)
{
	_ptr -= 1 * itrs;
}

template<typename Type>
typename ReverseArrayIterator<Type>::Iterator
ReverseArrayIterator<Type>::operator++()
{	
	--_ptr;
	return *this;
}

template<typename Type>
typename ReverseArrayIterator<Type>::Iterator
ReverseArrayIterator<Type>::operator-(int itrs)
{
	return Iterator(_ptr + 1 * itrs);
}

template<typename Type>
void ReverseArrayIterator<Type>::operator-=(int itrs)
{
	_ptr += 1 * itrs;
}

template<typename Type>
typename ReverseArrayIterator<Type>::Iterator
ReverseArrayIterator<Type>::operator--()
{
	++_ptr;
	return *this;
}

template<typename Type>
QBool ReverseArrayIterator<Type>::operator<(Iterator other) const
{
	return _ptr > other._ptr;
}

template<typename Type>
QBool ReverseArrayIterator<Type>::operator<=(Iterator other) const
{
	return _ptr >= other._ptr;
}

template<typename Type>
QBool ReverseArrayIterator<Type>::operator>(Iterator other) const
{
	return _ptr < other._ptr;
}

template<typename Type>
QBool ReverseArrayIterator<Type>::operator>=(Iterator other) const
{
	return _ptr <= other._ptr;
}