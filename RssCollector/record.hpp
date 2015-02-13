#ifndef RSS_ITEM_H
#define RSS_ITEM_H

#include <string>

namespace models {
    class record {
    public:
        record();
        record(
                const std::string id,
                const std::string link,
                const std::string date,
                const std::string title,
                const std::string description);

        record(const char* id,
                const char* link,
                const long date,
                const char* title,
                const char* description);

        std::string get_id() const;
        std::string get_title() const;
        std::string get_link() const;
        std::string get_description() const;
        long get_date() const;
        std::string get_hash() const;

    private:
        std::string id, title, description, link, hash;
        long date;

        long parse_date(const std::string &input);
        std::string md5(const std::string &input);
    };
}

#endif
