//
// Created by henry on 2021-09-06.
//

#include "transfer.h"

using namespace Database::SQL::MRDS;

Transfer::Transfer(const DATABASE_NAME db) : MRDSDB(db) {
    LogTool::_log("Transfer *****", LOGOUT_CLASS, boost::log::trivial::trace);
}

auto
Transfer::get_transfer_list(const std::string &cmcid) -> std::optional<std::vector<DB_SCHEMA::transfer_processing>> {
    LogTool::_log("get_transfer_list", LOGOUT_CLASS, boost::log::trivial::trace);
    auto where = [=]() -> std::string {
        if (cmcid.empty())
            return ";";
        else {
            auto queryCmd = boost::str(
                    boost::format(
                            "WHERE %1%.%2%.%3%.command_id LIKE '%%%4%%%' OR %1%.%2%.%3%.merged_command_id LIKE '%%%4%%%';") %
                    this->connector_->get_database_host().database %
                    this->SCHEMA %
                    this->TABLE_TRANSFER_PROCESSING %
                    cmcid);
            return queryCmd;
        }
    };

    auto queryCmd = boost::str(
            boost::format("SELECT %1%.%2%.%3%.receive_ts, "
                          "%1%.%2%.%3%.command_id, "
                          "%1%.%2%.%3%.source_port, "
                          "%1%.%2%.%3%.dest_port, "
                          "%1%.%2%.%3%.priority, "
                          "%1%.%2%.%3%.operator_id, "
                          "%1%.%2%.%3%.carrier_id, "
                          "%1%.%2%.%4%.merged_command_id, "
                          "%1%.%2%.%4%.vehicle_id, "
                          "%1%.%2%.%4%.transfer_state, "
                          "%1%.%2%.%4%.comment, "
                          "%1%.%2%.%4%.magic "
                          "FROM %1%.%2%.%3% "
                          "FULL OUTER JOIN  %1%.%2%.%4% ON %1%.%2%.%4%.command_id = %1%.%2%.%3%.command_id "
                          "%5%") %
            this->connector_->get_database_host().database %
            this->SCHEMA %
            this->TABLE_TRANSFER %
            this->TABLE_TRANSFER_PROCESSING %
            where());
    LogTool::_log("query cmd: " + queryCmd, LOGOUT_CLASS, boost::log::trivial::trace);
    auto query = this->connector_->exec(queryCmd);

    auto querySize{0};
    std::vector<DB_SCHEMA::transfer_processing> list_;
    list_.clear();
    while (query->next()) {
        auto loc{0};
        DB_SCHEMA::transfer_base transfer_base_;
        DB_SCHEMA::transfer_processing transfer_processing_;
        {
            transfer_base_.receive_ts = query->value(loc++).toString().toStdString();
            transfer_base_.command_id = query->value(loc++).toString().toStdString();
            transfer_base_.source_port = query->value(loc++).toString().toStdString();
            transfer_base_.dest_port = query->value(loc++).toString().toStdString();
            transfer_base_.priority = query->value(loc++).toInt();
            transfer_base_.operator_id = query->value(loc++).toString().toStdString();
            transfer_base_.carrier_id = query->value(loc++).toString().toStdString();
        }
        transfer_processing_.base = transfer_base_;
        transfer_processing_.merged_command_id = query->value(loc++).toString().toStdString();
        transfer_processing_.vehicle_id = query->value(loc++).toString().toStdString();
        transfer_processing_.transfer_state = query->value(loc++).toString().toStdString();
        transfer_processing_.comment = query->value(loc++).toString().toStdString();
        transfer_processing_.magic = query->value(loc++).toString().toStdString();
        list_.push_back(transfer_processing_);
        if (LOGOUT_QUERY_RESULT) {
            LogTool::_log("receive_ts: " + transfer_processing_.base.receive_ts, LOGOUT_CLASS,
                          boost::log::trivial::trace);
            LogTool::_log("command_id: " + transfer_processing_.base.command_id, LOGOUT_CLASS,
                          boost::log::trivial::trace);
            LogTool::_log("source_port: " + transfer_processing_.base.source_port, LOGOUT_CLASS,
                          boost::log::trivial::trace);
            LogTool::_log("dest_port: " + transfer_processing_.base.dest_port, LOGOUT_CLASS,
                          boost::log::trivial::trace);
            LogTool::_log("priority: " + transfer_processing_.base.priority, LOGOUT_CLASS,
                          boost::log::trivial::trace);
            LogTool::_log("operator_id: " + transfer_processing_.base.operator_id, LOGOUT_CLASS,
                          boost::log::trivial::trace);
            LogTool::_log("carrier_id: " + transfer_processing_.base.carrier_id, LOGOUT_CLASS,
                          boost::log::trivial::trace);
            LogTool::_log("merged_command_id: " + transfer_processing_.merged_command_id, LOGOUT_CLASS,
                          boost::log::trivial::trace);
            LogTool::_log("vehicle_id: " + transfer_processing_.vehicle_id, LOGOUT_CLASS,
                          boost::log::trivial::trace);
            LogTool::_log("transfer_state: " + transfer_processing_.transfer_state, LOGOUT_CLASS,
                          boost::log::trivial::trace);
            LogTool::_log("comment: " + transfer_processing_.comment, LOGOUT_CLASS, boost::log::trivial::trace);
            LogTool::_log("magic: " + transfer_processing_.magic, LOGOUT_CLASS, boost::log::trivial::trace);
            LogTool::_log("--------------------------------------------------------------------------------",
                          LOGOUT_CLASS, boost::log::trivial::trace);
        }
        querySize++;
    }
    if (querySize <= 0 && (NO_DATA_EXCEPTION_ALL || NO_DATA_EXCEPTION))
        throw Database::Exception::NoDataException();

    return querySize ? std::optional<std::reference_wrapper<std::vector<DB_SCHEMA::transfer_processing>>>{list_}
                     : std::nullopt;
}

