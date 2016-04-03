#include "..\..\Quake\Container\Include\Stack.hpp"

#include <GTest\gtest.h>

#define NAME DISABLED_Stack

TEST(NAME, CONSTRUCTOR)
{
	Stack<int> one(5);
	for (size_t i = 1; i < 11; ++i)
	{
		one.push(i * i);
	}
	Stack<int> two(one);
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
	Stack<int> three(nums, 15);
	EXPECT_EQ(196, three.peek());
}

TEST(NAME, SET)
{
	Stack<int> one;
	one.push(100);
	EXPECT_EQ(100, one.peek());
	one.set(400);
	EXPECT_EQ(400, one.peek());

	Stack<int> two;
	two.set(100000);
	EXPECT_EQ(100000, two.peek());
}

TEST(NAME, PUSH)
{
	Stack<int> stack(100);
	stack.push(3749827);
	EXPECT_EQ(3749827, stack.peek());
	Stack<int> other(10);
	for (size_t i = 1; i < 11; ++i)
	{
		other.push(i * i);
	}
	stack.push(other);
	EXPECT_EQ(100, stack.peek());
}

TEST(NAME, POP)
{
	Stack<int> stack(10);
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

TEST(NAME, TAKE)
{
	Stack<int> stack(10);
	int num1 = stack.take();
	EXPECT_EQ(Stack<int>::EMPTY_VALUE, num1);
	for (size_t i = 1; i < 11; ++i)
	{
		stack.push(i);
	}
	int num2 = stack.take();
	EXPECT_EQ(10, num2);
}

TEST(NAME, REVERSED)
{
	Stack<int> stack(10);
	for (size_t i = 1; i < 11; ++i)
	{
		stack.push(i);
	}
	Stack<int> reversed = stack.getReversed();
	EXPECT_EQ(1, reversed.peek());

	stack.reverse();
	EXPECT_EQ(1, stack.peek());
}

TEST(NAME, COPY)
{
	Stack<int> stk1(10);
	Stack<int> stk2(2);
	Stack<int> stk3(1);
	for (size_t i = 0; i < 10; ++i)
	{
		stk1.push(i);
	}
	stk2 = stk1;
	stk3.copy(stk2);
	EXPECT_EQ(true, stk2.peek() == stk1.peek());
	EXPECT_EQ(true, stk3.peek() == stk1.peek());
}

TEST(NAME, SWAP)
{
	Stack<int> stk1(10);
	Stack<int> stk2(10);
	for (size_t i = 1; i < 11; ++i)
	{
		if (i % 2 == 0)
		{
			stk1.push(i);
		}
		if (i % 3 == 0)
		{
			stk2.push(i);
		}
	}
	std::cout << stk1 << std::endl;
	std::cout << stk2 << std::endl;
	stk1.swap(stk2);
	std::cout << stk1 << std::endl;
	std::cout << stk2 << std::endl;

	EXPECT_EQ(10, stk2.peek());
	EXPECT_EQ(9, stk1.peek());
}

TEST(NAME, SHRINK)
{
	Stack<int> stk1(5);
	for (size_t i = 1; i < 6; ++i)
	{
		stk1.push(i);
	}
	stk1.shrink(3);
	EXPECT_EQ(3, stk1.peek());

	Stack<int> stk2(10);
	for (size_t i = 1; i < 11; ++i)
	{
		stk2.push(i);
	}
	for (int32 i = 4; i >= 1; --i)
	{
		stk2.resize(i);
		EXPECT_EQ(i, stk2.peek());
		EXPECT_EQ(i, stk2.getMaxSize());
		EXPECT_EQ(i, stk2.getSize());
	}
}

TEST(NAME, OPERATOR_PLUS)
{
	Stack<int> stk1(10);
	Stack<int> stk2(10);
	stk1.push(1);
	stk2.push(3);
	Stack<int> stk3 = stk1 + stk2;
	EXPECT_EQ(1, stk1.peek());
	EXPECT_EQ(3, stk3.peek());
	EXPECT_EQ(2, stk3.getSize());
}

TEST(NAME, OPERATOR_EQUAL_TO)
{
	Stack<int> stk1(10);
	Stack<int> stk2(10);
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
	Stack<int> stk1(10);
	Stack<int> stk2(10);
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
	Stack<int> stk1(10);
	Stack<int> stk2(10);
	EXPECT_EQ(false, stk1 < stk2);
	for (size_t i = 0; i < 10; ++i)
	{
		stk1.push(i * i);
		stk2.push(i);
	}
	EXPECT_EQ(false, stk1 < stk2);
}

TEST(NAME, OPERATOR_LESS_OR_EQUAL_TO)
{
	Stack<int> stk1(10);
	Stack<int> stk2(10);
	for (size_t i = 0; i < 10; ++i)
	{
		stk1.push(i * i);
		stk2.push(i);
	}
	EXPECT_EQ(false, stk1 <= stk2);
}

TEST(NAME, OPERATOR_GREATER_THAN)
{
	Stack<int> stk1(10);
	Stack<int> stk2(10);
	for (size_t i = 0; i < 10; ++i)
	{
		stk1.push(i * i);
		stk2.push(i);
	}
	EXPECT_EQ(false, stk1 > stk2);
}

TEST(NAME, OPERATOR_GREATER_OR_EQUAL_TO)
{
	Stack<int> stk1(10);
	Stack<int> stk2(10);
	for (size_t i = 0; i < 10; ++i)
	{
		stk1.push(i * i);
		stk2.push(i);
	}
	EXPECT_EQ(true, stk1 >= stk2);
}