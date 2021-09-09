//
// Created by henry on 2021-09-04.
//

#include <boost/format.hpp>
#include <boost/date_time.hpp>

#include "mrdsdb_base.h"

using namespace Database::SQL::MRDS;

MRDSDB::MRDSDB(const DATABASE_NAME db) {
    database_name_ = db;
}

int MRDSDB::connect(const Database::SQL::DatabaseHost host) {
    LogTool::_log("connect", LOGOUT_CLASS, boost::log::trivial::trace);

//    this->connector_.reset();
    if (!this->connector_) {
        if (database_name_ == DATABASE_NAME::POSTGRESQL)
            this->connector_ = std::make_shared<Database::SQL::PostgreSQLConn>();
        if (database_name_ == DATABASE_NAME::SQLSERVER)
            this->connector_ = std::make_shared<Database::SQL::SQLServerConn>();
    }

    return this->connector_->connect(host);
}

void MRDSDB::swap_connector(MRDSDB *ptr_mrdsdb) {
    LogTool::_log("swap", LOGOUT_CLASS, boost::log::trivial::trace);
    if (this->connector_)
        LogTool::_log("old connection name:" + this->connector_->get_connection_name(), LOGOUT_CLASS,
                      boost::log::trivial::trace);
    this->connector_.swap(ptr_mrdsdb->connector_);
    LogTool::_log("new connection name:" + this->connector_->get_connection_name(), LOGOUT_CLASS,
                  boost::log::trivial::trace);
}

std::string MRDSDB::get_datetime(const DT_SOURCE src) {
    if (src == DT_SOURCE::SYSTEM) {
        boost::posix_time::ptime timeLocal = boost::posix_time::microsec_clock::local_time();
        return std::string(boost::posix_time::to_iso_extended_string(timeLocal));
    } else if (src == DT_SOURCE::DATABASE) {
        auto query = this->connector_->exec("SELECT NOW();");
        if (query->next())
            return query->value(0).toString().toStdString();
    }
}


