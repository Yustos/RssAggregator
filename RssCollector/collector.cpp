#include "rss_parser.h"
#include "record.h"
#include "storage.h"
#include "feed.h"
#include "collector.h"

namespace collector
{
	void Collector::collectFeeds()
	{
		std::vector<models::feed> feeds = db.ReadFeeds();
		std::cout << "Feeds to collect: " << feeds.size() << std::endl;

		std::vector<models::feed>::const_iterator st = feeds.begin(), en = feeds.end();

		for (; st!=en; st++) {
			std::cout << "Collect feed: " << st->id << " -> " << st->url << std::endl;
			collectFeed(*st);
		}
	}

	void Collector::collectFeed(const models::feed &feed)
	{
		try
		{
			std::vector<models::record> records;
			std::string xml = feed.downloadFeed();
			records = rss_parser::parse_xml(xml);
			collectRecords(feed, records);
			std::cout << "Writed records: " << records.size() << std::endl;
		}
		catch (const char* e) {
			std::cerr << "Failed to collect feed" << std::endl;
			std::cerr << e << std::endl;
		}
		catch (...) {
			std::cerr << "Unknown exception";
		}
	}

	void Collector::collectRecords(const models::feed &feed, const std::vector<models::record> &items)
	{
		std::vector<models::record>::const_iterator st = items.begin(), en = items.end();
		for (; st!=en; st++) {
			db.Write(feed, *st);
		}
	}
}