auto Transfer::get_transfer(const std::string &command_id) -> std::optional<DB_SCHEMA::transfer_processing> {
    LogTool::_log("get_transfer", LOGOUT_CLASS, boost::log::trivial::trace);
    auto queryCmd = boost::str(
            boost::format("SELECT %1%.%2%.%3%.receive_ts "
                          "%1%.%2%.%3%.command_id "
                          "%1%.%2%.%3%.source_port "
                          "%1%.%2%.%3%.dest_port "
                          "%1%.%2%.%3%.priority "
                          "%1%.%2%.%3%.operator_id "
                          "%1%.%2%.%3%.carrier_id "
                          "%1%.%2%.%4%.merged_command_id "
                          "%1%.%2%.%4%.vehicle_id "
                          "%1%.%2%.%4%.transfer_state "
                          "%1%.%2%.%4%.comment "
                          "%1%.%2%.%4%.magic "
                          "FROM %1%.%2%.%3% "
                          "FULL OUTER JOIN  %1%.%2%.%4% ON %1%.%2%.%4%.command_id = %1%.%2%.%3%.command_id "
                          "WHERE %1%.%2%.%3%.command_id=%5%;") %
            this->connector_->get_database_host().database %
            this->SCHEMA %
            this->TABLE_TRANSFER %
            this->TABLE_TRANSFER_PROCESSING %
            null_(command_id));

    LogTool::_log("query cmd: " + queryCmd, LOGOUT_CLASS, boost::log::trivial::trace);
    auto query = this->connector_->exec(queryCmd);

    auto querySize{0};
    std::vector<DB_SCHEMA::transfer_processing> list_;
    list_.clear();
    while (query->next()) {
        auto loc{0};
        DB_SCHEMA::transfer_base transfer_base_;
        DB_SCHEMA::transfer_processing transfer_processing_;
        {
            transfer_base_.receive_ts = query->value(loc++).toString().toStdString();
            transfer_base_.command_id = query->value(loc++).toString().toStdString();
            transfer_base_.source_port = query->value(loc++).toString().toStdString();
            transfer_base_.dest_port = query->value(loc++).toString().toStdString();
            transfer_base_.priority = query->value(loc++).toInt();
            transfer_base_.operator_id = query->value(loc++).toString().toStdString();
            transfer_base_.carrier_id = query->value(loc++).toString().toStdString();
        }
        transfer_processing_.base = transfer_base_;
        transfer_processing_.merged_command_id = query->value(loc++).toString().toStdString();
        transfer_processing_.vehicle_id = query->value(loc++).toString().toStdString();
        transfer_processing_.transfer_state = query->value(loc++).toString().toStdString();
        transfer_processing_.comment = query->value(loc++).toString().toStdString();
        transfer_processing_.magic = query->value(loc++).toString().toStdString();
        list_.push_back(transfer_processing_);
        if (LOGOUT_QUERY_RESULT) {
            LogTool::_log("receive_ts: " + transfer_processing_.base.receive_ts, LOGOUT_CLASS,
                          boost::log::trivial::trace);
            LogTool::_log("command_id: " + transfer_processing_.base.command_id, LOGOUT_CLASS,
                          boost::log::trivial::trace);
            LogTool::_log("source_port: " + transfer_processing_.base.source_port, LOGOUT_CLASS,
                          boost::log::trivial::trace);
            LogTool::_log("dest_port: " + transfer_processing_.base.dest_port, LOGOUT_CLASS,
                          boost::log::trivial::trace);
            LogTool::_log("priority: " + transfer_processing_.base.priority, LOGOUT_CLASS,
                          boost::log::trivial::trace);
            LogTool::_log("operator_id: " + transfer_processing_.base.operator_id, LOGOUT_CLASS,
                          boost::log::trivial::trace);
            LogTool::_log("carrier_id: " + transfer_processing_.base.carrier_id, LOGOUT_CLASS,
                          boost::log::trivial::trace);
            LogTool::_log("merged_command_id: " + transfer_processing_.merged_command_id, LOGOUT_CLASS,
                          boost::log::trivial::trace);
            LogTool::_log("vehicle_id: " + transfer_processing_.vehicle_id, LOGOUT_CLASS,
                          boost::log::trivial::trace);
            LogTool::_log("transfer_state: " + transfer_processing_.transfer_state, LOGOUT_CLASS,
                          boost::log::trivial::trace);
            LogTool::_log("comment: " + transfer_processing_.comment, LOGOUT_CLASS, boost::log::trivial::trace);
            LogTool::_log("magic: " + transfer_processing_.magic, LOGOUT_CLASS, boost::log::trivial::trace);
            LogTool::_log("--------------------------------------------------------------------------------",
                          LOGOUT_CLASS, boost::log::trivial::trace);
        }
        querySize++;
    }
    if (querySize <= 0 && (NO_DATA_EXCEPTION_ALL || NO_DATA_EXCEPTION))
        throw Database::Exception::NoDataException();

    return querySize ? std::optional<std::reference_wrapper<DB_SCHEMA::transfer_processing>>{list_.at(0)}
                     : std::nullopt;
}

