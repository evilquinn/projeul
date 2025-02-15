
if(NOT ${BUILD_BOOST})
    return()
endif()

message("<boost>")
set(BOOST_ENABLE_CMAKE ON)
set(BOOST_INCLUDE_LIBRARIES filesystem system date_time regex program_options lexical_cast algorithm
                            multiprecision asio thread foreach format spirit property_tree stacktrace)

FetchContent_Declare(
    boost
    GIT_REPOSITORY https://github.com/boostorg/boost
    GIT_TAG        da041154c6bac1a4aa98254a7d6819059e8ac0b0
    OVERRIDE_FIND_PACKAGE
)

FetchContent_MakeAvailable(boost)

message("</boost>")