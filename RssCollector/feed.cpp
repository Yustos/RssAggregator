#include "feed.hpp"
#include "downloader.hpp"

namespace models {

	feed::feed(int id, const std::string &url)
	{
			this->id = id;
			this->url = url;
	};

	std::string feed::downloadFeed() const 
	{
		std::string xml = downloader::download(url);
		return xml;
	}
}
