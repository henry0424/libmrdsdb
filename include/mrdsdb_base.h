//
// Created by henry on 2021-09-04.
//

#ifndef LIBMRDSDB_MRDSDB_BASE_H
#define LIBMRDSDB_MRDSDB_BASE_H

#include "connector.h"

#define NO_DATA_EXCEPTION_ALL false

namespace Database::SQL::MRDS {

    enum DT_SOURCE {
        SYSTEM,
        DATABASE
    };

    class MRDSDB {
    private:
        const std::string LOGOUT_CLASS{"MRDSDB"};

    protected:
        std::shared_ptr<Database::SQL::QtConnector> connector_;

    public:
        MRDSDB();

        virtual ~MRDSDB() = default;

        int connect(const DatabaseHost host);

        void swap_connector(MRDSDB *ptr_mrdsdb);

        std::string null_(const std::string &src) {
            return (src.empty()) ? "NULL" : std::string("'" + src + "'");
        }

        std::string default_(const std::string &src) {
            return (src.empty()) ? "DEFAULT" : std::string("'" + src + "'");
        }

        std::string get_datetime(const DT_SOURCE src);
    };

}

#endif //LIBMRDSDB_MRDSDB_BASE_H
