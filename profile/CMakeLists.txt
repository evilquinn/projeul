include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_executable(profile_triangles triangle_numbers_profile.cpp)
target_link_libraries(profile_triangles number_lists
                                        gmock_main)

add_executable(profile_calc_prime_factors calc_prime_factors_profile.cpp
                                          ../exercises/pe47.cpp)
target_link_libraries(profile_calc_prime_factors PRIVATE utils
                                                 number_lists
                                                 gmock_main Boost::foreach)
