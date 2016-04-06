#include "..\Include\forward_list.hpp"

template<typename T, typename A>
const ForwardList<T, A> ForwardList<T, A>::EMPTY_FLIST(0);

template<typename T, typename A>
FL_Value<T, A> ForwardList<T, A>::EMPTY_VALUE = Value();

template<typename T, typename A>
ForwardList<T, A>::Node::Node(ConstReference dat)
	: data(dat), next()
{
}

template<typename T, typename A>
void ForwardList<T, A>::Node::set(ConstReference dat)
{
	data = dat;
}

template<typename T, typename A>
FL_Node<T, A>
ForwardList<T, A>::Node::getNext() const
{
	return next;
}

template<typename T, typename A>
void ForwardList<T, A>::Node::setNext(Node* nxt)
{
	next = nxt;
}

template<typename T, typename A>
ForwardList<T, A>::ForwardList(size_t maxSize)
	: _front(), _back(), _bbegin(), _end(), 
	_size(), _maxSize(maxSize), _allocator()
{
}

template<typename T, typename A>
ForwardList<T, A>::ForwardList(const Iterator begin, const Iterator end)
	: _front(), _back(), _bbegin(), _end(),
	_size(), _maxSize(), _allocator()
{
	size_t size = iterator_node_distance(begin, end);
	_maxSize = size;
	for (Iterator i = begin; i != end; ++i)
	{
		pushBack(i.get().data);
	}
}

template<typename T, typename A>
ForwardList<T, A>::ForwardList(const Container& container)
	: _front(), _back(), _bbegin(), _end(),
	_size(), _maxSize(container._maxSize), _allocator()
{
	size_t size = container._size;
	Node* i = container._front;
	while (size--)
	{
		pushBack(i->data);
		i = i->getNext();
	}
}

template<typename T, typename A>
ForwardList<T, A>::~ForwardList()
{
	while (!isEmpty())
	{
		popFront();
	}
	_allocator.destroy();
}

template<typename T, typename A>
void ForwardList<T, A>::pushFront(ConstReference reference)
{
	if (!isEmpty() && !isFull())
	{
		Node* node = _allocateNode(reference);
		node->setNext(_front);
		_front = node;
		_bbegin->setNext(_front);
		_incrementSize();
	}
	else if(isEmpty())
	{
		_initBounds(reference);
	}
}

template<typename T, typename A>
void ForwardList<T, A>::pushFront(const Container& container)
{
}

template<typename T, typename A>
void ForwardList<T, A>::popFront()
{
	if (!isEmpty())
	{
		Node* node = _front;
		_front = _front->getNext();
		_bbegin->setNext(_front);
		_deallocateNode(node);
		_decrementSize();
	}
}

template<typename T, typename A>
FL_ConstReference<T, A>
ForwardList<T, A>::front() const
{
	return !isEmpty() ? _front->data : EMPTY_VALUE;
}

template<typename T, typename A>
void ForwardList<T, A>::pushBack(ConstReference reference)
{
	if (!isEmpty() && !isFull())
	{
		Node* node = _allocateNode(reference);
		_back->setNext(node);
		_back = node;
		_back->setNext(_end);
		_incrementSize();
	}
	else if(isEmpty())
	{
		_initBounds(reference);
	}
}

template<typename T, typename A>
void ForwardList<T, A>::pushBack(const Container& container)
{
}

template<typename T, typename A>
void ForwardList<T, A>::popBack()
{
	if (!isEmpty())
	{
		Node* i = _front;
		while (i && i->getNext() != _back)
		{
			i = i->getNext();
		}
		_deallocateNode(_back);
		_back = i;
		_back->setNext(_end);
		_decrementSize();
	}
}

template<typename T, typename A>
FL_ConstReference<T, A>
ForwardList<T, A>::back() const
{
	return _back->data;
}

template<typename T, typename A>
void ForwardList<T, A>::insert(Node* after, ConstReference reference)
{
	if (!isFull())
	{
		Node* i = _front;
		while (i != NULL_NODE)
		{
			if (i->getNext()->data == reference)
			{
				Node* node = _allocateNode(reference);
				node->setNext(i->getNext());
				i->setNext(node);
				_incrementSize();
				break;
			}
			else
			{
				i = i->getNext();
			}
		}
	}
}

