//
// Created by henry on 2021-09-04.
//

#ifndef LIBMRDSDB_OBJECT_MGMT_H
#define LIBMRDSDB_OBJECT_MGMT_H

#include "mrdsdb_base.h"
#include "schema.hpp"

#define NO_DATA_EXCEPTION true
#define LOGOUT_QUERY_RESULT true

namespace Database::SQL::MRDS {

    class ObjectMgmt : public MRDSDB {
    private:
        const std::string LOGOUT_CLASS{"MRDS ObjectMgmt"};

    protected:
        const std::string SCHEMA{"configure"};
        const std::string TABLE_OBJECT_MGMT{"object_mgmt"};
        const std::string TABLE_OBJECT_PORT_MGMT{"object_port_mgmt"};

    public:
        ObjectMgmt(const DATABASE_NAME db = DATABASE_NAME::POSTGRESQL);

        auto get_object_mgmt_list(
                const std::string &keyword = std::string()) -> std::optional<std::vector<DB_SCHEMA::object_mgmt>>;
    };

    class VehicleMgmt : public ObjectMgmt {
    private:
        const std::string LOGOUT_CLASS{"MRDS VehicleMgmt"};

    protected:
        const std::string TABLE_VEHICLE_MGMT{"vehicle_mgmt"};

    public:
        VehicleMgmt(const DATABASE_NAME db = DATABASE_NAME::POSTGRESQL);

        auto get_vehicle_mgmt_list(
                const std::string &keyword = std::string()) -> std::optional<std::vector<DB_SCHEMA::vehicle_mgmt>>;

        void update_vehicle_mgmt(const DB_SCHEMA::vehicle_mgmt vehicle_status);
    };

    class VehicleSlotMgmt : public VehicleMgmt {
    private:
        const std::string LOGOUT_CLASS{"MRDS VehicleSlotMgmt"};

    public:
        VehicleSlotMgmt(const DATABASE_NAME db = DATABASE_NAME::POSTGRESQL);

        auto get_vehicle_slot_mgmt_list(
                const std::string &keyword = std::string()) -> std::optional<std::vector<DB_SCHEMA::vehicle_slot_mgmt>>;
    };

    class EquipmentMgmt : public ObjectMgmt {
    private:
        const std::string LOGOUT_CLASS{"MRDS VehicleSlotMgmt"};

    protected:
        const std::string TABLE_EQUIPMENT_MGMT{"equipment_mgmt"};

    public:
        EquipmentMgmt(const DATABASE_NAME db = DATABASE_NAME::POSTGRESQL);

        auto get_equipment_mgmt_list(
                const std::string &keyword = std::string()) -> std::optional<std::vector<DB_SCHEMA::equipment_mgmt>>;
    };

    class EquipmentPortMgmt : public EquipmentMgmt {
    private:
        const std::string LOGOUT_CLASS{"MRDS EquipmentPortMgmt"};

    public:
        EquipmentPortMgmt(const DATABASE_NAME db = DATABASE_NAME::POSTGRESQL);

        auto get_equipment_port_mgmt_list(
                const std::string &keyword = std::string()) -> std::optional<std::vector<DB_SCHEMA::equipment_port_mgmt>>;
    };

}

#endif //LIBMRDSDB_OBJECT_MGMT_H
