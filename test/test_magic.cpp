
#include <iostream>
#include <memory>
#include <thread>

//#include "../include/connector.h"
#include "../include/mrdsdb.h"

using namespace Database::SQL;

int main(int argc, char **argv) {
    std::cout << "test_magic" << std::endl;
    if (0) {
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

        std::map<std::string, std::string> magic;
        magic["Hello"] = "tryy";
        magic["VERSION_MRDSDB"] = "1.1";

        mrdsdb->set_magic_map(magic);
    }

    if(1) {
        DatabaseHost sql_host;
        sql_host.host = "tachyon.itriroboticslab.org";
        sql_host.port = 5432;
        sql_host.user = "postgres";
        sql_host.passwd = "itriacs";
        sql_host.database = "mrdsdb";
        auto mrdsdb = std::make_shared<MRDS::Magic>();
        mrdsdb->connect(sql_host);
        auto thread_ = [=]() {
//            auto mrdsdb = std::make_shared<MRDS::Magic>();
//            mrdsdb->connect(sql_host);
            auto value = mrdsdb->get_magic_value("VERSION_MRDS");
        };

        std::vector<std::thread> ths;
        for (int i = 0; i < 100; ++i) {
            ths.push_back(std::thread(thread_));
        }
        for (auto &th: ths) {
            th.join();
        }
    }

    sleep(1);
}