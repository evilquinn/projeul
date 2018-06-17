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

TEST_F( ContFractTest, testContFractWorksExpected )
{
    auto result = pe66::continued_fraction_of_root_of(13);
    EXPECT_THAT ( result, Eq( std::vector<int>{ 3, 1, 1, 1, 1, 6 } ) );
    result = pe66::continued_fraction_of_root_of(19);
    EXPECT_THAT ( result, Eq( std::vector<int>{ 4, 2, 1, 3, 1, 2, 8 } ) );
    std::cout << std::endl;


}
