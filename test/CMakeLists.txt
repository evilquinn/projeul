include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_executable(test_projeul main.cpp
                            prime_sieve_test.cpp
                            poker_test.cpp
                            card_test.cpp
                            polygonal_numbers_test.cpp
                            triangle_numbers_test.cpp
                            pentagonal_numbers_test.cpp
                            hexagonal_numbers_test.cpp
                            known_primes.cpp
                            utils_test.cpp
                            gint_test.cpp
                            bint_test.cpp
                            crypto_test.cpp
                            signal_handler_test.cpp
                            continued_fraction_test.cpp
                            unique_cptr_test.cpp)

target_link_libraries(test_projeul poker
                                   utils
                                   number_lists
                                   asio_context
                                   signal_handler
                                   gmock
                                   exercises)

if( ${ENABLE_COVERAGE} )
    target_link_libraries(test_projeul gcov)
endif()

add_test(NAME test_projeul
         COMMAND test_projeul)
