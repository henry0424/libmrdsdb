//
// Created by henry on 2021-09-04.
//

#include <boost/format.hpp>
#include <boost/date_time.hpp>

#include "mrdsdb_base.h"

using namespace Database::SQL::MRDS;

MRDSDB::MRDSDB() {

}

int MRDSDB::connect(const Database::SQL::DatabaseHost host) {
    LogTool::_log("connect", "MRDS MRDSDB", boost::log::trivial::trace);

    this->connector_.reset();
    this->connector_ = std::make_shared<Database::SQL::QtConnector>();
    return this->connector_->connect(host);
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
