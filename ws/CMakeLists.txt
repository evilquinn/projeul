
add_executable (ws main.cpp)
target_link_libraries (ws websocketpp
                          pthread)
