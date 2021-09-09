
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
        auto mrdsdb = std::make_shared<MRDS::VehicleStatus>();
        mrdsdb->connect(sql_host);
        auto list_ = mrdsdb->get_vehicle_status_list();
        auto list_2 = mrdsdb->get_vehicle_status_list("MR002");
        auto list_3 = mrdsdb->get_vehicle_status_list("LOW");
    }
    if (1) {
        auto mrdsdb = std::make_shared<MRDS::VehicleStatus>();
        mrdsdb->connect(sql_host);
        auto list_ = mrdsdb->get_vehicle_status_list("MR001");
        list_.at(0).battery_status = "HIGH";
        mrdsdb->update_vehicle_status(list_.at(0));
    }
    sleep(1);
}