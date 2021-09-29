
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
        auto mrdsdb = std::make_shared<MRDS::ParkingMgmt>();
        mrdsdb->connect(sql_host);
//        auto list_ = mrdsdb->get_parking_mgmt_list();
//        auto list_2 = mrdsdb->get_parking_mgmt_list("PARK_01");
        auto list_3 = mrdsdb->get_parking_mgmt_list("MR001");
        if (list_3.has_value()) {
            for (int i = 0; i < list_3->size(); ++i) {
                std::cout << list_3->at(i).parking_space_id << std::endl;
                std::cout <<"\t"<< list_3->at(i).parking_space_location << std::endl;
                for (int j = 0; j < list_3->at(i).prefer_vehicle.size(); ++j) {
                    std::cout <<"\t\t"<< list_3->at(i).prefer_vehicle.at(j) << std::endl;
                }
            }
        }

    }
    if (0) {
        auto mrdsdb = std::make_shared<MRDS::ParkingStatus>();
        mrdsdb->connect(sql_host);
        auto list_ = mrdsdb->get_parking_status_list();
        auto list_2 = mrdsdb->get_parking_status_list("PARK_01");
        auto list_3 = mrdsdb->get_parking_status_list("MR001");
    }
    if (1) {
        auto mrdsdb = std::make_shared<MRDS::ParkingStatus>();
        mrdsdb->connect(sql_host);
        auto parking_status = mrdsdb->get_parking_status_list("PARK_01");
        parking_status->at(0).booking = "UNBOOKING";
        parking_status->at(0).parking_vehicle_id = "";
        mrdsdb->update_parking_status(parking_status->at(0));

        parking_status->at(0).booking = "BOOKING";
        parking_status->at(0).parking_vehicle_id = "MR001";
        mrdsdb->update_parking_status(parking_status->at(0));
    }

    sleep(1);
}