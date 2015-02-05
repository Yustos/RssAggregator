/* rss_parser
 * modification from original source https://github.com/yukipyon/rss/blob/master/rss_parser.hpp
 * by kevin lampis (yukipyon, https://github.com/yukipyon )
 * project https://github.com/yukipyon/rss
*/

#ifndef RSS_PARSER_HPP
#define RSS_PARSER_HPP

#include <boost/spirit/include/qi.hpp>
#include "record.h"
#include <vector>
#include <string>

namespace rss_parser {

	class record_dto
	{
	public:
		std::string id, title, description, link, date;
	};

	struct rss_grammar : boost::spirit::qi::grammar<std::string::const_iterator, record_dto()> {

		rss_grammar();

		boost::spirit::qi::rule<std::string::const_iterator, std::string()> tag_text, cdata;
		boost::spirit::qi::rule<std::string::const_iterator, record_dto()> start;
		boost::spirit::qi::rule<std::string::const_iterator, boost::spirit::unused_type()>junk, any_tag;
		boost::spirit::qi::rule<std::string::const_iterator, boost::spirit::unused_type(std::string)>open_tag, close_tag, end_tag;

		boost::spirit::qi::rule<std::string::const_iterator, std::string(std::string)> tag;
		boost::spirit::qi::rule<std::string::const_iterator, boost::spirit::qi::locals<int>, char()> html_entity;
	};
	std::vector<models::record> parse_xml(const std::string &xml);
}
#endif