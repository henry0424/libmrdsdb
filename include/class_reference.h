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
        std::vector<DB_SCHEMA::carrier_class> get_carrier_class_list();

        std::vector<DB_SCHEMA::equipment_class> get_equipment_class_list();

        std::vector<DB_SCHEMA::event_class> get_event_class_list();

    };

}

#endif //LIBMRDSDB_CLASS_REFERENCE_H
