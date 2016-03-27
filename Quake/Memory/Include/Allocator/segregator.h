#pragma once

/*Custom library*/
#include "..\..\Internal\Include\traits.h"

#include "base_allocator.h"

template<typename threshold,
	typename SmallAllocator,
	typename LargeAllocator>
class Segregator
	:	private SmallAllocator,
		private LargeAllocator
{
public:
	Segregator							(void);
	virtual								~Segregator(void) override;

	virtual Block& allocate				(size_t size) override;
	virtual bool allocateAll			(size_t size) override;
	virtual bool deallocate				(Block& block) override;
	virtual bool deallocateAll			(void) override;
	virtual bool reallocate				(Block& block, size_t newSize) override;
	virtual bool realloateAll			(size_t newSize) override;
	virtual bool owns					(Block block) override;
	virtual void expand					(size_t amount) override;

private:
	Segregator					(const Segregator&) = delete;
	Segregator					(Segregator&&) = delete;
	Segregator& operator=		(Segregator) = delete;
};

///*
//==================================
//
//SEGREGATOR
//
//==================================
//*/
//
//#include "base_allocator.h"
//
//template<size_t threshold,
//	typename SmallAllocator,
//	typename LargeAllocator>
//class Segregator
//	:	private SmallAllocator,
//		private LargeAllocator
//{
//public:
//	Segregator(void);
//
//	virtual Block allocate				(size_t size) override;
//	virtual bool reallocate				(Block& block, size_t newSize) override;
//	virtual void deallocate				(Block& block) override;
//	virtual void deallocateAll			(void) override;
//	//virtual void expand				(Block& block, size_t delta);
//	virtual bool owns					(Block block) override;
//private:
//	Segregator							(const Segregator&) = delete;
//	Segregator							(Segregator&&) = delete;
//	Segregator& operator=				(Segregator) = delete;
//};