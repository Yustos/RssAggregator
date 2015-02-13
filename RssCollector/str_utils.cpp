#include "str_utils.hpp"
#include <string>
#include <vector>
#include <sstream>

namespace utils
{
	std::string Encode(const std::wstring &str)
	{
		std::string ret;
		ret.assign(str.begin(), str.end());
		return ret;
	}

	std::wstring Decode(const std::string &str)
	{
		std::wstring ret(str.begin(), str.end());
		return ret;
	}

	std::string to_string(long value)
	{
		std::ostringstream ss;
		ss << value;
		return ss.str();
	}

	int to_int(std::string value)
	{
		std::istringstream ss(value);
		int ret;
		ss >> ret;
		return ret;
	}
}
