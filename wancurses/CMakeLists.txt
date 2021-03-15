
add_executable( wancurses main.cpp )
target_link_libraries( wancurses ncurses
                                 boost_thread
                                 pthread )

add_executable( window_border window_border.cpp )
target_link_libraries( window_border ncurses )
