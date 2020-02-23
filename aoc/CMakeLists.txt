
set ( PROJEUL_AOC_PATH PROJEUL_AOC_PATH="${CMAKE_CURRENT_BINARY_DIR}" )

add_custom_target(01_input
    COMMAND ${CMAKE_COMMAND} -E copy
            ${CMAKE_CURRENT_SOURCE_DIR}/01_input.txt
            ${CMAKE_CURRENT_BINARY_DIR}/01_input.txt
    BYPRODUCTS ${CMAKE_CURRENT_BINARY_DIR}/01_input.txt)
add_executable ( 01_1 01_1.cpp )
add_dependencies ( 01_1 01_input )

add_executable ( 01_2 01_2.cpp )
add_dependencies ( 01_2 01_input )

add_executable ( 02_1 02_1.cpp )
add_executable ( 02_2 02_2.cpp )

add_executable ( 03_1 03_1.cpp )
add_executable ( 03_2 03_2.cpp )

add_executable ( 04_1 04_1.cpp )
add_executable ( 04_2 04_2.cpp )

add_executable ( 05_1 05_1.cpp )

add_custom_target(06_input
    COMMAND ${CMAKE_COMMAND} -E copy
            ${CMAKE_CURRENT_SOURCE_DIR}/06_input.txt
            ${CMAKE_CURRENT_BINARY_DIR}/06_input.txt
    BYPRODUCTS ${CMAKE_CURRENT_BINARY_DIR}/06_input.txt)
add_executable ( 06_1 06_1.cpp )
add_dependencies ( 06_1 06_input )
target_compile_definitions( 06_1 PUBLIC ${PROJEUL_AOC_PATH} )

add_executable ( 06_2 06_2.cpp )
add_dependencies ( 06_2 06_input )
target_compile_definitions( 06_2 PUBLIC ${PROJEUL_AOC_PATH} )

add_executable ( 07_1 07_1.cpp )
add_executable ( 07_2 07_2.cpp )
