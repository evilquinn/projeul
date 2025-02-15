
add_executable (ws main.cpp)
target_link_libraries (ws websocketpp
                          pthread
                          Boost::asio Boost::thread)

target_compile_definitions ( ws PUBLIC _GNU_SOURCE )
