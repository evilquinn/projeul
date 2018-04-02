
add_library(poker STATIC card.cpp
                         poker.cpp)

target_link_libraries(poker PUBLIC boost)

target_include_directories(poker PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
