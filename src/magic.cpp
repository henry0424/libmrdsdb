//
// Created by henry on 2021-09-04.
//

#include "magic.h"

using namespace Database::SQL::MRDS;

Magic::Magic(const DATABASE_NAME db) : MRDSDB(db) {
    LogTool::_log("Magic *****", LOGOUT_CLASS, boost::log::trivial::trace);
}

std::map<std::string, std::string> Magic::get_magic_map() {
    LogTool::_log("get_magic_map", LOGOUT_CLASS, boost::log::trivial::trace);
    auto queryCmd = boost::str(
            boost::format("SELECT key, value "
                          "FROM %1%.%2%.%3%;") %
            this->connector_->get_database_host().database %
            this->SCHEMA %
            this->TABLE_MAGIC);
    LogTool::_log("query cmd: " + queryCmd, LOGOUT_CLASS, boost::log::trivial::trace);
    auto query = this->connector_->exec(queryCmd);

    auto querySize{0};
    std::map<std::string, std::string> magic_map_;
    magic_map_.clear();
    while (query->next()) {
        auto loc{0};
        auto key = query->value(loc++).toString().toStdString();
        auto value = query->value(loc++).toString().toStdString();
        magic_map_[key] = value;
        if (LOGOUT_QUERY_RESULT) {
            LogTool::_log("key: " + key + " value: " + magic_map_[key], LOGOUT_CLASS, boost::log::trivial::trace);
        }
        querySize++;
    }
    if (querySize <= 0 && (NO_DATA_EXCEPTION_ALL || NO_DATA_EXCEPTION))
        throw Database::Exception::NoDataException();

    return magic_map_;
}

auto Magic::get_magic_value(const std::string &key) -> std::optional<std::string> {
    LogTool::_log("get_magic_value", LOGOUT_CLASS, boost::log::trivial::trace);
    auto queryCmd = boost::str(
            boost::format("SELECT value "
                          "FROM %1%.%2%.%3% "
                          "WHERE key=%4%") %
            this->connector_->get_database_host().database %
            this->SCHEMA %
            this->TABLE_MAGIC %
            null_(key));
    LogTool::_log("query cmd: " + queryCmd, LOGOUT_CLASS, boost::log::trivial::trace);
    auto query = this->connector_->exec(queryCmd);

    auto querySize{0};
    std::string value;
    value.clear();
    while (query->next()) {
        auto loc{0};
        value = query->value(loc++).toString().toStdString();
        if (LOGOUT_QUERY_RESULT) {
            LogTool::_log("key: " + key + " value: " + value, LOGOUT_CLASS, boost::log::trivial::trace);
        }
        querySize++;
    }
    if (querySize <= 0 && (NO_DATA_EXCEPTION_ALL || NO_DATA_EXCEPTION))
        throw Database::Exception::NoDataException();

    return querySize ? std::optional<std::reference_wrapper<std::string>>{value}
                     : std::nullopt;
}

void Magic::set_magic_map(const std::map<std::string, std::string> map) {
    LogTool::_log("set_magic_map", LOGOUT_CLASS, boost::log::trivial::trace);

    auto compare_diff_map = [=]() -> std::map<std::string, std::string> {
        auto mrdsdb_magic_map = this->get_magic_map();
        std::map<std::string, std::string> diff_map;
        diff_map.clear();
        for (const auto&[key, value]: map) {
            if (mrdsdb_magic_map[key] != value) {
                diff_map[key] = value;
                if (mrdsdb_magic_map.find(key) == mrdsdb_magic_map.end())
                    LogTool::_log("Magic change key: " + key + " value: " + value, LOGOUT_CLASS,
                                  boost::log::trivial::trace);
                else
                    LogTool::_log("Magic change key: " + key + " value: " + mrdsdb_magic_map[key] + " -> " + value,
                                  LOGOUT_CLASS,
                                  boost::log::trivial::trace);
            }
        }
        return diff_map;
    };

    auto diff_map = compare_diff_map();
    for (const auto&[key, value]: diff_map) {
        set_magic_value(key, value);
    }
}

void Magic::set_magic_value(const std::string &key, const std::string &value) {
    LogTool::_log("set_magic_value", LOGOUT_CLASS, boost::log::trivial::trace);
    auto queryCmd = boost::str(
            boost::format("SELECT key "
                          "FROM %1%.%2%.%3% "
                          "WHERE key=%4%") %
            this->connector_->get_database_host().database %
            this->SCHEMA %
            this->TABLE_MAGIC %
            null_(key));
    LogTool::_log("query cmd: " + queryCmd, LOGOUT_CLASS, boost::log::trivial::trace);
    auto query = this->connector_->exec(queryCmd);
    if (!query->next()) {
        auto queryCmd = boost::str(
                boost::format("INSERT INTO %1%.%2%.%3% (key, value) "
                              "VALUES(%4%, %5%);") %
                this->connector_->get_database_host().database %
                this->SCHEMA %
                this->TABLE_MAGIC %
                null_(key) %
                null_(value));
        LogTool::_log("query cmd: " + queryCmd, LOGOUT_CLASS, boost::log::trivial::trace);
        auto query = this->connector_->exec(queryCmd);
    } else {
        auto update_ts = this->get_datetime(DT_SOURCE::SYSTEM);
        auto queryCmd = boost::str(
                boost::format("UPDATE %1%.%2%.%3% "
                              "SET value=%4%, update_ts=%5% "
                              "WHERE key=%6%;") %
                this->connector_->get_database_host().database %
                this->SCHEMA %
                this->TABLE_MAGIC %
                null_(value) %
                null_(update_ts) %
                null_(key));
        LogTool::_log("query cmd: " + queryCmd, LOGOUT_CLASS, boost::log::trivial::trace);
        auto query = this->connector_->exec(queryCmd);
    }
}