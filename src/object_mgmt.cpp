//
// Created by henry on 2021-09-04.
//

#include "object_mgmt.h"

using namespace Database::SQL::MRDS;

std::vector<DB_SCHEMA::object_mgmt> ObjectMgmt::get_object_mgmt_list() {
    LogTool::_log("get_object_mgmt_list", LOGOUT_CLASS, boost::log::trivial::trace);
    auto queryCmd = boost::str(
            boost::format("SELECT obj_uid, obj_id, enable, create_ts, update_ts, region, equipment_class, vendor "
                          "FROM %1%.%2%.%3%;") %
            this->connector_->get_database_host().database %
            this->SCHEMA %
            this->TABLE_OBJECT_MGMT);
    LogTool::_log("query cmd: " + queryCmd, LOGOUT_CLASS, boost::log::trivial::trace);
    auto query = this->connector_->exec(queryCmd);

    auto querySize{0};
    std::vector<DB_SCHEMA::object_mgmt> list_;
    list_.clear();
    while (query->next()) {
        auto loc{0};
        DB_SCHEMA::object_mgmt object_mgmt_;
        object_mgmt_.obj_uid = query->value(loc++).toString().toStdString();
        object_mgmt_.obj_id = query->value(loc++).toString().toStdString();
        object_mgmt_.enable = query->value(loc++).toBool();
        object_mgmt_.create_ts = query->value(loc++).toString().toStdString();
        object_mgmt_.update_ts = query->value(loc++).toString().toStdString();
        object_mgmt_.region = query->value(loc++).toString().toStdString();
        object_mgmt_.equipment_class = query->value(loc++).toString().toStdString();
        object_mgmt_.vendor = query->value(loc++).toString().toStdString();
        list_.push_back(object_mgmt_);
        if (LOGOUT_QUERY_RESULT) {
            LogTool::_log("obj_uid: " + object_mgmt_.obj_uid, LOGOUT_CLASS, boost::log::trivial::trace);
            LogTool::_log("obj_id: " + object_mgmt_.obj_id, LOGOUT_CLASS, boost::log::trivial::trace);
            LogTool::_log("enable: " + std::to_string(object_mgmt_.enable), LOGOUT_CLASS,
                          boost::log::trivial::trace);
            LogTool::_log("create_ts: " + object_mgmt_.create_ts, LOGOUT_CLASS, boost::log::trivial::trace);
            LogTool::_log("update_ts: " + object_mgmt_.update_ts, LOGOUT_CLASS, boost::log::trivial::trace);
            LogTool::_log("region: " + object_mgmt_.region, LOGOUT_CLASS, boost::log::trivial::trace);
            LogTool::_log("equipment_class: " + object_mgmt_.equipment_class, LOGOUT_CLASS,
                          boost::log::trivial::trace);
            LogTool::_log("vendor: " + object_mgmt_.vendor, LOGOUT_CLASS, boost::log::trivial::trace);
        }
        querySize++;
    }
    if (querySize <= 0 && (NO_DATA_EXCEPTION_ALL || NO_DATA_EXCEPTION))
        throw Database::Exception::NoDataException();

    return list_;
}

