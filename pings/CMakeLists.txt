
add_executable ( sig2png main.cpp )

target_link_libraries( sig2png PRIVATE Boost::lexical_cast png )
