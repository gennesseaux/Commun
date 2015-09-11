

#pragma once


// Inculions STL
#include <algorithm>
#include <functional> 
#include <cctype>
#include <locale>
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

	// trim from start
	static inline std::string &ltrim(std::string &s)
	{
		s.erase(s.begin(),std::find_if(s.begin(),s.end(),std::not1(std::ptr_fun<int,int>(std::isspace))));
		return s;
	}

	// trim from end
	static inline std::string &rtrim(std::string &s)
	{
		s.erase(std::find_if(s.rbegin(),s.rend(),std::not1(std::ptr_fun<int,int>(std::isspace))).base(),s.end());
		return s;
	}

	// trim from both ends
	static inline std::string &trim(std::string &s)
	{
		return ltrim(rtrim(s));
	}

}