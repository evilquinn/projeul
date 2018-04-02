
include ( googlemock.cmake )

option(BUILD_BOOST "Downloads and builds required boost libraries" OFF)

if ( ${BUILD_BOOST} )
    include ( boost.cmake )
endif()
