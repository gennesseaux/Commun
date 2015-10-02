
// Inculions
#include "Outils/StringTools.h"

// Inclusion Poco
#include <Poco/Foundation.h>
#include <Poco/Format.h>
#include <Poco/String.h>


bool StringTools::starts_with(const std::string& str,const std::string& prefix)
{
	return prefix.size() <= str.size() && str.compare(0,prefix.size(),prefix) == 0;
}

bool StringTools::end_with(const std::string& str,const std::string& suffix)
{
	return str.size() >= suffix.size() && str.compare(str.size() - suffix.size(),suffix.size(),suffix) == 0;
}

std::string& StringTools::remove_from_start(std::string& str,const std::string& toRemove)
{
	return Poco::replaceInPlace<std::string>(str,toRemove,"",0);
}

std::string& StringTools::remove_from_end(std::string& str,const std::string& toRemove)
{
	return Poco::replaceInPlace<std::string>(str,toRemove,"",str.length() - toRemove.length());
}

std::string StringTools::toUpper(std::string& str)
{
	return Poco::toUpper(str);
}

std::string StringTools::toLower(std::string& str)
{
	return Poco::toLower(str);
}

std::string & StringTools::ltrim(std::string &s)
{
	s.erase(s.begin(),std::find_if(s.begin(),s.end(),std::not1(std::ptr_fun<int,int>(std::isspace))));
	return s;
}

std::string & StringTools::rtrim(std::string &s)
{
	s.erase(std::find_if(s.rbegin(),s.rend(),std::not1(std::ptr_fun<int,int>(std::isspace))).base(),s.end());
	return s;
}

std::string & StringTools::trim(std::string &s)
{
	return ltrim(rtrim(s));
}
