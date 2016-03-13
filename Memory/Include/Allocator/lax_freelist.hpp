#pragma once

#include "freelist.hpp"

template<size_t min,
	size_t max>
class LaxFreeList
{
	inline LaxFreeList(size_t capacity);
	inline ~LaxFreeList();

	inline Block allocate(size_t size);
	inline void deallocate(Block& block);
	inline QBool owns(Block block) const;
	void destroy();
private:
	Node* _getNext(Node* current);
	void _setNext(Node* current, Node* next);
};