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

    class [[deprecated("\033[93m Deprecated: Replaced by UniversalEventLog. \033[0m")]] EventLog : public MRDSDB {
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

    class UniversalEventLog : public MRDSDB {
    private:
        const std::string LOGOUT_CLASS{"MRDS UniversalEventLog"};

    protected:
        const std::string SCHEMA{"production"};
        const std::string TABLE_EVENT_LOG_VEHICLE{"universal_event_log"};

    public:
        UniversalEventLog(const DATABASE_NAME db = DATABASE_NAME::POSTGRESQL);

        void insert_universal_event_log(const DB_SCHEMA::universal_event_log log);
    };

}

#endif //LIBMRDSDB_EVENT_LOG_H
