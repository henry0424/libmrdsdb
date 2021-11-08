//
// Created by henry on 2021-09-06.
//

#include "transfer.h"

using namespace Database::SQL::MRDS;

Transfer::Transfer(const DATABASE_NAME db) : MRDSDB(db) {
    LogTool::_log("Transfer *****", LOGOUT_CLASS, boost::log::trivial::trace);
}

auto Transfer::get_transfer_processing(
        const std::string &keyword) -> std::optional<std::vector<DB_SCHEMA::transfer_processing>> {
    LogTool::_log("get_transfer_processing", LOGOUT_CLASS, boost::log::trivial::trace);

    auto queryCmd = boost::str(
            boost::format("SELECT %1%.%2%.%3%.serial_num, "
                          "%1%.%2%.%3%.receive_ts, "
                          "%1%.%2%.%3%.command_id, "
                          "%1%.%2%.%3%.source_port, "
                          "%1%.%2%.%3%.dest_port, "
                          "%1%.%2%.%3%.priority, "
                          "%1%.%2%.%3%.operator_id, "
                          "%1%.%2%.%3%.carrier_id, "
                          "%1%.%2%.%3%.merged_command_id, "
                          "%1%.%2%.%3%.vehicle_id, "
                          "%1%.%2%.%3%.transfer_state, "
                          "%1%.%2%.%3%.comment, "
                          "%1%.%2%.%3%.magic, "
                          "%1%.%2%.%3%.update_ts, "
                          "%1%.%2%.%3%.merged_ts, "
                          "%1%.%2%.%3%.assigned_ts, "
                          "%1%.%2%.%3%.delivery_start_ts, "
                          "%1%.%2%.%3%.delivery_stop_ts "
                          "FROM %1%.%2%.%3% "
                          "%4%") %
            this->connector_->get_database_host().database %
            this->SCHEMA %
            this->TABLE_TRANSFER_PROCESSING %
            fuzzy_query_(this->connector_->get_database_host().database, this->SCHEMA, this->TABLE_TRANSFER_PROCESSING,
                         keyword,
                         {"command_id", "source_port", "dest_port", "carrier_id", "merged_command_id", "vehicle_id",
                          "transfer_state", "magic"}));
    LogTool::_log("query cmd: " + queryCmd, LOGOUT_CLASS, boost::log::trivial::trace);
    auto query = this->connector_->exec(queryCmd);

    auto querySize{0};
    std::vector<DB_SCHEMA::transfer_processing> list_;
    list_.clear();
    while (query->next()) {
        auto loc{0};
        DB_SCHEMA::transfer_processing transfer_processing_;
        {
            {
                transfer_processing_.base_.serial_num = query->value(loc++).toInt();
                transfer_processing_.base_.receive_ts = query->value(loc++).toString().toStdString();
                transfer_processing_.base_.command_id = query->value(loc++).toString().toStdString();
                transfer_processing_.base_.source_port = query->value(loc++).toString().toStdString();
                transfer_processing_.base_.dest_port = query->value(loc++).toString().toStdString();
                transfer_processing_.base_.priority = query->value(loc++).toInt();
                transfer_processing_.base_.operator_id = query->value(loc++).toString().toStdString();
                transfer_processing_.base_.carrier_id = query->value(loc++).toString().toStdString();
            }
            transfer_processing_.merged_command_id = query->value(loc++).toString().toStdString();
            transfer_processing_.vehicle_id = query->value(loc++).toString().toStdString();
            transfer_processing_.transfer_state = query->value(loc++).toString().toStdString();
            transfer_processing_.comment = query->value(loc++).toString().toStdString();
            transfer_processing_.magic = query->value(loc++).toString().toStdString();
            transfer_processing_.update_ts = query->value(loc++).toString().toStdString();
            transfer_processing_.merged_ts = query->value(loc++).toString().toStdString();
            transfer_processing_.assigned_ts = query->value(loc++).toString().toStdString();
            transfer_processing_.delivery_start_ts = query->value(loc++).toString().toStdString();
            transfer_processing_.delivery_stop_ts = query->value(loc++).toString().toStdString();
        }
        list_.push_back(transfer_processing_);
        if (LOGOUT_QUERY_RESULT) {
            LogTool::_log("serial_num: -----> " + std::to_string(transfer_processing_.base_.serial_num), LOGOUT_CLASS,
                          boost::log::trivial::trace);
            {
//                LogTool::_log("serial_num: " + std::to_string(transfer_processing_.base_.serial_num), LOGOUT_CLASS,
//                              boost::log::trivial::trace);
                LogTool::_log("\treceive_ts: " + transfer_processing_.base_.receive_ts, LOGOUT_CLASS,
                              boost::log::trivial::trace);
                LogTool::_log("\tcommand_id: " + transfer_processing_.base_.command_id, LOGOUT_CLASS,
                              boost::log::trivial::trace);
                LogTool::_log("\tsource_port: " + transfer_processing_.base_.source_port, LOGOUT_CLASS,
                              boost::log::trivial::trace);
                LogTool::_log("\tdest_port: " + transfer_processing_.base_.dest_port, LOGOUT_CLASS,
                              boost::log::trivial::trace);
                LogTool::_log("\tpriority: " + std::to_string(transfer_processing_.base_.priority), LOGOUT_CLASS,
                              boost::log::trivial::trace);
                LogTool::_log("\toperator_id: " + transfer_processing_.base_.operator_id, LOGOUT_CLASS,
                              boost::log::trivial::trace);
                LogTool::_log("\tcarrier_id: " + transfer_processing_.base_.carrier_id, LOGOUT_CLASS,
                              boost::log::trivial::trace);
            }
            LogTool::_log("\t\tmerged_command_id: " + transfer_processing_.merged_command_id, LOGOUT_CLASS,
                          boost::log::trivial::trace);
            LogTool::_log("\t\tvehicle_id: " + transfer_processing_.vehicle_id, LOGOUT_CLASS,
                          boost::log::trivial::trace);
            LogTool::_log("\t\ttransfer_state: " + transfer_processing_.transfer_state, LOGOUT_CLASS,
                          boost::log::trivial::trace);
            LogTool::_log("\t\tcomment: " + transfer_processing_.comment, LOGOUT_CLASS,
                          boost::log::trivial::trace);
            LogTool::_log("\t\tmagic: " + transfer_processing_.magic, LOGOUT_CLASS,
                          boost::log::trivial::trace);
            LogTool::_log("\t\tupdate_ts: " + transfer_processing_.update_ts, LOGOUT_CLASS,
                          boost::log::trivial::trace);
            LogTool::_log("\t\tmerged_ts: " + transfer_processing_.merged_ts, LOGOUT_CLASS,
                          boost::log::trivial::trace);
            LogTool::_log("\t\tassigned_ts: " + transfer_processing_.assigned_ts, LOGOUT_CLASS,
                          boost::log::trivial::trace);
            LogTool::_log("\t\tdelivery_start_ts: " + transfer_processing_.delivery_start_ts, LOGOUT_CLASS,
                          boost::log::trivial::trace);
            LogTool::_log("\t\tdelivery_stop_ts: " + transfer_processing_.delivery_stop_ts, LOGOUT_CLASS,
                          boost::log::trivial::trace);
        }
        querySize++;
    }
    if (querySize <= 0 && (NO_DATA_EXCEPTION_ALL || NO_DATA_EXCEPTION))
        throw Database::Exception::NoDataException();

    return querySize ? std::optional<std::reference_wrapper<std::vector<DB_SCHEMA::transfer_processing>>>{list_}
                     : std::nullopt;
}

