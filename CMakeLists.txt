cmake_minimum_required(VERSION 2.8)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall")
include_directories($ENV{BOOST_ROOT})
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
add_subdirectory(prime_sieve)
add_executable(projeul main.cpp
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
                       pe42.cpp)

target_link_libraries(projeul prime_sieve)

add_subdirectory(test)
