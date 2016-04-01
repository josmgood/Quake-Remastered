#include "..\Include\qstack.hpp"

template<typename Type,
	typename TAllocator>
const QStack<Type, TAllocator> QStack<Type, TAllocator>::EMPTY_STACK(0);

//template<typename Type,
//	typename TAllocator>
//const QStack<Type, TAllocator>::Node* QStack<Type, TAllocator>::NULL_NODE = nullptr;

template<typename Type,
	typename TAllocator>
QStack<Type, TAllocator>::Node::Node(ConstReference dat)
	: data(dat), next(nullptr), prev(nullptr)
{
}

template<typename Type,
	typename TAllocator>
void QStack<Type, TAllocator>::Node::set(ConstReference dat)
{
	data = dat;
}

template<typename Type,
	typename TAllocator>
Stk_Node<Type, TAllocator>
QStack<Type, TAllocator>::Node::getNext() const
{
	return next;
}

template<typename Type,
	typename TAllocator>
Stk_Node<Type, TAllocator>
QStack<Type, TAllocator>::Node::getPrev() const
{
	return prev;
}

template<typename Type,
	typename TAllocator>
void QStack<Type, TAllocator>::Node::setNext(Node* nxt)
{
	next = nxt;
}

template<typename Type,
	typename TAllocator>
void QStack<Type, TAllocator>::Node::setPrev(Node* prv)
{
	prev = prv;
}


template<typename Type,
	typename TAllocator>
QStack<Type, TAllocator>::QStack(size_t maxSize)
	: _bottom(nullptr), _top(nullptr), _size(), _maxSize(maxSize), _allocator()
{
}

template<typename Type,
	typename TAllocator>
QStack<Type, TAllocator>::QStack(const Pointer array_ptr, size_t size)
	: _bottom(nullptr), _top(nullptr), _size(), _maxSize(size), _allocator()
{
	for (size_t i = 0; i < size; ++i)
	{
		Value value = array_ptr[i];
		push(value);
	}
}

template<typename Type,
	typename TAllocator>
QStack<Type, TAllocator>::QStack(const QStack& other)
	: _bottom(nullptr), _top(nullptr), _size(), _maxSize(), _allocator()
{
	if (other)
	{
		size_t size = other._size;
		_maxSize = other._maxSize;
		Node* i = other._bottom;
		while (size--)
		{
			push(i->data);
			i = i->getNext();
		}
	}
}

template<typename Type,
	typename TAllocator>
QStack<Type, TAllocator>::~QStack()
{
	clear();
}

template<typename Type,
	typename TAllocator>
void QStack<Type, TAllocator>::set(ConstReference reference)
{
	if (!isEmpty())
	{
		_top->set(reference);
	}
	else
	{
		_initBounds(reference);
	}
}

template<typename Type,
	typename TAllocator>
void QStack<Type, TAllocator>::push(const Pointer array_ptr, size_t size)
{
	if (_hasSpaceFor(size))
	{
		for (size_t i = 0; i < size; ++i)
		{
			Value value = array_ptr[i];
			push(value);
		}
	}
}

template<typename Type,
	typename TAllocator>
void QStack<Type, TAllocator>::push(const QStack& other)
{
	size_t size = other._size;
	if (_hasSpaceFor(size))
	{
		Node* i = other._bottom;
		while (size--)
		{
			push(i->data);
			i = i->getNext();
		}
	}
}

template<typename Type,
	typename TAllocator>
void QStack<Type, TAllocator>::push(ConstReference reference)
{
	if (isEmpty())
	{
		_initBounds(reference);
	}
	else if (!isFull())
	{
		Block block = _allocator.allocate(sizeof(Node));
		Node* node = static_cast<Node*>(block.memory);
		node->set(reference);
		node->setPrev(_top);
		node->getPrev()->setNext(node);
		_top = node;
		_incrementSize();
	}
}


template<typename Type,
	typename TAllocator>
void QStack<Type, TAllocator>::pop(size_t amount)
{
	while (!isEmpty() && amount--)
	{
		pop();
	}
}

template<typename Type,
	typename TAllocator>