void Transfer::insert_transfer_processing(const DB_SCHEMA::transfer_base transfer, const bool force_update) {
    DB_SCHEMA::transfer_processing tp;
    tp.base_ = transfer;
    return this->insert_transfer_processing(tp);
}

void Transfer::insert_transfer_processing(const DB_SCHEMA::transfer_processing transfer, const bool force_update) {
    LogTool::_log("insert_transfer_processing", LOGOUT_CLASS, boost::log::trivial::trace);
    auto queryCmd = boost::str(
            boost::format("SELECT %1%.%2%.%3%.command_id "
                          "FROM %1%.%2%.%3% "
                          "WHERE %1%.%2%.%3%.command_id=%4%;") %
            this->connector_->get_database_host().database %
            this->SCHEMA %
            this->TABLE_TRANSFER_PROCESSING %
            null_(transfer.base_.command_id));

    LogTool::_log("query cmd: " + queryCmd, LOGOUT_CLASS, boost::log::trivial::trace);
    auto query = this->connector_->exec(queryCmd);
    if (!query->next()) {
        auto queryCmd = boost::str(
                boost::format("INSERT INTO %1%.%2%.%3% "
                              "(receive_ts, command_id, source_port, dest_port, priority, operator_id, carrier_id) "
                              "VALUES (DEFAULT, %4%, %5%, %6%, %7%, %8%, %9%);") %
                this->connector_->get_database_host().database %
                this->SCHEMA %
                this->TABLE_TRANSFER_PROCESSING %
                null_(transfer.base_.command_id) %
                null_(transfer.base_.source_port) %
                null_(transfer.base_.dest_port) %
                transfer.base_.priority %
                default_(transfer.base_.operator_id) %
                null_(transfer.base_.carrier_id));
        LogTool::_log("query cmd: " + queryCmd, LOGOUT_CLASS, boost::log::trivial::trace);
        auto query = this->connector_->exec(queryCmd);
    } else if (force_update) {
        this->update_transfer_processing(transfer);
    } else if (DUPLICATE_DATA_EXCEPTION) {
        throw Database::Exception::DuplicateDataException();
    }
}

