
add_executable ( mdinphi main.cpp
                         table.cpp
                         diner.cpp )

target_link_libraries ( mdinphi signal_handler
                                asio_context )
