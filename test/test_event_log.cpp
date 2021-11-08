
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

    if (0) {
//        auto mrdsdb = std::make_shared<MRDS::EventLog>();
//        mrdsdb->connect(sql_host);
//
//        MRDS::DB_SCHEMA::event_log_vehicle event_log;
//        event_log.msg_uuid = "12345678";
//        event_log.event_class = "VEHICLE_NORMAL";
//        event_log.vehicle_id = "MR001";
//        event_log.vehicle_status = "Hi";
//        event_log.vehicle_location = "UNKNOW";
//        event_log.carrier_id = "?";
//        event_log.comment = "???";
//        mrdsdb->insert_vehicle_event(event_log);
//
//        event_log.comment = "++++";
//        mrdsdb->update_vehicle_event(event_log);
    }
    if (1) {
        auto mrdsdb = std::make_shared<MRDS::UniversalEventLog>();
        mrdsdb->connect(sql_host);

        MRDS::DB_SCHEMA::universal_event_log event_log;
        event_log.event_ts = mrdsdb->get_datetime(MRDS::DT_SOURCE::SYSTEM);
        event_log.event_class = "TRANSFER_COMMAND_NORMAL";
        event_log.obj_class = "TRANSFER_COMMAND";
        event_log.obj_id = "20210000001";
        event_log.carrier_id = "?";
        event_log.comment = "???";
        mrdsdb->insert_universal_event_log(event_log);
    }
    sleep(1);
}