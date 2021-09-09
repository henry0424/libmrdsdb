//
// Created by henry on 2021-09-04.
//

#include "class_reference.h"

using namespace Database::SQL::MRDS;

std::vector<DB_SCHEMA::carrier_class> ClassReference::get_carrier_class_list() {
    LogTool::_log("get_carrier_class_list", LOGOUT_CLASS, boost::log::trivial::trace);
    auto queryCmd = boost::str(
            boost::format("SELECT carrier_class "
                          "FROM %1%.%2%.%3%;") %
            this->connector_->get_database_host().database %
            this->SCHEMA %
            this->TABLE_CARRIER_CLASS);
    LogTool::_log("query cmd: " + queryCmd, LOGOUT_CLASS, boost::log::trivial::trace);
    auto query = this->connector_->exec(queryCmd);

    auto querySize{0};
    std::vector<DB_SCHEMA::carrier_class> list_;
    list_.clear();
    while (query->next()) {
        auto loc{0};
        DB_SCHEMA::carrier_class carrier_class_;
        carrier_class_.carrier_class = query->value(loc++).toString().toStdString();
        list_.push_back(carrier_class_);
        if (LOGOUT_QUERY_RESULT) {
            LogTool::_log("carrier_class: " + carrier_class_.carrier_class, LOGOUT_CLASS,
                          boost::log::trivial::trace);
        }
        querySize++;
    }
    if (querySize <= 0 && (NO_DATA_EXCEPTION_ALL || NO_DATA_EXCEPTION))
        throw Database::Exception::NoDataException();

    return list_;
}

std::vector<DB_SCHEMA::equipment_class> ClassReference::get_equipment_class_list() {
    LogTool::_log("get_equipment_class_list", LOGOUT_CLASS, boost::log::trivial::trace);
    auto queryCmd = boost::str(
            boost::format("SELECT equipment_class "
                          "FROM %1%.%2%.%3%;") %
            this->connector_->get_database_host().database %
            this->SCHEMA %
            this->TABLE_EQUIPMENT_CLASS);
    LogTool::_log("query cmd: " + queryCmd, LOGOUT_CLASS, boost::log::trivial::trace);
    auto query = this->connector_->exec(queryCmd);

    auto querySize{0};
    std::vector<DB_SCHEMA::equipment_class> list_;
    list_.clear();
    while (query->next()) {
        auto loc{0};
        DB_SCHEMA::equipment_class equipment_class_;
        equipment_class_.equipment_class = query->value(loc++).toString().toStdString();
        list_.push_back(equipment_class_);
        if (LOGOUT_QUERY_RESULT) {
            LogTool::_log("equipment_class: " + equipment_class_.equipment_class, LOGOUT_CLASS,
                          boost::log::trivial::trace);
        }
        querySize++;
    }
    if (querySize <= 0 && (NO_DATA_EXCEPTION_ALL || NO_DATA_EXCEPTION))
        throw Database::Exception::NoDataException();

    return list_;
}

std::vector<DB_SCHEMA::event_class> ClassReference::get_event_class_list() {
    LogTool::_log("get_event_class_list", LOGOUT_CLASS, boost::log::trivial::trace);
    auto queryCmd = boost::str(
            boost::format("SELECT event_class "
                          "FROM %1%.%2%.%3%;") %
            this->connector_->get_database_host().database %
            this->SCHEMA %
            this->TABLE_EVENT_CLASS);
    LogTool::_log("query cmd: " + queryCmd, LOGOUT_CLASS, boost::log::trivial::trace);
    auto query = this->connector_->exec(queryCmd);

    auto querySize{0};
    std::vector<DB_SCHEMA::event_class> list_;
    list_.clear();
    while (query->next()) {
        auto loc{0};
        DB_SCHEMA::event_class event_class_;
        event_class_.event_class = query->value(loc++).toString().toStdString();
        list_.push_back(event_class_);
        if (LOGOUT_QUERY_RESULT) {
            LogTool::_log("event_class: " + event_class_.event_class, LOGOUT_CLASS,
                          boost::log::trivial::trace);
        }
        querySize++;
    }
    if (querySize <= 0 && (NO_DATA_EXCEPTION_ALL || NO_DATA_EXCEPTION))
        throw Database::Exception::NoDataException();

    return list_;
}