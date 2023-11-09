set(INSTALL_DIR ${CMAKE_CURRENT_BINARY_DIR})

ExternalProject_Add(fmt_dl
    GIT_REPOSITORY https://github.com/fmtlib/fmt.git
    GIT_TAG        10.1.1
    CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${INSTALL_DIR}
               -DCMAKE_INSTALL_MESSAGE=LAZY
    BUILD_BYPRODUCTS ${INSTALL_DIR}/lib64/libfmt.a
)

set(INCLUDE_DIR ${INSTALL_DIR}/include)
file(MAKE_DIRECTORY ${INCLUDE_DIR})

add_library(fmt STATIC IMPORTED GLOBAL)
add_dependencies(fmt fmt_dl)
set_target_properties(fmt PROPERTIES
                      IMPORTED_LOCATION ${INSTALL_DIR}/lib64/libfmt.a
                      INTERFACE_INCLUDE_DIRECTORIES ${INCLUDE_DIR}
                      INTERFACE_SYSTEM_INCLUDE_DIRECTORIES ${INCLUDE_DIR})