void Transfer::update_transfer_processing(const DB_SCHEMA::transfer_processing transfer, const bool force_insert) {
    LogTool::_log("update_transfer_processing", LOGOUT_CLASS, boost::log::trivial::trace);
    auto queryCmd = boost::str(
            boost::format("SELECT %1%.%2%.%3%.command_id "
                          "FROM %1%.%2%.%3% "
                          "WHERE %1%.%2%.%3%.command_id=%4%;") %
            this->connector_->get_database_host().database %
            this->SCHEMA %
            this->TABLE_TRANSFER_PROCESSING %
            null_(transfer.base_.command_id));

    LogTool::_log("query cmd: " + queryCmd, LOGOUT_CLASS, boost::log::trivial::trace);
    auto query = this->connector_->exec(queryCmd);
    if (!query->next()) {
        auto queryCmd = boost::str(
                boost::format("UPDATE %1%.%2%.%3% \n"
                              "SET source_port=%5%, dest_port=%6%, priority=%7%, operator_id=%8%, carrier_id=%9% \n"
                              "merged_command_id=%10%, transfer_state=%11%, comment=%12%, magic=%13% \n"
                              "update_ts=%14%, merged_ts=%15%, assigned_ts=%16%, delivery_start_ts=%17%, delivery_stop_ts=%18% \n"
                              "WHERE command_id=%4%;") %
                this->connector_->get_database_host().database %
                this->SCHEMA %
                this->TABLE_TRANSFER_PROCESSING %
                null_(transfer.base_.command_id) %
                null_(transfer.base_.source_port) % //---Transfer base
                null_(transfer.base_.dest_port) %
                transfer.base_.priority %
                null_(transfer.base_.operator_id) %
                null_(transfer.base_.carrier_id) %  //---Transfer proc
                null_(transfer.merged_command_id) %
                null_(transfer.transfer_state) %
                null_(transfer.comment) %
                null_(transfer.magic) %
                this->get_datetime(DT_SOURCE::SYSTEM) % //---Transfer datetime
                null_(transfer.merged_ts) %
                null_(transfer.assigned_ts) %
                null_(transfer.delivery_start_ts) %
                null_(transfer.delivery_stop_ts) %
                null_(transfer.merged_ts));
        LogTool::_log("query cmd: " + queryCmd, LOGOUT_CLASS, boost::log::trivial::trace);
        auto query = this->connector_->exec(queryCmd);
    } else if (force_insert) {
        this->insert_transfer_processing(transfer);
    } else if (DUPLICATE_DATA_EXCEPTION) {
        throw Database::Exception::DuplicateDataException();
    }
}

void Transfer::delete_transfer_processing(const std::string &cmcid) {
    LogTool::_log("delete_transfer_processing", LOGOUT_CLASS, boost::log::trivial::trace);

    auto queryCmd = boost::str(
            boost::format("DELETE "
                          "FROM %1%.%2%.%3% "
                          "WHERE %1%.%2%.%3%.command_id=%4% OR %1%.%2%.%3%.merged_command_id=%4%;") %
            this->connector_->get_database_host().database %
            this->SCHEMA %
            this->TABLE_TRANSFER_PROCESSING %
            null_(cmcid));
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
                          "SET update_ts=%4%%5% "
                          "WHERE command_id IN (SELECT command_id "
                          "FROM %1%.%2%.%3% "
                          "WHERE %1%.%2%.%3%.command_id=%6% OR %1%.%2%.%3%.merged_command_id=%6%);") %
            this->connector_->get_database_host().database %
            this->SCHEMA %
            this->TABLE_TRANSFER_PROCESSING %
            default_(ts_) %
            ts_setter() %
            null_(cmcid));
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

