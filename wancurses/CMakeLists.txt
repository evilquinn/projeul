
add_compile_options(-Wno-error)

add_executable( wancurses main.cpp )
target_link_libraries( wancurses ncurses
                                 Boost::asio )
target_compile_definitions ( wancurses PUBLIC _GNU_SOURCE )


add_executable( window_border window_border.cpp )
target_link_libraries( window_border ncurses )


add_executable( example example.cpp )
target_link_libraries( example ncurses )

add_executable( cfire cfire.cpp )
target_link_libraries( cfire ncurses )
