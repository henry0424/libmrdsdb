//
// Created by henry on 2021-09-09.
//

#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/split.hpp>

#include "parking.h"

using namespace Database::SQL::MRDS;

std::vector<DB_SCHEMA::parking_mgmt> ParkingMgmt::get_parking_mgmt_list(const std::string &keyword) {
    LogTool::_log("get_parking_mgmt_list", LOGOUT_CLASS, boost::log::trivial::trace);

    auto where = [=]() -> std::string {
        if (keyword.empty())
            return ";";
        else {
            auto queryCmd = boost::str(
                    boost::format(
                            "WHERE %1%.%2%.%3%.parking_space_id LIKE '%%%4%%%' "
                            "OR %1%.%2%.%3%.parking_space_location LIKE '%%%4%%%'"
                            "OR %1%.%2%.%3%.prefer_vehicle LIKE '%%%4%%%';") %
                    this->connector_->get_database_host().database %
                    this->SCHEMA %
                    this->TABLE_PARKING_MGMT %
                    keyword);
            return queryCmd;
        }
    };

    auto queryCmd = boost::str(
            boost::format("SELECT %1%.%2%.%3%.parking_space_id, "
                          "%1%.%2%.%3%.parking_space_location, "
                          "%1%.%2%.%3%.prefer_vehicle "
                          "FROM %1%.%2%.%3% "
                          "%4%") %
            this->connector_->get_database_host().database %
            this->SCHEMA %
            this->TABLE_PARKING_MGMT %
            where());
    LogTool::_log("query cmd: " + queryCmd, LOGOUT_CLASS, boost::log::trivial::trace);
    auto query = this->connector_->exec(queryCmd);

    auto querySize{0};
    std::vector<DB_SCHEMA::parking_mgmt> list_;
    list_.clear();
    while (query->next()) {
        auto loc{0};
        DB_SCHEMA::parking_mgmt parking_mgmt_;
        {
            auto split_prefer_vehicle = [=](const std::string &prefer_vehicle) -> std::vector<std::string> {
                std::vector<std::string> rs;
                boost::split(rs, prefer_vehicle, boost::is_any_of(",;:"), boost::token_compress_on);
                return rs;
            };

            parking_mgmt_.parking_space_id = query->value(loc++).toString().toStdString();
            parking_mgmt_.parking_space_location = query->value(loc++).toString().toStdString();
            parking_mgmt_.prefer_vehicle = split_prefer_vehicle(query->value(loc++).toString().toStdString());
        }
        list_.push_back(parking_mgmt_);
        if (LOGOUT_QUERY_RESULT) {
            LogTool::_log("parking_space_id: " + parking_mgmt_.parking_space_id, LOGOUT_CLASS,
                          boost::log::trivial::trace);
            LogTool::_log("parking_space_location: " + parking_mgmt_.parking_space_location, LOGOUT_CLASS,
                          boost::log::trivial::trace);
            for (auto vehicle: parking_mgmt_.prefer_vehicle) {
                LogTool::_log("prefer_vehicle: " + vehicle, LOGOUT_CLASS,
                              boost::log::trivial::trace);
            }
        }
        querySize++;
    }
    if (querySize <= 0 && (NO_DATA_EXCEPTION_ALL || NO_DATA_EXCEPTION))
        throw Database::Exception::NoDataException();

    return list_;
}

//*****************************************************//
//*****************************************************//

