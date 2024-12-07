
add_library(computer computer.cpp)
target_link_libraries ( computer PUBLIC boost )

add_library(map map.cpp)
target_link_libraries ( map PUBLIC boost )

add_subdirectory(2019)
add_subdirectory(2020)

add_subdirectory(2022)
add_subdirectory(2023)
add_subdirectory(2024)
