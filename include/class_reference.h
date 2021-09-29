//
// Created by henry on 2021-09-04.
//

#ifndef LIBMRDSDB_CLASS_REFERENCE_H
#define LIBMRDSDB_CLASS_REFERENCE_H

#include "mrdsdb_base.h"
#include "schema.hpp"

#define NO_DATA_EXCEPTION true
#define LOGOUT_QUERY_RESULT true

namespace Database::SQL::MRDS {

    class ClassReference : public MRDSDB {
    private:
        const std::string LOGOUT_CLASS{"MRDS ClassReference"};

    protected:
        const std::string SCHEMA{"class_reference"};
        const std::string TABLE_CARRIER_CLASS{"carrier_class"};
        const std::string TABLE_EQUIPMENT_CLASS{"equipment_class"};
        const std::string TABLE_EVENT_CLASS{"event_class"};

    public:
        ClassReference(const DATABASE_NAME db = DATABASE_NAME::POSTGRESQL);

        auto get_carrier_class_list() -> std::optional<std::vector<DB_SCHEMA::carrier_class>>;

        auto get_equipment_class_list() -> std::optional<std::vector<DB_SCHEMA::equipment_class>>;

        auto get_event_class_list() -> std::optional<std::vector<DB_SCHEMA::event_class>>;
    };
}

#endif //LIBMRDSDB_CLASS_REFERENCE_H
