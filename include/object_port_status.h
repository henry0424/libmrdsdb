//
// Created by henry on 2021-09-10.
//

#ifndef LIBMRDSDB_OBJECT_PORT_STATUS_H
#define LIBMRDSDB_OBJECT_PORT_STATUS_H

#include "mrdsdb_base.h"

#define NO_DATA_EXCEPTION true
#define LOGOUT_QUERY_RESULT true

namespace Database::SQL::MRDS {

    class ObjectPortStatus : public MRDSDB {
    private:
        const std::string LOGOUT_CLASS{"MRDS ObjectPortStatus"};

    protected:
        const std::string SCHEMA{"production"};
        const std::string TABLE_OBJECT_PORT_STATUS{"object_port_status"};

    public:
    };
}


#endif //LIBMRDSDB_OBJECT_PORT_STATUS_H
