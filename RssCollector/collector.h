#ifndef COLLECTOR_H
#define	COLLECTOR_H

#include "feed.h"
#include "record.h"
#include "storage.h"

namespace collector
{
	class Collector
	{
	public:
		void collectFeeds();
	private:
		storage::Database db;

		void collectFeed(const models::feed &feed);
		void collectRecords(const models::feed &feed, const std::vector<models::record> &items);
	};
}
#endif