DB_SCHEMA::object_mgmt ObjectMgmt::get_object_mgmt(const std::string &obj_id) {
    LogTool::_log("get_object_mgmt", LOGOUT_CLASS, boost::log::trivial::trace);
    auto queryCmd = boost::str(
            boost::format("SELECT obj_uid, obj_id, enable, create_ts, update_ts, region, equipment_class, vendor "
                          "FROM %1%.%2%.%3% "
                          "WHERE obj_id=%4%;") %
            this->connector_->get_database_host().database %
            this->SCHEMA %
            this->TABLE_OBJECT_MGMT %
            null_(obj_id));
    LogTool::_log("query cmd: " + queryCmd, LOGOUT_CLASS, boost::log::trivial::trace);
    auto query = this->connector_->exec(queryCmd);
    DB_SCHEMA::object_mgmt object_mgmt_;
    if (query->next()) {
        auto loc{0};
        object_mgmt_.obj_uid = query->value(loc++).toString().toStdString();
        object_mgmt_.obj_id = query->value(loc++).toString().toStdString();
        object_mgmt_.enable = query->value(loc++).toBool();
        object_mgmt_.create_ts = query->value(loc++).toString().toStdString();
        object_mgmt_.update_ts = query->value(loc++).toString().toStdString();
        object_mgmt_.region = query->value(loc++).toString().toStdString();
        object_mgmt_.equipment_class = query->value(loc++).toString().toStdString();
        object_mgmt_.vendor = query->value(loc++).toString().toStdString();
        if (LOGOUT_QUERY_RESULT) {
            LogTool::_log("obj_uid: " + object_mgmt_.obj_uid, LOGOUT_CLASS, boost::log::trivial::trace);
            LogTool::_log("obj_id: " + object_mgmt_.obj_id, LOGOUT_CLASS, boost::log::trivial::trace);
            LogTool::_log("enable: " + std::to_string(object_mgmt_.enable), LOGOUT_CLASS,
                          boost::log::trivial::trace);
            LogTool::_log("create_ts: " + object_mgmt_.create_ts, LOGOUT_CLASS, boost::log::trivial::trace);
            LogTool::_log("update_ts: " + object_mgmt_.update_ts, LOGOUT_CLASS, boost::log::trivial::trace);
            LogTool::_log("region: " + object_mgmt_.region, LOGOUT_CLASS, boost::log::trivial::trace);
            LogTool::_log("equipment_class: " + object_mgmt_.equipment_class, LOGOUT_CLASS,
                          boost::log::trivial::trace);
            LogTool::_log("vendor: " + object_mgmt_.vendor, LOGOUT_CLASS, boost::log::trivial::trace);
        }
    } else if ((NO_DATA_EXCEPTION_ALL || NO_DATA_EXCEPTION))
        throw Database::Exception::NoDataException();

    return object_mgmt_;
}

//*****************************************************//
//*****************************************************//

std::vector<DB_SCHEMA::vehicle_mgmt> VehicleMgmt::get_vehicle_mgmt_list() {
    LogTool::_log("get_vehicle_mgmt_list", "MRDS VehicleMgmt", boost::log::trivial::trace);
    auto queryCmd = boost::str(
            boost::format(
                    "SELECT vehicle_id, carrier_class, slot_num, battery_threshold_full, battery_threshold_high, battery_threshold_low "
                    "FROM %1%.%2%.%3%;") %
            this->connector_->get_database_host().database %
            this->SCHEMA %
            this->TABLE_VEHICLE_MGMT);
    LogTool::_log("query cmd: " + queryCmd, "MRDS VehicleMgmt", boost::log::trivial::trace);
    auto query = this->connector_->exec(queryCmd);

    auto querySize{0};
    std::vector<DB_SCHEMA::vehicle_mgmt> list_;
    list_.clear();
    while (query->next()) {
        auto loc{0};
        DB_SCHEMA::vehicle_mgmt vehicle_mgmt_;
        vehicle_mgmt_.vehicle_id = query->value(loc++).toString().toStdString();
        vehicle_mgmt_.carrier_class = query->value(loc++).toString().toStdString();
        vehicle_mgmt_.slot_num = query->value(loc++).toInt();
        vehicle_mgmt_.battery_threshold_full = query->value(loc++).toInt();
        vehicle_mgmt_.battery_threshold_high = query->value(loc++).toInt();
        vehicle_mgmt_.battery_threshold_low = query->value(loc++).toInt();
        list_.push_back(vehicle_mgmt_);
        if (LOGOUT_QUERY_RESULT) {
            LogTool::_log("vehicle_id: " + vehicle_mgmt_.vehicle_id, "MRDS VehicleMgmt", boost::log::trivial::trace);
            LogTool::_log("carrier_class: " + vehicle_mgmt_.carrier_class, "MRDS VehicleMgmt",
                          boost::log::trivial::trace);
            LogTool::_log("slot_num: " + std::to_string(vehicle_mgmt_.slot_num), "MRDS VehicleMgmt",
                          boost::log::trivial::trace);
            LogTool::_log("battery_threshold_full: " + std::to_string(vehicle_mgmt_.battery_threshold_full),
                          "MRDS VehicleMgmt",
                          boost::log::trivial::trace);
            LogTool::_log("battery_threshold_high: " + std::to_string(vehicle_mgmt_.battery_threshold_high),
                          "MRDS VehicleMgmt",
                          boost::log::trivial::trace);
            LogTool::_log("battery_threshold_low: " + std::to_string(vehicle_mgmt_.battery_threshold_low),
                          "MRDS VehicleMgmt",
                          boost::log::trivial::trace);
        }
        querySize++;
    }
    if (querySize <= 0 && (NO_DATA_EXCEPTION_ALL || NO_DATA_EXCEPTION))
        throw Database::Exception::NoDataException();

    return list_;
}

