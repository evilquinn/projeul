cmake_minimum_required(VERSION 2.8)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall")

set(CMAKE_CXX_FLAGS_DEBUG
    "${CMAKE_CXX_FLAGS} -O0 -g3 -pg -ftest-coverage -fprofile-arcs")

include_directories($ENV{BOOST_ROOT})
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(number_lists)
include_directories(poker)
include_directories(utils)
add_subdirectory(number_lists)
add_subdirectory(poker)
add_subdirectory(utils)
add_executable(projeul main.cpp
                       pe61.cpp
                       pe27.cpp
                       pe29.cpp
                       pe30.cpp
                       pe31.cpp
                       pe32.cpp
                       pe33.cpp
                       pe34.cpp
                       pe35.cpp
                       pe36.cpp
                       pe37.cpp
                       pe38.cpp
                       pe39.cpp
                       pe40.cpp
                       pe41.cpp
                       pe42.cpp
                       pe43.cpp
                       pe44.cpp
                       pe45.cpp
                       pe46.cpp
                       pe47.cpp
                       pe48.cpp
                       pe49.cpp
                       pe50.cpp
                       pe51.cpp
                       pe52.cpp
                       pe53.cpp
                       pe54.cpp
                       pe55.cpp
                       pe56.cpp
                       pe57.cpp
                       pe58.cpp
                       pe59.cpp
                       pe60.cpp)


target_link_libraries(projeul utils
                              number_lists
                              poker)

add_subdirectory(test)
add_subdirectory(profile)
