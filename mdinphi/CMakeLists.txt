
add_executable ( mdinphi main.cpp
                         table.cpp
                         diner.cpp )

target_link_libraries ( mdinphi signal_handler
                                asio_context )

option(ASIO_TRACE "Enables the boost::asio trace output" OFF)
if ( ${ASIO_TRACE} )
    target_compile_definitions ( mdinphi
        PUBLIC "BOOST_ASIO_ENABLE_HANDLER_TRACKING" )
endif()