DB_SCHEMA::vehicle_mgmt VehicleMgmt::get_vehicle_mgmt(const std::string &obj_id) {
    LogTool::_log("get_vehicle_mgmt", "MRDS VehicleMgmt", boost::log::trivial::trace);
    auto queryCmd = boost::str(
            boost::format(
                    "SELECT vehicle_id, carrier_class, slot_num, battery_threshold_full, battery_threshold_high, battery_threshold_low "
                    "FROM %1%.%2%.%3% "
                    "WHERE vehicle_id=%4%;") %
            this->connector_->get_database_host().database %
            this->SCHEMA %
            this->TABLE_VEHICLE_MGMT %
            null_(obj_id));
    LogTool::_log("query cmd: " + queryCmd, "MRDS VehicleMgmt", boost::log::trivial::trace);
    auto query = this->connector_->exec(queryCmd);
    DB_SCHEMA::vehicle_mgmt vehicle_mgmt_;
    if (query->next()) {
        auto loc{0};
        vehicle_mgmt_.vehicle_id = query->value(loc++).toString().toStdString();
        vehicle_mgmt_.carrier_class = query->value(loc++).toString().toStdString();
        vehicle_mgmt_.slot_num = query->value(loc++).toInt();
        vehicle_mgmt_.battery_threshold_full = query->value(loc++).toInt();
        vehicle_mgmt_.battery_threshold_high = query->value(loc++).toInt();
        vehicle_mgmt_.battery_threshold_low = query->value(loc++).toInt();
        if (LOGOUT_QUERY_RESULT) {
            LogTool::_log("vehicle_id: " + vehicle_mgmt_.vehicle_id, "MRDS VehicleMgmt", boost::log::trivial::trace);
            LogTool::_log("carrier_class: " + vehicle_mgmt_.carrier_class, "MRDS VehicleMgmt",
                          boost::log::trivial::trace);
            LogTool::_log("slot_num: " + std::to_string(vehicle_mgmt_.slot_num), "MRDS VehicleMgmt",
                          boost::log::trivial::trace);
            LogTool::_log("battery_threshold_full: " + std::to_string(vehicle_mgmt_.battery_threshold_full),
                          "MRDS VehicleMgmt",
                          boost::log::trivial::trace);
            LogTool::_log("battery_threshold_high: " + std::to_string(vehicle_mgmt_.battery_threshold_high),
                          "MRDS VehicleMgmt",
                          boost::log::trivial::trace);
            LogTool::_log("battery_threshold_low: " + std::to_string(vehicle_mgmt_.battery_threshold_low),
                          "MRDS VehicleMgmt",
                          boost::log::trivial::trace);
        }
    } else if ((NO_DATA_EXCEPTION_ALL || NO_DATA_EXCEPTION))
        throw Database::Exception::NoDataException();

    return vehicle_mgmt_;
}

//*****************************************************//
//*****************************************************//

