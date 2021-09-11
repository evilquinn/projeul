
add_library ( sudoku square.cpp
                     grid.cpp
                     grid_reader.cpp
                     solver.cpp
                     util.cpp )

target_link_libraries ( sudoku PUBLIC boost )

add_executable ( solver solver_main.cpp )

target_link_libraries ( solver sudoku
                               signal_handler )
if ( ${BUILD_TESTS} )
add_subdirectory ( test )
endif()


add_executable ( cli cli_main.cpp )

target_link_libraries ( cli sudoku
                            signal_handler
                            pthread
                            asio_user_input )