template<typename T, typename A>
void ForwardList<T, A>::append(Node* before, ConstReference reference)
{
	if (!isFull())
	{
		Node* i = _front;
		while (i != NULL_NODE)
		{
			if (i->data == reference)
			{
				Node* node = _allocateNode(reference);
				node->setNext(i->getNext());
				i->setNext(node);
				_incrementSize();
				break;
			}
			else
			{
				i = i->getNext();
			}
		}
	}
}

template<typename T, typename A>
FL_Iterator<T, A>
ForwardList<T, A>::find(ConstReference reference) const
{
	Node* i = _front;
	while (i != NULL_NODE)
	{
		if (i->data == reference)
		{
			return Iterator(i);
		}
		else
		{
			i = i->getNext();
		}
	}
	return end();
}

template<typename T, typename A>
QBool ForwardList<T, A>::has(ConstReference reference) const
{
	Node* i = _front;
	while (i != NULL_NODE)
	{
		if (i->data == reference)
		{
			return true;
		}
		else
		{
			i = i->getNext();
		}
	}
	return false;
}

template<typename T, typename A>
void ForwardList<T, A>::clear()
{
	while (!isEmpty())
	{
		popFront();
	}
}

template<typename T, typename A>
void ForwardList<T, A>::copy(const Container& other)
{
	_maxSize = other._maxSize;
	size_t size = other._size;
	Node* i = other._front;
	while (size--)
	{
		pushBack(i->data);
		i = i->getNext();
	}
}

template<typename T, typename A>
void ForwardList<T, A>::reserve(size_t maxSize)
{
	if (maxSize > _maxSize)
	{
		_maxSize = maxSize;
	}
}

template<typename T, typename A>
void ForwardList<T, A>::shrink(size_t maxSize)
{
	if (maxSize < _size)
	{
		_maxSize = maxSize;
		while (_size-- != maxSize)
		{
			popBack();
		}
	}
}

template<typename T, typename A>
QBool ForwardList<T, A>::equals(const Container& other) const
{
	size_t tSize = _size;
	size_t oSize = other._size;
	if (tSize == oSize && tSize)
	{
		Node* i = _front;
		Node* j = other._front;
		while (i != NULL_NODE)
		{
			if (i->data != j->data)
			{
				return false;
			}
			else
			{
				i = i->getNext();
				j = j->getNext();
			}
		}
		return true;
	}
	return false;
}

template<typename T, typename A>
void ForwardList<T, A>::operator=(const Container& other)
{
	_maxSize = other._maxSize;
	size_t size = container._size;
	Node* i = container._front;
	while (size--)
	{
		pushBack(i->data);
		i = i->getNext();
	}
}

template<typename T, typename A>
ForwardList<T, A>::operator bool() const
{
	return _front && _back && _size;
}

template<typename T, typename A>
QBool ForwardList<T, A>::operator==(const Container& other) const
{
	size_t tSize = _size;
	size_t oSize = other._size;
	if (tSize == oSize && tSize)
	{
		Node* i = _front;
		Node* j = other._front;
		while (i != NULL_NODE)
		{
			if (i->data != j->data)
			{
				return false;
			}
			else
			{
				i = i->getNext();
				j = j->getNext();
			}
		}
		return true;
	}
	return false;
}

template<typename T, typename A>
QBool ForwardList<T, A>::operator!=(const Container& other) const
{
	size_t tSize = _size;
	size_t oSize = other._size;
	if (tSize == oSize && tSize)
	{
		Node* i = _front;
		Node* j = other._front;
		while (i != NULL_NODE)
		{
			if (i->data != j->data)
			{
				return true;
			}
		}
		return false;
	}
	return true;
}

template<typename T, typename A>
QBool ForwardList<T, A>::operator<(const Container& other) const
{
	size_t tSize = _size;
	size_t oSize = other._size;
	if (tSize == oSize && tSize)
	{
		Node* i = _front;
		Node* j = other._front;
		while (i != NULL_NODE)
		{
			if (i->data >= j->data)
			{
				return false;
			}
		}
		return true;
	}
	return tSize < oSize;
}