void Transfer::insert_transfer(const DB_SCHEMA::transfer_base transfer_base) {
    LogTool::_log("insert_transfer", LOGOUT_CLASS, boost::log::trivial::trace);
    auto queryCmd = boost::str(
            boost::format("SELECT %1%.%2%.%3%.command_id "
                          "FROM %1%.%2%.%3% "
                          "WHERE %1%.%2%.%3%.command_id=%5%;") %
            this->connector_->get_database_host().database %
            this->SCHEMA %
            this->TABLE_TRANSFER %
            this->TABLE_TRANSFER_PROCESSING %
            null_(transfer_base.command_id));

    LogTool::_log("query cmd: " + queryCmd, LOGOUT_CLASS, boost::log::trivial::trace);
    auto query = this->connector_->exec(queryCmd);
    if (!query->next()) {
        auto queryCmd = boost::str(
                boost::format("INSERT INTO %1%.%2%.%3% "
                              "(receive_ts, command_id, source_port, dest_port, priority, operator_id, carrier_id) "
                              "VALUES (DEFAULT, %5%, %6%, %7%, %8%, %9%, %10%);") %
                this->connector_->get_database_host().database %
                this->SCHEMA %
                this->TABLE_TRANSFER %
                this->TABLE_TRANSFER_PROCESSING %
                null_(transfer_base.command_id) %
                null_(transfer_base.source_port) %
                null_(transfer_base.dest_port) %
                transfer_base.priority %
                default_(transfer_base.operator_id) %
                null_(transfer_base.carrier_id));
        LogTool::_log("query cmd: " + queryCmd, LOGOUT_CLASS, boost::log::trivial::trace);
        auto query = this->connector_->exec(queryCmd);
    } else {
        this->update_transfer(transfer_base);
    }
}

