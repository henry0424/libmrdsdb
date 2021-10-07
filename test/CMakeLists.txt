cmake_minimum_required(VERSION 3.10)
project(test_libmrdsdb)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
add_compile_options(-Werror=deprecated-declarations)

find_package(Boost COMPONENTS system filesystem date_time thread log REQUIRED)
add_definitions(-DBOOST_LOG_DYN_LINK)

find_package(Qt5 COMPONENTS Core Sql REQUIRED)
set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

add_executable(test_connector ./test_connector.cpp)
target_link_libraries(test_connector
        mrdsdb
        )

add_executable(test_mrdsdb_base ./test_mrdsdb_base.cpp)
target_link_libraries(test_mrdsdb_base
        mrdsdb
        )

add_executable(test_class_reference ./test_class_reference.cpp)
target_link_libraries(test_class_reference
        mrdsdb
        )

add_executable(test_magic ./test_magic.cpp)
target_link_libraries(test_magic
        mrdsdb
        )

add_executable(test_object_mgmt ./test_object_mgmt.cpp)
target_link_libraries(test_object_mgmt
        mrdsdb
        )

add_executable(test_transfer ./test_transfer.cpp)
target_link_libraries(test_transfer
        mrdsdb
        )

add_executable(test_event_log ./test_event_log.cpp)
target_link_libraries(test_event_log
        mrdsdb
        )

add_executable(test_parking ./test_parking.cpp)
target_link_libraries(test_parking
        mrdsdb
        )

add_executable(test_vehicle_status ./test_vehicle_status.cpp)
target_link_libraries(test_vehicle_status
        mrdsdb
        )

add_executable(test_object_port_status ./test_object_port_status.cpp)
target_link_libraries(test_object_port_status
        mrdsdb
        )