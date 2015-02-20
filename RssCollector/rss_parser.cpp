#include "rss_parser.hpp"

#include <RSS.h>
#include <fstream>
#include <locale>
#include <vector>

namespace rss_parser {
    
    void RssErrorHandler(RSS_u32 error_level, const RSS_char* error, size_t pos)
    {
        if(error_level == RSS_EL_ERROR) {
                if(pos != RSS_NO_POS_INFO)
                        RSS_printf(RSS_text("[%d] %s\n"), pos, error);
                else
                        RSS_printf(RSS_text("%s\n"), error);
        }
        throw error;
    }    

    std::vector<models::record> parse_xml(const std::string &xml_p)
    {
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
    }
    
    std::vector<models::record> parse_url(const std::string &url)
    {
        std::vector<models::record> ret;
        RSS_Feed* feed = RSS_create_feed(url.c_str(), RssErrorHandler);

        RSS_Item* cur = feed->items;
        while (cur)
        {
                models::record r(cur->guid, cur->link, cur->pubDate, cur->title, cur->description);
                ret.push_back(r);
                cur = cur->next;
        }
        RSS_free_feed(feed);
        return ret;
    }
    
}
