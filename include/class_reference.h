//
// Created by henry on 2021-09-04.
//

#ifndef LIBMRDSDB_CLASS_REFERENCE_H
#define LIBMRDSDB_CLASS_REFERENCE_H

#include "mrdsdb_base.h"

#define NO_DATA_EXCEPTION true

namespace Database::SQL::MRDS {

    class ClassReference : public MRDSDB {

    private:
        const std::string SCHEMA{"class_reference"};

    public:

        struct CarrierClass {
            std::string carrier_class;
        };

        struct EquipmentClass {
            std::string equipment_class;
        };

        struct EventClass {
            std::string event_class;
        };

        std::vector<CarrierClass> get_carrier_class_list();

        std::vector<EquipmentClass> get_equipment_class_list();

        std::vector<EventClass> get_event_class_list();

    };

}

#endif //LIBMRDSDB_CLASS_REFERENCE_H
