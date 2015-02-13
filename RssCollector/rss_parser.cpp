/* rss_parser
 * modification from original source https://github.com/yukipyon/rss/blob/master/rss_parser.cpp
 * by kevin lampis (yukipyon, https://github.com/yukipyon )
 * project https://github.com/yukipyon/rss
*/

#include "rss_parser.hpp"

#ifdef USE_LIB_RSS
#include <RSS.h>
#else
#include <boost/spirit/include/phoenix.hpp>
#endif

#include <fstream>
#include <locale>
#include <vector>

namespace rss_parser {
#ifdef USE_LIB_RSS
	void RssErrorHandler(RSS_u32 error_level, const RSS_char* error, size_t pos) {
		if(error_level == RSS_EL_ERROR) {
			if(pos != RSS_NO_POS_INFO)
				RSS_printf(RSS_text("[%d] %s\n"), pos, error);
			else
				RSS_printf(RSS_text("%s\n"), error);
		}
		throw error;
	}
#else
	
	rss_grammar::rss_grammar() : rss_grammar::base_type(start) {

	using boost::phoenix::bind;
	using boost::spirit::standard::char_;
	using boost::spirit::lit;
	using boost::spirit::int_;

	tag = open_tag(boost::spirit::qi::labels::_r1) >>
		tag_text >>
		close_tag(boost::spirit::qi::labels::_r1);

	//May not be valid xml.
	any_tag = &boost::spirit::lit("<") >> lit("<") >> !boost::spirit::lit("/") >> 
		(+((char_ - char_("/>")) >> *(lit("/") >> !lit(">"))))  
		>> ("/>" | ">" >> junk >> "</" >> +(char_ - ">") >> ">");

	open_tag = &lit("<") >> "<" >>
		end_tag(boost::spirit::qi::labels::_r1);

	close_tag = &lit("</") >> "</" >>
		end_tag(boost::spirit::qi::labels::_r1);

	end_tag = boost::spirit::standard::string(boost::spirit::qi::labels::_r1) >> 
		">";

	junk = tag_text;
	tag_text = +(+(html_entity | (char_ - char_("<"))) | cdata);

	cdata = "<![CDATA[" >> 
		*(
			html_entity | char_("&") | (char_ - char_("]"))
		) >> 
		lit("]]>");

	start = lit("<item>") >> *(
		junk |
				(tag(std::string("guid"))[bind(&record_dto::id, boost::spirit::qi::_val) = boost::spirit::qi::_1]) |
		(tag(std::string("title"))[bind(&record_dto::title, boost::spirit::qi::_val) = boost::spirit::qi::_1]) |
		(tag(std::string("description"))[bind(&record_dto::description, boost::spirit::qi::_val) = boost::spirit::qi::_1]) |
		(tag(std::string("link"))[bind(&record_dto::link, boost::spirit::qi::_val) = boost::spirit::qi::_1]) |
				(tag(std::string("pubDate"))[bind(&record_dto::date, boost::spirit::qi::_val) = boost::spirit::qi::_1]) |
		any_tag
		) >>
		lit("</item>");	

		html_entity = (lit('&') >> lit('#') >> boost::spirit::int_[boost::spirit::qi::_a = boost::spirit::qi::_1] >> lit(';')[boost::spirit::qi::_val = boost::spirit::qi::_a]);
}
	
#endif

	std::vector<models::record> parse_xml(const std::string &xml_p) {
#ifdef USE_LIB_RSS
		std::vector<models::record> ret;
		RSS_Feed* feed = RSS_create_feed_from_str(xml_p.c_str(), RssErrorHandler);

		RSS_Item* cur = feed->items;
		while (cur)
		{
			models::record r(cur->guid, cur->link, cur->pubDate, cur->title, cur->description);
			ret.push_back(r);
			cur = cur->next;
		}
		RSS_free_feed(feed);
		return ret;
#else		
		rss_grammar g;
		std::vector<models::record> ret;
		std::string::const_iterator st = xml_p.begin(), en = xml_p.end();

		record_dto dto;
		do {
			if (boost::spirit::qi::parse(st, en, g, dto))
				ret.push_back(models::record(dto.id,dto.link, dto.date, dto.title, dto.description));
			else
				st++;
		} while (st!=en);

		return ret;
#endif
	}
}
