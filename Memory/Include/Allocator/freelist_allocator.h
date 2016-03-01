//#pragma once
//
///*Custom Library*/
//#include "base_allocator.h"
//
//template<typename Parent, bool isShared, size_t minSize, size_t maxSize, size_t capacity, >
//class FreelistAllocator
//	: public BaseAllocator
//{
//public:
//	FreelistAllocator(void);
//	~FreelistAllocator(void);
//private:
//	struct _Node
//	{
//		_Node*	next;
//		Block	block;
//	};
//	Parent	_parent;
//	Node*	_root;
//};