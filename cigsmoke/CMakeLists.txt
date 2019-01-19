
add_executable ( cigsmoke main.cpp
                          table.cpp
                          smoker.cpp )

target_link_libraries ( cigsmoke PUBLIC signal_handler
                                        asio_context )
