
add_library(computer computer.cpp)
target_link_libraries ( computer PUBLIC Boost::algorithm Boost::lexical_cast)

add_library(map map.cpp)

add_subdirectory(2019)
add_subdirectory(2020)

add_subdirectory(2022)
add_subdirectory(2023)
add_subdirectory(2024)
