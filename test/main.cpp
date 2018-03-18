
#include <iostream>
#include <gmock/gmock.h>
#include <gtest/gtest.h>

static int run_all_tests(int* argc, char** argv)
{
  // Since Google Mock depends on Google Test, InitGoogleMock() is
  // also responsible for initializing Google Test.  Therefore there's
  // no need for calling testing::InitGoogleTest() separately.
  testing::InitGoogleMock(argc, argv);
  return RUN_ALL_TESTS();
}

int main(int argc, char** argv)
{
    return run_all_tests(&argc, argv);
}
