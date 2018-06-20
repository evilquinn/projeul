#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <pe66.hpp>
#include <iostream>

using ::testing::Eq;
using ::testing::ElementsAreArray;

class ContFractTest : public ::testing::Test
{
public:
    ContFractTest() {}
    ~ContFractTest() override = default;

protected:
};

TEST_F( ContFractTest, testIsSquareWorksExpected )
{
    EXPECT_TRUE  ( pe66::is_square(1) );
    EXPECT_FALSE ( pe66::is_square(2) );
    EXPECT_FALSE ( pe66::is_square(3) );
    EXPECT_TRUE  ( pe66::is_square(4) );
}
