//
// Created by henry on 2021-09-04.
//

#ifndef LIBMRDSDB_OBJECT_MGMT_H
#define LIBMRDSDB_OBJECT_MGMT_H

#include "mrdsdb_base.h"

#define NO_DATA_EXCEPTION true
#define LOGOUT_QUERY_RESULT true

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

        struct vehicle_slot_mgmt {
            std::string vehicle_id;
            std::string vehicle_slot_id;
        };

        struct equipment_mgmt {
            std::string equipment_id;
        };

        struct equipment_port_mgmt {
            std::string equipment_id;
            std::string equipment_port_id;
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

    class VehicleSlotMgmt : public VehicleMgmt {
    public:
        std::vector<DB_SCHEMA::vehicle_slot_mgmt> get_vehicle_slot_mgmt_list();

        std::vector<DB_SCHEMA::vehicle_slot_mgmt> get_vehicle_slot_mgmt_list(const std::string &obj_id);

        DB_SCHEMA::vehicle_slot_mgmt get_vehicle_slot_mgmt(const std::string &vehicle_slot_id);
    };

    class EquipmentMgmt : public ObjectMgmt {
    public:
        std::vector<DB_SCHEMA::equipment_mgmt> get_equipment_mgmt_list();

        DB_SCHEMA::equipment_mgmt get_equipment_mgmt(const std::string &obj_id);
    };

    class EquipmentPortMgmt : public EquipmentMgmt {
    public:
        std::vector<DB_SCHEMA::equipment_port_mgmt> get_equipment_port_mgmt_list();

        std::vector<DB_SCHEMA::equipment_port_mgmt> get_equipment_port_mgmt_list(const std::string &obj_id);

        DB_SCHEMA::equipment_port_mgmt get_equipment_port_mgmt(const std::string &equipment_port_id);
    };

}

#endif //LIBMRDSDB_OBJECT_MGMT_H