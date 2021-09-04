//
// Created by henry on 2021-09-04.
//

#include "class_reference.h"

using namespace Database::SQL::MRDS;

std::vector<ClassReference::CarrierClass> ClassReference::get_carrier_class_list() {
    LogTool::_log("get_carrier_class_list", "MRDS ClassReference", boost::log::trivial::trace);
    auto queryCmd = boost::str(
            boost::format("SELECT carrier_class "
                          "FROM %1%.%2%.%3%;") %
            this->connector_->get_database_host().database %
            this->SCHEMA %
            "carrier_class");
    LogTool::_log("query cmd: " + queryCmd, "MRDS ClassReference", boost::log::trivial::trace);
    auto query = this->connector_->exec(queryCmd);

    auto querySize{0};
    std::vector<ClassReference::CarrierClass> list_;
    list_.clear();
    while (query->next()) {
        auto loc{0};
        CarrierClass carrier_class_;
        carrier_class_.carrier_class = query->value(loc++).toString().toStdString();
        list_.push_back(carrier_class_);
        LogTool::_log("carrier_class: " + carrier_class_.carrier_class, "MRDS ClassReference", boost::log::trivial::trace);
        querySize++;
    }
    if (querySize <= 0 && (NO_DATA_EXCEPTION_ALL || NO_DATA_EXCEPTION))
        throw Database::Exception::NoDataException();

    return list_;
}

std::vector<ClassReference::EquipmentClass> ClassReference::get_equipment_class_list() {
    LogTool::_log("get_equipment_class_list", "MRDS ClassReference", boost::log::trivial::trace);
    auto queryCmd = boost::str(
            boost::format("SELECT equipment_class "
                          "FROM %1%.%2%.%3%;") %
            this->connector_->get_database_host().database %
            this->SCHEMA %
            "equipment_class");
    LogTool::_log("query cmd: " + queryCmd, "MRDS ClassReference", boost::log::trivial::trace);
    auto query = this->connector_->exec(queryCmd);

    auto querySize{0};
    std::vector<ClassReference::EquipmentClass> list_;
    list_.clear();
    while (query->next()) {
        auto loc{0};
        EquipmentClass equipment_class_;
        equipment_class_.equipment_class = query->value(loc++).toString().toStdString();
        list_.push_back(equipment_class_);
        LogTool::_log("equipment_class: " + equipment_class_.equipment_class, "MRDS ClassReference", boost::log::trivial::trace);
        querySize++;
    }
    if (querySize <= 0 && (NO_DATA_EXCEPTION_ALL || NO_DATA_EXCEPTION))
        throw Database::Exception::NoDataException();

    return list_;
}

std::vector<ClassReference::EventClass> ClassReference::get_event_class_list() {
    LogTool::_log("get_event_class_list", "MRDS ClassReference", boost::log::trivial::trace);
    auto queryCmd = boost::str(
            boost::format("SELECT event_class "
                          "FROM %1%.%2%.%3%;") %
            this->connector_->get_database_host().database %
            this->SCHEMA %
            "event_class");
    LogTool::_log("query cmd: " + queryCmd, "MRDS ClassReference", boost::log::trivial::trace);
    auto query = this->connector_->exec(queryCmd);

    auto querySize{0};
    std::vector<ClassReference::EventClass> list_;
    list_.clear();
    while (query->next()) {
        auto loc{0};
        EventClass event_class_;
        event_class_.event_class = query->value(loc++).toString().toStdString();
        list_.push_back(event_class_);
        LogTool::_log("event_class: " + event_class_.event_class, "MRDS ClassReference", boost::log::trivial::trace);
        querySize++;
    }
    if (querySize <= 0 && (NO_DATA_EXCEPTION_ALL || NO_DATA_EXCEPTION))
        throw Database::Exception::NoDataException();

    return list_;
}