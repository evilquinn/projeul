cmake_minimum_required(VERSION 2.8)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS} -O0 -g3")

option(ENABLE_COVERAGE "Enable code coverage metrics for debug builds" OFF)
if ( ${ENABLE_COVERAGE} )
    set(CMAKE_CXX_FLAGS_DEBUG
        "${CMAKE_CXX_FLAGS_DEBUG} -ftest-coverage -fprofile-arcs -pg")
endif()

option(BUILD_BOOST "Downloads and builds required boost libraries" OFF)

message("CMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}")
message("BUILD_BOOST=${BUILD_BOOST}")
message("ENABLE_COVERAGE=${ENABLE_COVERAGE}")

add_subdirectory(third_party)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
add_subdirectory(number_lists)
add_subdirectory(poker)
add_subdirectory(utils)
add_subdirectory(signal_handler)
add_subdirectory(asio)
add_subdirectory(messenger)
add_subdirectory(exercises)


add_executable(projeul main.cpp)

target_link_libraries(projeul signal_handler
                              boost_program_options
                              exercises)

enable_testing()
add_subdirectory(test)
add_subdirectory(profile)
