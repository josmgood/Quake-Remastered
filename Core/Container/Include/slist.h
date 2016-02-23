#pragma once

/*RENAME TO QFowardList*/

/*
==================================

SList

==================================
*/

template<typename T>
class SList
{
public:
	struct Node
	{
		Node		(const T& d);
		Node*		next;
		T			data;
	};
	SList					(void);
	~SList					(void);

	void pushFront			(const T& elem);
	void pushBack			(const T& elem);

	void popFront			(void);
	void popBack			(void); /*SLOWER THAN POPPING FRONT*/

	void insert				(const T& elem, Node* next);
	void append				(const T& elem, Node* prev);
	Node* find				(const T& elem);
	void erase				(Node* node);
	void clear				(void);
	bool isEmpty			(void) const;

	void print				(void);

	const T& getFront		(void) const;
	const T& getBack		(void) const;
	UINT32 getSize			(void) const;
private:
	void _incrementSize		(void);
	void _decrementSize		(void);

	Node*		_front;
	Node*		_back;
	UINT32		_size;
};

/*
=================================

NODE ALIAS DEFINITIONS

=================================
*/

template<typename T>
using SLNode = typename SList<T>::Node;

template<typename T>
using pSLNode = typename SList<T>::Node*;

/*
=================================

PUBLIC METHODS

=================================
*/

template<typename T>
SList<T>::Node::Node(const T& d)
	: next(nullptr), data(d)
{
}

template<typename T>
SList<T>::SList(void)
	: _front(nullptr), _back(nullptr), _size()
{
}

template<typename T>
SList<T>::~SList(void)
{
	clear();
}

template<typename T>
void SList<T>::pushFront(const T& elem)
{
	if (_front == nullptr && _back == nullptr)
	{
		_front = _back = new Node(elem);
	}
	else if (_front == _back)
	{
		_front = new Node(elem);
		_front->next = _back;
	}
	else
	{
		Node* node = new Node(elem);
		node->next = _front;
		_front = node;
	}
	_incrementSize();
}

template<typename T>
void SList<T>::pushBack(const T& elem)
{
	if (_front == nullptr && _back == nullptr)
	{
		_front = _back = new Node(elem);
	}
	else if (_front == _back)
	{
		_back = new Node(elem);
		_front->next = _back;
	}
	else
	{
		Node* node = new Node(elem);
		_back->next = node;
		_back = _back->next;
	}
	_incrementSize();
}

template<typename T>
void SList<T>::popFront(void)
{
	if (_front && _front == _back)
	{
		delete _front;
	}
	else if (_front)
	{
		Node* tmp = _front;
		_front = _front->next;
		delete tmp;
	}
	_decrementSize();
}

template<typename T>
void SList<T>::popBack(void)
{
	if (_back && _back == _front)
	{
		delete _back;
	}
	else if (_back)
	{
		for (Node* itr = _front; itr; itr = itr->next)
		{
			if (itr->next == _back)
			{
				delete _back;
				_back = itr;
				return;
			}
		}
	}
	_decrementSize();
}

template<typename T>
void SList<T>::insert(const T& elem, Node* next)
{
	for (Node* nItr = _front->next, *pItr = _front; nItr; 
	nItr = nItr->next, pItr = pItr->next)
	{
		if (nItr == next)
		{
			Node* node = new Node(elem);
			node->next = nItr;
			pItr->next = node;
			_incrementSize();
			return;
		}
	}
}

template<typename T>
void SList<T>::append(const T& elem, Node* prev)
{
	for (Node* itr = _front; itr; itr = itr->next)
	{
		if (itr == prev)
		{
			Node* node = new Node(elem);
			node->next = itr->next;
			itr->next = node;
			_incrementSize();
			return;
		}
	}
}

template<typename T>
typename SList<T>::Node* SList<T>::find(const T& elem)
{
	for (Node* itr = _front; itr; itr = itr->next)
	{
		if (itr->data == elem)
		{
			return itr;
		}
	}
	return nullptr;
}

template<typename T>
void SList<T>::erase(Node* node)
{
	if (node == _front)
	{
		popFront();
	}
	else if (node == _back)
	{
		popBack();
	}
	else
	{
		for (Node* nItr = _front->next, *pItr = _front; nItr; nItr = nItr->next, pItr = pItr->next)
		{
			if (node == nItr)
			{
				pItr->next = nItr->next;
				delete nItr;
				_decrementSize();
				return;
			}
		}
	}
}

template<typename T>
void SList<T>::clear(void)
{
	while (!isEmpty())
	{
		popFront();
	}
}

template<typename T>
bool SList<T>::isEmpty(void) const
{
	return !_size;
}

template<typename T>
void SList<T>::print(void)
{
	if (!isEmpty())
	{
		UINT32 count = 0;
		for (Node* itr = _front; itr; count++, itr = itr->next)
		{
			std::cout << count << ": " << itr->data << std::endl;
		}
	}
	else
	{
		std::cout << "SList is empty" << std::endl;
	}
}

template<typename T>
const T& SList<T>::getFront(void) const
{
	return _front->data;
}

template<typename T>
const T& SList<T>::getBack(void) const
{
	return _back->data;
}

template<typename T>
UINT32 SList<T>::getSize(void) const
{
	return _size;
}

/*
=================================

PRIVATE METHODS

=================================
*/

template<typename T>
void SList<T>::_incrementSize(void)
{
	_size++;
}

template<typename T>
void SList<T>::_decrementSize(void)
{
	if (_size)
	{
		_size--;
	}
}