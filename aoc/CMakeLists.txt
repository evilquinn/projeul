
add_library(computer computer.cpp)
target_link_libraries ( computer PUBLIC boost )

add_library(coord coord.cpp)
target_link_libraries ( coord PUBLIC boost )

add_library(map map.cpp)
target_link_libraries ( map PUBLIC coord
                                   boost )

add_subdirectory(2019)
add_subdirectory(2020)

add_subdirectory(2022)
