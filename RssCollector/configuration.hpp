#ifndef CONFIG_HPP
#define	CONFIG_HPP

#include <string>

namespace configuration {
    class config {
    public:
	config();
	std::string getConnectionString() const;
    private:
	std::string _connectionString;
	static const char* _configFilename;
    };
}

#endif
