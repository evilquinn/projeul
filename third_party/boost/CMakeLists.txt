
message("<boost>")
set(BOOST_ENABLE_CMAKE ON)
#set(BOOST_INCLUDE_LIBRARIES filesystem system date_time regex program_options)
#set(BOOST_INCLUDE_LIBRARIES "filesystem;system;date_time;regex;program_options" CACHE STRING "List of libraries to build (default: all but excluded and incompatible)")
#set(BOOST_EXCLUDE_LIBRARIES "bimap graph" CACHE STRING "List of libraries to exlude from build (default: none)")

FetchContent_Declare(
    boost
    GIT_REPOSITORY https://github.com/boostorg/boost
    GIT_TAG        da041154c6bac1a4aa98254a7d6819059e8ac0b0
    OVERRIDE_FIND_PACKAGE
)

FetchContent_MakeAvailable(boost)

message("</boost>")