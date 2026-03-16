
if(NOT ${BUILD_BOOST})
    return()
endif()

message("<boost>")
set(BOOST_ENABLE_CMAKE ON)
set(BOOST_INCLUDE_LIBRARIES filesystem system date_time regex program_options lexical_cast algorithm
                            multiprecision asio thread foreach format spirit property_tree stacktrace type_traits)

FetchContent_Declare(
    boost
    GIT_REPOSITORY https://github.com/boostorg/boost
    GIT_TAG        ab7968a0bbcf574a7859240d1d8443f58ed6f6cf # v1.85.0
    OVERRIDE_FIND_PACKAGE
)

FetchContent_MakeAvailable(boost)

message("</boost>")