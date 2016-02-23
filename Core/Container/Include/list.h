#pragma once

/*RENAME TO QLIST*/

/*
==================================

List

==================================
*/

template<typename T>
class List
{
public:
	struct Node
	{
		Node		(T data);
		Node*		next;
		Node*		prev;
		T			data;
	};
	List				(void);
	~List				(void);

	void pushFront			(const T& elem);
	void pushBack			(const T& elem);

	void popBack			(void);
	void popFront			(void);

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
using LNode = typename List<T>::Node;

template<typename T>
using pLNode = typename List<T>::Node*;

/*
=================================

PUBLIC METHODS

=================================
*/

template<typename T>
List<T>::Node::Node(T d)
	: next(nullptr), prev(nullptr), data(d)
{
}

template<typename T>
List<T>::List(void)
	: _front(nullptr), _back(nullptr), _size(0)
{
}

template<typename T>
List<T>::~List(void)
{
	clear();
}

template<typename T>
void List<T>::pushBack(const T& elem)
{
	if (_front == nullptr && _back == nullptr)
	{
		_front = _back = new Node(elem);
	}
	else if(_front == _back)
	{
		_back->next = new Node(elem);
		_back = _back->next;
		_back->prev = _front;
		_front->next = _back;
	}
	else
	{
		Node* tmp = _back;
		_back->next = new Node(elem);
		_back = _back->next;
		_back->prev = tmp;
	}
	_incrementSize();
}

template<typename T>
void List<T>::pushFront(const T& elem)
{
	if (_front == nullptr && _back == nullptr)
	{
		_front = _back = new Node(elem);
	}
	else if (_front == _back)
	{
		_front->prev = new Node(elem);
		_front = _front->prev;
		_front->next = _back;
		_back->prev = _front;
	}
	else
	{
		_front->prev = new Node(elem);
		_front->prev->next = _front;
		_front = _front->prev;
	}
	_incrementSize();
}

template<typename T>
void List<T>::popFront(void)
{
	if (_front && _front == _back)
	{
		delete _front;
	}
	else if (_front)
	{
		_front = _front->next;
		delete _front->prev;
	}
	_decrementSize();
}

template<typename T>
void List<T>::popBack(void)
{
	if (_back && _back == _front)
	{
		delete _back;
	}
	else if (_back)
	{
		_back = _back->prev;
		delete _back->next;
	}
	_decrementSize();
}

template<typename T>
void List<T>::insert(const T& elem, Node* next)
{
	Node* itr = _front;
	while (itr)
	{
		if (itr == next)
		{
			Node* newNode = new Node(elem);
			next->prev->next = newNode;
			newNode->prev = next->prev;
			next->prev = newNode;
			newNode->next = next;
			_incrementSize();
			return;
		}
		else
		{
			itr = itr->next;
		}
	}
}

template<typename T>
void List<T>::append(const T& elem, Node* prev)
{
	Node* itr = _front;
	while (itr)
	{
		if (itr == prev)
		{
			Node* newNode = Node(elem);
			prev->next->prev = newNode;
			newNode->prev = prev;
			newNode->next = prev->next;
			prev->next = newNode;
			_incrementSize();
			return;
		}
		else
		{
			itr = itr->next;
		}
	}
}

template<typename T>
typename List<T>::Node* List<T>::find(const T& elem)
{
	Node* itr = _front;
	while (itr)
	{
		if (itr->data == elem)
		{
			return itr;
		}
		else
		{
			itr = itr->next;
		}
	}
	return nullptr;
}

template<typename T>
void List<T>::erase(Node* del)
{
	if (del == _front)
	{
		popFront();
	}
	else if (del == _back)
	{
		popBack();
	}
	else
	{
		Node* itr = _front;
		while (itr)
		{
			if (itr == del)
			{
				itr->prev->next = del->next;
				del->next->prev = itr->prev;
				delete del;
				_decrementSize();
				return;
			}
			else
			{
				itr = itr->next;
			}
		}
	}
}

template<typename T>
void List<T>::clear(void)
{
	while (!isEmpty())
	{
		popBack();
	}
}

template<typename T>
bool List<T>::isEmpty(void) const
{
	return !_size;
}

template<typename T>
void List<T>::print(void)
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
		std::cout << "List is empty." << std::endl;
	}
}

template<typename T>
const T& List<T>::getFront(void) const
{
	return _front->data;
}

template<typename T>
const T& List<T>::getBack(void) const
{
	return _back->data;
}

template<typename T>
UINT32 List<T>::getSize(void) const
{
	return _size;
}

/*
=================================

PRIVATE METHODS

=================================
*/

template<typename T>
void List<T>::_incrementSize(void)
{
	_size++;
}

template<typename T>
void List<T>::_decrementSize(void)
{
	if (_size)
	{
		_size--;
	}
}