std::vector<DB_SCHEMA::parking_status> ParkingStatus::get_parking_status_list(const std::string &keyword) {
    LogTool::_log("get_parking_status_list", LOGOUT_CLASS, boost::log::trivial::trace);

    auto where = [=]() -> std::string {
        if (keyword.empty())
            return ";";
        else {
            auto queryCmd = boost::str(
                    boost::format(
                            "WHERE %1%.%2%.%3%.parking_space_id LIKE '%%%4%%%' "
                            "OR %1%.%2%.%3%.booking LIKE '%%%4%%%'"
                            "OR %1%.%2%.%3%.booking_owner LIKE '%%%4%%%'"
                            "OR %1%.%2%.%3%.parking_vehicle_id LIKE '%%%4%%%';") %
                    this->connector_->get_database_host().database %
                    this->SCHEMA %
                    this->TABLE_PARKING_STATUS %
                    keyword);
            return queryCmd;
        }
    };

    auto queryCmd = boost::str(
            boost::format("SELECT %1%.%2%.%3%.parking_space_id, "
                          "%1%.%2%.%3%.booking, "
                          "%1%.%2%.%3%.booking_owner, "
                          "%1%.%2%.%3%.parking_vehicle_id "
                          "FROM %1%.%2%.%3% "
                          "%4%") %
            this->connector_->get_database_host().database %
            this->SCHEMA %
            this->TABLE_PARKING_STATUS %
            where());
    LogTool::_log("query cmd: " + queryCmd, LOGOUT_CLASS, boost::log::trivial::trace);
    auto query = this->connector_->exec(queryCmd);

    auto querySize{0};
    std::vector<DB_SCHEMA::parking_status> list_;
    list_.clear();
    while (query->next()) {
        auto loc{0};
        DB_SCHEMA::parking_status parking_status_;
        {
            parking_status_.parking_space_id = query->value(loc++).toString().toStdString();
            parking_status_.booking = query->value(loc++).toString().toStdString();
            parking_status_.booking_owner = query->value(loc++).toString().toStdString();
            parking_status_.parking_vehicle_id = query->value(loc++).toString().toStdString();
        }
        list_.push_back(parking_status_);
        if (LOGOUT_QUERY_RESULT) {
            LogTool::_log("parking_space_id: " + parking_status_.parking_space_id, LOGOUT_CLASS,
                          boost::log::trivial::trace);
            LogTool::_log("booking: " + parking_status_.booking, LOGOUT_CLASS,
                          boost::log::trivial::trace);
            LogTool::_log("booking_owner: " + parking_status_.booking_owner, LOGOUT_CLASS,
                          boost::log::trivial::trace);
            LogTool::_log("parking_vehicle_id: " + parking_status_.parking_vehicle_id, LOGOUT_CLASS,
                          boost::log::trivial::trace);
        }
        querySize++;
    }
    if (querySize <= 0 && (NO_DATA_EXCEPTION_ALL || NO_DATA_EXCEPTION))
        throw Database::Exception::NoDataException();

    return list_;
}

void ParkingStatus::update_parking_status(const DB_SCHEMA::parking_status parking_status) {
    LogTool::_log("update_parking_status", LOGOUT_CLASS, boost::log::trivial::trace);
    auto queryCmd = boost::str(
            boost::format("SELECT %1%.%2%.%3%.parking_space_id "
                          "FROM %1%.%2%.%3% "
                          "WHERE %1%.%2%.%3%.parking_space_id=%4%;") %
            this->connector_->get_database_host().database %
            this->SCHEMA %
            this->TABLE_PARKING_STATUS %
            null_(parking_status.parking_space_id));

    LogTool::_log("query cmd: " + queryCmd, LOGOUT_CLASS, boost::log::trivial::trace);
    auto query = this->connector_->exec(queryCmd);
    if (!query->next()) {
        auto queryCmd = boost::str(
                boost::format("INSERT INTO %1%.%2%.%3% "
                              "(parking_space_id) "
                              "VALUES (%4%);") %
                this->connector_->get_database_host().database %
                this->SCHEMA %
                this->TABLE_PARKING_STATUS %
                null_(parking_status.parking_space_id));
        LogTool::_log("query cmd: " + queryCmd, LOGOUT_CLASS, boost::log::trivial::trace);
        auto query = this->connector_->exec(queryCmd);
    }
    {
        auto queryCmd = boost::str(
                boost::format("UPDATE %1%.%2%.%3% "
                              "SET update_ts=%4%, booking=%5%, booking_owner=%6%, parking_vehicle_id=%7% "
                              "WHERE parking_space_id=%8%;") %
                this->connector_->get_database_host().database %
                this->SCHEMA %
                this->TABLE_PARKING_STATUS %
                default_(this->get_datetime(DT_SOURCE::SYSTEM)) %
                null_(parking_status.booking) %
                null_(parking_status.booking_owner) %
                null_(parking_status.parking_vehicle_id) %
                null_(parking_status.parking_space_id));
        LogTool::_log("query cmd: " + queryCmd, LOGOUT_CLASS, boost::log::trivial::trace);
        auto query = this->connector_->exec(queryCmd);
    }
}
