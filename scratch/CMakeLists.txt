
add_executable ( dreturn dreturn.cpp )

add_executable ( readbuf readbuf.cpp )
target_link_libraries( readbuf PRIVATE Boost::foreach )

add_executable ( dirent_poc dirent_poc.cpp )

add_executable ( trapped_water trapped_water.cpp )

add_executable ( exmult exmult.cpp )
target_compile_features( exmult PRIVATE cxx_std_20 )

add_executable ( smallest_common smallest_common.cpp )

add_executable ( move_zeroes move_zeroes.cpp )
target_compile_features( move_zeroes PRIVATE cxx_std_20 )
