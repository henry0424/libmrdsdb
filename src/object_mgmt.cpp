//
// Created by henry on 2021-09-04.
//

#include "object_mgmt.h"

using namespace Database::SQL::MRDS;

ObjectMgmt::ObjectMgmt(const DATABASE_NAME db) : MRDSDB(db) {
    LogTool::_log("ObjectMgmt *****", LOGOUT_CLASS, boost::log::trivial::trace);
}

auto
ObjectMgmt::get_object_mgmt_list(const std::string &keyword) -> std::optional<std::vector<DB_SCHEMA::object_mgmt>> {
    LogTool::_log("get_object_mgmt_list", LOGOUT_CLASS, boost::log::trivial::trace);

    auto queryCmd = boost::str(
            boost::format("SELECT %1%.%2%.%3%.obj_uid, "
                          "%1%.%2%.%3%.obj_id, "
                          "%1%.%2%.%3%.enable, "
                          "%1%.%2%.%3%.region, "
                          "%1%.%2%.%3%.equipment_class, "
                          "%1%.%2%.%3%.vendor "
                          "FROM %1%.%2%.%3% "
                          "%4%") %
            this->connector_->get_database_host().database %
            this->SCHEMA %
            this->TABLE_OBJECT_MGMT %
            fuzzy_query_(this->connector_->get_database_host().database, this->SCHEMA, this->TABLE_OBJECT_MGMT,
                         keyword, {"obj_uid", "obj_id", "CAST:enable", "region", "equipment_class", "vendor"}));
    LogTool::_log("query cmd: " + queryCmd, LOGOUT_CLASS, boost::log::trivial::trace);
    auto query = this->connector_->exec(queryCmd);

    auto querySize{0};
    std::vector<DB_SCHEMA::object_mgmt> list_;
    list_.clear();
    while (query->next()) {
        auto loc{0};
        DB_SCHEMA::object_mgmt object_mgmt_;
        {
            object_mgmt_.obj_uid = query->value(loc++).toString().toStdString();
            object_mgmt_.obj_id = query->value(loc++).toString().toStdString();
            object_mgmt_.enable = query->value(loc++).toBool();
            object_mgmt_.region = query->value(loc++).toString().toStdString();
            object_mgmt_.equipment_class = query->value(loc++).toString().toStdString();
            object_mgmt_.vendor = query->value(loc++).toString().toStdString();
        }
        list_.push_back(object_mgmt_);
        if (LOGOUT_QUERY_RESULT) {
            LogTool::_log("obj_uid: " + object_mgmt_.obj_uid, LOGOUT_CLASS, boost::log::trivial::trace);
            LogTool::_log("obj_id: " + object_mgmt_.obj_id, LOGOUT_CLASS, boost::log::trivial::trace);
            LogTool::_log("enable: " + std::to_string(object_mgmt_.enable), LOGOUT_CLASS, boost::log::trivial::trace);
            LogTool::_log("region: " + object_mgmt_.region, LOGOUT_CLASS, boost::log::trivial::trace);
            LogTool::_log("equipment_class: " + object_mgmt_.equipment_class, LOGOUT_CLASS, boost::log::trivial::trace);
            LogTool::_log("vendor: " + object_mgmt_.vendor, LOGOUT_CLASS, boost::log::trivial::trace);
        }
        querySize++;
    }
    if (querySize <= 0 && (NO_DATA_EXCEPTION_ALL || NO_DATA_EXCEPTION))
        throw Database::Exception::NoDataException();

    return querySize ? std::optional<std::reference_wrapper<std::vector<DB_SCHEMA::object_mgmt>>>{list_}
                     : std::nullopt;
}

//*****************************************************//
//*****************************************************//

VehicleMgmt::VehicleMgmt(const DATABASE_NAME db) : ObjectMgmt(db) {
    LogTool::_log("VehicleMgmt *****", LOGOUT_CLASS, boost::log::trivial::trace);
}

