#pragma once

#include "..\..\Container\Include\string.hpp"
#include "..\..\Container\Include\vector.hpp"

#define MAX_PATH 64
#define MAX_OSPATH 128

#define PAK_LEN 56
#define MAX_FILES_IN_PACK 2048

//class File
//{
//public:
//	File();
//	File(std::ifstream& input, size_t position = 0);
//	File(const String& name, size_t position = 0);
//
//	void open(const String& name);	
//	void setPosition(size_t pos);
//	void clear();
//
//	const String& name() const;
//	size_t position() const;
//protected:
//	String _name;
//	size_t _position;
//};
//
//class PakFile
//	: public File
//{
//public:
//
//protected:
//
//};
//
////typedef ForwardList<PakFile> Paths;
//
//class SearchPath
//{
//public:
//
//protected:
//	
//};