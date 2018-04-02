
add_library(utils STATIC utils.cpp
                         gint.cpp
                         bint.cpp
                         crypto.cpp)

target_link_libraries ( utils PUBLIC number_lists
                                     crypto
                                     ssl )

if( ${BUILD_BOOST} )
    target_link_libraries(utils PUBLIC boost)
endif()

target_include_directories(utils PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
