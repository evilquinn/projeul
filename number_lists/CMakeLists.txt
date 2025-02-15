
add_library(number_lists STATIC prime_sieve.cpp
                                polygonal_numbers.cpp
                                triangle_numbers.cpp
                                pentagonal_numbers.cpp
                                hexagonal_numbers.cpp
                                pyth_triples.cpp)

target_link_libraries(number_lists PUBLIC utils Boost::dynamic_bitset)

target_include_directories(number_lists PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
