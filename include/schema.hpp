//
// Created by henry on 2021-09-09.
//

#ifndef LIBMRDSDB_SCHEMA_HPP
#define LIBMRDSDB_SCHEMA_HPP

namespace Database::SQL::MRDS {

    namespace DB_SCHEMA {

        //ClassReference
        struct carrier_class {
            std::string carrier_class;
        };

        struct equipment_class {
            std::string equipment_class;
        };

        struct event_class {
            std::string event_class;
        };

        //ObjectMgmt
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

        //VehicleMgmt
        struct vehicle_mgmt {
            std::string vehicle_id;
            std::string carrier_class;
            int slot_num;
            int battery_threshold_full;
            int battery_threshold_high;
            int battery_threshold_low;
            std::string macaddr;
            std::string ipaddr;
        };

        //VehicleSlotMgmt
        struct vehicle_slot_mgmt {
            std::string vehicle_id;
            std::string vehicle_slot_id;
        };

        //EquipmentMgmt
        struct equipment_mgmt {
            std::string equipment_id;
        };

        //EquipmentPortMgmt
        struct equipment_port_mgmt {
            std::string equipment_id;
            std::string equipment_port_id;
        };

        //Transfer
        struct transfer_base {
            std::string receive_ts;
            std::string command_id;
            std::string source_port;
            std::string dest_port;
            int priority = 0;
            std::string operator_id = "MRDS_SYSTEM";
            std::string carrier_id;
        };

        struct transfer_processing {
            DB_SCHEMA::transfer_base base;
            std::string merged_command_id;
            std::string vehicle_id;
            std::string transfer_state;
            std::string comment;
            std::string magic;
        };

        //ObjectPortStatus
        struct object_port_status {
            std::string obj_id;
            std::string obj_port_id;
            std::string carrier_id;
        };

        //VehicleStatus
        struct vehicle_status {
            std::string vehicle_id;
            std::string vehicle_location;
            std::string vehicle_status;
            std::string battery_status;
        };

        //ParkingMgmt
        struct parking_mgmt {
            std::string parking_space_id;
            std::string parking_space_location;
            std::vector<std::string> prefer_vehicle;
        };

        //ParkingStatus
        struct parking_status {
            std::string parking_space_id;
            std::string booking;
            std::string booking_owner;
            std::string parking_vehicle_id;
        };

        //EventLog
        struct event_log_vehicle {
            std::string msg_uuid;
            std::string event_class;
            std::string vehicle_id;
            std::string vehicle_status;
            std::string vehicle_location;
            std::string carrier_id;
            std::string comment;
        };

        struct universal_event_log {
            std::string event_ts;
            std::string event_class;
            std::string obj_class;
            std::string obj_id;
            std::string obj_port_id;
            std::string obj_location;
            std::string carrier_id;
            std::string comment;
            std::string msg_uuid;
        };

    }
}
#endif //LIBMRDSDB_SCHEMA_HPP
