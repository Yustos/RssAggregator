#ifndef FEED_H
#define FEED_H

#include <string>

namespace models {

	class feed {
	public:
		int id;
		std::string url;
		feed(int id, const std::string &url);
		std::string downloadFeed() const;
	};

}
#endif
