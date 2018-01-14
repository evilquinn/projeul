
add_library(poker STATIC card.cpp
                         poker.cpp)

target_include_directories(poker PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
