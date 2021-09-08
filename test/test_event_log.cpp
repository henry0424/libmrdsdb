
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
        auto mrdsdb = std::make_shared<MRDS::EventLog>();
        mrdsdb->connect(sql_host);

        MRDS::DB_SCHEMA::event_log_vehicle event_log;
        event_log.msg_uuid = "12345678";
        event_log.event_class = "VEHICLE_NORMAL";
        event_log.vehicle_id = "MR001";
        event_log.vehicle_status = "Hi";
        event_log.vehicle_location = "UNKNOW";
        event_log.carrier_id = "?";
        event_log.comment = "???";
        mrdsdb->insert_vehicle_event(event_log);

        event_log.comment = "++++";
        mrdsdb->update_vehicle_event(event_log);
    }
    sleep(1);
}