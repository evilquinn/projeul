
add_executable ( sudoku_test sudoku_test.cpp )

target_link_libraries ( sudoku_test GTest::gmock_main sudoku )
