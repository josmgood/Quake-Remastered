#pragma once

/*Standard Library*/
#include <iostream>
#include <memory>

/*Custom Library*/
#include "..\..\Internal\Include\auxiliary.h"

#include "base_allocator.h"

template<size_t chunkSize>
class PoolAllocator
	:	public BaseAllocator,
		public alloc::GetAllocateVoid,
		public alloc::GetDeallocate,
		public alloc::GetOwns,
		public alloc::GetExpand
{
public:
#define CHUNK_HEADER_SIZE		sizeof(internal::Byte*)
#define FULL_CHUNK				(CHUNK_HEADER_SIZE + chunkSize)

	PoolAllocator						(size_t chunkCapacity);
	virtual ~PoolAllocator				(void) override;

	virtual Block allocate				(void) override;
	virtual void deallocate				(Block& block) override;
	virtual bool owns					(Block block) override;
	virtual void expand					(size_t amount)override;
	virtual void reset					(void) override;
	virtual void destory				(void) override;

	size_t getChunkCapacity				(void) const;
	size_t getNumAllocatedChunks		(void) const;
private:
	/*internal::Byte* _getNext			(internal::Byte* block);*/
	void _setNext						(internal::Byte* block, internal::Byte* next);

	/*Searches for free memory*/
	internal::Byte* _search(void);

	internal::Byte**		_pool;
	internal::Byte*			_front;
	size_t					_chunkCapacity;
	size_t					_numAllocatedChunks;
};

#include "..\Source\pool_allocator.inl"