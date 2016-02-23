#pragma once

/*Standard Library*/
#include <vector>
#include <string>
#include <memory>

/*
==================================

TYPEDEFS

==================================
*/

/*=========Redefintions========*/
typedef unsigned int					UINT32;

typedef float							float32;
typedef double							float64;

typedef int								int32;
typedef long long						int64;
typedef unsigned int					uint32;
typedef unsigned long long				uint64;

typedef unsigned long					size64;

typedef unsigned char					byte;

typedef std::string						String;
typedef std::vector<std::string>		StringVec;


#define WINDOW_WIDTH		800
#define WINDOW_HEIGHT		600

namespace com
{	
	std::string clipExtension		(const std::string& file);
	bool checkParm					(const StringVec& args, const std::string& parm);
}