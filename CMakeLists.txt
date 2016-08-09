cmake_minimum_required(VERSION 2.8)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall")
include_directories($ENV{BOOST_ROOT})
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(number_lists)
include_directories(poker)
add_subdirectory(number_lists)
add_subdirectory(poker)
add_executable(projeul main.cpp
                       utils.cpp
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
                       pe54.cpp)

target_link_libraries(projeul number_lists)

add_subdirectory(test)
add_subdirectory(profile)
