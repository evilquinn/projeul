cmake_minimum_required(VERSION 2.8.12)

option(USE_CLANG "Use clang to build." OFF)
if ( ${USE_CLANG} )
    set(CMAKE_TOOLCHAIN_FILE "${CMAKE_SOURCE_DIR}/clang.toolchain.cmake")
endif()

project(projeul C CXX)

enable_testing()

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# CXX settings
if( NOT CMAKE_CXX_STANDARD )
    set(CMAKE_CXX_STANDARD 20)
endif()

find_program(CCACHE_FOUND ccache)
if(CCACHE_FOUND)
    message("CCACHE_FOUND=${CCACHE_FOUND}")
    set(CMAKE_C_COMPILER_LAUNCHER ccache)
    set(CMAKE_CXX_COMPILER_LAUNCHER ccache)
endif()

option(BUILD_BOOST "Downloads and builds required boost libraries" ON)
option(BUILD_TESTS "Builds tests" ON) # tests? pfft.

message("CMAKE_CXX_STANDARD=${CMAKE_CXX_STANDARD}")
message("CMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}")
message("BUILD_BOOST=${BUILD_BOOST}")
message("BUILD_TESTS=${BUILD_TESTS}")
message("ENABLE_COVERAGE=${ENABLE_COVERAGE}")

add_subdirectory(third_party)


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror")
option(ENABLE_NO_PIE
       "Enables --no-pie compiler option (netbeans executable workaround)" OFF)
if ( ${ENABLE_NO_PIE} )
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC -no-pie")
endif()

# debug settings
option(ENABLE_COVERAGE "Enable code coverage metrics for debug builds" OFF)
if ( ${ENABLE_COVERAGE} )
    set(CMAKE_CXX_FLAGS_DEBUG
        "${CMAKE_CXX_FLAGS_DEBUG} -ftest-coverage -fprofile-arcs -pg")
endif()

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
add_subdirectory(accumulator)
add_subdirectory(ansi)
add_subdirectory(aoc)
add_subdirectory(boost_version_poc)
add_subdirectory(chunker)
add_subdirectory(fmt_poc)
add_subdirectory(number_lists)
add_subdirectory(poker)
add_subdirectory(utils)
add_subdirectory(signal_handler)
add_subdirectory(asio)
add_subdirectory(messenger)
add_subdirectory(exercises)
add_subdirectory(dinphi)
add_subdirectory(mdinphi)
add_subdirectory(cigsmoke)
add_subdirectory(leetcode)
add_subdirectory(log_file_stream)
add_subdirectory(oathstuff)
add_subdirectory(pings)
add_subdirectory(quoted)
add_subdirectory(resolver)
add_subdirectory(rlpoc)
add_subdirectory(rulez)
add_subdirectory(scratch)
add_subdirectory(sorts)
add_subdirectory(sudoku)
add_subdirectory(spirit)
add_subdirectory(wancurses)
add_subdirectory(ws)


add_executable(projeul main.cpp)

target_link_libraries(projeul signal_handler
Boost::program_options
                              exercises)

if ( ${BUILD_TESTS} )

    add_subdirectory(test)
    add_subdirectory(profile)

endif()
