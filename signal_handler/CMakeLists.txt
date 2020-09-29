
add_library(signal_handler STATIC signal_handler.cpp)

target_link_libraries ( signal_handler PUBLIC dl
                                              boost_system )
target_compile_definitions ( signal_handler PUBLIC _GNU_SOURCE )

target_include_directories(signal_handler PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