auto
VehicleMgmt::get_vehicle_mgmt_list(const std::string &keyword) -> std::optional<std::vector<DB_SCHEMA::vehicle_mgmt>> {
    LogTool::_log("get_vehicle_mgmt_list", LOGOUT_CLASS, boost::log::trivial::trace);

    auto queryCmd = boost::str(
            boost::format("SELECT %1%.%2%.%3%.vehicle_id, "
                          "%1%.%2%.%3%.carrier_class, "
                          "%1%.%2%.%3%.slot_num, "
                          "%1%.%2%.%3%.battery_threshold_full, "
                          "%1%.%2%.%3%.battery_threshold_high, "
                          "%1%.%2%.%3%.battery_threshold_low, "
                          "%1%.%2%.%3%.macaddr, "
                          "host(%1%.%2%.%3%.ipaddr) "
                          "FROM %1%.%2%.%3% "
                          "%4%") %
            this->connector_->get_database_host().database %
            this->SCHEMA %
            this->TABLE_VEHICLE_MGMT %
            fuzzy_query_(this->connector_->get_database_host().database, this->SCHEMA, this->TABLE_VEHICLE_MGMT,
                         keyword, {"vehicle_id", "carrier_class", "CAST:macaddr", "CAST:ipaddr"}));
    LogTool::_log("query cmd: " + queryCmd, LOGOUT_CLASS, boost::log::trivial::trace);
    auto query = this->connector_->exec(queryCmd);

    auto querySize{0};
    std::vector<DB_SCHEMA::vehicle_mgmt> list_;
    list_.clear();
    while (query->next()) {
        auto loc{0};
        DB_SCHEMA::vehicle_mgmt vehicle_mgmt_;
        {
            vehicle_mgmt_.vehicle_id = query->value(loc++).toString().toStdString();
            vehicle_mgmt_.carrier_class = query->value(loc++).toString().toStdString();
            vehicle_mgmt_.slot_num = query->value(loc++).toInt();
            vehicle_mgmt_.battery_threshold_full = query->value(loc++).toInt();
            vehicle_mgmt_.battery_threshold_high = query->value(loc++).toInt();
            vehicle_mgmt_.battery_threshold_low = query->value(loc++).toInt();
            vehicle_mgmt_.macaddr = query->value(loc++).toString().toStdString();
            vehicle_mgmt_.ipaddr = query->value(loc++).toString().toStdString();
        }
        list_.push_back(vehicle_mgmt_);
        if (LOGOUT_QUERY_RESULT) {
            LogTool::_log("vehicle_id: " + vehicle_mgmt_.vehicle_id, LOGOUT_CLASS, boost::log::trivial::trace);
            LogTool::_log("carrier_class: " + vehicle_mgmt_.carrier_class, LOGOUT_CLASS,
                          boost::log::trivial::trace);
            LogTool::_log("slot_num: " + std::to_string(vehicle_mgmt_.slot_num), LOGOUT_CLASS,
                          boost::log::trivial::trace);
            LogTool::_log("battery_threshold_full: " + std::to_string(vehicle_mgmt_.battery_threshold_full),
                          LOGOUT_CLASS,
                          boost::log::trivial::trace);
            LogTool::_log("battery_threshold_high: " + std::to_string(vehicle_mgmt_.battery_threshold_high),
                          LOGOUT_CLASS,
                          boost::log::trivial::trace);
            LogTool::_log("battery_threshold_low: " + std::to_string(vehicle_mgmt_.battery_threshold_low),
                          LOGOUT_CLASS,
                          boost::log::trivial::trace);
            LogTool::_log("macaddr: " + vehicle_mgmt_.macaddr, LOGOUT_CLASS,
                          boost::log::trivial::trace);
            LogTool::_log("ipaddr: " + vehicle_mgmt_.ipaddr, LOGOUT_CLASS,
                          boost::log::trivial::trace);
        }
        querySize++;
    }
    if (querySize <= 0 && (NO_DATA_EXCEPTION_ALL || NO_DATA_EXCEPTION))
        throw Database::Exception::NoDataException();

    return querySize ? std::optional<std::reference_wrapper<std::vector<DB_SCHEMA::vehicle_mgmt>>>{list_}
                     : std::nullopt;
}

