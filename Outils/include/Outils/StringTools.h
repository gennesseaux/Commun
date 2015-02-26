

#pragma once


// Inculions STL
#include <algorithm>
#include <string>

// Inculions Poco
#include <Poco/Foundation.h>
#include <Poco/Format.h>
#include <Poco/String.h>


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

	//
	inline std::string toUpper(std::string& str)
	{
		return Poco::toUpper(str);
	}

	//
	inline std::string toLower(std::string& str)
	{
		return Poco::toLower(str);
	}

}