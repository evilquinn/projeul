
add_compile_definitions(PROJEUL_AOC_PATH="${CMAKE_CURRENT_SOURCE_DIR}")

add_executable ( aoc_2024_01_1 01_1.cpp )
add_executable ( aoc_2024_02_1 02_1.cpp )
target_link_libraries(aoc_2024_02_1 PRIVATE boost)
add_executable ( aoc_2024_03_1 03_1.cpp )
target_link_libraries(aoc_2024_03_1 PRIVATE boost)
add_executable ( aoc_2024_04_1 04_1.cpp )
add_executable ( aoc_2024_05_1 05_1.cpp )
target_link_libraries(aoc_2024_05_1 PRIVATE boost)
add_executable ( aoc_2024_06_1 06_1.cpp )
