
add_compile_definitions(PROJEUL_AOC_PATH="${CMAKE_CURRENT_SOURCE_DIR}")
link_libraries(boost)
add_executable ( 2020_01_1 01_1.cpp )

add_executable ( 2020_02_1 02_1.cpp )
target_link_libraries ( 2020_02_1 boost_regex )
