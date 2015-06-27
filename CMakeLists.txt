set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
include_directories($ENV{BOOST_ROOT})
add_executable(projeul main.cpp
                       prime_sieve.cpp
                       pe27.cpp
                       pe29.cpp
                       pe30.cpp
                       pe31.cpp)
