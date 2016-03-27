//#include "..\Include\fallback_allocator.h"
//
//template<typename Primary, typename Fallback>
//FallbackAllocator<Primary, Fallback>::FallbackAllocator(void)
//{
//	if (typeid(Primary) == typeid(Fallback))
//	{
//		/*error*/
//	}
//}
//
//template<typename Primary, typename Fallback>
//Block FallbackAllocator<Primary, Fallback>::allocate(size_t size)
//{
//	Block block = Primary::allocate(size);
//	if (!block)
//	{
//		block = Fallback::allocate(size);
//	}
//	return block;
//}
//
//template<typename Primary, typename Fallback>
//bool FallbackAllocator<Primary, Fallback>::reallocate(Block& block, size_t newSize)
//{
//	if (Primary::owns(block))
//	{
//		return(Primary::reallocate(block, newSize));
//	}
//	else if(Fallback::owns(block))
//	{
//		return(Fallback::owns(block, newSize));
//	}
//	return(false);
//}
//
//template<typename Primary, typename Fallback>
//void FallbackAllocator<Primary, Fallback>::deallocate(Block& block)
//{
//	if (Primary::owns(block))
//	{
//		Primary::deallocate(block);
//	}
//	else if (Fallback::owns(block))
//	{
//		Fallback::owns(block);
//	}
//}
//
//template<typename Primary, typename Fallback>
//void FallbackAllocator<Primary, Fallback>::deallocateAll(void)
//{
//	Primary::deallocateAll();
//	Fallback::deallocateAll();
//}
//
//template<typename Primary, typename Fallback>
//bool FallbackAllocator<Primary, Fallback>::owns(Block block)
//{
//	return(Primary::owns(block) || Fallback::owns(block));
//}