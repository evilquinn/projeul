include(ExternalProject)

set(INSTALL_DIR ${CMAKE_BINARY_DIR}/googletest)

ExternalProject_Add(googletest_dl
    GIT_REPOSITORY https://github.com/google/googletest
    CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${INSTALL_DIR}
    BUILD_BYPRODUCTS "${INSTALL_DIR}/lib/libgmock.a"
)

add_library(googletest INTERFACE IMPORTED GLOBAL)
add_dependencies(googletest googletest_dl)
set_target_properties(googletest PROPERTIES
                      INTERFACE_INCLUDE_DIRECTORIES ${INSTALL_DIR}/include
                      INTERFACE_SYSTEM_INCLUDE_DIRECTORIES
                          ${INSTALL_DIR}/include)

add_library(gtest STATIC IMPORTED GLOBAL)
add_dependencies(gtest googletest_dl)
set_target_properties(gtest PROPERTIES
                      IMPORTED_LOCATION ${INSTALL_DIR}/lib/libgtest.a)
target_link_libraries(gtest INTERFACE googletest)

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
