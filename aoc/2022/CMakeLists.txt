
add_compile_definitions(PROJEUL_AOC_PATH="${CMAKE_CURRENT_SOURCE_DIR}")

add_executable ( aoc_2022_01_1 01_1.cpp )

add_executable ( aoc_2022_02_1 02_1.cpp )

add_executable ( aoc_2022_03_1 03_1.cpp )

add_executable ( aoc_2022_04_1 04_1.cpp )

add_executable ( aoc_2022_05_1 05_1.cpp )

add_executable ( aoc_2022_06_1 06_1.cpp )

add_executable ( aoc_2022_07_1 07_1.cpp )

add_executable ( aoc_2022_08_1 08_1.cpp )
target_link_libraries( aoc_2022_08_1 PRIVATE coord)

add_executable ( aoc_2022_09_1 09_1.cpp )
target_link_libraries( aoc_2022_09_1 PRIVATE coord)

add_executable ( aoc_2022_10_1 10_1.cpp )

add_executable ( aoc_2022_11_1 11_1.cpp )

add_executable ( aoc_2022_12_1 12_1.cpp )
target_link_libraries( aoc_2022_12_1 PRIVATE coord)

add_executable ( aoc_2022_13_1 13_1.cpp )