std::vector<DB_SCHEMA::vehicle_slot_mgmt> VehicleSlotMgmt::get_vehicle_slot_mgmt_list(const std::string &obj_id) {
    LogTool::_log("get_vehicle_slot_mgmt_list", "MRDS VehicleSlotMgmt", boost::log::trivial::trace);

    auto where = [=]() -> std::string {
        if (obj_id.empty()) {
            auto queryCmd = boost::str(
                    boost::format("SELECT vehicle_id FROM %1%.%2%.%4%") %
                    this->connector_->get_database_host().database %
                    this->SCHEMA %
                    this->TABLE_OBJECT_PORT_MGMT %
                    this->TABLE_VEHICLE_MGMT);
            return queryCmd;
        } else {
            return null_(obj_id);
        }
    };

    auto queryCmd = boost::str(
            boost::format("SELECT obj_id as vehicle_id, obj_port_id as vehicle_slot_id "
                          "FROM %1%.%2%.%3% "
                          "WHERE obj_id IN (%4%);") %
            this->connector_->get_database_host().database %
            this->SCHEMA %
            this->TABLE_OBJECT_PORT_MGMT %
            where());
    LogTool::_log("query cmd: " + queryCmd, "MRDS VehicleSlotMgmt", boost::log::trivial::trace);
    auto query = this->connector_->exec(queryCmd);

    auto querySize{0};
    std::vector<DB_SCHEMA::vehicle_slot_mgmt> list_;
    list_.clear();
    while (query->next()) {
        auto loc{0};
        DB_SCHEMA::vehicle_slot_mgmt vehicle_slot_mgmt_;
        vehicle_slot_mgmt_.vehicle_id = query->value(loc++).toString().toStdString();
        vehicle_slot_mgmt_.vehicle_slot_id = query->value(loc++).toString().toStdString();
        list_.push_back(vehicle_slot_mgmt_);
        if (LOGOUT_QUERY_RESULT) {
            LogTool::_log("vehicle_id: " + vehicle_slot_mgmt_.vehicle_id, "MRDS VehicleSlotMgmt",
                          boost::log::trivial::trace);
            LogTool::_log("vehicle_slot_id: " + vehicle_slot_mgmt_.vehicle_slot_id, "MRDS VehicleSlotMgmt",
                          boost::log::trivial::trace);
        }
        querySize++;
    }
    if (querySize <= 0 && (NO_DATA_EXCEPTION_ALL || NO_DATA_EXCEPTION))
        throw Database::Exception::NoDataException();

    return list_;
}

DB_SCHEMA::vehicle_slot_mgmt VehicleSlotMgmt::get_vehicle_slot_mgmt(const std::string &vehicle_slot_id) {
    LogTool::_log("get_vehicle_slot_mgmt", "MRDS VehicleSlotMgmt", boost::log::trivial::trace);
    auto queryCmd = boost::str(
            boost::format(
                    "SELECT obj_id as vehicle_id, obj_port_id as vehicle_slot_id "
                    "FROM %1%.%2%.%3% "
                    "WHERE obj_port_id=%4%;") %
            this->connector_->get_database_host().database %
            this->SCHEMA %
            this->TABLE_OBJECT_PORT_MGMT %
            null_(vehicle_slot_id));
    LogTool::_log("query cmd: " + queryCmd, "MRDS VehicleSlotMgmt", boost::log::trivial::trace);
    auto query = this->connector_->exec(queryCmd);

    auto querySize{0};
    std::vector<DB_SCHEMA::vehicle_slot_mgmt> list_;
    list_.clear();
    while (query->next()) {
        auto loc{0};
        DB_SCHEMA::vehicle_slot_mgmt vehicle_slot_mgmt_;
        vehicle_slot_mgmt_.vehicle_id = query->value(loc++).toString().toStdString();
        vehicle_slot_mgmt_.vehicle_slot_id = query->value(loc++).toString().toStdString();
        list_.push_back(vehicle_slot_mgmt_);
        if (LOGOUT_QUERY_RESULT) {
            LogTool::_log("vehicle_id: " + vehicle_slot_mgmt_.vehicle_id, "MRDS VehicleSlotMgmt",
                          boost::log::trivial::trace);
            LogTool::_log("vehicle_slot_id: " + vehicle_slot_mgmt_.vehicle_slot_id, "MRDS VehicleSlotMgmt",
                          boost::log::trivial::trace);
        }
        querySize++;
    }
    if (querySize <= 0 && (NO_DATA_EXCEPTION_ALL || NO_DATA_EXCEPTION))
        throw Database::Exception::NoDataException();

    return list_.at(0);
}

