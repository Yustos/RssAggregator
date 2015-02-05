#ifndef STR_UTILS_H
#define STR_UTILS_H

#include <string>

namespace utils
{
	std::string Encode(const std::wstring &str);
	std::wstring Decode(const std::string &str);
	std::string to_string(long value);
	int to_int(std::string value);
}

#endif