cmake_minimum_required(VERSION 3.10)
project(libmrdsdb)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
add_compile_options(-Werror=deprecated-declarations)

find_package(Boost COMPONENTS system filesystem date_time thread log REQUIRED)
add_definitions(-DBOOST_LOG_DYN_LINK)

find_package(Qt5 COMPONENTS Core Sql REQUIRED)
set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

include_directories(
        include
        ${Qt5Core_INCLUDE_DIRS}
        ${Qt5Sql_INCLUDE_DIRS}
)

link_directories(
        ${Qt5Sql_LIBRARIES}
)

add_library(mrdsdb SHARED
        src/connector.cpp
        src/mrdsdb_base.cpp
        src/class_reference.cpp
        src/object_mgmt.cpp
        src/transfer.cpp
        src/vehicle_status.cpp
        src/object_port_status.cpp
        src/parking.cpp
        src/event_log.cpp
        src/magic.cpp
        )

target_link_libraries(mrdsdb
        ${Boost_LIBRARIES}
        ${Qt5Sql_LIBRARIES}
        crypto
        boost_log_setup
        )

add_executable(test_connector test/test_connector.cpp)
target_link_libraries(test_connector
        mrdsdb
        )

add_executable(test_mrdsdb_base test/test_mrdsdb_base.cpp)
target_link_libraries(test_mrdsdb_base
        mrdsdb
        )

add_executable(test_class_reference test/test_class_reference.cpp)
target_link_libraries(test_class_reference
        mrdsdb
        )

add_executable(test_magic test/test_magic.cpp)
target_link_libraries(test_magic
        mrdsdb
        )

add_executable(test_object_mgmt test/test_object_mgmt.cpp)
target_link_libraries(test_object_mgmt
        mrdsdb
        )

add_executable(test_transfer test/test_transfer.cpp)
target_link_libraries(test_transfer
        mrdsdb
        )

add_executable(test_event_log test/test_event_log.cpp)
target_link_libraries(test_event_log
        mrdsdb
        )

add_executable(test_parking test/test_parking.cpp)
target_link_libraries(test_parking
        mrdsdb
        )

add_executable(test_vehicle_status test/test_vehicle_status.cpp)
target_link_libraries(test_vehicle_status
        mrdsdb
        )

add_executable(test_object_port_status test/test_object_port_status.cpp)
target_link_libraries(test_object_port_status
        mrdsdb
        )