//
// Created by henry on 2021-09-09.
//

#include "vehicle_status.h"

using namespace Database::SQL::MRDS;

VehicleStatus::VehicleStatus(const DATABASE_NAME db) : MRDSDB(db) {
    LogTool::_log("VehicleStatus *****", LOGOUT_CLASS, boost::log::trivial::trace);
}

auto Database::SQL::MRDS::VehicleStatus::get_vehicle_status_list(
        const std::string &keyword) -> std::optional<std::vector<DB_SCHEMA::vehicle_status>> {
    LogTool::_log("get_vehicle_status_list", LOGOUT_CLASS, boost::log::trivial::trace);

    auto where = [=]() -> std::string {
        if (keyword.empty())
            return ";";
        else {
            auto queryCmd = boost::str(
                    boost::format(
                            "WHERE %1%.%2%.%3%.vehicle_id LIKE '%%%4%%%' "
                            "OR %1%.%2%.%3%.vehicle_location LIKE '%%%4%%%'"
                            "OR %1%.%2%.%3%.vehicle_status LIKE '%%%4%%%'"
                            "OR %1%.%2%.%3%.battery_status LIKE '%%%4%%%';") %
                    this->connector_->get_database_host().database %
                    this->SCHEMA %
                    this->TABLE_VEHICLE_STATUS %
                    keyword);
            return queryCmd;
        }
    };

    auto queryCmd = boost::str(
            boost::format("SELECT %1%.%2%.%3%.vehicle_id, "
                          "%1%.%2%.%3%.vehicle_location, "
                          "%1%.%2%.%3%.vehicle_status, "
                          "%1%.%2%.%3%.battery_status "
                          "FROM %1%.%2%.%3% "
                          "%4%") %
            this->connector_->get_database_host().database %
            this->SCHEMA %
            this->TABLE_VEHICLE_STATUS %
            where());
    LogTool::_log("query cmd: " + queryCmd, LOGOUT_CLASS, boost::log::trivial::trace);
    auto query = this->connector_->exec(queryCmd);

    auto querySize{0};
    std::vector<DB_SCHEMA::vehicle_status> list_;
    list_.clear();
    while (query->next()) {
        auto loc{0};
        DB_SCHEMA::vehicle_status vehicle_status_;
        {
            vehicle_status_.vehicle_id = query->value(loc++).toString().toStdString();
            vehicle_status_.vehicle_location = query->value(loc++).toString().toStdString();
            vehicle_status_.vehicle_status = query->value(loc++).toString().toStdString();
            vehicle_status_.battery_status = query->value(loc++).toString().toStdString();
        }
        list_.push_back(vehicle_status_);
        if (LOGOUT_QUERY_RESULT) {
            LogTool::_log("vehicle_id: " + vehicle_status_.vehicle_id, LOGOUT_CLASS, boost::log::trivial::trace);
            LogTool::_log("vehicle_location: " + vehicle_status_.vehicle_location, LOGOUT_CLASS,
                          boost::log::trivial::trace);
            LogTool::_log("vehicle_status: " + vehicle_status_.vehicle_status, LOGOUT_CLASS,
                          boost::log::trivial::trace);
            LogTool::_log("battery_status: " + vehicle_status_.battery_status, LOGOUT_CLASS,
                          boost::log::trivial::trace);
        }
        querySize++;
    }
    if (querySize <= 0 && (NO_DATA_EXCEPTION_ALL || NO_DATA_EXCEPTION))
        throw Database::Exception::NoDataException();

    return querySize ? std::optional<std::reference_wrapper<std::vector<DB_SCHEMA::vehicle_status>>>{list_}
                     : std::nullopt;
}

void VehicleStatus::update_vehicle_status(const DB_SCHEMA::vehicle_status vehicle_status) {
    LogTool::_log("update_vehicle_status", LOGOUT_CLASS, boost::log::trivial::trace);
    auto queryCmd = boost::str(
            boost::format("SELECT %1%.%2%.%3%.vehicle_id "
                          "FROM %1%.%2%.%3% "
                          "WHERE %1%.%2%.%3%.vehicle_id=%4%;") %
            this->connector_->get_database_host().database %
            this->SCHEMA %
            this->TABLE_VEHICLE_STATUS %
            null_(vehicle_status.vehicle_id));

    LogTool::_log("query cmd: " + queryCmd, LOGOUT_CLASS, boost::log::trivial::trace);
    auto query = this->connector_->exec(queryCmd);
    if (!query->next()) {
        auto queryCmd = boost::str(
                boost::format("INSERT INTO %1%.%2%.%3% "
                              "(vehicle_id) "
                              "VALUES (%4%);") %
                this->connector_->get_database_host().database %
                this->SCHEMA %
                this->TABLE_VEHICLE_STATUS %
                null_(vehicle_status.vehicle_id));
        LogTool::_log("query cmd: " + queryCmd, LOGOUT_CLASS, boost::log::trivial::trace);
        auto query = this->connector_->exec(queryCmd);
    }
    {
        auto queryCmd = boost::str(
                boost::format("UPDATE %1%.%2%.%3% "
                              "SET update_ts=%4%, vehicle_location=%5%, vehicle_status=%6%, battery_status=%7% "
                              "WHERE vehicle_id=%8%;") %
                this->connector_->get_database_host().database %
                this->SCHEMA %
                this->TABLE_VEHICLE_STATUS %
                default_(this->get_datetime(DT_SOURCE::SYSTEM)) %
                null_(vehicle_status.vehicle_location) %
                null_(vehicle_status.vehicle_status) %
                null_(vehicle_status.battery_status) %
                null_(vehicle_status.vehicle_id));
        LogTool::_log("query cmd: " + queryCmd, LOGOUT_CLASS, boost::log::trivial::trace);
        auto query = this->connector_->exec(queryCmd);
    }
}