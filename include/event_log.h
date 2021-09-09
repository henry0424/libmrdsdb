//
// Created by henry on 2021-09-08.
//

#ifndef LIBMRDSDB_EVENT_LOG_H
#define LIBMRDSDB_EVENT_LOG_H

#include "mrdsdb_base.h"
#include "schema.hpp"

#define NO_DATA_EXCEPTION true
#define LOGOUT_QUERY_RESULT true

namespace Database::SQL::MRDS {

    class EventLog : public MRDSDB {
    private:
        const std::string LOGOUT_CLASS{"MRDS EventLog"};

    protected:
        const std::string SCHEMA{"production"};
        const std::string TABLE_EVENT_LOG_VEHICLE{"event_log_vehicle"};

    public:
        EventLog(const DATABASE_NAME db = DATABASE_NAME::POSTGRESQL);

        void insert_vehicle_event(const DB_SCHEMA::event_log_vehicle log);

        void update_vehicle_event(const DB_SCHEMA::event_log_vehicle log);

    };

}

#endif //LIBMRDSDB_EVENT_LOG_H
