#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <gint.hpp>
#include <prime_sieve.hpp>
#include <utils.hpp>

using ::testing::Eq;

class UtilsTest : public ::testing::Test
{
public:
    UtilsTest() {}
    ~UtilsTest() override = default;

protected:
};

TEST_F( UtilsTest, testDigitPatternWorksExpected )
{
    size_t              num = 12123;
    digit_count_map_t   digit_count;
    digit_pattern_map_t digit_pattern;

    size_t digits = pattern_of_digits( num, digit_count, digit_pattern );

    EXPECT_THAT( digits, Eq( 3 ) );
    EXPECT_THAT( digit_count[0], Eq( 0 ) );
    EXPECT_THAT( digit_count[1], Eq( 2 ) );
    EXPECT_THAT( digit_count[2], Eq( 2 ) );
    EXPECT_THAT( digit_count[3], Eq( 1 ) );
    EXPECT_THAT( digit_pattern[0], Eq( 0 ) );
    EXPECT_THAT( digit_pattern[1], Eq( 10100 ) );
    EXPECT_THAT( digit_pattern[2], Eq( 1010 ) );
    EXPECT_THAT( digit_pattern[3], Eq( 1 ) );
}

TEST_F( UtilsTest, testDigitPatternWorksExpectedExtended )
{
    size_t              num = 9330467415;
    digit_count_map_t   digit_count;
    digit_pattern_map_t digit_pattern;

    size_t digits = pattern_of_digits( num, digit_count, digit_pattern );

    EXPECT_THAT( digits, Eq( 8 ) );
    EXPECT_THAT( digit_count[0], Eq( 1 ) );
    EXPECT_THAT( digit_count[1], Eq( 1 ) );
    EXPECT_THAT( digit_count[2], Eq( 0 ) );
    EXPECT_THAT( digit_count[3], Eq( 2 ) );
    EXPECT_THAT( digit_count[4], Eq( 2 ) );
    EXPECT_THAT( digit_count[5], Eq( 1 ) );
    EXPECT_THAT( digit_count[6], Eq( 1 ) );
    EXPECT_THAT( digit_count[7], Eq( 1 ) );
    EXPECT_THAT( digit_count[8], Eq( 0 ) );
    EXPECT_THAT( digit_count[9], Eq( 1 ) );
    EXPECT_THAT( digit_pattern[0], Eq( 1000000 ) );
    EXPECT_THAT( digit_pattern[1], Eq( 10 ) );
    EXPECT_THAT( digit_pattern[2], Eq( 0 ) );
    EXPECT_THAT( digit_pattern[3], Eq( 110000000 ) );
    EXPECT_THAT( digit_pattern[4], Eq( 100100 ) );
    EXPECT_THAT( digit_pattern[5], Eq( 1 ) );
    EXPECT_THAT( digit_pattern[6], Eq( 10000 ) );
    EXPECT_THAT( digit_pattern[7], Eq( 1000 ) );
    EXPECT_THAT( digit_pattern[8], Eq( 0 ) );
    EXPECT_THAT( digit_pattern[9], Eq( 1000000000 ) );
}

TEST_F( UtilsTest, testSameDigitsWorksExpected )
{
    for ( int i = 0; i < 10000; ++i )
    {
        EXPECT_TRUE( same_digits( 123, 321 ) );
        EXPECT_FALSE( same_digits( 123, 320 ) );
        EXPECT_FALSE( same_digits( 123456, 321 ) );
        EXPECT_TRUE( same_digits( 123456, 321456 ) );
        EXPECT_FALSE( same_digits( 123456, 36621 ) );
        EXPECT_TRUE( same_digits( 123999, 321999 ) );
    }
}

TEST_F( UtilsTest, testSameDigitsOldWorksExpected )
{
    for ( int i = 0; i < 10000; ++i )
    {
        EXPECT_TRUE( same_digits_old( 123, 321 ) );
        EXPECT_FALSE( same_digits_old( 123, 320 ) );
        EXPECT_FALSE( same_digits_old( 123456, 321 ) );
        EXPECT_TRUE( same_digits_old( 123456, 321456 ) );
        EXPECT_FALSE( same_digits_old( 123456, 36621 ) );
        EXPECT_TRUE( same_digits_old( 123999, 321999 ) );
    }
}

TEST_F( UtilsTest, testNCRReturnsExpected )
{
    EXPECT_THAT( n_c_r( 5, 3 ), Eq( 10 ) );
}

TEST_F( UtilsTest, testConcat )
{
    EXPECT_EQ( 123456789, concat( 1, 23456789 ) );
    EXPECT_EQ( 123456789, concat( 123, 456789 ) );
    EXPECT_EQ( 123456789, concat( 12345, 6789 ) );
    EXPECT_EQ( 123456789, concat( 123456, 789 ) );
    EXPECT_EQ( 123456789, concat( 1234567, 89 ) );
    EXPECT_EQ( 123456789, concat( 12345678, 9 ) );
}

TEST_F( UtilsTest, testIsPrime )
{
    prime_sieve primes( 1000 );

    for ( size_t i = 0; i < 1000; ++i )
    {
        EXPECT_EQ( primes.is_prime( i ), is_prime( primes, i ) ) << i;
    }
}

TEST_F( UtilsTest, testNextPrime )
{
    prime_sieve primes( 1000 );

    size_t i = 0;
    while ( i < 1000 )
    {
        size_t next_i = primes.next_prime( i );
        EXPECT_EQ( next_i, next_prime( primes, i ) ) << i;
        i = next_i;
    }
}

TEST_F( UtilsTest, testMultDigitArrayByWorks )
{
    const size_t num_digits              = 100;
    int          digit_array[num_digits] = { 0 };
    digit_array[num_digits - 1]          = 4;

    mult_digit_array_by( digit_array, num_digits, 2 );
    EXPECT_THAT( digit_array[num_digits - 1], Eq( 4 * 2 ) );

    mult_digit_array_by( digit_array, num_digits, 5 );
    EXPECT_THAT( digit_array[num_digits - 2], Eq( 4 ) );

    mult_digit_array_by( digit_array, num_digits, 10 );
    EXPECT_THAT( digit_array[num_digits - 3], Eq( 4 ) );

    mult_digit_array_by( digit_array, num_digits, 500 );
    EXPECT_THAT( digit_array[num_digits - 6], Eq( 2 ) );
}

TEST_F ( UtilsTest, testDigitArrayFrom )
{
    auto arr = digit_array_from(12345);
    EXPECT_THAT ( arr, Eq(std::vector<uint8_t>{ 1, 2, 3, 4, 5 } ) );
}
