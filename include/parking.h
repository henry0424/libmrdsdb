//
// Created by henry on 2021-09-09.
//

#ifndef LIBMRDSDB_PARKING_H
#define LIBMRDSDB_PARKING_H

#include "mrdsdb_base.h"
#include "schema.hpp"

#define NO_DATA_EXCEPTION true
#define LOGOUT_QUERY_RESULT true

namespace Database::SQL::MRDS {

    class ParkingMgmt : public MRDSDB {
    private:
        const std::string LOGOUT_CLASS{"MRDS ParkingMgmt"};

    protected:
        const std::string SCHEMA{"configure"};
        const std::string TABLE_PARKING_MGMT{"parking_mgmt"};

    public:
        ParkingMgmt(const DATABASE_NAME db = DATABASE_NAME::POSTGRESQL);

        std::vector<DB_SCHEMA::parking_mgmt> get_parking_mgmt_list(const std::string &keyword = std::string());

    };

    class ParkingStatus : public ParkingMgmt {
    private:
        const std::string SCHEMA{"production"};
        const std::string LOGOUT_CLASS{"MRDS ParkingStatus"};

    protected:
        const std::string TABLE_PARKING_STATUS{"parking_status"};

    public:
        ParkingStatus(const DATABASE_NAME db = DATABASE_NAME::POSTGRESQL);

        std::vector<DB_SCHEMA::parking_status> get_parking_status_list(const std::string &keyword = std::string());

        void update_parking_status(const DB_SCHEMA::parking_status parking_status);

    };

}

#endif //LIBMRDSDB_PARKING_H
