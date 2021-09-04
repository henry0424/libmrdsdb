//
// Created by henry on 2021-09-04.
//

#ifndef LIBMRDSDB_OBJECT_MGMT_H
#define LIBMRDSDB_OBJECT_MGMT_H

#include "mrdsdb_base.h"

#define NO_DATA_EXCEPTION true

namespace Database::SQL::MRDS {

    namespace DB_SCHEMA {
        struct object_mgmt {
            std::string obj_uid;
            std::string obj_id;
            bool enable;
            std::string create_ts;
            std::string update_ts;
            std::string region;
            std::string equipment_class;
            std::string vendor;
        };

        struct vehicle_mgmt {
            std::string vehicle_id;
            std::string carrier_class;
            int slot_num;
            int battery_threshold_full;
            int battery_threshold_high;
            int battery_threshold_low;
        };

    }

    class ObjectMgmt : public MRDSDB {

    protected:
        const std::string SCHEMA{"configure"};

    public:
        std::vector<DB_SCHEMA::object_mgmt> get_object_mgmt_list();

        DB_SCHEMA::object_mgmt get_object_mgmt(const std::string &obj_id);

    };

    class VehicleMgmt : public ObjectMgmt {
    public:
        std::vector<DB_SCHEMA::vehicle_mgmt> get_vehicle_mgmt_list();

        DB_SCHEMA::vehicle_mgmt get_vehicle_mgmt(const std::string &obj_id);
    };

}

#endif //LIBMRDSDB_OBJECT_MGMT_H
