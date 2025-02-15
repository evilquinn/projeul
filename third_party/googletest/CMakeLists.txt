
if ( NOT ${BUILD_TESTS} )
    return()
endif()

message("<googletest>")

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        6910c9d9165801d8827d628cb72eb7ea9dd538c5
  OVERRIDE_FIND_PACKAGE
)

FetchContent_MakeAvailable(googletest)

message("</googletest>")