
add_executable ( messenger main.cpp )

target_link_libraries ( messenger asio_context
                                  signal_handler )
