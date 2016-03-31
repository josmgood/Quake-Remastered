#include "..\..\Quake\Container\Include\qstack.hpp"

#include <GTest\gtest.h>

#define NAME QSTACK

TEST(NAME, CONSTRUCTOR)
{
	QStack<int> one(5);
	for (size_t i = 1; i < 11; ++i)
	{
		one.push(i * i);
	}
	QStack<int> two(one);
	EXPECT_EQ(5, two.getSize());
	EXPECT_EQ(25, two.peek());

	for (size_t i = 1; i < 6; ++i)
	{
		one.pop();
	}
	EXPECT_EQ(0, one.getSize());

	int* nums = new int[15];
	for (int32 i = 0; i < 15; ++i)
	{
		nums[i] = i * i;
	}
	QStack<int> three(nums, 15);
	EXPECT_EQ(196, three.peek());
}

TEST(NAME, SET)
{
	QStack<int> one;
	one.push(100);
	EXPECT_EQ(100, one.peek());
	one.set(400);
	EXPECT_EQ(400, one.peek());

	QStack<int> two;
	two.set(100000);
	EXPECT_EQ(100000, two.peek());
}

TEST(NAME, PUSH)
{
	QStack<int> stack(100);
	stack.push(3749827);
	EXPECT_EQ(3749827, stack.peek());
	QStack<int> other(10);
	for (size_t i = 1; i < 11; ++i)
	{
		other.push(i * i);
	}
	stack.push(other);
	EXPECT_EQ(100, stack.peek());

	int* nums = new int[10];
	for (size_t i = 1; i < 11; ++i)
	{
		nums[i - 1] = i * i * i;
	}
	stack.push(nums, 10);
	EXPECT_EQ(1000, stack.peek());
}

TEST(NAME, POP)
{
	QStack<int> stack(10);
	for (size_t i = 1; i <= 8; ++i)
	{
		stack.push(i);
	}
	stack.pop(3);
	EXPECT_EQ(5, stack.peek());
	for (size_t i = 0; i < 2; ++i)
	{
		stack.pop();
	}
	EXPECT_EQ(3, stack.peek());
}