
add_executable ( rlpoc rlpoc.cpp )
target_link_libraries ( rlpoc readline
                              ncurses
                              pthread )
