
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

    std::vector<std::string> cid_list = {"YYDS001", "YYDS002", "YYDS003", "YYDS004"};
    std::string mcid = "YYDS1234-MMDS1234";

    if (1) {
        auto mrdsdb = std::make_shared<MRDS::Transfer>();
        mrdsdb->connect(sql_host);
        for (auto cid: cid_list) {
            mrdsdb->delete_transfer_processing(cid);
        }
        mrdsdb->delete_transfer_processing(mcid);
        usleep(1);
    }
    if (1) {
        auto mrdsdb = std::make_shared<MRDS::Transfer>();
        mrdsdb->connect(sql_host);
        for (auto cid: cid_list) {
            Database::SQL::MRDS::DB_SCHEMA::transfer_processing tp;
            tp.base_.command_id = cid;
            tp.base_.dest_port = "(x0,y0)";
            mrdsdb->insert_transfer_processing(tp);
        }
        usleep(1);

    }
    if (1) {
        auto mrdsdb = std::make_shared<MRDS::Transfer>();
        mrdsdb->connect(sql_host);
        mrdsdb->set_merged_command_id(cid_list, mcid);
        usleep(1);
    }
    if (1) {
        auto mrdsdb = std::make_shared<MRDS::Transfer>();
        mrdsdb->connect(sql_host);
        auto all_list_ = mrdsdb->get_transfer_processing();
        auto one_list = mrdsdb->get_transfer_processing(cid_list.at(0));
        auto merged_list = mrdsdb->get_transfer_processing(mcid);
        usleep(1);
    }
    if (1) {
        auto mrdsdb = std::make_shared<MRDS::Transfer>();
        mrdsdb->connect(sql_host);
        mrdsdb->set_vehicle_id(mcid, "MR001");
        auto vehilce = mrdsdb->get_vehicle_id(mcid);
        usleep(1);
    }
    if (1) {
        auto mrdsdb = std::make_shared<MRDS::Transfer>();
        mrdsdb->connect(sql_host);
        mrdsdb->set_transfer_state(mcid, "DONE");
    }
    if (1) {
        auto mrdsdb = std::make_shared<MRDS::Transfer>();
        mrdsdb->connect(sql_host);
        for (int i = 0; i < 20; ++i) {
            mrdsdb->set_comment(mcid, std::to_string(i));
        }
    }
    if (1) {
        auto mrdsdb = std::make_shared<MRDS::Transfer>();
        mrdsdb->connect(sql_host);
        mrdsdb->set_magic(mcid, "M1");
        mrdsdb->set_magic(mcid, "M2");
    }

    sleep(1);
}