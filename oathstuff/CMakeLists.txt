add_executable ( otps main.cpp config.cpp key_data.cpp display.cpp )
target_link_libraries ( otps ansi_escapes
                             boost_regex
                             oath
                             pthread
                             stdc++fs )
