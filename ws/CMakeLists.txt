
add_executable (ws main.cpp)
target_link_libraries (ws websocketpp
                          pthread
                          boost_system
                          boost_thread)
