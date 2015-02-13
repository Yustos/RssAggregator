#include "storage.hpp"
#include "feed.hpp"
#include "str_utils.hpp"
#include "configuration.hpp"

#include <iostream>
#include <string>
#include <sstream>
#include <iostream>
#include <vector>
#include <map>
#include <libpq-fe.h>

#define HAVE_STRUCT_TIMESPEC

namespace storage {
    void Database::finish_with_error() const 
    {
        char* error = PQerrorMessage(_connection);
        std::cerr << error;
        PQfinish(_connection);
        throw error;
    }

    std::string Database::Escape(const std::string &wStr) const 
    {
        char* escaped = PQescapeLiteral(_connection, wStr.c_str(), wStr.length());
        return std::string(escaped);
    }

    Database::Database(const configuration::config &cfg)
    {
        _connection = PQconnectdb(cfg.getConnectionString().c_str());
        if (PQstatus(_connection) != CONNECTION_OK)
        {
            finish_with_error();
        }
    }

    Database::~Database()
    {
        PQfinish(_connection);
    }

    std::vector<models::feed> Database::ReadFeeds() const
    {
        PGresult *res = PQexec(_connection, "SELECT id, url FROM feed");
        if ((!res) || (PQresultStatus(res) != PGRES_TUPLES_OK))
        {
            PQclear(res);
            finish_with_error();
        }

        std::map<std::string, int> columns;
        int columnCount = PQnfields(res);
        for (int i = 0; i < columnCount; i++)
        {
            char* columnName = PQfname(res, i);
            columns.insert(std::pair<std::string, int>(std::string(columnName), i));
        }

            
        int recordCount = PQntuples(res);
        std::vector<models::feed> result;
        for(int i = 0 ; i < recordCount ; i++)
        {
            int id = utils::to_int(PQgetvalue(res, i, columns["id"]));
            char* url = PQgetvalue(res, i, columns["url"]);
            models::feed f(id, url);
            result.push_back(f);
        }

        PQclear(res);
        return result;
    }

    void Database::Write(const models::feed& feed, const models::record& item) const {
            std::string query = "SELECT add_record(";

            query.append(utils::to_string(feed.id));

            query.append(",");
            query.append(Escape(item.get_hash()));
            query.append(",");

            query.append(Escape(item.get_id()));
            query.append(",");
            query.append(utils::to_string(item.get_date()));
            query.append(",");
            query.append(Escape(item.get_link()));
            query.append(",");
            query.append(Escape(item.get_title()));
            query.append(",");
            query.append(Escape(item.get_description()));
            query.append(")");

            PGresult *res = PQexec(_connection, query.c_str());
            if ((!res) || (PQresultStatus(res) != PGRES_TUPLES_OK))
            {
                PQclear(res);
                finish_with_error();
            }
            PQclear(res);
    }
}
