
set ( PROJEUL_AOC_PATH PROJEUL_AOC_PATH="${CMAKE_CURRENT_SOURCE_DIR}" )

add_library(computer computer.cpp)
target_link_libraries ( computer PUBLIC boost )

add_library(coord coord.cpp)
target_link_libraries ( coord PUBLIC boost )

add_library(map map.cpp)
target_link_libraries ( map PUBLIC coord
                                   boost )

add_executable ( 01_1 01_1.cpp )

add_executable ( 01_2 01_2.cpp )
target_compile_definitions( 01_2 PUBLIC ${PROJEUL_AOC_PATH} )

add_executable ( 02_1 02_1.cpp )
target_link_libraries ( 02_1 PUBLIC boost )
add_executable ( 02_2 02_2.cpp )
target_link_libraries ( 02_2 PUBLIC boost )

add_executable ( 03_1 03_1.cpp )
target_link_libraries ( 03_1 PUBLIC boost )
add_executable ( 03_2 03_2.cpp )
target_link_libraries ( 03_2 PUBLIC boost )

add_executable ( 04_1 04_1.cpp )
add_executable ( 04_2 04_2.cpp )

add_executable ( 05_1 05_1.cpp )
target_link_libraries ( 05_1 PUBLIC boost )

add_executable ( 06_1 06_1.cpp )
target_compile_definitions( 06_1 PUBLIC ${PROJEUL_AOC_PATH} )
target_link_libraries( 06_1 PUBLIC boost )

add_executable ( 06_2 06_2.cpp )
target_compile_definitions( 06_2 PUBLIC ${PROJEUL_AOC_PATH} )
target_link_libraries( 06_2 PUBLIC boost )

add_executable ( 07_1 07_1.cpp )
target_link_libraries ( 07_1 PUBLIC boost )
add_executable ( 07_2 07_2.cpp )
target_link_libraries( 07_2 computer )

add_executable ( 08_1 08_1.cpp )
target_compile_definitions( 08_1 PUBLIC ${PROJEUL_AOC_PATH} )

add_executable ( 08_2 08_2.cpp )
target_compile_definitions( 08_2 PUBLIC ${PROJEUL_AOC_PATH} )

add_executable ( 09_1 09_1.cpp )
target_compile_definitions( 09_1 PUBLIC ${PROJEUL_AOC_PATH} )
target_link_libraries( 09_1 computer )

add_executable ( 10_1 10_1.cpp )
target_link_libraries( 10_1 boost
                            coord
                            map )

add_executable ( 11_1 11_1.cpp )
target_link_libraries( 11_1 boost
                            computer
                            coord )

add_executable ( 12_1 12_1.cpp )
target_link_libraries( 12_1 boost )

add_executable ( 13_1 13_1.cpp )
target_link_libraries( 13_1 boost
                            computer
                            coord )

add_executable ( 14_1 14_1.cpp )
target_link_libraries( 14_1 boost )

add_executable ( 14_2 14_2.cpp )
target_link_libraries( 14_2 boost )
