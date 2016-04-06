#include "..\..\Quake\Container\Include\vector.hpp"

#include <GTest\gtest.h>

#define NAME VECTOR

TEST(NAME, CONSTRUCTOR)
{
	Vector<int> vector;
	EXPECT_EQ(DEFAULT_CONTAINER_SIZE, vector.maxSize());

	vector.pushBack(10);
	vector.pushBack(100);
	vector.pushBack(1000);
	EXPECT_EQ(1000, vector.back());
	EXPECT_EQ(3, vector.size());
	EXPECT_EQ(DEFAULT_CONTAINER_SIZE, vector.maxSize());

	Vector<int> vector2(vector);
	EXPECT_EQ(1000, vector2.back());
	EXPECT_EQ(3, vector2.size());
	EXPECT_EQ(DEFAULT_CONTAINER_SIZE, vector.maxSize());

	Vector<int> vector3(vector.begin(), vector.end());
	EXPECT_EQ(1000, vector3.back());
	EXPECT_EQ(3, vector3.size());
	EXPECT_EQ(3, vector3.maxSize());
}

TEST(NAME, BACK)
{
	Vector<int> vector(1);
	vector.pushBack(10);
	vector.pushBack(100);
	EXPECT_EQ(2, vector.size());
	EXPECT_EQ(4, vector.maxSize());
	EXPECT_EQ(10, vector.front());
	EXPECT_EQ(100, vector.back());

	vector.popBack();
	EXPECT_EQ(10, vector.front());
	EXPECT_EQ(10, vector.back());
}

TEST(NAME, SEARCH)
{
	Vector<int> vector;
	for (size_t i = 1; i < 100; i++)
	{
		vector.pushBack(i * i);
	}
	Vector<int>::Iterator found = vector.find(25);
	EXPECT_EQ(16, (found - 1).get());

	found = vector.find(9801);
	EXPECT_EQ(vector.end(), ++found);

	QBool has = vector.has(100);
	EXPECT_EQ(true, has);
}

TEST(NAME, COPY)
{
	Vector<int> vector;
	for (size_t i = 0; i < DEFAULT_CONTAINER_SIZE; i++)
	{
		vector.pushBack(i * i);
	}

	Vector<int> vector2;
	vector2.copy(vector);
	for (size_t i = 0; i < DEFAULT_CONTAINER_SIZE; i++)
	{
		EXPECT_EQ(true, vector2[i] == vector[i]);
		EXPECT_EQ(false, (void*)&vector2[i] == (void*)&vector[i]);
	}

	Vector<int> vector3 = vector2;
	for (size_t i = 0; i < DEFAULT_CONTAINER_SIZE; i++)
	{
		EXPECT_EQ(true, vector2[i] == vector3[i]);
		EXPECT_EQ(false, (void*)&vector2[i] == (void*)&vector3[i]);
	}
}

TEST(NAME, CLEAR)
{
	Vector<int> vector;
	for (size_t i = 0; i < DEFAULT_CONTAINER_SIZE; i++)
	{
		vector.pushBack(i);
	}
	EXPECT_EQ(DEFAULT_CONTAINER_SIZE, vector.size());
	EXPECT_EQ(DEFAULT_CONTAINER_SIZE, vector.maxSize());
	EXPECT_EQ(false, !vector.array());

	vector.clear();
	EXPECT_EQ(0, vector.size());
	EXPECT_EQ(0, vector.maxSize());
	EXPECT_EQ(true, !vector.array());
	vector.pushBack(10000);
	EXPECT_EQ(10000, vector.back());
}

TEST(NAME, RESERVE)
{
	Vector<int> vector(4);
	for (size_t i = 1; i < 5; i++)
	{
		vector.pushBack(i);
	}
	EXPECT_EQ(4, vector.back());
	EXPECT_EQ(4, vector.size());
	EXPECT_EQ(4, vector.maxSize());

	for (size_t i = 5; i < 101; i++)
	{
		vector.pushBack(i);
	}
	EXPECT_EQ(100, vector.back());
	EXPECT_EQ(false, !vector.array());
	EXPECT_EQ(100, vector.size());
	EXPECT_EQ(100, vector.maxSize());
}