//*****************************************************//
//*****************************************************//

std::vector<DB_SCHEMA::equipment_mgmt> EquipmentMgmt::get_equipment_mgmt_list() {
    LogTool::_log("get_equipment_mgmt_list", "MRDS EquipmentMgmt", boost::log::trivial::trace);
    auto queryCmd = boost::str(
            boost::format(
                    "SELECT equipment_id "
                    "FROM %1%.%2%.%3%;") %
            this->connector_->get_database_host().database %
            this->SCHEMA %
            "equipment_mgmt");
    LogTool::_log("query cmd: " + queryCmd, "MRDS EquipmentMgmt", boost::log::trivial::trace);
    auto query = this->connector_->exec(queryCmd);

    auto querySize{0};
    std::vector<DB_SCHEMA::equipment_mgmt> list_;
    list_.clear();
    while (query->next()) {
        auto loc{0};
        DB_SCHEMA::equipment_mgmt equipment_mgmt_;
        equipment_mgmt_.equipment_id = query->value(loc++).toString().toStdString();

        list_.push_back(equipment_mgmt_);
        if (LOGOUT_QUERY_RESULT) {
            LogTool::_log("equipment_id: " + equipment_mgmt_.equipment_id, "MRDS EquipmentMgmt",
                          boost::log::trivial::trace);
        }

        querySize++;
    }
    if (querySize <= 0 && (NO_DATA_EXCEPTION_ALL || NO_DATA_EXCEPTION))
        throw Database::Exception::NoDataException();

    return list_;
}

DB_SCHEMA::equipment_mgmt EquipmentMgmt::get_equipment_mgmt(const std::string &obj_id) {
    LogTool::_log("get_vehicle_mgmt", "MRDS EquipmentMgmt", boost::log::trivial::trace);
    auto queryCmd = boost::str(
            boost::format(
                    "SELECT equipment_id "
                    "FROM %1%.%2%.%3% "
                    "WHERE equipment_id=%4%;") %
            this->connector_->get_database_host().database %
            this->SCHEMA %
            "equipment_mgmt" %
            null_(obj_id));
    LogTool::_log("query cmd: " + queryCmd, "MRDS EquipmentMgmt", boost::log::trivial::trace);
    auto query = this->connector_->exec(queryCmd);
    DB_SCHEMA::equipment_mgmt equipment_mgmt_;
    if (query->next()) {
        auto loc{0};
        equipment_mgmt_.equipment_id = query->value(loc++).toString().toStdString();
        if (LOGOUT_QUERY_RESULT) {
            LogTool::_log("query cmd: " + queryCmd, "MRDS EquipmentMgmt", boost::log::trivial::trace);
        }
    } else if ((NO_DATA_EXCEPTION_ALL || NO_DATA_EXCEPTION))
        throw Database::Exception::NoDataException();

    return equipment_mgmt_;
}

//*****************************************************//
//*****************************************************//

