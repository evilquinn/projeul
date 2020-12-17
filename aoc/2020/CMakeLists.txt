
add_compile_definitions(PROJEUL_AOC_PATH="${CMAKE_CURRENT_SOURCE_DIR}")
link_libraries(boost)
add_executable ( 2020_01_1 01_1.cpp )

add_executable ( 2020_02_1 02_1.cpp )
target_link_libraries ( 2020_02_1 boost_regex )

add_executable ( 2020_03_1 03_1.cpp )
target_link_libraries ( 2020_03_1 map )

add_executable ( 2020_04_1 04_1.cpp )

add_executable ( 2020_05_1 05_1.cpp )
target_link_libraries ( 2020_05_1 coord )

add_executable ( 2020_06_1 06_1.cpp )

add_executable ( 2020_07_1 07_1.cpp )
target_link_libraries ( 2020_07_1 boost_regex )

add_executable ( 2020_08_1 08_1.cpp )

add_executable ( 2020_09_1 09_1.cpp )

add_executable ( 2020_10_1 10_1.cpp )

add_executable ( 2020_11_1 11_1.cpp )
target_link_libraries ( 2020_11_1 coord )

add_executable ( 2020_12_1 12_1.cpp )
target_link_libraries ( 2020_12_1 coord )

add_executable ( 2020_13_1 13_1.cpp )

add_executable ( 2020_14_1 14_1.cpp )
target_link_libraries ( 2020_14_1 boost_regex )
