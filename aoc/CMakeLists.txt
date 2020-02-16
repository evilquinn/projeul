
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
