#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <utils.hpp>

using ::testing::Eq;

class UtilsTest : public ::testing::Test
{
public:
    UtilsTest()
    {
    }
    ~UtilsTest(){}

    virtual void SetUp(){}
    virtual void TearDown(){}
protected:
};

TEST_F(UtilsTest, testDigitPatternWorksExpected)
{
    size_t num = 12123;
    digit_count_map_t digit_count;
    digit_pattern_map_t digit_pattern;

    size_t digits = pattern_of_digits(num, digit_count, digit_pattern);

    EXPECT_THAT(digits, Eq(3));
    EXPECT_THAT(digit_count[0], Eq(0));
    EXPECT_THAT(digit_count[1], Eq(2));
    EXPECT_THAT(digit_count[2], Eq(2));
    EXPECT_THAT(digit_count[3], Eq(1));
    EXPECT_THAT(digit_pattern[0], Eq(0));
    EXPECT_THAT(digit_pattern[1], Eq(10100));
    EXPECT_THAT(digit_pattern[2], Eq(1010));
    EXPECT_THAT(digit_pattern[3], Eq(1));
}

TEST_F(UtilsTest, testDigitPatternWorksExpectedExtended)
{
    size_t num = 9330467415;
    digit_count_map_t digit_count;
    digit_pattern_map_t digit_pattern;

    size_t digits = pattern_of_digits(num, digit_count, digit_pattern);

    EXPECT_THAT(digits, Eq(8));
    EXPECT_THAT(digit_count[0], Eq(1));
    EXPECT_THAT(digit_count[1], Eq(1));
    EXPECT_THAT(digit_count[2], Eq(0));
    EXPECT_THAT(digit_count[3], Eq(2));
    EXPECT_THAT(digit_count[4], Eq(2));
    EXPECT_THAT(digit_count[5], Eq(1));
    EXPECT_THAT(digit_count[6], Eq(1));
    EXPECT_THAT(digit_count[7], Eq(1));
    EXPECT_THAT(digit_count[8], Eq(0));
    EXPECT_THAT(digit_count[9], Eq(1));
    EXPECT_THAT(digit_pattern[0], Eq(1000000));
    EXPECT_THAT(digit_pattern[1], Eq(10));
    EXPECT_THAT(digit_pattern[2], Eq(0));
    EXPECT_THAT(digit_pattern[3], Eq(110000000));
    EXPECT_THAT(digit_pattern[4], Eq(100100));
    EXPECT_THAT(digit_pattern[5], Eq(1));
    EXPECT_THAT(digit_pattern[6], Eq(10000));
    EXPECT_THAT(digit_pattern[7], Eq(1000));
    EXPECT_THAT(digit_pattern[8], Eq(0));
    EXPECT_THAT(digit_pattern[9], Eq(1000000000));
}
