#include "common.h"

namespace com
{
	std::string clipExtension(const std::string& file)
	{
		std::string extension = std::string();
		for (UINT32 i = 0; i < file.length(); i++)
		{
			if (file.at(i) == '.')
			{
				extension = file.substr(i + 1, file.npos);
				return extension;
			}
		}
		return std::string();
	}
	bool checkParm(const StringVec& args, const std::string& parm)
	{
		for (UINT32 i = 0; i < args.size(); i++)
		{
			if (args.at(i) != parm)
			{
				return false;
			}
		}
		return true;
	}
}