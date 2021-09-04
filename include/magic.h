//
// Created by henry on 2021-09-04.
//

#ifndef LIBMRDSDB_MAGIC_H
#define LIBMRDSDB_MAGIC_H

#include <map>
#include "mrdsdb_base.h"

#define NO_DATA_EXCEPTION true

namespace Database::SQL::MRDS {

    class Magic : public MRDSDB {

    protected:
        const std::string SCHEMA{"messy"};

    public:
        std::map<std::string, std::string> get_magic_map();

        std::string get_magic_value(const std::string &key);

    };

}


#endif //LIBMRDSDB_MAGIC_H
