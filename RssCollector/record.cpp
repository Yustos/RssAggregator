#include "record.hpp"
#include "md5.hpp"
#include "str_utils.hpp"
#include <ctime>

namespace models
{
	record::record()
	{
	}

	record::record(const char* id,
			const char* link,
			const long date,
			const char* title,
			const char* description)
	{
			this->id = std::string(id);
			this->link = std::string(link);
			this->title = std::string(title);
			if (description == NULL)
			{
			    this->description = std::string("");
			}
			else
			{
			    this->description = std::string(description);
			}

			this->hash = md5(this->id);
			this->date = date;
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
