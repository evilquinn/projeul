
option(BUILD_BOOST "Downloads and builds required boost libraries" OFF)
if ( ${BUILD_BOOST} )

include( ExternalProject )

set( URL
  "https://dl.bintray.com/boostorg/release/1.66.0/source/boost_1_66_0.tar.bz2" )
set( SHA256 "5721818253e6a0989583192f96782c4a98eb6204965316df9f5ad75819225ca9" )
set( INSTALL_DIR ${CMAKE_CURRENT_BINARY_DIR}/boost )
set( INCLUDE_DIR ${INSTALL_DIR}/include )
set( LIB_DIR ${INSTALL_DIR}/lib )

ExternalProject_Add( external_boost
        PREFIX boost
        URL ${URL}
        URL_HASH SHA256=${SHA256}
        BUILD_IN_SOURCE 1
        CONFIGURE_COMMAND ./bootstrap.sh
            --with-libraries=filesystem
            --with-libraries=system
            --with-libraries=date_time
            --with-libraries=program_options
            --prefix=<INSTALL_DIR>
        BUILD_COMMAND
        ./b2 -d0 link=static variant=release threading=multi runtime-link=static
        INSTALL_COMMAND ./b2 -d0 install
        INSTALL_DIR ${INSTALL_DIR} )

file(MAKE_DIRECTORY ${INCLUDE_DIR})

add_library(boost INTERFACE IMPORTED GLOBAL)
add_dependencies(boost external_boost)
set_target_properties(boost PROPERTIES
                      INTERFACE_INCLUDE_DIRECTORIES ${INCLUDE_DIR}
                      INTERFACE_SYSTEM_INCLUDE_DIRECTORIES ${INCLUDE_DIR})

set( LIB_SUFFIX .a )

add_library( boost_date_time STATIC IMPORTED GLOBAL)
set_target_properties( boost_date_time PROPERTIES
    IMPORTED_LOCATION ${LIB_DIR}/libboost_date_time${LIB_SUFFIX} )
target_link_libraries( boost_date_time INTERFACE boost )

add_library( boost_system STATIC IMPORTED GLOBAL)
set_target_properties( boost_system PROPERTIES
    IMPORTED_LOCATION ${LIB_DIR}/libboost_system${LIB_SUFFIX} )
target_link_libraries( boost_system INTERFACE boost )

add_library( boost_file_system STATIC IMPORTED GLOBAL)
set_target_properties( boost_file_system PROPERTIES
    IMPORTED_LOCATION ${LIB_DIR}/libboost_file_system${LIB_SUFFIX} )
target_link_libraries( boost_file_system INTERFACE boost )

add_library( boost_program_options STATIC IMPORTED GLOBAL)
set_target_properties( boost_program_options PROPERTIES
    IMPORTED_LOCATION ${LIB_DIR}/libboost_program_options${LIB_SUFFIX} )
target_link_libraries( boost_program_options INTERFACE boost )

else()

# dummy target to link against when we didn't build boost ourselves
add_library(boost INTERFACE IMPORTED GLOBAL)

endif()
