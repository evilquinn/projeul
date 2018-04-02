cmake_minimum_required(VERSION 2.8)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall")

set(CMAKE_CXX_FLAGS_DEBUG
    "${CMAKE_CXX_FLAGS} -O0 -g3 -pg -ftest-coverage -fprofile-arcs")

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

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

add_subdirectory(test)
add_subdirectory(profile)
