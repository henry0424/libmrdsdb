//
// Created by henry on 2021-09-04.
//

#include <boost/date_time.hpp>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>

#include <openssl/md5.h>

#include "connector.h"

using namespace Database::Log;

inline std::string
Database::SQL::calculate_hash(const std::string &content, const std::string &hash, const bool lowercase) {
    unsigned char *md5_result = (unsigned char *) malloc(MD5_DIGEST_LENGTH);
    unsigned char *content_c_str = (unsigned char *) malloc(content.size() + 1);
    std::copy(content.begin(), content.end(), content_c_str);
    content_c_str[content.length()] = 0;
    MD5(content_c_str, content.size(), md5_result);
    free(content_c_str);

    std::stringstream ss;
    ss.clear();
    for (auto i = 0; i < MD5_DIGEST_LENGTH; i++) {
        ss << std::hex << std::setw(2) << std::setfill('0') << (int) md5_result[i];
    }
    auto ret = ss.str();
    if (!lowercase)
        ret = boost::to_upper_copy<std::string>(ret);
    else
        ret = boost::to_lower_copy<std::string>(ret);
//    std::cout << "calculate hash : " << ret << std::endl << std::flush;
    free(md5_result);

    return ret;
}

Database::SQL::Connector::Connector() {

    boost::uuids::name_generator sgen(boost::uuids::nil_uuid());
    auto uuid_sgen = sgen(std::string(
            boost::posix_time::to_iso_extended_string(
                    boost::posix_time::microsec_clock::local_time())));
    this->uuid_ = boost::uuids::to_string(uuid_sgen);

    LogTool::_log_init(LogOutput::FILE | LogOutput::SCEEN, "./Log/", "SQL_LOG_");
    LogTool::_log("Connector Init (" + this->uuid_ + ")", "Qt Connector", boost::log::trivial::info);

}

Database::SQL::QtConnector::QtConnector() {
    LogTool::_log("QtConnector Init (" + this->uuid_ + ")", "Qt Connector", boost::log::trivial::info);
}

Database::SQL::QtConnector::~QtConnector() {
    LogTool::_log("QtConnector Delete (" + this->uuid_ + ")", "Qt Connector", boost::log::trivial::info);
    this->close();
}

int Database::SQL::QtConnector::connect(const DatabaseHost host) {
    this->databasehost_ = std::make_shared<DatabaseHost>(host);

    LogTool::_log("host: " + this->databasehost_->host, "Qt Connector", boost::log::trivial::info);
    LogTool::_log("port: " + std::to_string(this->databasehost_->port), "Qt Connector", boost::log::trivial::info);
    LogTool::_log("user: " + this->databasehost_->user, "Qt Connector", boost::log::trivial::info);
    LogTool::_log("passwd: " + calculate_hash(this->databasehost_->passwd), "Qt Connector", boost::log::trivial::info);
    LogTool::_log("database: " + this->databasehost_->database, "Qt Connector", boost::log::trivial::info);
    LogTool::_log("driver: " + this->databasehost_->driver, "Qt Connector", boost::log::trivial::info);

    this->qt_db_ = std::make_shared<QSqlDatabase>(QSqlDatabase::addDatabase(
            this->databasehost_->driver.c_str(), QString(this->uuid_.c_str())));

    qt_db_->setHostName(this->databasehost_->host.c_str());
    qt_db_->setPort(this->databasehost_->port);
    qt_db_->setUserName(this->databasehost_->user.c_str());
    qt_db_->setPassword(this->databasehost_->passwd.c_str());
    qt_db_->setDatabaseName(this->databasehost_->database.c_str());

    if (this->qt_db_->open())
        LogTool::_log("Connect: " + this->qt_db_->connectionName().toStdString() + " host: " +
                      this->databasehost_->host + "@" + this->databasehost_->user + " succ", "Qt Connector",
                      boost::log::trivial::info);
    else {
        LogTool::_log("Connect: " + this->qt_db_->connectionName().toStdString() + " host: " +
                      this->databasehost_->host + "@" + this->databasehost_->user + " failed " +
                      qt_db_->lastError().text().toStdString(), "Qt Connector",
                      boost::log::trivial::info);
        throw std::runtime_error("Connect: " + this->qt_db_->connectionName().toStdString() + " host: " +
                                 this->databasehost_->host + "@" + this->databasehost_->user + " failed");
    }
//    this->qt_query_ = std::make_shared<QSqlQuery>(*qt_db_);
}


void Database::SQL::QtConnector::close() {
    std::lock_guard<std::mutex> lock(mutex_);

//    LogTool::_log("QSqlQuery clear+finish", "Qt Connector", boost::log::trivial::trace);
//    this->qt_query_->clear();
//    this->qt_query_->finish();

    LogTool::_log("QSqlDatabase close", "Qt Connector", boost::log::trivial::trace);
    this->qt_db_->close();

    LogTool::_log("QSqlDatabase removeDatabase", "Qt Connector", boost::log::trivial::trace);
    auto name = this->qt_db_->connectionName();
    QSqlDatabase::removeDatabase(name);

    LogTool::_log("Close:" + std::string(name.toStdString()) + " succ ", "Qt Connector",
                  boost::log::trivial::trace);
}

QueryInfo Database::SQL::QtConnector::exec(const std::string &query) {
    std::lock_guard<std::mutex> lock(mutex_);
    auto sql_query_ = std::make_shared<QSqlQuery>(*qt_db_);
    LogTool::_log("exec: " + query, "Qt Connector", boost::log::trivial::trace);
    if (!sql_query_->exec(query.c_str())) {
        if (LOGOUT_EXEC)
            LogTool::_log("exec: " + query + " exception", "Qt Connector", boost::log::trivial::error);
        throw Database::Exception::QueryException();
    }
    return sql_query_;
}

Database::SQL::DatabaseHost Database::SQL::QtConnector::get_database_host() {
    return *this->databasehost_;
}

std::string Database::SQL::QtConnector::get_connection_name() {
    return this->qt_db_->connectionName().toStdString();
}