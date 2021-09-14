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
    std::lock_guard<std::mutex> lock(s_mutex_);
    boost::uuids::name_generator sgen(boost::uuids::nil_uuid());
    auto uuid_sgen = sgen(std::string(
            boost::posix_time::to_iso_extended_string(
                    boost::posix_time::microsec_clock::local_time())));
    this->uuid_ = boost::uuids::to_string(uuid_sgen);

    LogTool::_log_init(LogOutput::FILE | LogOutput::SCEEN, "./Log/", "SQL_LOG_");
    LogTool::_set_filter_level(boost::log::trivial::trace);
    LogTool::_log("Connector Init (" + this->uuid_ + ")", LOGOUT_CLASS, boost::log::trivial::info);

}

Database::SQL::QtConnector::QtConnector() {
    LogTool::_log("QtConnector Init (" + this->uuid_ + ")", LOGOUT_CLASS, boost::log::trivial::info);
}

Database::SQL::QtConnector::~QtConnector() {
    LogTool::_log("QtConnector Delete (" + this->uuid_ + ")", LOGOUT_CLASS, boost::log::trivial::info);
    this->close();
}

int Database::SQL::QtConnector::connect(const DatabaseHost host) {
    this->databasehost_ = std::make_shared<DatabaseHost>(host);

    LogTool::_log("host: " + this->databasehost_->host, LOGOUT_CLASS, boost::log::trivial::info);
    LogTool::_log("port: " + std::to_string(this->databasehost_->port), LOGOUT_CLASS, boost::log::trivial::info);
    LogTool::_log("user: " + this->databasehost_->user, LOGOUT_CLASS, boost::log::trivial::info);
    LogTool::_log("passwd: " + calculate_hash(this->databasehost_->passwd), LOGOUT_CLASS, boost::log::trivial::info);
    LogTool::_log("database: " + this->databasehost_->database, LOGOUT_CLASS, boost::log::trivial::info);
    LogTool::_log("driver: " + this->databasehost_->driver, LOGOUT_CLASS, boost::log::trivial::info);

    this->qt_db_ = std::make_shared<QSqlDatabase>(QSqlDatabase::addDatabase(
            this->databasehost_->driver.c_str(), QString(this->uuid_.c_str())));

    qt_db_->setHostName(this->databasehost_->host.c_str());
    qt_db_->setPort(this->databasehost_->port);
    qt_db_->setUserName(this->databasehost_->user.c_str());
    qt_db_->setPassword(this->databasehost_->passwd.c_str());
    qt_db_->setDatabaseName(this->databasehost_->database.c_str());

    if (this->qt_db_->open())
        LogTool::_log("Connect: " + this->qt_db_->connectionName().toStdString() + " host: " +
                      this->databasehost_->user + "@" + this->databasehost_->host + " succ", LOGOUT_CLASS,
                      boost::log::trivial::info);
    else {
        LogTool::_log("Connect: " + this->qt_db_->connectionName().toStdString() + " host: " +
                      this->databasehost_->user + "@" + this->databasehost_->host + " failed " +
                      qt_db_->lastError().text().toStdString(), LOGOUT_CLASS,
                      boost::log::trivial::info);
        throw std::runtime_error("Connect: " + this->qt_db_->connectionName().toStdString() + " host: " +
                                 this->databasehost_->user + "@" + this->databasehost_->host + " failed");
    }
//    this->qt_query_ = std::make_shared<QSqlQuery>(*qt_db_);
}


void Database::SQL::QtConnector::close() {
    std::lock_guard<std::mutex> lock(mutex_);

//    LogTool::_log("QSqlQuery clear+finish", LOGOUT_CLASS, boost::log::trivial::trace);
//    this->qt_query_->clear();
//    this->qt_query_->finish();

    LogTool::_log("QSqlDatabase close", LOGOUT_CLASS, boost::log::trivial::trace);
    this->qt_db_->close();

    LogTool::_log("QSqlDatabase removeDatabase", LOGOUT_CLASS, boost::log::trivial::trace);
    auto name = this->qt_db_->connectionName();
    QSqlDatabase::removeDatabase(name);

    LogTool::_log("Close:" + std::string(name.toStdString()) + " succ ", LOGOUT_CLASS,
                  boost::log::trivial::trace);
}

QueryInfo Database::SQL::QtConnector::exec(const std::string &query) {
    std::lock_guard<std::mutex> lock(mutex_);
    auto sql_query_ = std::make_shared<QSqlQuery>(*qt_db_);
    LogTool::_log("exec: " + query, LOGOUT_CLASS, boost::log::trivial::trace);
    if (!sql_query_->exec(query.c_str())) {
        if (LOGOUT_EXEC)
            LogTool::_log("exec: " + query + " exception", LOGOUT_CLASS, boost::log::trivial::error);
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

int Database::SQL::SQLServerConn::connect(const Database::SQL::DatabaseHost host) {
    LogTool::_log("connect m2", LOGOUT_CLASS, boost::log::trivial::info);


    this->qt_db_ = std::make_shared<QSqlDatabase>(QSqlDatabase::addDatabase(
            this->QT_SQL_DRIVER.c_str(), QString(this->uuid_.c_str())));


    this->qt_db_->setUserName(host.user.c_str());
    this->qt_db_->setPassword(host.passwd.c_str());

    std::string hostname{"tcp:127.0.0.1"};

    std::vector<std::string> hostnames;
    hostnames.clear();

//    hostnames.push_back("tcp:127.0.0.1");
    auto host_ip = boost::str(boost::format("tcp:%1%") % host.host);
    hostnames.push_back(host_ip);

    for (auto host_ip: hostnames) {
        if (!this->qt_db_->isOpen()) {
            auto ODBC3_DRIVE = boost::str(
                    boost::format("DRIVER={%1%}; SERVER=%2%; DATABASE=%3%; odbc_cursortype=2") %
                    "ODBC Driver 17 for SQL Server" %
                    host_ip %
                    host.database);
            this->qt_db_->setDatabaseName(ODBC3_DRIVE.c_str());
            this->qt_db_->setConnectOptions("SQL_ATTR_LOGIN_TIMEOUT=1");

            LogTool::_log("Connect: " + this->qt_db_->connectionName().toStdString() + " -> " +
                          std::string(host.user) + "@" + host_ip,
                          LOGOUT_CLASS, boost::log::trivial::info);
            if (this->qt_db_->open()) {
                break;
            } else {
                LogTool::_log(
                        "Connect: " + this->qt_db_->connectionName().toStdString() + " -> " + std::string(host_ip) +
                        "@" + host.user + " failed", LOGOUT_CLASS,
                        boost::log::trivial::error);
            }
        }
    }

    if (this->qt_db_->open()) {
        LogTool::_log(
                "Connect: " + this->qt_db_->connectionName().toStdString() + " -> " + std::string(host.user) + "@" +
                host_ip + " succ", LOGOUT_CLASS, boost::log::trivial::info);
    } else {
        throw std::runtime_error("Connect: " + this->qt_db_->connectionName().toStdString() + " -> " +
                                 std::string(host.user) + "@" + host_ip + " failed");
    }
//    this->qt_query_ = std::make_shared<QSqlQuery>(*qt_db_);
}
