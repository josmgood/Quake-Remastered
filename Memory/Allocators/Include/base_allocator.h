#pragma once

/*Standard Library*/
#include <type_traits>

/*Custom Libraries*/
#include "..\..\..\Core\common.h"

#define ALLOCATED	1
#define FREE		0

/*
*======================================================================
* 
* MEMORY BLOCK
*
* Fundamental data structure in an allocator.
*
* void* memory -		memory held within the block
* size_t size -			size of the block
* size_t alignment -	alignment to fit perfectly in an allocator
*
*======================================================================
*/
struct Block
{
	Block(void* addr, size_t size);
	Block();
	void free();

	operator bool() const;

	void*		address;
	size_t		size;
};

#define DEAD_BLOCK		Block()
#define DEAD_BLOCKS		nullptr

/*
*========================================================================
*
* BASE ALLOCATOR
*
* Allocator interface. Key component for allocator composition.
*
*========================================================================
*/
class BaseAllocator
{
public:
	inline BaseAllocator(size_t capacity);
	virtual inline ~BaseAllocator() {}
	virtual inline bool owns(Block block) = 0;
	virtual inline void reset();
	virtual inline void destroy() = 0;
	
	inline size_t getCapacity() const;
	inline size_t getAllocatedSize() const;
	inline size_t getNumAllocations() const;
protected:
	inline void _setCapacity(size_t capac);
	inline void _addCapacity(size_t amount);

	inline void _setAllocationSize(size_t size);
	inline void _addAllocationSize(size_t amount);
	inline void _subAllocationSize(size_t amount);

	inline void _setNumAllocations(size_t num);
	inline void _incrementNumAllocations();
	inline void _decrementNumAllocations();

	size_t _capacity;
	size_t _allocatedSize;
	size_t _numAllocations;
};

/*
*===========================================================================================
*
* ALLOC NAMESPACE
*
* Contains allocator components for robust allocator composition.
* Motivation - Not every allocator requires every type of method.
*
*===========================================================================================
*/
namespace alloc
{
	class GetAllocate
	{
	public:
		virtual inline Block* allocate(size_t size = 1) = 0;
	};

	class GetAllocateAll
	{
	public:
		virtual inline bool allocateAll(size_t size) = 0;
	};

	class GetDeallocate
	{
	public:
		virtual inline void deallocate(Block* blocks, size_t amount = 1) = 0;
	};

	class GetDeallocateAll
	{
	public:
		virtual inline bool deallocateAll(void) = 0;
	};

	class GetReallocate
	{
	public:
		virtual inline bool reallocate(Block& block, size_t newSize) = 0;
	};

	class GetRealloateAll
	{
	public:
		virtual inline bool reallocateAll(size_t newSize) = 0;
	};

	class GetExpand
	{
	public:
		virtual inline void expand(size_t amount) = 0;

		void inline setExpansionAllowance(bool expand) { _allowExpansion = expand; }
		bool inline isAllowingExpansion(void) const { return _allowExpansion; }
	protected:
		bool _allowExpansion;
	};
}