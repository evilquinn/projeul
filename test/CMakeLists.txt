include_directories($ENV{GMOCK_ROOT}/include $ENV{GTEST_ROOT}/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory($ENV{GMOCK_ROOT} ${CMAKE_BINARY_DIR}/gmock)
add_executable(test_projeul prime_sieve_test.cpp)
target_link_libraries(test_projeul prime_sieve
                                   gmock_main)

