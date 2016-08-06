include_directories($ENV{GMOCK_ROOT}/include $ENV{GTEST_ROOT}/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_executable(profile_triangles triangle_numbers_profile.cpp)
target_link_libraries(profile_triangles number_lists
                                        gmock_main)

add_executable(profile_calc_prime_factors calc_prime_factors_profile.cpp
                                          ../utils.cpp
                                          ../pe47.cpp)
target_link_libraries(profile_calc_prime_factors number_lists
                                                 gmock_main)
