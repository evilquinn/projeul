
add_executable ( dinphi main.cpp )

target_link_libraries ( dinphi signal_handler
                               pthread )
