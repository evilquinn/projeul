
add_executable ( sudoku_test sudoku_test.cpp )

target_link_libraries ( sudoku_test gtest_main sudoku )

add_test ( NAME sudoku_test
           COMMAND sudoku_test )
