
add_library(ansi_escapes STATIC escapes.cpp )
target_include_directories(ansi_escapes INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

add_executable( ansi_demo ansi_demo.cpp )
target_link_libraries( ansi_demo ansi_escapes )