void VehicleMgmt::update_vehicle_mgmt(const DB_SCHEMA::vehicle_mgmt vehicle_status) {
    LogTool::_log("update_vehicle_mgmt", LOGOUT_CLASS, boost::log::trivial::trace);

    auto queryCmd = boost::str(
            boost::format("SELECT %1%.%2%.%3%.vehicle_id "
                          "FROM %1%.%2%.%3% "
                          "WHERE %1%.%2%.%3%.vehicle_id=%4%;") %
            this->connector_->get_database_host().database %
            this->SCHEMA %
            this->TABLE_VEHICLE_MGMT %
            null_(vehicle_status.vehicle_id));

    LogTool::_log("query cmd: " + queryCmd, LOGOUT_CLASS, boost::log::trivial::trace);
    auto query = this->connector_->exec(queryCmd);
    if (query->next()) {
        auto queryCmd = boost::str(
                boost::format("UPDATE %1%.%2%.%3% "
                              "SET carrier_class=%4%, "
                              "slot_num=%5%, "
                              "battery_threshold_full=%6%, "
                              "battery_threshold_high=%7%, "
                              "battery_threshold_low=%8%, "
                              "macaddr=%9%, "
                              "ipaddr=%10% "
                              "WHERE vehicle_id=%11%;") %
                this->connector_->get_database_host().database %
                this->SCHEMA %
                this->TABLE_VEHICLE_MGMT %
                null_(vehicle_status.carrier_class) %
                vehicle_status.slot_num %
                vehicle_status.battery_threshold_full %
                vehicle_status.battery_threshold_high %
                vehicle_status.battery_threshold_low %
                null_(vehicle_status.macaddr) %
                null_(vehicle_status.ipaddr + "/32") %
                null_(vehicle_status.vehicle_id));
        LogTool::_log("query cmd: " + queryCmd, LOGOUT_CLASS, boost::log::trivial::trace);
        auto query = this->connector_->exec(queryCmd);
    } else {
        throw Exception::NoDataException();
    }
}

//*****************************************************//
//*****************************************************//

VehicleSlotMgmt::VehicleSlotMgmt(const DATABASE_NAME db) : VehicleMgmt(db) {
    LogTool::_log("VehicleSlotMgmt *****", LOGOUT_CLASS, boost::log::trivial::trace);
}

auto VehicleSlotMgmt::get_vehicle_slot_mgmt_list(
        const std::string &keyword) -> std::optional<std::vector<DB_SCHEMA::vehicle_slot_mgmt>> {
    LogTool::_log("get_vehicle_slot_mgmt_list", LOGOUT_CLASS, boost::log::trivial::trace);

    auto where = [=]() -> std::string {
        if (keyword.empty()) {
            auto queryCmd = boost::str(
                    boost::format("WHERE obj_id IN (SELECT vehicle_id FROM %1%.%2%.%3%)") %
                    this->connector_->get_database_host().database %
                    this->SCHEMA %
                    this->TABLE_VEHICLE_MGMT);
            return queryCmd;
        } else {
            auto queryCmd = boost::str(
                    boost::format("WHERE obj_id IN (SELECT vehicle_id FROM %1%.%2%.%4%) "
                                  "AND %1%.%2%.%3%.obj_port_id LIKE '%%%5%%%';") %
                    this->connector_->get_database_host().database %
                    this->SCHEMA %
                    this->TABLE_OBJECT_PORT_MGMT %
                    this->TABLE_VEHICLE_MGMT %
                    keyword);
            return queryCmd;
        }
    };

    auto queryCmd = boost::str(
            boost::format("SELECT obj_id as vehicle_id, "
                          "obj_port_id as vehicle_slot_id "
                          "FROM %1%.%2%.%3% "
                          "%4%") %
            this->connector_->get_database_host().database %
            this->SCHEMA %
            this->TABLE_OBJECT_PORT_MGMT %
            where());
    LogTool::_log("query cmd: " + queryCmd, LOGOUT_CLASS, boost::log::trivial::trace);
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
            LogTool::_log("vehicle_id: " + vehicle_slot_mgmt_.vehicle_id, LOGOUT_CLASS,
                          boost::log::trivial::trace);
            LogTool::_log("vehicle_slot_id: " + vehicle_slot_mgmt_.vehicle_slot_id, LOGOUT_CLASS,
                          boost::log::trivial::trace);
        }
        querySize++;
    }
    if (querySize <= 0 && (NO_DATA_EXCEPTION_ALL || NO_DATA_EXCEPTION))
        throw Database::Exception::NoDataException();

    return querySize ? std::optional<std::reference_wrapper<std::vector<DB_SCHEMA::vehicle_slot_mgmt>>>{list_}
                     : std::nullopt;
}

//*****************************************************//
//*****************************************************//

EquipmentMgmt::EquipmentMgmt(
        const DATABASE_NAME db) : ObjectMgmt(db) {
    LogTool::_log("EquipmentMgmt *****", LOGOUT_CLASS, boost::log::trivial::trace);
}

