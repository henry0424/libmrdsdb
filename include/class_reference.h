//
// Created by henry on 2021-09-04.
//

#ifndef LIBMRDSDB_CLASS_REFERENCE_H
#define LIBMRDSDB_CLASS_REFERENCE_H

#include "mrdsdb_base.h"

#define NO_DATA_EXCEPTION true

namespace Database::SQL::MRDS {

    namespace DB_SCHEMA {
        struct carrier_class {
            std::string carrier_class;
        };

        struct equipment_class {
            std::string equipment_class;
        };

        struct event_class {
            std::string event_class;
        };
    }

    class ClassReference : public MRDSDB {

    protected:
        const std::string SCHEMA{"class_reference"};

    public:

        std::vector<DB_SCHEMA::carrier_class> get_carrier_class_list();

        std::vector<DB_SCHEMA::equipment_class> get_equipment_class_list();

        std::vector<DB_SCHEMA::event_class> get_event_class_list();

    };

}

#endif //LIBMRDSDB_CLASS_REFERENCE_H