auto Transfer::get_vehicle_id(const std::string &cmcid) -> std::optional<std::string> {
    LogTool::_log("get_vehicle_id", LOGOUT_CLASS, boost::log::trivial::trace);
    auto queryCmd = boost::str(
            boost::format("SELECT DISTINCT(vehicle_id) "
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

    if (querySize > 1)
        LogTool::_log("find vehicle id size: [" + std::to_string(querySize) + "] > 1, only return first vehicle id",
                      LOGOUT_CLASS,
                      boost::log::trivial::warning);


    return querySize ? std::optional<std::reference_wrapper<std::string>>{list_.at(0)}
                     : std::nullopt;
}

void Transfer::set_vehicle_id(const std::string &cmcid, const std::string &vehicle_id) {
    LogTool::_log("set_merged_command_id", LOGOUT_CLASS, boost::log::trivial::trace);
    auto queryCmd = boost::str(
            boost::format("UPDATE %1%.%2%.%3% "
                          "SET vehicle_id=%4% "
                          "WHERE %1%.%2%.%3%.command_id=%5% OR %1%.%2%.%3%.merged_command_id=%5%;") %
            this->connector_->get_database_host().database %
            this->SCHEMA %
            this->TABLE_TRANSFER_PROCESSING %
            null_(vehicle_id) %
            null_(cmcid));
    LogTool::_log("query cmd: " + queryCmd, LOGOUT_CLASS, boost::log::trivial::trace);
    auto query = this->connector_->exec(queryCmd);
    this->set_transfer_timestamp(cmcid, TS_ATTRIBUTE::assigned_ts);
}

void Transfer::set_transfer_state(const std::string &cmcid, const std::string &transfer_state) {
    LogTool::_log("set_transfer_state", LOGOUT_CLASS, boost::log::trivial::trace);
    auto queryCmd = boost::str(
            boost::format("UPDATE %1%.%2%.%3% "
                          "SET transfer_state=%4% "
                          "WHERE %1%.%2%.%3%.command_id=%5% OR %1%.%2%.%3%.merged_command_id=%5%;") %
            this->connector_->get_database_host().database %
            this->SCHEMA %
            this->TABLE_TRANSFER_PROCESSING %
            null_(transfer_state) %
            null_(cmcid));
    LogTool::_log("query cmd: " + queryCmd, LOGOUT_CLASS, boost::log::trivial::trace);
    auto query = this->connector_->exec(queryCmd);
    this->set_transfer_timestamp(cmcid, TS_ATTRIBUTE::update_ts);
}

void Transfer::set_comment(const std::string &cmcid, const std::string &comment) {
    LogTool::_log("set_comment", LOGOUT_CLASS, boost::log::trivial::trace);
    auto queryCmd = boost::str(
            boost::format("UPDATE %1%.%2%.%3% "
                          "SET comment=comment || ',' ||%4% "
                          "WHERE %1%.%2%.%3%.command_id=%5% OR %1%.%2%.%3%.merged_command_id=%5%;") %
            this->connector_->get_database_host().database %
            this->SCHEMA %
            this->TABLE_TRANSFER_PROCESSING %
            null_(comment) %
            null_(cmcid));
    LogTool::_log("query cmd: " + queryCmd, LOGOUT_CLASS, boost::log::trivial::trace);
    auto query = this->connector_->exec(queryCmd);
    this->set_transfer_timestamp(cmcid, TS_ATTRIBUTE::update_ts);
}

void Transfer::set_magic(const std::string &cmcid, const std::string &magic) {
    LogTool::_log("set_magic", LOGOUT_CLASS, boost::log::trivial::trace);
    auto queryCmd = boost::str(
            boost::format("UPDATE %1%.%2%.%3% "
                          "SET magic=%4% "
                          "WHERE %1%.%2%.%3%.command_id=%5% OR %1%.%2%.%3%.merged_command_id=%5%;") %
            this->connector_->get_database_host().database %
            this->SCHEMA %
            this->TABLE_TRANSFER_PROCESSING %
            null_(magic) %
            null_(cmcid));
    LogTool::_log("query cmd: " + queryCmd, LOGOUT_CLASS, boost::log::trivial::trace);
    auto query = this->connector_->exec(queryCmd);
    this->set_transfer_timestamp(cmcid, TS_ATTRIBUTE::update_ts);
}
