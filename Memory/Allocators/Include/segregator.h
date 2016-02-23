//#pragma once
//
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