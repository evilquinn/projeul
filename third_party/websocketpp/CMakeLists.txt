
include( ExternalProject )

set( URL
  "https://github.com/zaphoyd/websocketpp/archive/0.8.2.tar.gz" )
set( SHA256 "6ce889d85ecdc2d8fa07408d6787e7352510750daa66b5ad44aacb47bea76755" )
set( INSTALL_DIR ${CMAKE_CURRENT_BINARY_DIR} )
set( INCLUDE_DIR_SOURCE ${INSTALL_DIR}/websocketpp_dl-prefix/src/websocketpp_dl/websocketpp )
set( INCLUDE_DIR ${INSTALL_DIR}/install )

ExternalProject_Add(websocketpp_dl
        URL ${URL}
        URL_HASH SHA256=${SHA256}
        CONFIGURE_COMMAND ""
        BUILD_COMMAND ""
        INSTALL_COMMAND cp -r ${INCLUDE_DIR_SOURCE} ${INCLUDE_DIR}/. )

file(MAKE_DIRECTORY ${INCLUDE_DIR})

add_library(websocketpp INTERFACE)
add_dependencies(websocketpp websocketpp_dl)
set_target_properties(websocketpp PROPERTIES
                      INTERFACE_INCLUDE_DIRECTORIES ${INCLUDE_DIR}
                      INTERFACE_SYSTEM_INCLUDE_DIRECTORIES ${INCLUDE_DIR} )
