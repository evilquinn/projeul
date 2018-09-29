#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <iostream>
#include <pe66.hpp>

using ::testing::Eq;

class ContFractTest : public ::testing::Test
{
public:
    ContFractTest()           = default;
    ~ContFractTest() override = default;

protected:
};

TEST_F( ContFractTest, testContFractWorksExpected )
{
    auto result = pe66::continued_fraction_of_root_of( 13 );
    EXPECT_THAT( result, Eq( std::vector<int>{ 3, 1, 1, 1, 1, 6 } ) );
    result = pe66::continued_fraction_of_root_of( 19 );
    EXPECT_THAT( result, Eq( std::vector<int>{ 4, 2, 1, 3, 1, 2, 8 } ) );
    std::cout << std::endl;
}

TEST_F( ContFractTest, testIsSquareWorksExpected )
{
    auto result = pe66::continued_fraction_of_root_of( 13 );
    EXPECT_THAT( result, Eq( std::vector<int>{ 3, 1, 1, 1, 1, 6 } ) );
    result = pe66::continued_fraction_of_root_of( 19 );
    EXPECT_THAT( result, Eq( std::vector<int>{ 4, 2, 1, 3, 1, 2, 8 } ) );
    std::cout << std::endl;

    EXPECT_TRUE( pe66::is_square( 1 ) );
    EXPECT_FALSE( pe66::is_square( 2 ) );
    EXPECT_FALSE( pe66::is_square( 3 ) );
    EXPECT_TRUE( pe66::is_square( 4 ) );
}
