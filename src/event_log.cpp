//
// Created by henry on 2021-09-08.
//

#include "event_log.h"

using namespace Database::SQL::MRDS;

void EventLog::insert_vehicle_event(const DB_SCHEMA::event_log_vehicle log) {
    LogTool::_log("insert_vehicle_event", "MRDS EventLog", boost::log::trivial::trace);
    auto queryCmd = boost::str(
            boost::format("SELECT %1%.%2%.%3%.msg_uuid "
                          "FROM %1%.%2%.%3% "
                          "WHERE %1%.%2%.%3%.msg_uuid=%4%;") %
            this->connector_->get_database_host().database %
            this->SCHEMA %
            this->TABLE_EVENT_LOG_VEHICLE %
            null_(log.msg_uuid));

    LogTool::_log("query cmd: " + queryCmd, "MRDS EventLog", boost::log::trivial::trace);
    auto query = this->connector_->exec(queryCmd);
    if (!query->next()) {
        auto queryCmd = boost::str(
                boost::format("INSERT INTO %1%.%2%.%3% "
                              "(msg_uuid, event_class, vehicle_id, vehicle_status, vehicle_location, carrier_id, comment) "
                              "VALUES (%4%, %5%, %6%, %7%, %8%, %9%, %10%);") %
                this->connector_->get_database_host().database %
                this->SCHEMA %
                this->TABLE_EVENT_LOG_VEHICLE %
                null_(log.msg_uuid) %
                null_(log.event_class) %
                null_(log.vehicle_id) %
                null_(log.vehicle_status) %
                null_(log.vehicle_location) %
                null_(log.carrier_id) %
                null_(log.comment));
        LogTool::_log("query cmd: " + queryCmd, "MRDS EventLog", boost::log::trivial::trace);
        auto query = this->connector_->exec(queryCmd);
    } else {
        this->update_vehicle_event(log);
    }
}

void EventLog::update_vehicle_event(const DB_SCHEMA::event_log_vehicle log) {
    LogTool::_log("update_vehicle_event", "MRDS EventLog", boost::log::trivial::trace);
    auto queryCmd = boost::str(
            boost::format("SELECT %1%.%2%.%3%.msg_uuid "
                          "FROM %1%.%2%.%3% "
                          "WHERE %1%.%2%.%3%.msg_uuid=%4%;") %
            this->connector_->get_database_host().database %
            this->SCHEMA %
            this->TABLE_EVENT_LOG_VEHICLE %
            null_(log.msg_uuid));

    LogTool::_log("query cmd: " + queryCmd, "MRDS EventLog", boost::log::trivial::trace);
    auto query = this->connector_->exec(queryCmd);
    if (query->next()) {
        auto queryCmd = boost::str(
                boost::format("UPDATE %1%.%2%.%3% "
                              "SET event_class=%4%, vehicle_id=%5%, vehicle_status=%6%, vehicle_location=%7%, carrier_id=%8%, comment=%9% "
                              "WHERE msg_uuid=%10%;") %
                this->connector_->get_database_host().database %
                this->SCHEMA %
                this->TABLE_EVENT_LOG_VEHICLE %
                null_(log.event_class) %
                null_(log.vehicle_id) %
                null_(log.vehicle_status) %
                null_(log.vehicle_location) %
                null_(log.carrier_id) %
                null_(log.comment) %
                null_(log.msg_uuid));
        LogTool::_log("query cmd: " + queryCmd, "MRDS EventLog", boost::log::trivial::trace);
        auto query = this->connector_->exec(queryCmd);
    } else {
        this->insert_vehicle_event(log);
    }
}
