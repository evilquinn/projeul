
add_library(boost INTERFACE IMPORTED GLOBAL)

if ( ${BUILD_BOOST} )

include( ExternalProject )

set( URL
  "https://archives.boost.io/release/1.75.0/source/boost_1_75_0.tar.gz" )
set( SHA256 "aeb26f80e80945e82ee93e5939baebdca47b9dee80a07d3144be1e1a6a66dd6a" )
set( INSTALL_DIR ${CMAKE_CURRENT_BINARY_DIR} )
set( INCLUDE_DIR ${INSTALL_DIR}/include )
set( LIB_DIR ${INSTALL_DIR}/lib )

ExternalProject_Add( external_boost
        #PREFIX boost
        URL ${URL}
        URL_HASH SHA256=${SHA256}
        BUILD_IN_SOURCE 1
        CONFIGURE_COMMAND ./bootstrap.sh
            --with-libraries=filesystem
            --with-libraries=system
            --with-libraries=date_time
            --with-libraries=program_options
            --with-libraries=iostreams
            --with-libraries=regex
            --with-libraries=thread
            --prefix=${INSTALL_DIR}
        BUILD_COMMAND
        ./b2 -d0 link=static variant=release threading=multi runtime-link=static
        INSTALL_COMMAND ./b2 -d0 install
        #INSTALL_DIR ${INSTALL_DIR}
        BUILD_BYPRODUCTS ${LIB_DIR}/libboost_program_options.a ${LIB_DIR}/libboost_system.a ${LIB_DIR}/libboost_regex.a)

file(MAKE_DIRECTORY ${INCLUDE_DIR})

add_dependencies(boost external_boost)
set_target_properties(boost PROPERTIES
                      INTERFACE_INCLUDE_DIRECTORIES ${INCLUDE_DIR}
                      INTERFACE_SYSTEM_INCLUDE_DIRECTORIES ${INCLUDE_DIR} )

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

add_library( boost_regex STATIC IMPORTED GLOBAL)
set_target_properties( boost_regex PROPERTIES
    IMPORTED_LOCATION ${LIB_DIR}/libboost_regex${LIB_SUFFIX} )
target_link_libraries( boost_regex INTERFACE boost )

add_library( boost_thread STATIC IMPORTED GLOBAL)
set_target_properties( boost_thread PROPERTIES
    IMPORTED_LOCATION ${LIB_DIR}/libboost_thread${LIB_SUFFIX} )
target_link_libraries( boost_thread INTERFACE boost )

endif()
