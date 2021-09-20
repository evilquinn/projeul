
add_executable( wancurses main.cpp )
target_link_libraries( wancurses ncurses
                                 boost_system
                                 boost_thread
                                 pthread )
target_compile_definitions ( wancurses PUBLIC _GNU_SOURCE )


add_executable( window_border window_border.cpp )
target_link_libraries( window_border ncurses )


add_executable( example example.cpp )
target_link_libraries( example ncurses )
