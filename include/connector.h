//
// Created by henry on 2021-09-04.
//

#ifndef LIBMRDSDB_CONNECTOR_H
#define LIBMRDSDB_CONNECTOR_H

#include <iostream>
#include <memory>
#include <vector>
#include <mutex>
#include <locale>
#include <codecvt>

#include <boost/format.hpp>
#include <boost/date_time.hpp>

#include <qt5/QtSql/qsqldatabase.h>
#include <qt5/QtSql/qsqlquery.h>
#include <qt5/QtSql/qsqlerror.h>
#include <qt5/QtCore/QtDebug>

#include "log.hpp"
#include "exception.hpp"

typedef std::shared_ptr<QSqlQuery> QueryInfo;

using namespace Database::Log;

namespace Database::SQL {

    struct DatabaseHost {
        std::string host;
        int port;
        std::string user;
        std::string passwd;
        std::string database;
        std::string driver{"QPSQL"};
    };

    inline std::string
    calculate_hash(const std::string &content, const std::string &hash = "MD5", const bool lowercase = true);


    class Connector {
    protected:
        std::mutex mutex_;
        std::string uuid_;
        std::shared_ptr<DatabaseHost> databasehost_;

    public:
        Connector();

        virtual ~Connector() = default;

        virtual int connect(const DatabaseHost host) = 0;

        virtual void close() = 0;

    };

    class QtConnector : public Connector {
    protected:
        std::shared_ptr<QSqlDatabase> qt_db_;
        std::shared_ptr<QSqlQuery> qt_query_;

    public:
        QtConnector();

        ~QtConnector();

        int connect(const DatabaseHost host) override;

        void close() override;

        QueryInfo exec(const std::string &query);

        DatabaseHost get_database_host();
    };

}


#endif //LIBMRDSDB_CONNECTOR_H
