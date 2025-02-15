
add_compile_definitions(PROJEUL_AOC_PATH="${CMAKE_CURRENT_SOURCE_DIR}")
link_libraries( Boost::algorithm Boost::lexical_cast Boost::dynamic_bitset)

add_executable ( 01_1 01_1.cpp )

add_executable ( 01_2 01_2.cpp )

add_executable ( 02_1 02_1.cpp )
add_executable ( 02_2 02_2.cpp )

add_executable ( 03_1 03_1.cpp )
add_executable ( 03_2 03_2.cpp )

add_executable ( 04_1 04_1.cpp )
add_executable ( 04_2 04_2.cpp )

add_executable ( 05_1 05_1.cpp )

add_executable ( 06_1 06_1.cpp )

add_executable ( 06_2 06_2.cpp )

add_executable ( 07_1 07_1.cpp )
add_executable ( 07_2 07_2.cpp )
target_link_libraries( 07_2 computer )

add_executable ( 08_1 08_1.cpp )

add_executable ( 08_2 08_2.cpp )

add_executable ( 09_1 09_1.cpp )
target_link_libraries( 09_1 computer )

add_executable ( 10_1 10_1.cpp )
target_link_libraries( 10_1 map )

add_executable ( 11_1 11_1.cpp )
target_link_libraries( 11_1 computer )

add_executable ( 12_1 12_1.cpp )

add_executable ( 13_1 13_1.cpp )
target_link_libraries( 13_1 computer )

add_executable ( 14_1 14_1.cpp )

add_executable ( 14_2 14_2.cpp )

add_executable ( 15_1 15_1.cpp )
target_link_libraries( 15_1 computer )

add_executable ( 16_1 16_1.cpp )

add_executable ( 2019_17_1 17_1.cpp )
target_link_libraries( 2019_17_1 computer )

add_executable ( 2019_18_1 18_1.cpp )
