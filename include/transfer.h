//
// Created by henry on 2021-09-06.
//

#ifndef LIBMRDSDB_TRANSFER_H
#define LIBMRDSDB_TRANSFER_H

#include "mrdsdb_base.h"

#define NO_DATA_EXCEPTION true
#define LOGOUT_QUERY_RESULT true

namespace Database::SQL::MRDS {

    namespace DB_SCHEMA {
        struct transfer_base {
            std::string receive_ts;
            std::string command_id;
            std::string source_port;
            std::string dest_port;
            int priority = 0;
            std::string operator_id = "MRDS_SYSTEM";
            std::string carrier_id;
        };

        struct transfer_processing {
            DB_SCHEMA::transfer_base base;
            std::string merged_command_id;
            std::string vehicle_id;
            std::string transfer_state;
            std::string comment;
            std::string magic;
        };
    }

    class Transfer : public MRDSDB {
    public:
        enum TS_ATTRIBUTE {
            update_ts,
            merged_ts,
            assigned_ts,
            delivery_start_ts,
            delivery_stop_ts
        };

    protected:
        const std::string SCHEMA{"production"};
        const std::string TABLE_TRANSFER{"transfer"};
        const std::string TABLE_TRANSFER_PROCESSING{"transfer_processing"};
        const std::string TABLE_TRANSFER_TIMESTAMP{"transfer_timestamp"};

        /* cmcid -> Command And Merged Command.*/
    public:
        std::vector<DB_SCHEMA::transfer_processing>
        get_transfer_list(const std::string &cmcid = std::string());

        DB_SCHEMA::transfer_processing get_transfer(const std::string &command_id);

        void insert_transfer(const DB_SCHEMA::transfer_base transfer_base);

        void update_transfer(const DB_SCHEMA::transfer_base transfer_base);

        void insert_transfer_task(const DB_SCHEMA::transfer_base transfer_base);

        void update_transfer_processing(const DB_SCHEMA::transfer_processing transfer_processing);

        void set_transfer_timestamp(const std::string &cmcid, const Transfer::TS_ATTRIBUTE attribute,
                                    const std::string &ts = std::string());

        void set_merged_command_id(const std::vector<std::string> command_id, const std::string &merged_command_id);

        std::string get_vehicle_id(const std::string &cmcid);

        void set_vehicle_id(const std::string &cmcid, const std::string &vehicle_id);

        void set_transfer_state(const std::string &cmcid, const std::string &transfer_state);

        void set_comment(const std::string &cmcid, const std::string &comment);

        void set_magic(const std::string &cmcid, const std::string &magic);
    };

}

#endif //LIBMRDSDB_TRANSFER_H