TEST(NAME, SHRINK)
{
	Vector<int> vector(4);
	for (size_t i = 1; i < 5; i++)
	{
		vector.pushBack(i);
	}
	EXPECT_EQ(4, vector.back());
	vector.shrink(2);
	EXPECT_EQ(2, vector.back());
	EXPECT_EQ(2, vector.size());
	EXPECT_EQ(2, vector.maxSize());
}

TEST(NAME, INDEX_ACCESS)
{
	Vector<int> vector(10);
	EXPECT_EQ(Vector<int>::EMPTY_VALUE, vector[2]);
	for (size_t i = 1; i < 11; i++)
	{
		vector.pushBack(i);
	}
	EXPECT_EQ(10, vector[9]);
	EXPECT_EQ(Vector<int>::EMPTY_VALUE, vector.at(100));

	Vector<int> vector2(1);
	vector2.pushBack(1);
	EXPECT_EQ(1, vector2[0]);
	EXPECT_EQ(1, vector2.maxSize());
}

TEST(NAME, OPERATOR_EQUALS)
{
	Vector<int> vector;
	Vector<int> vector2;
	for (size_t i = 0; i < 10; i++)
	{
		vector.pushBack(i);
		vector2.pushBack(i);
	}
	EXPECT_EQ(true, vector == vector2);
	EXPECT_EQ(true, vector.equals(vector2));
	EXPECT_EQ(false, vector == Vector<int>());
}

TEST(NAME, OPERATOR_NOT_EQUALS)
{
	Vector<int> vector;
	Vector<int> vector2;
	for (size_t i = 0; i < 10; i++)
	{
		vector.pushBack(i);
		vector2.pushBack(i * i);
	}
	EXPECT_EQ(true, vector != vector2);
	EXPECT_EQ(true, vector != Vector<int>());
}

TEST(NAME, OPERATOR_LESS_THAN)
{
	Vector<int> vector;
	Vector<int> vector2;
	for (size_t i = 2; i < 10; i++)
	{
		vector.pushBack(i);
		vector2.pushBack(i * i);
	}
	EXPECT_EQ(true, vector < vector2);
	EXPECT_EQ(false, vector < Vector<int>());
}

TEST(NAME, OPERATOR_LESS_OR_EQUAL)
{
	Vector<int> vector;
	Vector<int> vector2;
	for (size_t i = 0; i < 10; i++)
	{
		vector.pushBack(i);
		vector2.pushBack(i * i);
	}
	EXPECT_EQ(true, vector <= vector2);
	EXPECT_EQ(false, vector <= Vector<int>());
}

TEST(NAME, OPERATOR_GREATER_THAN)
{
	Vector<int> vector;
	Vector<int> vector2;
	for (size_t i = 2; i < 10; i++)
	{
		vector.pushBack(i);
		vector2.pushBack(i * i);
	}
	EXPECT_EQ(true, vector2 > vector);
	EXPECT_EQ(true, vector > Vector<int>());
}

TEST(NAME, OPERATOR_GREATER_OR_EQUAL)
{
	Vector<int> vector;
	Vector<int> vector2;
	for (size_t i = 0; i < 10; i++)
	{
		vector.pushBack(i);
		vector2.pushBack(i * i);
	}
	EXPECT_EQ(true, vector2 >= vector);
	EXPECT_EQ(true, vector >= Vector<int>());
}

TEST(NAME, ITERATOR)
{
	Vector<int> vector(10);
	for (size_t i = 0; i < 10; i++)
	{
		vector.pushBack(i);
	}
	size_t j = 0;
	for (Vector<int>::Iterator i = vector.begin(); i != vector.end(); ++i, ++j)
	{
		EXPECT_EQ(j, i.get());
	}
}

TEST(NAME, REVERSE_ITERATOR)
{
	Vector<int> vector(10);
	for (size_t i = 0; i < 10; i++)
	{
		vector.pushBack(i);
	}
	size_t j = 9;
	for (Vector<int>::ReverseIterator i = vector.rbegin(); i != vector.rbegin(); ++i, ++j)
	{
		EXPECT_EQ(j, i.get());
	}
}