
#include <iostream>
#include <memory>

//#include "../include/connector.h"
#include "../include/mrdsdb.h"

using namespace Database::SQL;

int main(int argc, char **argv) {
    std::cout << "test_mrdsdb_base" << std::endl;

    DatabaseHost sql_host;
    sql_host.host = "tachyon.itriroboticslab.org";
    sql_host.port = 5432;
    sql_host.user = "postgres";
    sql_host.passwd = "itriacs";
    sql_host.database = "mrdsdb";

    auto mrdsdb = std::make_shared<MRDS::MRDSDB>();
    mrdsdb->connect(sql_host);
    auto str = mrdsdb->null_(std::string(""));
    auto dt_SYSTEM = mrdsdb->get_datetime(MRDS::DT_SOURCE::SYSTEM);
    auto dt_DATABASE = mrdsdb->get_datetime(MRDS::DT_SOURCE::DATABASE);
    sleep(1);
}