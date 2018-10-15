
add_library(exercises STATIC pe_register.cpp
                             pe89.cpp
                             pe86.cpp
                             pe85.cpp
                             pe84.cpp
                             pe83.cpp
                             pe82.cpp
                             pe81.cpp
                             pe79.cpp
                             pe78.cpp
                             pe77.cpp
                             pe76.cpp
                             pe75.cpp
                             pe74.cpp
                             pe73.cpp
                             pe72.cpp
                             pe71.cpp
                             pe70.cpp
                             pe69.cpp
                             pe68.cpp
                             pe67.cpp
                             pe66.cpp
                             pe65.cpp
                             pe64.cpp
                             pe63.cpp
                             pe62.cpp
                             pe61.cpp
                             pe27.cpp
                             pe29.cpp
                             pe30.cpp
                             pe31.cpp
                             pe32.cpp
                             pe33.cpp
                             pe34.cpp
                             pe35.cpp
                             pe36.cpp
                             pe37.cpp
                             pe38.cpp
                             pe39.cpp
                             pe40.cpp
                             pe41.cpp
                             pe42.cpp
                             pe43.cpp
                             pe44.cpp
                             pe45.cpp
                             pe46.cpp
                             pe47.cpp
                             pe48.cpp
                             pe49.cpp
                             pe50.cpp
                             pe51.cpp
                             pe52.cpp
                             pe53.cpp
                             pe54.cpp
                             pe55.cpp
                             pe56.cpp
                             pe57.cpp
                             pe58.cpp
                             pe59.cpp
                             pe60.cpp)

target_link_libraries ( exercises PUBLIC utils
                                         number_lists
                                         poker )

target_include_directories( exercises PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
