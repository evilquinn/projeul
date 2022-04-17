
add_library(ansi_escapes INTERFACE IMPORTED GLOBAL)
target_include_directories(ansi_escapes INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

add_executable( ansi_demo ansi_demo.cpp )
