
#include <iostream>
#include <memory>

#include "../include/connector.h"

using namespace Database::SQL;

int main(int argc, char **argv) {
    std::cout << "test_connector" << std::endl;

    Database::SQL::DatabaseHost sql_host;
    sql_host.host = "tachyon.itriroboticslab.org";
    sql_host.port = 5432;
    sql_host.user = "postgres";
    sql_host.passwd = "itriacs";
    sql_host.database = "mrdsdb";

    auto sql_connector = std::make_shared<QtConnector>();
    sql_connector->connect(sql_host);

    for (int i = 0; i < 100; ++i) {
        auto query = sql_connector->exec("SELECT NOW()");
        if (query->next())
            std::cout << query->value(0).toString().toStdString() << std::endl;
    }
}