void Transfer::update_transfer(const DB_SCHEMA::transfer_base transfer_base) {
    LogTool::_log("update_transfer", LOGOUT_CLASS, boost::log::trivial::trace);
    auto queryCmd = boost::str(
            boost::format("SELECT %1%.%2%.%3%.command_id "
                          "FROM %1%.%2%.%3% "
                          "WHERE %1%.%2%.%3%.command_id=%5%;") %
            this->connector_->get_database_host().database %
            this->SCHEMA %
            this->TABLE_TRANSFER %
            this->TABLE_TRANSFER_PROCESSING %
            null_(transfer_base.command_id));

    LogTool::_log("query cmd: " + queryCmd, LOGOUT_CLASS, boost::log::trivial::trace);
    auto query = this->connector_->exec(queryCmd);
    if (query->next()) {
        auto queryCmd = boost::str(
                boost::format("UPDATE %1%.%2%.%3% "
                              "SET source_port=%6%, dest_port=%7%, priority=%8%, operator_id=%9%, carrier_id=%10% "
                              "WHERE command_id=%5%;") %
                this->connector_->get_database_host().database %
                this->SCHEMA %
                this->TABLE_TRANSFER %
                this->TABLE_TRANSFER_PROCESSING %
                null_(transfer_base.command_id) %
                null_(transfer_base.source_port) %
                null_(transfer_base.dest_port) %
                transfer_base.priority %
                default_(transfer_base.operator_id) %
                null_(transfer_base.carrier_id));
        LogTool::_log("query cmd: " + queryCmd, LOGOUT_CLASS, boost::log::trivial::trace);
        auto query = this->connector_->exec(queryCmd);
    } else {
        this->insert_transfer(transfer_base);
    }
}

void Transfer::insert_transfer_task(const DB_SCHEMA::transfer_base transfer_base) {
    LogTool::_log("insert_transfer_task", LOGOUT_CLASS, boost::log::trivial::trace);
    auto queryCmd = boost::str(
            boost::format("SELECT %1%.%2%.%3%.command_id "
                          "FROM %1%.%2%.%3% "
                          "WHERE %1%.%2%.%3%.command_id=%5%;") %
            this->connector_->get_database_host().database %
            this->SCHEMA %
            this->TABLE_TRANSFER %
            this->TABLE_TRANSFER_PROCESSING %
            null_(transfer_base.command_id));
    LogTool::_log("query cmd: " + queryCmd, LOGOUT_CLASS, boost::log::trivial::trace);
    auto query = this->connector_->exec(queryCmd);
    if (!query->next()) {
        this->insert_transfer(transfer_base);
        {
            auto querycm = boost::str(boost::format());
            auto querycmd_table_transfer_processing = boost::str(
                    boost::format("INSERT INTO %1%.%2%.%4% "
                                  "(command_id, transfer_state) "
                                  "VALUES (%5%, DEFAULT);") %
                    this->connector_->get_database_host().database %
                    this->SCHEMA %
                    this->TABLE_TRANSFER %
                    this->TABLE_TRANSFER_PROCESSING %
                    null_(transfer_base.command_id));

            auto querycmd_table_transfer_timestamp = boost::str(
                    boost::format("INSERT INTO %1%.%2%.%4% "
                                  "(command_id) "
                                  "VALUES (%5%);") %
                    this->connector_->get_database_host().database %
                    this->SCHEMA %
                    this->TABLE_TRANSFER %
                    this->TABLE_TRANSFER_TIMESTAMP %
                    null_(transfer_base.command_id));

            queryCmd = querycmd_table_transfer_processing + " " +
                       querycmd_table_transfer_timestamp;
            LogTool::_log("query cmd: " + queryCmd, LOGOUT_CLASS, boost::log::trivial::trace);
            auto query = this->connector_->exec(queryCmd);
        }
    }
}

void Transfer::update_transfer_processing(const DB_SCHEMA::transfer_processing transfer_processing) {
    LogTool::_log("update_transfer_processing", LOGOUT_CLASS, boost::log::trivial::trace);
    auto queryCmd = boost::str(
            boost::format("UPDATE %1%.%2%.%4% "
                          "SET merged_command_id=%5%, vehicle_id=%6%, transfer_state=%7%, comment=%8%, magic=%9% "
                          "WHERE command_id=%10%;") %
            this->connector_->get_database_host().database %
            this->SCHEMA %
            this->TABLE_TRANSFER %
            this->TABLE_TRANSFER_PROCESSING %
            null_(transfer_processing.merged_command_id) %
            null_(transfer_processing.vehicle_id) %
            default_(transfer_processing.transfer_state) %
            null_(transfer_processing.comment) %
            null_(transfer_processing.magic) %
            null_(transfer_processing.base.command_id));
    LogTool::_log("query cmd: " + queryCmd, LOGOUT_CLASS, boost::log::trivial::trace);
    auto query = this->connector_->exec(queryCmd);
}

