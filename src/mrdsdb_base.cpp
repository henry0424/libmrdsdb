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

std::string MRDSDB::fuzzy_query_(const std::string db, const std::string schema, const std::string table,
                                 const std::string keyword, const std::initializer_list<std::string> columns) {
    LogTool::_log("fuzzy_query_: " + table + " <- " + keyword, LOGOUT_CLASS,
                  boost::log::trivial::trace);

    if (keyword.empty())
        return ";";

    auto dst = boost::str(boost::format("%1%.%2%.%3%.") %
                          db %
                          schema %
                          table);

    auto queryCmd = boost::str(boost::format());
    auto i = 0;
    for (auto col: columns) {
        i == 0 ? queryCmd += "WHERE " : queryCmd += "OR ";
        if (col.find("CAST:") == std::string::npos) {
            queryCmd += dst + boost::str(boost::format("%1% LIKE '%%%2%%%' ") %
                                         col %
                                         keyword);
        } else {
            const std::string CAST{"CAST:"};
            auto idx = col.find(CAST);
            col.erase(idx, CAST.length());
            queryCmd += "CAST(" + dst + boost::str(boost::format("%1% as varchar) LIKE '%%%2%%%' ") %
                                                   col %
                                                   keyword);
        }
        i++;
    }
    queryCmd += ";";
    return queryCmd;
}


