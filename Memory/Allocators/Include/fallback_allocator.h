//#pragma once
//
///*Standard Library*/
//#include <typeinfo>
//
///*Custom Library*/
//#include "base_allocator.h"
//
//template<typename Primary, typename Fallback>
//class FallbackAllocator
//	:	public Primary,
//		public Fallback
//{
//public:
//	FallbackAllocator					(void);
//	virtual Block allocate				(size_t size) override;
//	virtual bool reallocate				(Block& block, size_t newSize) override;
//	virtual void deallocate				(Block& block) override;
//	virtual void deallocateAll			(void) override;
//	virtual bool owns					(Block block) override;
//};