

#pragma once


// Inculions STL
#include <string>
#include <functional> 
#include <cctype>


namespace StringTools
{
	//
	bool starts_with(const std::string& str, const std::string& prefix);

	//
	bool end_with(const std::string& str, const std::string& suffix);

	//
	std::string& remove_from_start(std::string& str, const std::string& toRemove);

	//
	std::string& remove_from_end(std::string& str, const std::string& toRemove);

	//
	std::string toUpper(std::string& str);

	//
	std::string toLower(std::string& str);

	// trim from start
	static std::string &ltrim(std::string &s);

	// trim from end
	static std::string &rtrim(std::string &s);

	// trim from both ends
	static std::string &trim(std::string &s);

}