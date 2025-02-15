add_executable ( oathstuff main.cpp )
target_link_libraries ( oathstuff PRIVATE Boost::regex Boost::algorithm oath )
