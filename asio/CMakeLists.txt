
add_library ( asio_context STATIC asio_context.cpp )

target_link_libraries ( asio_context PUBLIC boost_system
                                            pthread )
target_compile_definitions ( asio_context PUBLIC _GNU_SOURCE )

target_include_directories(asio_context PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