void Transfer::set_transfer_timestamp(const std::string &cmcid, const Transfer::TS_ATTRIBUTE attribute,
                                      const std::string &ts) {
    LogTool::_log("set_transfer_timestamp", LOGOUT_CLASS, boost::log::trivial::trace);

    auto ts_attribute = [=]() -> std::string {
        switch (attribute) {
            case Transfer::TS_ATTRIBUTE::update_ts:
                return "update_ts";
            case Transfer::TS_ATTRIBUTE::merged_ts:
                return "merged_ts";
            case Transfer::TS_ATTRIBUTE::assigned_ts:
                return "assigned_ts";
            case Transfer::TS_ATTRIBUTE::delivery_start_ts:
                return "delivery_start_ts";
            case Transfer::TS_ATTRIBUTE::delivery_stop_ts:
                return "delivery_stop_ts";
        }
    };

    auto ts_ = ts;
    if (ts_.empty())
        ts_ = this->get_datetime(DT_SOURCE::SYSTEM);

    auto ts_setter = [=]() -> std::string {
        if (attribute == Transfer::TS_ATTRIBUTE::update_ts)
            return "";
        else
            return ", " + ts_attribute() + "=" + null_(ts_);
    };

    auto queryCmd = boost::str(
            boost::format("UPDATE %1%.%2%.%3% "
                          "SET update_ts=%5%%6% "
                          "WHERE command_id IN (SELECT command_id "
                          "FROM %1%.%2%.%4% "
                          "WHERE %1%.%2%.%4%.command_id LIKE '%%%7%%%' OR %1%.%2%.%4%.merged_command_id LIKE '%%%7%%%');") %
            this->connector_->get_database_host().database %
            this->SCHEMA %
            this->TABLE_TRANSFER_TIMESTAMP %
            this->TABLE_TRANSFER_PROCESSING %
            default_(ts_) %
            ts_setter() %
            cmcid);
    LogTool::_log("query cmd: " + queryCmd, LOGOUT_CLASS, boost::log::trivial::trace);
    auto query = this->connector_->exec(queryCmd);
}

void Transfer::set_merged_command_id(const std::vector<std::string> command_id, const std::string &merged_command_id) {
    LogTool::_log("set_merged_command_id", LOGOUT_CLASS, boost::log::trivial::trace);
    auto where = [=]() -> std::string {
        auto where_query = boost::str(boost::format());
        for (auto cmd: command_id) {
            where_query += boost::str(
                    boost::format(
                            "%1%") %
                    null_(cmd));
            if (cmd != command_id.back())
                where_query += ", ";
        }
        return where_query;
    };

    auto queryCmd = boost::str(
            boost::format("UPDATE %1%.%2%.%3% "
                          "SET merged_command_id=%4% "
                          "WHERE command_id IN (%5%);") %
            this->connector_->get_database_host().database %
            this->SCHEMA %
            this->TABLE_TRANSFER_PROCESSING %
            null_(merged_command_id) %
            where());
    LogTool::_log("query cmd: " + queryCmd, LOGOUT_CLASS, boost::log::trivial::trace);
    auto query = this->connector_->exec(queryCmd);
    this->set_transfer_timestamp(merged_command_id, TS_ATTRIBUTE::merged_ts);
}

std::string Transfer::get_vehicle_id(const std::string &cmcid) {
    LogTool::_log("get_vehicle_id", LOGOUT_CLASS, boost::log::trivial::trace);
    auto queryCmd = boost::str(
            boost::format("SELECT vehicle_id "
                          "FROM %1%.%2%.%3% "
                          "WHERE transfer_processing.command_id LIKE '%%%4%%%' OR transfer_processing.merged_command_id LIKE '%%%4%%%';") %
            this->connector_->get_database_host().database %
            this->SCHEMA %
            this->TABLE_TRANSFER_PROCESSING %
            cmcid);
    LogTool::_log("query cmd: " + queryCmd, LOGOUT_CLASS, boost::log::trivial::trace);
    auto query = this->connector_->exec(queryCmd);

    auto querySize{0};
    std::vector<std::string> list_;
    list_.clear();
    while (query->next()) {
        auto loc{0};
        auto vehicle_id = query->value(loc++).toString().toStdString();
        list_.push_back(vehicle_id);
        if (LOGOUT_QUERY_RESULT) {
            LogTool::_log("vehicle_id: " + vehicle_id, LOGOUT_CLASS, boost::log::trivial::trace);
        }
        querySize++;
    }
    if (querySize <= 0 && (NO_DATA_EXCEPTION_ALL || NO_DATA_EXCEPTION))
        throw Database::Exception::NoDataException();

    return list_.at(0);
}

