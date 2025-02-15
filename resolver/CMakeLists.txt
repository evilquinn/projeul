
add_executable ( resolver main.cpp )

target_link_libraries ( resolver PRIVATE Boost::asio )
target_compile_definitions ( resolver PUBLIC _GNU_SOURCE )
