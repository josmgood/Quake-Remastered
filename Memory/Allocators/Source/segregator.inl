//#include "..\Include\segregator.h"
//
//template<size_t threshold, typename SmallAllocator, typename LargeAllocator>
//Segregator<threshold, SmallAllocator, LargeAllocator>::Segregator(void)
//{
//	if (typeid(SmallAllocator) == typeid(LargeAllocator))
//	{
//		/*Throw an error*/
//	}
//}
//
//template<size_t threshold, typename SmallAllocator, typename LargeAllocator>
//Block Segregator<threshold, SmallAllocator, LargeAllocator>::allocate(size_t size)
//{
//	void* memory = (size > threshold) ?
//		LargeAllocator::allocate(size) : SmallAllocator::allocate(size);
//	Block block(memory, size);
//	return(block);
//}
//
//template<size_t threshold, typename SmallAllocator, typename LargeAllocator>
//bool Segregator<threshold, SmallAllocator, LargeAllocator>::reallocate(Block& block, size_t newSize)
//{
//	/*New Size is bigger than the threshold. Block was previously in smaller allocator.*/
//	if ((newSize > threshold) && (block.length <= threshold))
//	{
//		block.length = newSize;
//		LargeAllocator::allocate(block);
//		SmallAllocator::deallocate(block);
//		return(true);
//	}
//	/*New size and block length are both under threshold.*/
//	else if ((newSize <= threshold) && (block.length <= threshold))
//	{
//		return(SmallAllocator::reallocate(block, newSize));
//	}
//	/*New size is smaller than threshold. Block was previously in larger allocator.*/
//	else if ((newSize <= threshold) && (block.length > threshold))
//	{
//		block.length = newSize;
//		SmallAllocator::allocate(block);
//		LargeAllocator::deallocate(block);
//		return(true);
//	}
//	return(false);
//}
//
//template<size_t threshold, typename SmallAllocator, typename LargeAllocator>
//void Segregator<threshold, SmallAllocator, LargeAllocator>::deallocate(Block& block)
//{
//	if (block) /*We do not want to deallocate a free block*/
//	{
//		(block > threshold) ?
//			LargeAllocator::deallocate(block) : SmallAllocator::deallocate(block);
//	}
//}
//
//template<size_t threshold, typename SmallAllocator, typename LargeAllocator>
//void Segregator<threshold, SmallAllocator, LargeAllocator>::deallocateAll(void)
//{
//	SmallAllocator::deallocateAll();
//	LargeAllocator::deallocateAll();
//}
//
//template<size_t threshold, typename SmallAllocator, typename LargeAllocator>
//bool Segregator<threshold, SmallAllocator, LargeAllocator>::owns(Block block)
//{
//	return((block.length > threshold)
//		? LargeAllocator::owns(block) : SmallAllocator::owns(block));
//}