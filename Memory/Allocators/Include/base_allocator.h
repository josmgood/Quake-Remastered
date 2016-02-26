#pragma once

/*Standard Library*/
#include <type_traits>

/*Custom Libraries*/
#include "..\..\..\Core\common.h"

#define ALLOCATED	true
#define FREE		false

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
	Block				(void* addr, size_t size);
	Block				(void);
	void free			(void);

	operator bool(void) const;

	void*		address;
	size_t		size;
};

#define DEAD_BLOCK Block()

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
	virtual ~BaseAllocator		(void) {}
	virtual void reset			(void) = 0;
	virtual void destroy		(void) = 0;
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
	class GetAllocateVoid
	{
	public:
		virtual Block allocate(void) = 0;
	};
	class GetAllocateSize
	{
	public:
		virtual Block allocate(size_t size) = 0;
	};
	class GetAllocateAll
	{
	public:
		virtual bool allocateAll(size_t size) = 0;
	};

	class GetDeallocate
	{
	public:
		virtual void deallocate(Block& block) = 0;
	};

	class GetDeallocateAll
	{
	public:
		virtual bool deallocateAll(void) = 0;
	};

	class GetReallocate
	{
	public:
		virtual bool reallocate(Block& block, size_t newSize) = 0;
	};

	class GetRealloateAll
	{
	public:
		virtual bool reallocateAll(size_t newSize) = 0;
	};

	class GetOwns
	{
	public:
		virtual bool owns(Block block) = 0;
	};

	class GetExpand
	{
	public:
		virtual void expand				(size_t amount) = 0;

		void setExpansionAllowance		(bool expand) { _allowExpansion = expand; }
		bool isAllowingExpansion		(void) const { return _allowExpansion; }
	protected:
		bool _allowExpansion;
	};
}