
add_executable ( sudoku main.cpp
                        square.cpp
                        grid.cpp
                        grid_reader.cpp
                        solver.cpp
                        util.cpp )

target_link_libraries ( sudoku signal_handler )
