
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-error")

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

add_executable( cfire cfire.cpp )
target_link_libraries( cfire ncurses )
