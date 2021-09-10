
#include <iostream>
#include <memory>

//#include "../include/connector.h"
#include "../include/mrdsdb.h"

using namespace Database::SQL;

int main(int argc, char **argv) {
    std::cout << "test_transfer" << std::endl;

    DatabaseHost sql_host;
    sql_host.host = "tachyon.itriroboticslab.org";
    sql_host.port = 5432;
    sql_host.user = "postgres";
    sql_host.passwd = "itriacs";
    sql_host.database = "mrdsdb";

    if (1) {
        auto mrdsdb = std::make_shared<MRDS::ObjectPortStatus>();
        mrdsdb->connect(sql_host);
        auto list_ = mrdsdb->get_object_port_status_list();
        auto list_2 = mrdsdb->get_object_port_status_list("123");
        auto list_3 = mrdsdb->get_object_port_status_list("MR001");
        auto list_4 = mrdsdb->get_object_port_status_list("MR001_SL002");
    }
    if (1) {
        auto mrdsdb = std::make_shared<MRDS::ObjectPortStatus>();
        mrdsdb->connect(sql_host);
        auto list_4 = mrdsdb->get_object_port_status_list("MR001_SL002");
        list_4.at(0).carrier_id = "xxx";
        mrdsdb->update_object_port_status(list_4.at(0));
    }
    sleep(1);
}