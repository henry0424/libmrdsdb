
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
        auto mrdsdb = std::make_shared<MRDS::Transfer>();
        mrdsdb->connect(sql_host);
        auto list_ = mrdsdb->get_transfer_list();
        list_ = mrdsdb->get_transfer_list("YY");
//        auto trasnfer = mrdsdb->get_transfer(list_.at(0).base.command_id);
    }
    if (0) {
        auto mrdsdb = std::make_shared<MRDS::Transfer>();
        mrdsdb->connect(sql_host);

        for (int i = 0; i < 5; ++i) {
            MRDS::DB_SCHEMA::transfer_processing tp;
            tp.base.command_id = std::to_string(i);
            tp.base.dest_port = "NA";
            mrdsdb->insert_transfer_task(tp.base);
        }
    }
    if (0) {
        auto mrdsdb = std::make_shared<MRDS::Transfer>();
        mrdsdb->connect(sql_host);
        auto tp_list = mrdsdb->get_transfer_list();
        tp_list.at(0).merged_command_id = "MC1";
        mrdsdb->update_transfer_processing(tp_list.at(0));
    }
    if (0) {
        auto mrdsdb = std::make_shared<MRDS::Transfer>();
        mrdsdb->connect(sql_host);
        mrdsdb->set_transfer_timestamp("vg", MRDS::Transfer::TS_ATTRIBUTE::merged_ts);
    }
    if (1) {
        auto mrdsdb = std::make_shared<MRDS::Transfer>();
        mrdsdb->connect(sql_host);
        auto list = mrdsdb->get_transfer_list();
        std::vector<std::string> all;
        all.clear();
        for (auto tp: list) {
            all.push_back(tp.base.command_id);
        }
        mrdsdb->set_merged_command_id(all, "YYY");
    }
    if (1) {
        auto mrdsdb = std::make_shared<MRDS::Transfer>();
        mrdsdb->connect(sql_host);

        mrdsdb->set_vehicle_id("YYY", "MR002");
    }
    if (1) {
        auto mrdsdb = std::make_shared<MRDS::Transfer>();
        mrdsdb->connect(sql_host);
        mrdsdb->set_comment("YYY", "C1");
        mrdsdb->set_comment("vg", "C2");
    }
    if (1) {
        auto mrdsdb = std::make_shared<MRDS::Transfer>();
        mrdsdb->connect(sql_host);
        mrdsdb->set_magic("YYY", "M1");
        mrdsdb->set_magic("vg", "M2");
    }

    sleep(1);
}