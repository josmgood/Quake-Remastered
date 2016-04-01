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

TEST(NAME, COPY)
{
	QStack<int> stk1(10);
	QStack<int> stk2(2);
	QStack<int> stk3(1);
	for (size_t i = 0; i < 10; ++i)
	{
		stk1.push(i);
	}
	stk2 = stk1;
	stk3.copy(stk2);
	EXPECT_EQ(true, stk2.peek() == stk1.peek());
	EXPECT_EQ(true, stk3.peek() == stk1.peek());
}

TEST(NAME, OPERATOR_EQUAL_TO)
{
	QStack<int> stk1(10);
	QStack<int> stk2(10);
	EXPECT_EQ(true, stk1 == stk2);
	for (size_t i = 0; i < 5; ++i)
	{
		stk1.push(i);
		stk2.push(i);
	}
	EXPECT_EQ(true, stk1 == stk2);
	stk2.pop();
	EXPECT_EQ(false, stk1 == stk2);
	EXPECT_EQ(false, stk1.equals(stk2));
	stk2.pop();
	stk1.pop(2);
	EXPECT_EQ(true, stk1 == stk2);
	EXPECT_EQ(true, stk1.equals(stk2));
}

TEST(NAME, OPERATOR_NOT_EQUAL_TO)
{
	QStack<int> stk1(10);
	QStack<int> stk2(10);
	EXPECT_EQ(false, stk1 != stk2);

	for (size_t i = 0; i < 10; ++i)
	{
		stk1.push(i);
		stk2.push(i * i);
	}
	EXPECT_EQ(true, stk1 != stk2);
}

TEST(NAME, OPERATOR_LESS_THAN)
{
	/*QStack<int> stk1(10);
	QStack<int> stk2(10);
	EXPECT_EQ(false, stk1 < stk2);

	for (size_t i = 0; i < 10; ++i)
	{
		stk1.push(i);
		stk2.push(i * i);
	}
	EXPECT_EQ(true, stk1 < stk2);*/
}