#include "storage.h"
#include "feed.h"
#include "str_utils.h"
#include <iostream>
#include <string>
#include <sstream>
#include <iostream>
#include "mysql.h"
#include <vector>
#include <map>

namespace storage {
	void finish_with_error(MYSQL *con)
	{
		std::cerr << mysql_error(con);
		mysql_close(con);
		//TODO: throw
	}

	std::string Escape(MYSQL *mysql, const std::string &wStr)
	{
		const char* wstr = wStr.c_str();
		const int wlen = wStr.length();
		std::vector<char> escaped(wlen * 2 + 1);
		unsigned long escapedLen = mysql_real_escape_string(mysql, &escaped[0], wstr, wlen);
		if (escapedLen > 0)
				return std::string(&escaped[0], escapedLen);

		return std::string();
	}

	Database::Database()
	{
		connection = mysql_init(NULL);
		if (mysql_real_connect(connection, "localhost", "rss", MYSQL_USER,
				MYSQL_PASSWORD, 0, NULL, 0) == NULL)
		{
				finish_with_error(connection);
		}
	}

	Database::~Database()
	{
		mysql_close(connection);
	}

	std::vector<models::feed> Database::ReadFeeds()
	{
		if (mysql_query(connection, "SELECT id, url FROM feeds"))
		{
				finish_with_error(connection);
		}

		MYSQL_RES *cursor = mysql_store_result(connection);
		if (cursor == NULL)
		{
				finish_with_error(connection);
		}

		std::map<std::string, int> columns;
		int i = 0;
		MYSQL_FIELD* field;
		while (field = mysql_fetch_field(cursor)){
				columns.insert(std::pair<std::string, int>(field->name, i++));
		}

		MYSQL_ROW row;
		std::vector<models::feed> result;
		while ((row = mysql_fetch_row(cursor)))
		{
			int id = utils::to_int(std::string(row[columns["id"]]));
			std::string url(row[columns["url"]]);
			models::feed f(id, url);
			result.push_back(f);
		}

		mysql_free_result(cursor);
		return result;
	}

	void Database::Write(const models::feed& feed, const models::record& item){
		std::string query = "CALL add_record (";

		query.append(utils::to_string(feed.id));

		query.append(",'");
		query.append(Escape(connection, item.get_hash()));
		query.append("','");

		query.append(Escape(connection, item.get_id()));
		query.append("','");
		query.append(utils::to_string(item.get_date()));
		query.append("','");
		query.append(Escape(connection, item.get_link()));
		query.append("','");
		query.append(Escape(connection, item.get_title()));
		query.append("','");
		query.append(Escape(connection, item.get_description()));
		query.append("')");

		if (mysql_query(connection, query.c_str())) {
				finish_with_error(connection);
		}

		mysql_commit(connection);
	}
}