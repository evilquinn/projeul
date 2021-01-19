include(ExternalProject)

set(INSTALL_DIR ${CMAKE_CURRENT_BINARY_DIR})

ExternalProject_Add(googletest_dl
    GIT_REPOSITORY https://github.com/google/googletest
    GIT_TAG release-1.8.0
    CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${INSTALL_DIR}
               -DCMAKE_INSTALL_MESSAGE=LAZY
    BUILD_BYPRODUCTS ${INSTALL_DIR}/lib/libgmock.a
                     ${INSTALL_DIR}/lib/libgmock_main.a
                     ${INSTALL_DIR}/lib/libgtest_main.a
                     ${INSTALL_DIR}/lib/libgtest.a
)

set(INCLUDE_DIR ${INSTALL_DIR}/include)
file(MAKE_DIRECTORY ${INCLUDE_DIR})

add_library(googletest INTERFACE IMPORTED GLOBAL)
add_dependencies(googletest googletest_dl)
set_target_properties(googletest PROPERTIES
                      INTERFACE_INCLUDE_DIRECTORIES ${INCLUDE_DIR}
                      INTERFACE_SYSTEM_INCLUDE_DIRECTORIES ${INCLUDE_DIR})

add_library(gtest STATIC IMPORTED GLOBAL)
add_dependencies(gtest googletest_dl)
set_target_properties(gtest PROPERTIES
                      IMPORTED_LOCATION ${INSTALL_DIR}/lib/libgtest.a)
target_link_libraries(gtest INTERFACE googletest)


add_library(gtest_main STATIC IMPORTED GLOBAL)
add_dependencies(gtest_main googletest_dl)
set_target_properties(gtest_main PROPERTIES
                      IMPORTED_LOCATION ${INSTALL_DIR}/lib/libgtest_main.a)
target_link_libraries(gtest_main INTERFACE gtest pthread)

add_library(gmock STATIC IMPORTED GLOBAL)
add_dependencies(gmock googletest_dl)
set_target_properties(gmock PROPERTIES
                      IMPORTED_LOCATION ${INSTALL_DIR}/lib/libgmock.a)
target_link_libraries(gmock INTERFACE gtest)

add_library(gmock_main STATIC IMPORTED GLOBAL)
add_dependencies(gmock_main googletest_dl)
set_target_properties(gmock_main PROPERTIES
                      IMPORTED_LOCATION ${INSTALL_DIR}/lib/libgmock_main.a)
target_link_libraries(gmock_main INTERFACE gmock pthread)
