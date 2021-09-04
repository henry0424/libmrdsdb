
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

    {
        auto mrdsdb = std::make_shared<MRDS::ObjectMgmt>();
        mrdsdb->connect(sql_host);

        auto object_mgmt_list = mrdsdb->get_object_mgmt_list();
        auto object_mgmt = mrdsdb->get_object_mgmt(object_mgmt_list.at(0).obj_id);
    }
    {
        auto mrdsdb = std::make_shared<MRDS::VehicleMgmt>();
        mrdsdb->connect(sql_host);

        auto vehicle_mgmt_list = mrdsdb->get_vehicle_mgmt_list();
        auto vehicle_mgmt = mrdsdb->get_vehicle_mgmt(vehicle_mgmt_list.at(0).vehicle_id);
    }

    sleep(1);
}