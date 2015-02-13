#ifndef COLLECTOR_H
#define	COLLECTOR_H

#include "feed.hpp"
#include "record.hpp"
#include "storage.hpp"
#include "configuration.hpp"

namespace collector
{
    class Collector
    {
    public:
        Collector(const configuration::config &cfg);
        void collectFeeds();
    private:
        const storage::Database _db;

        void collectFeed(const models::feed &feed);
        void collectRecords(const models::feed &feed, const std::vector<models::record> &items);
    };
}
#endif