void QStack<Type, TAllocator>::pop()
{
	if (!isEmpty())
	{
		void* mem = static_cast<void*>(_top);
		size_t size = sizeof(Node);
		Block block(mem, size);
		_top = _top->getPrev();
		_allocator.deallocate(block);
		_decrementSize();
	}
}

template<typename Type,
	typename TAllocator>
Stk_Value<Type, TAllocator>
QStack<Type, TAllocator>::take()
{
	if (!isEmpty())
	{
		Value value = _top->data;
		pop();
		return value;
	}
}

template<typename Type,
	typename TAllocator>
Stk_ConstReference<Type, TAllocator>
QStack<Type, TAllocator>::peek() const
{
	return _top->data;
}

template<typename Type,
	typename TAllocator>
QStack<Type, TAllocator>
QStack<Type, TAllocator>::reversed() const
{
	QStack stack(_maxSize);
	/*size_t size = _size;
	Node* i = _top;
	while (size--)
	{
		stack.push(i->data);
		i = get_next(i);
	}*/
	return stack;
}

template<typename Type,
	typename TAllocator>
void QStack<Type, TAllocator>::reverse()
{
	/*size_t size = _size;
	for (Node* front = _bottom, *back = _top;
		size--;
		front = get_next(front), back = get_next(back))
	{
		if (front != back)
		{
			Value value = front->data;
			front->data = back->data;
			back->data = value;
		}
	}*/
}

template<typename Type,
	typename TAllocator>
void QStack<Type, TAllocator>::clear()
{
	while (!isEmpty())
	{
		pop();
	}
}

template<typename Type,
	typename TAllocator>
void QStack<Type, TAllocator>::copy(const QStack& other)
{
	size_t size = other._size;
	_maxSize = _maxSize > other._maxSize ? _maxSize : other._maxSize;
	while (_size > size)
	{
		pop();
	}
	Node* i = _bottom;
	Node* j = other._bottom;
	while (size--)
	{
		if (i)
		{
			Value value = j->data;
			i->data = value;
			i = i->getNext();
		}
		else
		{
			push(j->data);
		}
		j = j->getNext();
	}
}

template<typename Type,
	typename TAllocator>
void QStack<Type, TAllocator>::swap(QStack& other)
{
	size_t tSize = _size;
	size_t oSize = other._size;

}

template<typename Type,
	typename TAllocator>
void QStack<Type, TAllocator>::resize(size_t maxSize)
{
	_maxSize = maxSize;
}

template<typename Type,
	typename TAllocator>
QBool QStack<Type, TAllocator>::equals(const QStack& other) const
{
	size_t tSize = _size;
	size_t oSize = other._size;
	if (tSize == oSize)
	{
		for (Node* i = _bottom, *j = other._bottom;
		tSize--;
			i = i->getNext(),
			j = j->getNext())
		{
			if (i->data != j->data)
			{
				return false;
			}
		}
		return true;
	}
	return false;
}

template<typename Type,
	typename TAllocator>
QBool QStack<Type, TAllocator>::isEmpty() const
{
	return _size == 0;
}

template<typename Type,
	typename TAllocator>
QBool QStack<Type, TAllocator>::isFull() const
{
	return _size == _maxSize;
}

template<typename Type,
	typename TAllocator>
QStack<Type, TAllocator>
QStack<Type, TAllocator>::operator+(ConstReference reference)
{
	QStack stack = *this;
	stack.push(reference);
	return stack;
}

template<typename Type,
	typename TAllocator>
QStack<Type, TAllocator>
QStack<Type, TAllocator>::operator+(const QStack& other)
{
	size_t size = _size + other._size;
	QStack stack(size);

	/*Node* i = _bottom;
	size_t tSize = _size;
	while (tSize--)
	{
		stack.push(i->data);
		i = get_next(i);
	}

	i = other._bottom;
	size_t oSize = other._size;
	while (oSize--)
	{
		stack.push(i->data);
		i = get_next(i);
	}*/
	return stack;
}

template<typename Type, 
	typename TAllocator>
QStack<Type, TAllocator>
QStack<Type, TAllocator>::operator+=(const QStack& other)
{
	size_t size = other._size;
	if (_hasSpaceFor(size))
	{
		Node* i = other._bottom;
		while (size--)
		{
			push(i->data);
			i = i->getNext();
		}
	}
}

template<typename Type,
	typename TAllocator>
