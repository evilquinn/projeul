include_directories($ENV{GMOCK_ROOT}/include
                    $ENV{GTEST_ROOT}/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_executable(test_projeul ../utils.cpp
                            prime_sieve_test.cpp
                            poker_test.cpp
                            card_test.cpp
                            triangle_numbers_test.cpp
                            pentagonal_numbers_test.cpp
                            hexagonal_numbers_test.cpp
                            known_primes.cpp
                            utils_test.cpp)

add_subdirectory($ENV{GMOCK_ROOT}
                 ${CMAKE_BINARY_DIR}/gmock)

target_link_libraries(test_projeul poker
                                   number_lists
                                   gmock_main)

