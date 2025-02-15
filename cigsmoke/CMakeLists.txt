
add_executable ( cigsmoke main.cpp
                          table.cpp
                          smoker.cpp
                          agent.cpp )

target_link_libraries ( cigsmoke PUBLIC signal_handler
                                        asio_context Boost::random)
