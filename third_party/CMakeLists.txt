
include(ExternalProject)

if ( ${BUILD_TESTS} )
    add_subdirectory(googletest)
endif()
add_subdirectory(boost)
add_subdirectory(fmt)
add_subdirectory(websocketpp)
