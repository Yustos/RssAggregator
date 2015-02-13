#ifndef STORAGE_H
#define STORAGE_H

#include "record.hpp"
#include "feed.hpp"
#include "configuration.hpp"
#include <vector>
#include <string>
#include <libpq-fe.h>

namespace storage {
    class Database
    {
        public:
            Database(const configuration::config &cfg);
            ~Database();

            std::vector<models::feed> ReadFeeds() const;
            void Write(const models::feed& feed, const models::record& item) const;
        private:
            PGconn* _connection;
            void finish_with_error() const;
            std::string Escape(const std::string &wStr) const;
    };

}

#endif