template<typename T, typename A>
QBool ForwardList<T, A>::operator<=(const Container& other) const
{
	size_t tSize = _size;
	size_t oSize = other._size;
	if (tSize == oSize && tSize)
	{
		Node* i = _front;
		Node* j = other._front;
		while (i != NULL_NODE)
		{
			if (i->data > j->data)
			{
				return false;
			}
		}
		return true;
	}
	return tSize <= oSize;
}

template<typename T, typename A>
QBool ForwardList<T, A>::operator>(const Container& other) const
{
	size_t tSize = _size;
	size_t oSize = other._size;
	if (tSize == oSize && tSize)
	{
		Node* i = _front;
		Node* j = other._front;
		while (i != NULL_NODE)
		{
			if (i->data <= j->data)
			{
				return false;
			}
		}
		return true;
	}
	return tSize > oSize;
}

template<typename T, typename A>
QBool ForwardList<T, A>::operator>=(const Container& other) const
{
	size_t tSize = _size;
	size_t oSize = other._size;
	if (tSize == oSize && tSize)
	{
		Node* i = _front;
		Node* j = other._front;
		while (i != NULL_NODE)
		{
			if (i->data < j->data)
			{
				return false;
			}
		}
		return true;
	}
	return tSize >= oSize;
}


template<typename T, typename A>
QBool ForwardList<T, A>::isEmpty() const
{
	return _size == 0;
}

template<typename T, typename A>
QBool ForwardList<T, A>::isFull() const
{
	return _size == _maxSize;
}

template<typename T, typename A>
const FL_Iterator<T, A>
ForwardList<T, A>::begin() const
{
	return Iterator(*_front);
}

template<typename T, typename A>
const FL_Iterator<T, A>
ForwardList<T, A>::bbegin() const
{
	return Iterator(*_bbegin);
}

template<typename T, typename A>
const FL_Iterator<T, A>
ForwardList<T, A>::end() const
{
	return Iterator(*_end);
}

template<typename T, typename A>
const FL_ConstIterator<T, A>
ForwardList<T, A>::cbegin() const
{
	return ConstIterator(*_front);
}

template<typename T, typename A>
const FL_ConstIterator<T, A>
ForwardList<T, A>::cbbegin() const
{
	return ConstIterator(*_bbegin);
}

template<typename T, typename A>
const FL_ConstIterator<T, A>
ForwardList<T, A>::cend() const
{
	return ConstIterator(*_end);
}

template<typename T, typename A>
size_t ForwardList<T, A>::size() const
{
	return _size;
}

template<typename T, typename A>
size_t ForwardList<T, A>::maxSize() const
{
	return _maxSize;
}

template<typename T, typename A>
void ForwardList<T, A>::_incrementSize()
{
	_size++;
}

template<typename T, typename A>
void ForwardList<T, A>::_decrementSize()
{
	_size--;
} 

template<typename T, typename A>
FL_Node<T, A>
ForwardList<T, A>::_allocateNode(ConstReference reference)
{
	Block block = _allocator.allocate(sizeof(Node));
	Node* node = static_cast<Node*>(block.memory);
	node->set(reference);
	return node;
}

template<typename T, typename A>
void ForwardList<T, A>::_deallocateNode(Node* node)
{
	if (node != NULL_NODE)
	{
		size_t size = sizeof(Node);
		void* mem = static_cast<void*>(node);
		Block block(mem, size);
		_allocator.deallocate(block);
	}
}

template<typename T, typename A>
QBool ForwardList<T, A>::_hasSpaceFor(size_t amount) const
{
	return _size + amount <= _maxSize;
}

template<typename T, typename A>
void ForwardList<T, A>::_initBounds(ConstReference reference)
{
	if (isEmpty() && _maxSize > 0)
	{
		Node* node = _allocateNode(reference);
		_bbegin = _allocateNode(EMPTY_VALUE);
		_end = _allocateNode(EMPTY_VALUE);
		_front = _back = node;
		_bbegin->setNext(_front);
		_back->setNext(_end);
		_incrementSize();
	}
}

template<typename T, typename A>
std::ostream& operator<<(std::ostream& os, const ForwardList<T, A>& list)
{
	size_t count = 0;
	for (ForwardList<T, A>::Iterator i = list.begin(); i < list.end(); ++i, ++count)
	{
		os << "Node " << count << ": " << i.get().data << std::endl;
	}
	return os;
}