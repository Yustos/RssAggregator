#ifndef RSS_PARSER_HPP
#define RSS_PARSER_HPP

#include "record.hpp"
#include <vector>
#include <string>

namespace rss_parser {

	class record_dto
	{
	public:
		std::string id, title, description, link, date;
	};

	std::vector<models::record> parse_xml(const std::string &xml);
        std::vector<models::record> parse_url(const std::string &url);
}
#endif