auto EquipmentMgmt::get_equipment_mgmt_list(
        const std::string &keyword) -> std::optional<std::vector<DB_SCHEMA::equipment_mgmt>> {
    LogTool::_log("get_equipment_mgmt_list", LOGOUT_CLASS, boost::log::trivial::trace);

    auto queryCmd = boost::str(
            boost::format("SELECT %1%.%2%.%3%.equipment_id "
                          "FROM %1%.%2%.%3% "
                          "%4%") %
            this->connector_->get_database_host().database %
            this->SCHEMA %
            this->TABLE_EQUIPMENT_MGMT %
            fuzzy_query_(this->connector_->get_database_host().database, this->SCHEMA, this->TABLE_EQUIPMENT_MGMT,
                         keyword, {"equipment_id"}));
    LogTool::_log("query cmd: " + queryCmd, LOGOUT_CLASS, boost::log::trivial::trace);
    auto query = this->connector_->exec(queryCmd);

    auto querySize{0};
    std::vector<DB_SCHEMA::equipment_mgmt> list_;
    list_.clear();
    while (query->next()) {
        auto loc{0};
        DB_SCHEMA::equipment_mgmt equipment_mgmt_;
        {
            equipment_mgmt_.equipment_id = query->value(loc++).toString().toStdString();
        }
        list_.push_back(equipment_mgmt_);
        if (LOGOUT_QUERY_RESULT) {
            LogTool::_log("equipment_id: " + equipment_mgmt_.equipment_id, LOGOUT_CLASS, boost::log::trivial::trace);
        }
        querySize++;
    }
    if (querySize <= 0 && (NO_DATA_EXCEPTION_ALL || NO_DATA_EXCEPTION))
        throw Database::Exception::NoDataException();

    return querySize ? std::optional<std::reference_wrapper<std::vector<DB_SCHEMA::equipment_mgmt>>>{list_}
                     : std::nullopt;
}

//*****************************************************//
//*****************************************************//

EquipmentPortMgmt::EquipmentPortMgmt(
        const DATABASE_NAME db) : EquipmentMgmt(db) {
    LogTool::_log("EquipmentPortMgmt *****", LOGOUT_CLASS, boost::log::trivial::trace);
}

auto EquipmentPortMgmt::get_equipment_port_mgmt_list(
        const std::string &keyword) -> std::optional<std::vector<DB_SCHEMA::equipment_port_mgmt>> {
    LogTool::_log("equipment_port_mgmt", LOGOUT_CLASS, boost::log::trivial::trace);

    auto where = [=]() -> std::string {
        if (keyword.empty()) {
            auto queryCmd = boost::str(
                    boost::format("WHERE obj_id IN (SELECT equipment_id FROM %1%.%2%.%3%)") %
                    this->connector_->get_database_host().database %
                    this->SCHEMA %
                    this->TABLE_EQUIPMENT_MGMT);
            return queryCmd;
        } else {
            auto queryCmd = boost::str(
                    boost::format("WHERE obj_id IN (SELECT equipment_id FROM %1%.%2%.%4%) "
                                  "AND %1%.%2%.%3%.obj_port_id LIKE '%%%5%%%';") %
                    this->connector_->get_database_host().database %
                    this->SCHEMA %
                    this->TABLE_OBJECT_PORT_MGMT %
                    this->TABLE_EQUIPMENT_MGMT %
                    keyword);
            return queryCmd;
        }
    };

    auto queryCmd = boost::str(
            boost::format("SELECT obj_id as equipment_id, "
                          "obj_port_id as equipment_port_id "
                          "FROM %1%.%2%.%3% "
                          "%4%") %
            this->connector_->get_database_host().database %
            this->SCHEMA %
            this->TABLE_OBJECT_PORT_MGMT %
            where());
    LogTool::_log("query cmd: " + queryCmd, LOGOUT_CLASS, boost::log::trivial::trace);
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
            LogTool::_log("equipment_id: " + equipment_port_mgmt_.equipment_id, LOGOUT_CLASS,
                          boost::log::trivial::trace);
            LogTool::_log("equipment_port_id: " + equipment_port_mgmt_.equipment_port_id, LOGOUT_CLASS,
                          boost::log::trivial::trace);
        }
        querySize++;
    }
    if (querySize <= 0 && (NO_DATA_EXCEPTION_ALL || NO_DATA_EXCEPTION))
        throw Database::Exception::NoDataException();

    return querySize ? std::optional<std::reference_wrapper<std::vector<DB_SCHEMA::equipment_port_mgmt>>>{list_}
                     : std::nullopt;
}

