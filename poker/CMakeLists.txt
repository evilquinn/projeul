
add_library(poker STATIC card.cpp
                         poker.cpp)

if( ${BUILD_BOOST} )
    target_link_libraries(poker PUBLIC Boost::foreach Boost::tokenizer)
endif()

target_include_directories(poker PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
