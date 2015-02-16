#include "configuration.hpp"

#include <fstream>
#include <string>
#include <json-c/json.h>

namespace configuration {
	const char* config::_configFilename = "settings.conf";
	
	config::config()
	{
		std::ifstream ifs(_configFilename);
		std::string settingsText((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());
		if (settingsText.size() == 0)
		{
		    throw "Empty config";
		}
		
		json_object* cfg = json_tokener_parse(settingsText.c_str());
		json_object* csObject;
		json_bool b = json_object_object_get_ex(cfg, "connectionString", &csObject);
		if (!b)
		{
			throw "Failed to read connection string from configuration";
		}
		const char* cs = json_object_get_string(csObject);
		_connectionString = std::string(cs);
	}
        
	std::string config::getConnectionString() const
	{
		return _connectionString;
	}
}
