#include "..\..\Quake\Container\Include\qstring.h"

#include <GTest\gtest.h>

#define NAME QSTRING

TEST(NAME, FRONT)
{
	QString string(15);
	string.pushFront('W');
	string.pushFront('Y');
	EXPECT_EQ('Y', string.getFront());

	string.setFront('Z');
	EXPECT_EQ('Z', string.getFront());

	/*string.pushFront("Hello");
	std::cout << string << std::endl;
	EXPECT_EQ(true, string.getFront() == 'H');
	EXPECT_EQ(true, string.getBack() == 'W');*/
}

TEST(NAME, BACK)
{
	QString string(1);
	string.pushBack('h');
	EXPECT_EQ('h', string.getBack());

	string.setBack('Z');
	EXPECT_EQ('Z', string.getBack());

	/*string.pushBack("Hello");
	EXPECT_EQ(true, string.getBack() == 'o');
	EXPECT_EQ(true, string.getFront() == 'h');*/
}

TEST(NAME, CONCAT)
{
	QString string(4);
	string.concat("Hello");
	EXPECT_EQ('H', string.getFront());

	string.concat("WorldDD");
	EXPECT_EQ('D', string.getBack());

	string.concat(QString("Goodbye!"));
	EXPECT_EQ('!', string.getBack());
}

TEST(NAME, SET)
{
	QString string("Hello");
	string.set(0, 'W');
	string.set(1, 'D');
	EXPECT_EQ('W', string.getFront());
	EXPECT_EQ('D', string.at(1));

	const char* swag = "Swags";
	string.set(2, 4, swag);
	EXPECT_EQ('S', string.at(2));
	EXPECT_EQ('w', string.at(3));
	EXPECT_EQ('a', string.at(4));
	//EXPECT_EQ('g', string.at(4));

	QString other("Goody");
	string.set(0, 4, other);
	EXPECT_EQ('G', string.at(0));
	EXPECT_EQ('o', string.at(1));
	EXPECT_EQ('o', string.at(2));
	EXPECT_EQ('d', string.at(3));
	EXPECT_EQ('y', string.at(4));

	QString hello("Hello");
	hello.set(2, 4, "EIS");
	EXPECT_EQ('E', hello.at(2));
	EXPECT_EQ('I', hello.at(3));
	EXPECT_EQ('S', hello.at(4));
}

TEST(NAME, SUBSTRING)
{
	QString string("This is a long string.");
	QString sub1 = string.substring(3);
	EXPECT_EQ(sub1[0], string[3]);
	EXPECT_EQ(sub1.getLength(), string.getLength() - 3);
	EXPECT_EQ(true, !string.substring(1000));

	QString sub2 = string.substring(4, 9);
	size_t len = sub2.getLength();
	//std::cout << "Substring: " << sub2 << std::endl;
	//std::cout << sub2[len -1 ] << std::endl;
	//std::cout << string[8] << std::endl;
	//EXPECT_EQ(sub2[0], string[4]);
	//EXPECT_EQ(sub2[len - 1], string[8]);
}

TEST(NAME, FIND)
{
	QString str1("Hello");
	QString::Iterator found = str1.find('e');
	EXPECT_EQ('e', found.get());

	found = str1.find('l', 1);
	EXPECT_EQ('e', (found - 1).get());

	found = str1.find('l', 2);
	EXPECT_EQ('l', (found - 1).get());

	found = str1.find("ElLo", 1, STR_INSENSITIVE);
	EXPECT_EQ('e', found.get());

	found = str1.find(QString("HELLO"));
	EXPECT_EQ('\0', found.get());

	QString str2("Hello Hello");
	found = str2.find("Hello", 2);
	EXPECT_EQ(' ', (found - 1).get());

	found = str2.find("Hello", 3);
	EXPECT_EQ('\0', found.get());

	found = str2.find(QString("LLo"), 2, STR_INSENSITIVE);
	EXPECT_EQ('l', found.get());
}

TEST(NAME, RFIND)
{
	/*QString string("Hello");
	QString::ReverseIterator found = string.rfind('H');
	EXPECT_EQ('H', found.get());

	found = string.rfind('L', STR_INSENSITIVE);
	EXPECT_EQ('l', found.get());

	found = string.rfind("llo");
	EXPECT_EQ('o', found.get());*/

}

TEST(NAME, FIND_LAST)
{
	QString str1("Hello World");
	QString::Iterator found = str1.findLast('L', STR_INSENSITIVE);
	EXPECT_EQ('r', (found - 1).get());

	found = str1.findLast('o');
	EXPECT_EQ('W', (found - 1).get());

	QString str2("oollloollloolllZoolllooMllloolllo");
	found = str2.findLast("llloo");
	EXPECT_EQ('M', (found - 1).get());

	QString other("oollloo");
	found = str2.findLast(other);
	EXPECT_EQ('Z', (found - 1).get());
}

TEST(NAME, HAS)
{
	QString string("775191asdfaf0362asdfasdfmljk");
	EXPECT_EQ(true, string.has('3'));
	EXPECT_EQ(false, string.has("ashdjfoiasodfkj"));
	EXPECT_EQ(false, string.has("7519 1asdfa"));
	EXPECT_EQ(true, string.has(QString("asdfmljk"), STR_INSENSITIVE));
}

//TEST(NAME, GET_FRONT)
//{
//	/*QString string("Hello World");
//	EXPECT_EQ('H', string.getFront());
//	string.pushFront('_');
//	EXPECT_EQ('_', string.getFront());*/
//}