void Transfer::set_vehicle_id(const std::string &cmcid, const std::string &vehicle_id) {
    LogTool::_log("set_merged_command_id", LOGOUT_CLASS, boost::log::trivial::trace);
    auto queryCmd = boost::str(
            boost::format("UPDATE %1%.%2%.%3% "
                          "SET vehicle_id=%4% "
                          "WHERE %1%.%2%.%3%.command_id LIKE '%%%5%%%' OR %1%.%2%.%3%.merged_command_id LIKE '%%%5%%%';") %
            this->connector_->get_database_host().database %
            this->SCHEMA %
            this->TABLE_TRANSFER_PROCESSING %
            null_(vehicle_id) %
            cmcid);
    LogTool::_log("query cmd: " + queryCmd, LOGOUT_CLASS, boost::log::trivial::trace);
    auto query = this->connector_->exec(queryCmd);
    this->set_transfer_timestamp(cmcid, TS_ATTRIBUTE::assigned_ts);
}

void Transfer::set_transfer_state(const std::string &cmcid, const std::string &transfer_state) {
    LogTool::_log("set_transfer_state", LOGOUT_CLASS, boost::log::trivial::trace);
    auto queryCmd = boost::str(
            boost::format("UPDATE %1%.%2%.%3% "
                          "SET transfer_state=%4% "
                          "WHERE %1%.%2%.%3%.command_id LIKE '%%%5%%%' OR %1%.%2%.%3%.merged_command_id LIKE '%%%5%%%';") %
            this->connector_->get_database_host().database %
            this->SCHEMA %
            this->TABLE_TRANSFER_PROCESSING %
            null_(transfer_state) %
            cmcid);
    LogTool::_log("query cmd: " + queryCmd, LOGOUT_CLASS, boost::log::trivial::trace);
    auto query = this->connector_->exec(queryCmd);
    this->set_transfer_timestamp(cmcid, TS_ATTRIBUTE::update_ts);
}

void Transfer::set_comment(const std::string &cmcid, const std::string &comment) {
    LogTool::_log("set_comment", LOGOUT_CLASS, boost::log::trivial::trace);
    auto queryCmd = boost::str(
            boost::format("UPDATE %1%.%2%.%3% "
                          "SET comment=%4% "
                          "WHERE %1%.%2%.%3%.command_id LIKE '%%%5%%%' OR %1%.%2%.%3%.merged_command_id LIKE '%%%5%%%';") %
            this->connector_->get_database_host().database %
            this->SCHEMA %
            this->TABLE_TRANSFER_PROCESSING %
            null_(comment) %
            cmcid);
    LogTool::_log("query cmd: " + queryCmd, LOGOUT_CLASS, boost::log::trivial::trace);
    auto query = this->connector_->exec(queryCmd);
    this->set_transfer_timestamp(cmcid, TS_ATTRIBUTE::update_ts);
}

void Transfer::set_magic(const std::string &cmcid, const std::string &magic) {
    LogTool::_log("set_magic", LOGOUT_CLASS, boost::log::trivial::trace);
    auto queryCmd = boost::str(
            boost::format("UPDATE %1%.%2%.%3% "
                          "SET magic=%4% "
                          "WHERE %1%.%2%.%3%.command_id LIKE '%%%5%%%' OR %1%.%2%.%3%.merged_command_id LIKE '%%%5%%%';") %
            this->connector_->get_database_host().database %
            this->SCHEMA %
            this->TABLE_TRANSFER_PROCESSING %
            null_(magic) %
            cmcid);
    LogTool::_log("query cmd: " + queryCmd, LOGOUT_CLASS, boost::log::trivial::trace);
    auto query = this->connector_->exec(queryCmd);
    this->set_transfer_timestamp(cmcid, TS_ATTRIBUTE::update_ts);
}
