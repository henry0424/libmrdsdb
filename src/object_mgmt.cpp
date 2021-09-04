//
// Created by henry on 2021-09-04.
//

#include "object_mgmt.h"

using namespace Database::SQL::MRDS;

std::vector<DB_SCHEMA::object_mgmt> ObjectMgmt::get_object_mgmt_list() {
    LogTool::_log("get_object_mgmt_list", "MRDS ObjectMgmt", boost::log::trivial::trace);
    auto queryCmd = boost::str(
            boost::format("SELECT obj_uid, obj_id, enable, create_ts, update_ts, region, equipment_class, vendor "
                          "FROM %1%.%2%.%3%;") %
            this->connector_->get_database_host().database %
            this->SCHEMA %
            "object_mgmt");
    LogTool::_log("query cmd: " + queryCmd, "MRDS ObjectMgmt", boost::log::trivial::trace);
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
        LogTool::_log("obj_uid: " + object_mgmt_.obj_uid, "MRDS ClassReference", boost::log::trivial::trace);
        LogTool::_log("obj_id: " + object_mgmt_.obj_id, "MRDS ClassReference", boost::log::trivial::trace);
        LogTool::_log("enable: " + std::to_string(object_mgmt_.enable), "MRDS ClassReference",
                      boost::log::trivial::trace);
        LogTool::_log("create_ts: " + object_mgmt_.create_ts, "MRDS ClassReference", boost::log::trivial::trace);
        LogTool::_log("update_ts: " + object_mgmt_.update_ts, "MRDS ClassReference", boost::log::trivial::trace);
        LogTool::_log("region: " + object_mgmt_.region, "MRDS ClassReference", boost::log::trivial::trace);
        LogTool::_log("equipment_class: " + object_mgmt_.equipment_class, "MRDS ClassReference",
                      boost::log::trivial::trace);
        LogTool::_log("vendor: " + object_mgmt_.vendor, "MRDS ClassReference", boost::log::trivial::trace);
        querySize++;
    }
    if (querySize <= 0 && (NO_DATA_EXCEPTION_ALL || NO_DATA_EXCEPTION))
        throw Database::Exception::NoDataException();

    return list_;
}

DB_SCHEMA::object_mgmt ObjectMgmt::get_object_mgmt(const std::string &obj_id) {
    LogTool::_log("get_object_mgmt", "MRDS ObjectMgmt", boost::log::trivial::trace);
    auto queryCmd = boost::str(
            boost::format("SELECT obj_uid, obj_id, enable, create_ts, update_ts, region, equipment_class, vendor "
                          "FROM %1%.%2%.%3% "
                          "WHERE obj_id=%4%") %
            this->connector_->get_database_host().database %
            this->SCHEMA %
            "object_mgmt" %
            null_(obj_id));
    LogTool::_log("query cmd: " + queryCmd, "MRDS ObjectMgmt", boost::log::trivial::trace);
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
        LogTool::_log("obj_uid: " + object_mgmt_.obj_uid, "MRDS ClassReference", boost::log::trivial::trace);
        LogTool::_log("obj_id: " + object_mgmt_.obj_id, "MRDS ClassReference", boost::log::trivial::trace);
        LogTool::_log("enable: " + std::to_string(object_mgmt_.enable), "MRDS ClassReference",
                      boost::log::trivial::trace);
        LogTool::_log("create_ts: " + object_mgmt_.create_ts, "MRDS ClassReference", boost::log::trivial::trace);
        LogTool::_log("update_ts: " + object_mgmt_.update_ts, "MRDS ClassReference", boost::log::trivial::trace);
        LogTool::_log("region: " + object_mgmt_.region, "MRDS ClassReference", boost::log::trivial::trace);
        LogTool::_log("equipment_class: " + object_mgmt_.equipment_class, "MRDS ClassReference",
                      boost::log::trivial::trace);
        LogTool::_log("vendor: " + object_mgmt_.vendor, "MRDS ClassReference", boost::log::trivial::trace);
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
            "vehicle_mgmt");
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
        LogTool::_log("vehicle_id: " + vehicle_mgmt_.vehicle_id, "MRDS ClassReference", boost::log::trivial::trace);
        LogTool::_log("carrier_class: " + vehicle_mgmt_.carrier_class, "MRDS ClassReference",
                      boost::log::trivial::trace);
        LogTool::_log("slot_num: " + std::to_string(vehicle_mgmt_.slot_num), "MRDS ClassReference",
                      boost::log::trivial::trace);
        LogTool::_log("battery_threshold_full: " + std::to_string(vehicle_mgmt_.battery_threshold_full),
                      "MRDS ClassReference",
                      boost::log::trivial::trace);
        LogTool::_log("battery_threshold_high: " + std::to_string(vehicle_mgmt_.battery_threshold_high),
                      "MRDS ClassReference",
                      boost::log::trivial::trace);
        LogTool::_log("battery_threshold_low: " + std::to_string(vehicle_mgmt_.battery_threshold_low),
                      "MRDS ClassReference",
                      boost::log::trivial::trace);
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
            "vehicle_mgmt" %
            null_(obj_id));
    LogTool::_log("query cmd: " + queryCmd, "MRDS ObjectMgmt", boost::log::trivial::trace);
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
        LogTool::_log("vehicle_id: " + vehicle_mgmt_.vehicle_id, "MRDS ClassReference", boost::log::trivial::trace);
        LogTool::_log("carrier_class: " + vehicle_mgmt_.carrier_class, "MRDS ClassReference",
                      boost::log::trivial::trace);
        LogTool::_log("slot_num: " + std::to_string(vehicle_mgmt_.slot_num), "MRDS ClassReference",
                      boost::log::trivial::trace);
        LogTool::_log("battery_threshold_full: " + std::to_string(vehicle_mgmt_.battery_threshold_full),
                      "MRDS ClassReference",
                      boost::log::trivial::trace);
        LogTool::_log("battery_threshold_high: " + std::to_string(vehicle_mgmt_.battery_threshold_high),
                      "MRDS ClassReference",
                      boost::log::trivial::trace);
        LogTool::_log("battery_threshold_low: " + std::to_string(vehicle_mgmt_.battery_threshold_low),
                      "MRDS ClassReference",
                      boost::log::trivial::trace);
    } else if ((NO_DATA_EXCEPTION_ALL || NO_DATA_EXCEPTION))
        throw Database::Exception::NoDataException();

    return vehicle_mgmt_;
}