//TEST(NAME, RESERVE)
//{
//	QString string("Hello World");
//	size_t len = string.getLength() + 1;
//	string.reserve(len);
//	EXPECT_EQ(len, string.getMaxLength());
//}

TEST(NAME, CSTRING_COPY)
{
	QString string;
	string.copy("Hello World");
	EXPECT_EQ(true, string == "Hello World");
}

TEST(NAME, COPY)
{
	QString string("Hello World");
	QString other;
	other.copy(string);
	EXPECT_EQ(true, string == other);
}

TEST(NAME, EQUAL)
{
	QString one("Hello World");
	QString two("Hello World");
	QString three("Hello Wor");
	EXPECT_EQ(true, one == two);
	EXPECT_EQ(false, one == three);
	EXPECT_EQ(true, one == "Hello World");
	EXPECT_EQ(true, one.equals("Hello World"));
}

TEST(NAME, UNEQUAL)
{
	QString one("Hello World");
	QString two("Hello Worl");
	QString three("Hello World");
	EXPECT_EQ(true, one != two);
	EXPECT_EQ(false, one != three);
	EXPECT_EQ(true, two != "Goodbye World!");
	EXPECT_EQ(false, !one.equals("Hello World"));
}

TEST(NAME, OPERATOR_LESSER)
{
	QString one("Hello Wo");
	QString two("Hello Wor");
	EXPECT_EQ(true, one < two);
	EXPECT_EQ(true, one < "Hello Wor");
	EXPECT_EQ(true, one < "hello world");
	EXPECT_EQ(false, one < "All the people.");
}

TEST(NAME, OPERATOR_LESSER_EQUAL)
{
	QString one("Hello Wo");
	QString two("Hello Wor");
	EXPECT_EQ(true, one <= two);
	EXPECT_EQ(true, one <= one);
	EXPECT_EQ(false, two <= one);
	EXPECT_EQ(false, two <= "AAAAAAAAAAAAAAAAA");
}

TEST(NAME, OPERATOR_GREATER)
{
	QString one("Hello Wo");
	QString two("Hello Wor");
	EXPECT_EQ(true, two > one);
	EXPECT_EQ(false, one > two);
	EXPECT_EQ(true, one > "Hello");
}

TEST(NAME, OPERATOR_GREATER_EQUAL)
{
	QString one("Hello World");
	QString two("Hello World!");
	EXPECT_EQ(true, two >= one);
	EXPECT_EQ(false, two >= "Hello World!!");
	EXPECT_EQ(true, two >= "Hello World");
}

TEST(NAME, BEGIN_END)
{
	QString str1("Hello World");
	QString::Iterator begin = str1.getBegin();
	QString::Iterator end = str1.getEnd();
	EXPECT_EQ('H', begin.get());
	EXPECT_EQ('d', (end - 1).get());

	QString str2;
	begin = str2.getBegin();
	end = str2.getEnd();
	EXPECT_EQ('\0', begin.get());
	EXPECT_EQ('\0', end.get());

	str2.pushFront('h');
	str2.pushBack('g');
	begin = str2.getBegin();
	end = str2.getEnd();
	EXPECT_EQ('h', begin.get());
	EXPECT_EQ('\0', end.get());
}

TEST(NAME, CBEGIN_CEND)
{
	QString str1("Hello World");
	QString::ConstIterator begin = str1.getCBegin();
	QString::ConstIterator end = str1.getCEnd();

	EXPECT_EQ('H', begin.get());
	EXPECT_EQ('d', (end - 1).get());

	QString str2;
	begin = str2.getCBegin();
	end = str2.getCEnd();
	EXPECT_EQ('\0', begin.get());
	EXPECT_EQ('\0', end.get());

	str2.pushFront('h');
	str2.pushBack('g');
	begin = str2.getCBegin();
	end = str2.getCEnd();
	EXPECT_EQ('h', begin.get());
	EXPECT_EQ('\0', end.get());
}

TEST(NAME, RBEGIN_REND)
{
	QString str1("Hello World");
	QString::ReverseIterator begin = str1.getRBegin();
	QString::ReverseIterator end = str1.getREnd();
	EXPECT_EQ('d', begin.get());
	EXPECT_EQ('H', (end - 1).get());

	QString str2;
	begin = str2.getRBegin();
	end = str2.getREnd();
	EXPECT_EQ('\0', (begin - 1).get());
	EXPECT_EQ('\0', (end - 1).get());

	str2.pushFront('h');
	str2.pushBack('g');
	begin = str2.getRBegin();
	end = str2.getREnd();
	EXPECT_EQ('g', begin.get());
	EXPECT_EQ('h', (end - 1).get());
}

TEST(NAME, CRBEGIN_CREND)
{
	QString str1("Hello World");
	QString::ConstReverseIterator begin = str1.getCRBegin();
	QString::ConstReverseIterator end = str1.getCREnd();
	EXPECT_EQ('d', begin.get());
	EXPECT_EQ('H', (end - 1).get());

	QString str2;
	begin = str2.getCRBegin();
	end = str2.getCREnd();
	EXPECT_EQ('\0', (begin - 1).get());
	EXPECT_EQ('\0', (end - 1).get());

	str2.pushFront('h');
	str2.pushBack('g');
	begin = str2.getCRBegin();
	end = str2.getCREnd();
	EXPECT_EQ('g', begin.get());
	EXPECT_EQ('h', (end - 1).get());
}