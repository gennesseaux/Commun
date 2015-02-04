

#pragma once


// Inculions
#include <algorithm>
#include <string>

namespace StringTools
{
	//
	inline bool starts_with(const std::string& str, const std::string& prefix)
	{
		return prefix.size() <= str.size() && str.compare(0, prefix.size(), prefix) == 0;
	}

	//
	inline bool end_with(const std::string& str, const std::string& suffix)
	{
		return str.size() >= suffix.size() && str.compare(str.size() - suffix.size(), suffix.size(), suffix) == 0;
	}

	//
	inline std::string& remove_from_start(std::string& str, const std::string& toRemove)
	{
		return Poco::replaceInPlace<std::string>(str, toRemove, "", 0);
	}

	//
	inline std::string& remove_from_end(std::string& str, const std::string& toRemove)
	{
		return Poco::replaceInPlace<std::string>(str, toRemove, "", str.length() - toRemove.length());
	}

}