
add_library(utils STATIC utils.cpp
                         gint.cpp
                         bint.cpp
                         crypto.cpp)

target_link_libraries ( utils number_lists
                              crypto
                              ssl )

target_include_directories(utils PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
