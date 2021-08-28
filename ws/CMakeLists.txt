
add_executable (ws main.cpp)
target_link_libraries (ws websocketpp
                          pthread
                          boost_system
                          boost_thread)

target_compile_definitions ( ws PUBLIC _GNU_SOURCE )
