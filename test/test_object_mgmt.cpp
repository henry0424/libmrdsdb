
#include <iostream>
#include <memory>

//#include "../include/connector.h"
#include "../include/mrdsdb.h"

using namespace Database::SQL;

int main(int argc, char **argv) {
    std::cout << "test_object_mgmt" << std::endl;

    DatabaseHost sql_host;
    sql_host.host = "tachyon.itriroboticslab.org";
    sql_host.port = 5432;
    sql_host.user = "postgres";
    sql_host.passwd = "itriacs";
    sql_host.database = "mrdsdb";

    if (0) {
        auto mrdsdb = std::make_shared<MRDS::ObjectMgmt>();
        mrdsdb->connect(sql_host);

        auto object_mgmt_list = mrdsdb->get_object_mgmt_list();
        auto object_mgmt = mrdsdb->get_object_mgmt_list(object_mgmt_list->at(0).obj_id);
    }
    if (1) {
        auto mrdsdb = std::make_shared<MRDS::VehicleMgmt>();
        mrdsdb->connect(sql_host);

        auto vehicle_mgmt_list = mrdsdb->get_vehicle_mgmt_list();
//        auto vehicle_mgmt = mrdsdb->get_vehicle_mgmt_list(vehicle_mgmt_list.at(0).vehicle_id);
        auto vehicle_mgmt = mrdsdb->get_vehicle_mgmt_list("192.168.10.2");
        vehicle_mgmt->at(0).battery_threshold_full = 10;
        vehicle_mgmt->at(0).battery_threshold_high = 10;
        vehicle_mgmt->at(0).battery_threshold_low = 10;
        vehicle_mgmt->at(0).ipaddr="192.168.99.1";
        mrdsdb->update_vehicle_mgmt(vehicle_mgmt->at(0));
    }
    if (0) {
        auto mrdsdb = std::make_shared<MRDS::VehicleSlotMgmt>();
        mrdsdb->connect(sql_host);

        auto vehicle_slot_mgmt_list = mrdsdb->get_vehicle_slot_mgmt_list();
        auto vehicle_slot_mgmt_list_2 = mrdsdb->get_vehicle_slot_mgmt_list(vehicle_slot_mgmt_list->at(0).vehicle_id);
        auto vehicle_slot_mgmt = mrdsdb->get_vehicle_slot_mgmt_list(vehicle_slot_mgmt_list->at(0).vehicle_slot_id);
    }
    if (0) {
        auto mrdsdb = std::make_shared<MRDS::EquipmentMgmt>();
        mrdsdb->connect(sql_host);

        auto equipment_mgmt_list = mrdsdb->get_equipment_mgmt_list();
        auto equipment_mgmt = mrdsdb->get_equipment_mgmt_list(equipment_mgmt_list->at(0).equipment_id);
    }
    if (1) {
        auto mrdsdb = std::make_shared<MRDS::EquipmentPortMgmt>();
        mrdsdb->connect(sql_host);

        auto equipment_port_mgmt_list = mrdsdb->get_equipment_port_mgmt_list();
        auto equipment_port_mgmt_list_2 = mrdsdb->get_equipment_port_mgmt_list(
                equipment_port_mgmt_list->at(0).equipment_id);
        auto equipment_port_mgmt = mrdsdb->get_equipment_port_mgmt_list(equipment_port_mgmt_list_2->at(0).equipment_port_id);
    }

    sleep(1);
}