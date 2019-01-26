
add_library ( sudoku square.cpp
                     grid.cpp
                     grid_reader.cpp
                     solver.cpp
                     util.cpp )

add_executable ( solver main.cpp )

target_link_libraries ( solver sudoku
                               signal_handler )

add_subdirectory ( test )
