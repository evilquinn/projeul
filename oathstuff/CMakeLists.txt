add_executable ( oathstuff main.cpp )
target_link_libraries ( oathstuff ansi_escapes
                                  boost_regex
                                  oath
                                  pthread )
