#ifndef STORAGE_H
#define STORAGE_H

#include "record.h"
#include "feed.h"
#include "mysql.h"
#include <vector>

namespace storage {
	class Database
	{
		public:
			Database();
			~Database();

			std::vector<models::feed> ReadFeeds();
			void Write(const models::feed& feed, const models::record& item);
		private:
			MYSQL* connection;
	};

}

#endif