std::vector<DB_SCHEMA::equipment_port_mgmt> EquipmentPortMgmt::get_equipment_port_mgmt_list(const std::string &obj_id) {
    LogTool::_log("equipment_port_mgmt", "MRDS EquipmentPortMgmt", boost::log::trivial::trace);

    auto where = [=]() -> std::string {
        if (obj_id.empty()) {
            auto queryCmd = boost::str(
                    boost::format("SELECT equipment_id FROM %1%.%2%.%4%") %
                    this->connector_->get_database_host().database %
                    this->SCHEMA %
                    this->TABLE_OBJECT_PORT_MGMT %
                    this->TABLE_EQUIPMENT_MGMT);
            return queryCmd;
        } else {
            return null_(obj_id);
        }
    };

    auto queryCmd = boost::str(
            boost::format("SELECT obj_id as equipment_id, obj_port_id as equipment_port_id "
                          "FROM %1%.%2%.%3% "
                          "WHERE obj_id IN (%4%);") %
            this->connector_->get_database_host().database %
            this->SCHEMA %
            this->TABLE_OBJECT_PORT_MGMT %
            where());
    LogTool::_log("query cmd: " + queryCmd, "MRDS EquipmentPortMgmt", boost::log::trivial::trace);
    auto query = this->connector_->exec(queryCmd);

    auto querySize{0};
    std::vector<DB_SCHEMA::equipment_port_mgmt> list_;
    list_.clear();
    while (query->next()) {
        auto loc{0};
        DB_SCHEMA::equipment_port_mgmt equipment_port_mgmt_;
        equipment_port_mgmt_.equipment_id = query->value(loc++).toString().toStdString();
        equipment_port_mgmt_.equipment_port_id = query->value(loc++).toString().toStdString();
        list_.push_back(equipment_port_mgmt_);
        if (LOGOUT_QUERY_RESULT) {
            LogTool::_log("equipment_id: " + equipment_port_mgmt_.equipment_id, "MRDS EquipmentPortMgmt",
                          boost::log::trivial::trace);
            LogTool::_log("equipment_port_id: " + equipment_port_mgmt_.equipment_port_id, "MRDS EquipmentPortMgmt",
                          boost::log::trivial::trace);
        }
        querySize++;
    }
    if (querySize <= 0 && (NO_DATA_EXCEPTION_ALL || NO_DATA_EXCEPTION))
        throw Database::Exception::NoDataException();

    return list_;
}

DB_SCHEMA::equipment_port_mgmt EquipmentPortMgmt::get_equipment_port_mgmt(const std::string &equipment_port_id) {
    LogTool::_log("get_equipment_port_mgmt", "MRDS EquipmentPortMgmt", boost::log::trivial::trace);
    auto queryCmd = boost::str(
            boost::format(
                    "SELECT obj_id as equipment_id, obj_port_id as equipment_port_id "
                    "FROM %1%.%2%.%3% "
                    "WHERE obj_port_id=%4%;") %
            this->connector_->get_database_host().database %
            this->SCHEMA %
            this->TABLE_OBJECT_PORT_MGMT %
            null_(equipment_port_id));
    LogTool::_log("query cmd: " + queryCmd, "MRDS EquipmentPortMgmt", boost::log::trivial::trace);
    auto query = this->connector_->exec(queryCmd);

    auto querySize{0};
    std::vector<DB_SCHEMA::equipment_port_mgmt> list_;
    list_.clear();
    while (query->next()) {
        auto loc{0};
        DB_SCHEMA::equipment_port_mgmt equipment_port_mgmt_;
        equipment_port_mgmt_.equipment_id = query->value(loc++).toString().toStdString();
        equipment_port_mgmt_.equipment_port_id = query->value(loc++).toString().toStdString();
        list_.push_back(equipment_port_mgmt_);
        if (LOGOUT_QUERY_RESULT) {
            LogTool::_log("equipment_id: " + equipment_port_mgmt_.equipment_id, "MRDS EquipmentPortMgmt",
                          boost::log::trivial::trace);
            LogTool::_log("vehicle_slot_id: " + equipment_port_mgmt_.equipment_port_id, "MRDS EquipmentPortMgmt",
                          boost::log::trivial::trace);
        }
        querySize++;
    }
    if (querySize <= 0 && (NO_DATA_EXCEPTION_ALL || NO_DATA_EXCEPTION))
        throw Database::Exception::NoDataException();

    return list_.at(0);
}

