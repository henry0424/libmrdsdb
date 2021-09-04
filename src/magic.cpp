//
// Created by henry on 2021-09-04.
//

#include "magic.h"

using namespace Database::SQL::MRDS;

std::map<std::string, std::string> Magic::get_magic_map() {
    LogTool::_log("get_magic_map", "MRDS Magic", boost::log::trivial::trace);
    auto queryCmd = boost::str(
            boost::format("SELECT key, value "
                          "FROM %1%.%2%.%3%;") %
            this->connector_->get_database_host().database %
            this->SCHEMA %
            "magic");
    LogTool::_log("query cmd: " + queryCmd, "MRDS ClassReference", boost::log::trivial::trace);
    auto query = this->connector_->exec(queryCmd);

    auto querySize{0};
    std::map<std::string, std::string> magic_map_;
    magic_map_.clear();
    while (query->next()) {
        auto loc{0};
        auto key = query->value(loc++).toString().toStdString();
        auto value = query->value(loc++).toString().toStdString();
        magic_map_[key] = value;
        LogTool::_log("key: " + key + " value: " + magic_map_[key], "MRDS ClassReference", boost::log::trivial::trace);
        querySize++;
    }
    if (querySize <= 0 && (NO_DATA_EXCEPTION_ALL || NO_DATA_EXCEPTION))
        throw Database::Exception::NoDataException();

    return magic_map_;
}

std::string Magic::get_magic_value(const std::string &key) {
    LogTool::_log("get_magic_value", "MRDS Magic", boost::log::trivial::trace);
    auto queryCmd = boost::str(
            boost::format("SELECT value "
                          "FROM %1%.%2%.%3% "
                          "WHERE key=%4%") %
            this->connector_->get_database_host().database %
            this->SCHEMA %
            "magic" %
            null_(key));
    LogTool::_log("query cmd: " + queryCmd, "MRDS ClassReference", boost::log::trivial::trace);
    auto query = this->connector_->exec(queryCmd);

    auto querySize{0};
    std::string value;
    value.clear();
    while (query->next()) {
        auto loc{0};
        value = query->value(loc++).toString().toStdString();
        LogTool::_log("key: " + key + " value: " + value, "MRDS ClassReference", boost::log::trivial::trace);
        querySize++;
    }
    if (querySize <= 0 && (NO_DATA_EXCEPTION_ALL || NO_DATA_EXCEPTION))
        throw Database::Exception::NoDataException();

    return value;
}