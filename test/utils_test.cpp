#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <utils.hpp>
#include <gint.hpp>

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

TEST_F(UtilsTest, testSameDigitsWorksExpected)
{
    for ( int i = 0; i< 10000; ++i)
    {
    EXPECT_TRUE(same_digits(123, 321));
    EXPECT_FALSE(same_digits(123, 320));
    EXPECT_FALSE(same_digits(123456, 321));
    EXPECT_TRUE(same_digits(123456, 321456));
    EXPECT_FALSE(same_digits(123456, 36621));
    EXPECT_TRUE(same_digits(123999, 321999));
    }
}


TEST_F(UtilsTest, testSameDigitsOldWorksExpected)
{
    for ( int i = 0; i< 10000; ++i)
    {
    EXPECT_TRUE(same_digits_old(123, 321));
    EXPECT_FALSE(same_digits_old(123, 320));
    EXPECT_FALSE(same_digits_old(123456, 321));
    EXPECT_TRUE(same_digits_old(123456, 321456));
    EXPECT_FALSE(same_digits_old(123456, 36621));
    EXPECT_TRUE(same_digits_old(123999, 321999));
    }
}

TEST_F(UtilsTest, testNCRReturnsExpected)
{
    EXPECT_THAT(n_c_r(5, 3), Eq(10));
}

TEST_F(UtilsTest, testGintConstructorWorksExpected)
{
    gint gi(1234);
    gint gd(1234);
    gi.print();

    gi.add(1234);
    gi.print();

    gi.add(1234);
    gi.print();

    gi.add(1234).add(1234);
    gi.add(1234).add(1234);
    gi.add_reverse_of(4321).add(gd).add(1234);
    gi.print();

    gi.add(gi);
    gi.print();

}


TEST_F(UtilsTest, testGintIsPalindromeWorksExpected)
{
    gint p1(1234);
    gint p2(1221);
    gint p3(1);
    EXPECT_FALSE(p1.is_palindrome());
    EXPECT_TRUE(p2.is_palindrome());
    EXPECT_TRUE(p3.is_palindrome());
}

TEST_F(UtilsTest, testGintMultiplyBy)
{
    gint g1(1234);
    g1.multiply_by(28456212);
    g1.print();
    size_t expected = 1234ll * 28456212;
    std::cout << expected << std::endl;
}