void QStack<Type, TAllocator>::operator=(const QStack& other)
{
	size_t size = other._size;
	_maxSize = _maxSize > other._maxSize ? _maxSize : other._maxSize;
	while (_size > size)
	{
		pop();
	}
	Node* i = _bottom;
	Node* j = other._bottom;
	while (size--)
	{
		if (i)
		{
			Value value = j->data;
			i->data = value;
			i = i->getNext();
		}
		else
		{
			push(j->data);
		}
		j = j->getNext();
	}
}

template<typename Type,
	typename TAllocator>
QStack<Type, TAllocator>::operator bool() const
{
	return _bottom && _size && _maxSize;
}

template<typename Type,
	typename TAllocator>
QBool QStack<Type, TAllocator>::operator==(const QStack& other) const
{
	size_t tSize = _size;
	size_t oSize = other._size;
	if (tSize == oSize)
	{
		for (Node* i = _bottom, *j = other._bottom;
			tSize--;
			i = i->getNext(),
			j = j->getNext())
		{
			if (i->data != j->data)
			{
				return false;
			}
		}
		return true;
	}
	return false;
}

template<typename Type,
	typename TAllocator>
QBool QStack<Type, TAllocator>::operator!=(const QStack& other) const
{
	size_t tSize = _size;
	size_t oSize = other._size;
	if (tSize == oSize)
	{
		for (Node* i = _bottom, *j = other._bottom;
			tSize--;
			i = i->getNext(),
			j = j->getNext())
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

template<typename Type,
	typename TAllocator>
QBool QStack<Type, TAllocator>::operator<(const QStack& other) const
{
	/*size_t tSize = _size;
	size_t oSize = other._size;
	if (tSize == oSize && tSize)
	{
		std::cout << "IN HERE" << std::endl;
		for (Node* i = _bottom, *j = other._bottom;
			tSize--;
			i = i->getNext(),
			j = j->getNext())
		{
			if (i->data >= j->data)
			{
				std::cout << "i: " << i->data << std::endl;
				std::cout << "j: " << j->data << std::endl;
				return false;
			}
		}
		return true && oSize != 0;
	}
	return tSize < oSize;*/
	return false;
}

template<typename Type,
	typename TAllocator>
size_t QStack<Type, TAllocator>::getSize() const
{
	return _size;
}

template<typename Type,
	typename TAllocator>
size_t QStack<Type, TAllocator>::getMaxSize() const
{
	return _maxSize;
}

template<typename Type,
	typename TAllocator>
void QStack<Type, TAllocator>::_setSize(size_t size)
{
	_size = size;
}

template<typename Type,
	typename TAllocator>
void QStack<Type, TAllocator>::_setMaxSize(size_t max)
{
	_maxSize = max;
}

template<typename Type,
	typename TAllocator>
void QStack<Type, TAllocator>::_incrementSize()
{
	_size++;
}

template<typename Type,
	typename TAllocator>
void QStack<Type, TAllocator>::_decrementSize()
{
	_size--;
}

template<typename Type,
	typename TAllocator>
void QStack<Type, TAllocator>::_addSize(size_t amount)
{
	_size += amount;
}

template<typename Type,
	typename TAllocator>
void QStack<Type, TAllocator>::_subtractSize(size_t amount)
{
	_size -= amount;
}

template<typename Type,
	typename TAllocator>
QBool QStack<Type, TAllocator>::_hasSpaceFor(size_t num) const
{
	return _size + num <= _maxSize;
}

template<typename Type,
	typename TAllocator>
void QStack<Type, TAllocator>::_initBounds(ConstReference reference)
{
	if (!_bottom && !_top && _maxSize)
	{
		Block block = _allocator.allocate(sizeof(Node));
		Node* node = static_cast<Node*>(block.memory);
		node->set(reference);
		_bottom = _top = node;
		_incrementSize();
	}
}

template<typename Type,
	typename TAllocator>
std::ostream& operator<<(std::ostream& os, const QStack<Type, TAllocator>& stack)
{
	size_t size = stack._size;
	for (Stk_Node<Type, TAllocator> i = stack._top;
		size--;
		i = i->getPrev())
	{
		os << "Node " << size << ": " << i->data << std::endl;
	}
	return os;
}