
#include <iostream>
#include <memory>

//#include "../include/connector.h"
#include "../include/mrdsdb.h"

using namespace Database::SQL;

int main(int argc, char **argv) {
    std::cout << "test_class_reference" << std::endl;

    DatabaseHost sql_host;
    sql_host.host = "tachyon.itriroboticslab.org";
    sql_host.port = 5432;
    sql_host.user = "postgres";
    sql_host.passwd = "itriacs";
    sql_host.database = "mrdsdb";

    auto mrdsdb = std::make_shared<MRDS::Magic>();
    mrdsdb->connect(sql_host);

    auto magic_map = mrdsdb->get_magic_map();
    auto value = mrdsdb->get_magic_value("VERSION_MRDS");

    sleep(1);
}