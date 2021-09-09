//
// Created by henry on 2021-09-09.
//

#ifndef LIBMRDSDB_VEHICLE_STATUS_H
#define LIBMRDSDB_VEHICLE_STATUS_H

#include "mrdsdb_base.h"
#include "schema.hpp"

#define NO_DATA_EXCEPTION true
#define LOGOUT_QUERY_RESULT true

namespace Database::SQL::MRDS {

    class VehicleStatus : public MRDSDB {
    private:
        const std::string LOGOUT_CLASS{"MRDS VehicleStatus"};

    protected:
        const std::string SCHEMA{"production"};
        const std::string TABLE_VEHICLE_STATUS{"vehicle_status"};

    public:
        std::vector<DB_SCHEMA::vehicle_status> get_vehicle_status_list(const std::string &keyword = std::string());

        void update_vehicle_status(const DB_SCHEMA::vehicle_status vehicle_status);

    };
}


#endif //LIBMRDSDB_VEHICLE_STATUS_H
