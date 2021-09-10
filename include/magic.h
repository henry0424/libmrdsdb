//
// Created by henry on 2021-09-04.
//

#ifndef LIBMRDSDB_MAGIC_H
#define LIBMRDSDB_MAGIC_H

#include <map>
#include "mrdsdb_base.h"
#include "schema.hpp"

#define NO_DATA_EXCEPTION true
#define LOGOUT_QUERY_RESULT true

namespace Database::SQL::MRDS {

    class Magic : public MRDSDB {
    private:
        const std::string LOGOUT_CLASS{"MRDS Magic"};

    protected:
        const std::string SCHEMA{"messy"};
        const std::string TABLE_MAGIC{"magic"};

    public:
        Magic(const DATABASE_NAME db = DATABASE_NAME::POSTGRESQL);

        std::map<std::string, std::string> get_magic_map();

        std::string get_magic_value(const std::string &key);

        void set_magic_map(const std::map<std::string, std::string> map);

        void set_magic_value(const std::string &key, const std::string &value);

    };

}

#endif //LIBMRDSDB_MAGIC_H
