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

//    namespace DB_SCHEMA {
//        struct event_log_vehicle {
//            std::string msg_uuid;
//            std::string event_class;
//            std::string vehicle_id;
//            std::string vehicle_status;
//            std::string vehicle_location;
//            std::string carrier_id;
//            std::string comment;
//        };
//    }

    class EventLog : public MRDSDB {

    protected:
    protected:
        const std::string SCHEMA{"production"};
        const std::string TABLE_EVENT_LOG_VEHICLE{"event_log_vehicle"};

    public:
        void insert_vehicle_event(const DB_SCHEMA::event_log_vehicle log);

        void update_vehicle_event(const DB_SCHEMA::event_log_vehicle log);

    };

}

#endif //LIBMRDSDB_EVENT_LOG_H