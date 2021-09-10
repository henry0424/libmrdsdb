//
// Created by henry on 2021-09-10.
//

#include "object_port_status.h"

using namespace Database::SQL::MRDS;

ObjectPortStatus::ObjectPortStatus(const DATABASE_NAME db) : MRDSDB(db) {
    LogTool::_log("ObjectPortStatus *****", LOGOUT_CLASS, boost::log::trivial::trace);
}

std::vector<DB_SCHEMA::object_port_status>
ObjectPortStatus::get_object_port_status_list(const std::string &keyword) {
    LogTool::_log("get_object_port_status_list", LOGOUT_CLASS, boost::log::trivial::trace);

    auto where = [=]() -> std::string {
        if (keyword.empty())
            return ";";
        else {
            auto queryCmd = boost::str(
                    boost::format(
                            "WHERE %1%.%2%.%3%.obj_id LIKE '%%%4%%%' "
                            "OR %1%.%2%.%3%.obj_port_id LIKE '%%%4%%%'"
                            "OR %1%.%2%.%3%.carrier_id LIKE '%%%4%%%';") %
                    this->connector_->get_database_host().database %
                    this->SCHEMA %
                    this->TABLE_OBJECT_PORT_STATUS %
                    keyword);
            return queryCmd;
        }
    };

    auto queryCmd = boost::str(
            boost::format("SELECT %1%.%2%.%3%.obj_id, "
                          "%1%.%2%.%3%.obj_port_id, "
                          "%1%.%2%.%3%.carrier_id "
                          "FROM %1%.%2%.%3% "
                          "%4%") %
            this->connector_->get_database_host().database %
            this->SCHEMA %
            this->TABLE_OBJECT_PORT_STATUS %
            where());
    LogTool::_log("query cmd: " + queryCmd, LOGOUT_CLASS, boost::log::trivial::trace);
    auto query = this->connector_->exec(queryCmd);

    auto querySize{0};
    std::vector<DB_SCHEMA::object_port_status> list_;
    list_.clear();
    while (query->next()) {
        auto loc{0};
        DB_SCHEMA::object_port_status object_port_status_;
        {
            object_port_status_.obj_id = query->value(loc++).toString().toStdString();
            object_port_status_.obj_port_id = query->value(loc++).toString().toStdString();
            object_port_status_.carrier_id = query->value(loc++).toString().toStdString();
        }
        list_.push_back(object_port_status_);
        if (LOGOUT_QUERY_RESULT) {
            LogTool::_log("obj_id: " + object_port_status_.obj_id, LOGOUT_CLASS, boost::log::trivial::trace);
            LogTool::_log("obj_port_id: " + object_port_status_.obj_port_id, LOGOUT_CLASS, boost::log::trivial::trace);
            LogTool::_log("carrier_id: " + object_port_status_.carrier_id, LOGOUT_CLASS, boost::log::trivial::trace);
        }
        querySize++;
    }
    if (querySize <= 0 && (NO_DATA_EXCEPTION_ALL || NO_DATA_EXCEPTION))
        throw Database::Exception::NoDataException();

    return list_;
}

void ObjectPortStatus::update_object_port_status(const DB_SCHEMA::object_port_status object_port_status) {
    LogTool::_log("update_object_port_status", LOGOUT_CLASS, boost::log::trivial::trace);
    auto queryCmd = boost::str(
            boost::format("SELECT %1%.%2%.%3%.obj_port_id "
                          "FROM %1%.%2%.%3% "
                          "WHERE %1%.%2%.%3%.obj_port_id=%4%;") %
            this->connector_->get_database_host().database %
            this->SCHEMA %
            this->TABLE_OBJECT_PORT_STATUS %
            null_(object_port_status.obj_port_id));

    LogTool::_log("query cmd: " + queryCmd, LOGOUT_CLASS, boost::log::trivial::trace);
    auto query = this->connector_->exec(queryCmd);
    if (!query->next()) {
        auto queryCmd = boost::str(
                boost::format("INSERT INTO %1%.%2%.%3% "
                              "(obj_id, obj_port_id) "
                              "VALUES (%4%, %5%);") %
                this->connector_->get_database_host().database %
                this->SCHEMA %
                this->TABLE_OBJECT_PORT_STATUS %
                null_(object_port_status.obj_id) %
                null_(object_port_status.obj_port_id));
        LogTool::_log("query cmd: " + queryCmd, LOGOUT_CLASS, boost::log::trivial::trace);
        auto query = this->connector_->exec(queryCmd);
    }
    {
        auto queryCmd = boost::str(
                boost::format("UPDATE %1%.%2%.%3% "
                              "SET update_ts=%4%, carrier_id=%5% "
                              "WHERE obj_port_id=%6%;") %
                this->connector_->get_database_host().database %
                this->SCHEMA %
                this->TABLE_OBJECT_PORT_STATUS %
                default_(this->get_datetime(DT_SOURCE::SYSTEM)) %
                null_(object_port_status.carrier_id) %
                null_(object_port_status.obj_port_id));
        LogTool::_log("query cmd: " + queryCmd, LOGOUT_CLASS, boost::log::trivial::trace);
        auto query = this->connector_->exec(queryCmd);
    }
}
