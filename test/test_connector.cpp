
#include <iostream>
#include <memory>

#include "../include/connector.h"

using namespace Database::SQL;

int main(int argc, char **argv) {
    std::cout << "test_connector" << std::endl;
    if (1) {
        Database::SQL::DatabaseHost sql_host;
        sql_host.host = "tachyon.itriroboticslab.org";
        sql_host.port = 5432;
        sql_host.user = "postgres";
        sql_host.passwd = "itriacs";
        sql_host.database = "mrdsdb";

        auto sql_connector = std::make_shared<PostgreSQLConn>();
        sql_connector->connect(sql_host);

        for (int i = 0; i < 1; ++i) {
            auto query = sql_connector->exec("SELECT NOW()");
            if (query->next())
                std::cout << query->value(0).toString().toStdString() << std::endl;
        }
    }
    if (1) {
        Database::SQL::DatabaseHost sql_host;
        sql_host.host = "tachyon.itriroboticslab.org";
        sql_host.port = 1433;
        sql_host.user = "sa";
        sql_host.passwd = "K??k\"HSF!w5A";
        sql_host.database = "imcsdb";

        auto sql_connector = std::make_shared<SQLServerConn>();
        sql_connector->connect(sql_host);

        for (int i = 0; i < 1; ++i) {
            auto query = sql_connector->exec("SELECT GETDATE()");
            if (query->next())
                std::cout << query->value(0).toString().toStdString() << std::endl;
        }
    }

}