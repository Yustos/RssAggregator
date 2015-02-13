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
        const char* _configFileName = "settings.conf";
    };
}

#endif
