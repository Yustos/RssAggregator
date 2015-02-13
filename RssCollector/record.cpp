#include "record.hpp"
#include "md5.hpp"
#include "str_utils.hpp"
#include <ctime>
#include <boost/date_time.hpp>
#include <boost/date_time/local_time/local_time.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

namespace models
{
	record::record()
	{
	}

	record::record(const std::string id,
			const std::string link,
			const std::string date,
			const std::string title,
			const std::string description)
	{
			this->id = id;
			this->link = link;
			this->title = title;
			this->description = description;

			this->hash = md5(id);
			this->date = parse_date(date);
	}

	std::string record::get_id() const
	{
			return id;
	}


	std::string record::get_title() const
	{
			return title;
	}
	std::string record::get_link() const
	{
			return link;
	}

	std::string record::get_description() const
	{
			return description;
	}

	long record::get_date() const
	{
			return date;
	}

	std::string record::get_hash() const
	{
			return hash;
	}

	long record::parse_date(const std::string &input) {
			using namespace boost::gregorian;
			using namespace boost::local_time;
			using namespace boost::posix_time;

			boost::local_time::local_time_input_facet* lif(new boost::local_time::local_time_input_facet("%a, %d %b %Y %H:%M:%S GMT"));
			std::stringstream ss(input);
			ss.imbue(std::locale(std::locale::classic(), lif));

			boost::local_time::local_date_time dt(boost::local_time::local_sec_clock::local_time(boost::local_time::time_zone_ptr()));
			ss >> dt;

			boost::posix_time::ptime time_t_epoch(boost::gregorian::date(1970, 1, 1));
			time_duration diff = dt.utc_time() - time_t_epoch;
			return diff.total_seconds();
	}


	std::string record::md5(const std::string &input)
	{
		return utils::md5(input);
	}

	/*std::wstring record::date_str()
	{
			std::wstring result;
			boost::local_time::local_time_facet* lf(new boost::local_time::local_time_facet("%a, %d %b %Y %H:%M:%S GMT"));
			try
			{
					std::wstringstream ss;
					ss.imbue(std::locale(ss.getloc(), lf));
					ss << m_dt;
					result = ss.str();
					std::wcout << result;
			}
			catch (std::exception& e)
			{
					std::cout << "Exception: " << e.what() << std::endl;
			}
			return result;
	}*/
}
