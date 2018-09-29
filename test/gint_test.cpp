#include <gmock/gmock.h>
#include <memory>

#include <gint.hpp>
#include <utils.hpp>

class GintTest : public ::testing::Test
{
public:
    GintTest()           = default;
    ~GintTest() override = default;

protected:
};

TEST_F( GintTest, testGintConstructorWorksExpected )
{
    gint gi( 1234 );
    gint gd( 1234 );
    EXPECT_EQ( gi, gd );

    auto largest = static_cast<size_t>( -1 );
    EXPECT_EQ( gint( largest ), gint( largest ) );

    auto hegi = std::make_unique<gint>( 1234 );
    EXPECT_EQ( *hegi, gint( 1234 ) );
}

TEST_F( GintTest, testGintIsPalindromeWorksExpected )
{
    gint p1( 1234 );
    gint p2( 1221 );
    gint p3( 1 );
    EXPECT_FALSE( p1.is_palindrome() );
    EXPECT_TRUE( p2.is_palindrome() );
    EXPECT_TRUE( p3.is_palindrome() );
}

TEST_F( GintTest, testGintOperatorEquals )
{
    EXPECT_EQ( gint( 1 ), gint( 1 ) );
    EXPECT_EQ( gint( 1234 ), gint( 1234 ) );
    EXPECT_EQ( gint( 3957264503 ), gint( 3957264503 ) );
    EXPECT_EQ( gint( 81792879281171948 ), gint( 81792879281171948 ) );
    EXPECT_NE( gint( 1 ), gint( 1234 ) );
    EXPECT_NE( gint( 1234 ), gint( 1 ) );
    EXPECT_NE( gint( 395764503 ), gint( 3957264503 ) );
    EXPECT_NE( gint( 81692879281171948 ), gint( 81792879281171948 ) );
    EXPECT_NE( gint( 81792879281171948 ), gint( 81792879281172948 ) );
    EXPECT_NE( gint( 81792879281171948 ), gint( 8179287928117948 ) );
    EXPECT_NE( gint( 81892879281171948 ), gint( 81792879281171948 ) );
}

TEST_F( GintTest, testGintOperatorLessThan )
{
    EXPECT_LT( gint( 1 ), gint( 2 ) );
    EXPECT_LT( gint( 1224 ), gint( 1234 ) );
    EXPECT_LT( gint( 3954503 ), gint( 3957264503 ) );
    EXPECT_LT( gint( 817929281171948 ), gint( 81792879281171948 ) );
}

TEST_F( GintTest, testGintOperators )
{
    EXPECT_LE( gint( 1 ), gint( 1 ) );
    EXPECT_LE( gint( 1234 ), gint( 1234 ) );
    EXPECT_LE( gint( 3957264503 ), gint( 3957264503 ) );
    EXPECT_LE( gint( 81792879281171948 ), gint( 81792879281171948 ) );
}

TEST_F( GintTest, testGintIncrementDecrementWorks )
{
    gint gi( -5 );
    --gi;
    --gi;
    EXPECT_EQ( --gi, gint( -8 ) );
    ++gi;
    ++gi;
    ++gi;
    ++gi;
    ++gi;
    ++gi;
    ++gi;
    EXPECT_EQ( ++gi, gint( 0 ) );
    EXPECT_EQ( gi++, gint( 0 ) );
    ++gi;
    ++gi;
    ++gi;
    ++gi;
    ++gi;
    EXPECT_EQ( --gi, gint( 5 ) );
    EXPECT_EQ( gi--, gint( 5 ) );
    --gi;
    --gi;
    --gi;
    EXPECT_EQ( --gi, gint( 0 ) );
    EXPECT_EQ( gi--, gint( 0 ) );
    --gi;
    EXPECT_EQ( --gi, gint( -3 ) );
}

TEST_F( GintTest, testGintAddSubtractWorks )
{
    /*
     * a + b, where a < b
     * a + b, where a == b
     * a + b, where a > b
     * a + -b, where a < b
     * a + -b, where a == b
     * a + -b, where a > b
     * -a + b, where a < b
     * -a + b, where a == b
     * -a + b, where a > b
     * -a + -b, where a < b
     * -a + -b, where a == b
     * -a + -b, where a > b
     * a - b, where a < b
     * a - b, where a == b
     * a - b, where a > b
     * a - -b, where a < b
     * a - -b, where a == b
     * a - -b, where a > b
     * -a - b, where a < b
     * -a - b, where a == b
     * -a - b, where a > b
     * -a - -b, where a < b
     * -a - -b, where a == b
     * -a - -b, where a > b
     */

    EXPECT_EQ( gint( 100 ) + gint( 200 ), gint( 100 + 200 ) );
    EXPECT_EQ( gint( 100 ) + gint( 100 ), gint( 100 + 100 ) );
    EXPECT_EQ( gint( 200 ) + gint( 100 ), gint( 200 + 100 ) );
    EXPECT_EQ( gint( 100 ) + gint( -200 ), gint( 100 + ( -200 ) ) );
    EXPECT_EQ( gint( 100 ) + gint( -100 ), gint( 100 + ( -100 ) ) );
    EXPECT_EQ( gint( 200 ) + gint( -100 ), gint( 200 + ( -100 ) ) );
    EXPECT_EQ( gint( -100 ) + gint( 200 ), gint( ( -100 ) + 200 ) );
    EXPECT_EQ( gint( -100 ) + gint( 100 ), gint( ( -100 ) + 100 ) );
    EXPECT_EQ( gint( -200 ) + gint( 100 ), gint( ( -200 ) + 100 ) );
    EXPECT_EQ( gint( -100 ) + gint( -200 ), gint( ( -100 ) + ( -200 ) ) );
    EXPECT_EQ( gint( -100 ) + gint( -100 ), gint( ( -100 ) + ( -100 ) ) );
    EXPECT_EQ( gint( -200 ) + gint( -100 ), gint( ( -200 ) + ( -100 ) ) );
    EXPECT_EQ( gint( 100 ) - gint( 200 ), gint( 100 - 200 ) );
    EXPECT_EQ( gint( 100 ) - gint( 100 ), gint( 100 - 100 ) );
    EXPECT_EQ( gint( 200 ) - gint( 100 ), gint( 200 - 100 ) );
    EXPECT_EQ( gint( 100 ) - gint( -200 ), gint( 100 - ( -200 ) ) );
    EXPECT_EQ( gint( 100 ) - gint( -100 ), gint( 100 - ( -100 ) ) );
    EXPECT_EQ( gint( 200 ) - gint( -100 ), gint( 200 - ( -100 ) ) );
    EXPECT_EQ( gint( -100 ) - gint( 200 ), gint( ( -100 ) - 200 ) );
    EXPECT_EQ( gint( -100 ) - gint( 100 ), gint( ( -100 ) - 100 ) );
    EXPECT_EQ( gint( -200 ) - gint( 100 ), gint( ( -200 ) - 100 ) );
    EXPECT_EQ( gint( -100 ) - gint( -200 ), gint( ( -100 ) - ( -200 ) ) );
    EXPECT_EQ( gint( -100 ) - gint( -100 ), gint( ( -100 ) - ( -100 ) ) );
    EXPECT_EQ( gint( -200 ) - gint( -100 ), gint( ( -200 ) - ( -100 ) ) );

    gint selfadd( 1234 );
    EXPECT_EQ( selfadd.add( selfadd ), gint( 2468 ) );
    gint self( 1234 );
    EXPECT_EQ( self.subtract( self ), gint( 0 ) );
    self = gint( 1234 );
    EXPECT_EQ( self.add_reverse_of( self ), gint( 5555 ) );
    EXPECT_EQ( self.add_reverse_of( gint( 9999999999 ) ),
               gint( 9999999999 + 5555 ) );
    EXPECT_EQ( self.add_reverse_of( gint( 12 ) ),
               gint( 9999999999 + 5555 + 21 ) );
}

TEST_F( GintTest, testGintMultiplyWorks )
{
    EXPECT_EQ( gint( 100 ) * gint( 0 ), gint( 0 ) );
    EXPECT_EQ( gint( 100 ) * gint( 200 ), gint( 100 * 200 ) );
    EXPECT_EQ( gint( 100 ) * gint( 100 ), gint( 100 * 100 ) );
    EXPECT_EQ( gint( 200 ) * gint( 100 ), gint( 200 * 100 ) );
    EXPECT_EQ( gint( 100 ) * gint( -200 ), gint( 100 * ( -200 ) ) );
    EXPECT_EQ( gint( 100 ) * gint( -100 ), gint( 100 * ( -100 ) ) );
    EXPECT_EQ( gint( 200 ) * gint( -100 ), gint( 200 * ( -100 ) ) );
    EXPECT_EQ( gint( -100 ) * gint( 200 ), gint( ( -100 ) * 200 ) );
    EXPECT_EQ( gint( -100 ) * gint( 100 ), gint( ( -100 ) * 100 ) );
    EXPECT_EQ( gint( -200 ) * gint( 100 ), gint( ( -200 ) * 100 ) );
    EXPECT_EQ( gint( -100 ) * gint( -200 ), gint( ( -100 ) * ( -200 ) ) );
    EXPECT_EQ( gint( -100 ) * gint( -100 ), gint( ( -100 ) * ( -100 ) ) );
    EXPECT_EQ( gint( -200 ) * gint( -100 ), gint( ( -200 ) * ( -100 ) ) );

    gint self( 1234 );
    EXPECT_EQ( self.multiply_by( self ), gint( 1234 * 1234 ) );
    EXPECT_EQ( gint( 999 ) * gint( 999999 ), gint( 999 * 999999 ) );
    EXPECT_EQ( gint( 999 ) * gint( 999 ), gint( 999 * 999 ) );
    EXPECT_EQ( gint( 999999 ) * gint( 999 ), gint( 999 * 999999 ) );
}

TEST_F( GintTest, testSumDigitsWorks )
{
    EXPECT_EQ( gint( 1234 ).sum_digits(), 10 );
}

TEST_F( GintTest, testGintStreamOutWorks )
{
    gint g1( 1234 );
    std::cout << g1 * gint( 2 ) << std::endl;
    std::cout << g1 - gint( 2 ) << std::endl;
    std::cout << g1 - gint( 2000 ) << std::endl;
    g1.print();
}

TEST_F( GintTest, testNumDigitsWorks )
{
    gint gi( 1234 );
    EXPECT_EQ( ( gi *= gint( 10 ) ).num_digits(), 5 );
    EXPECT_EQ( ( gi *= gint( 10 ) ).num_digits(), 6 );
    EXPECT_EQ( ( gi *= gint( 10 ) ).num_digits(), 7 );
    EXPECT_EQ( ( gi *= gint( 10 ) ).num_digits(), 8 );
    EXPECT_EQ( ( gi *= gint( 10 ) ).num_digits(), 9 );
    EXPECT_EQ( ( gi *= gint( 10 ) ).num_digits(), 10 );
    EXPECT_EQ( ( gi *= gint( 10 ) ).num_digits(), 11 );
    EXPECT_EQ( ( gi *= gint( 10 ) ).num_digits(), 12 );
    EXPECT_EQ( ( gi *= gint( 10 ) ).num_digits(), 13 );
    EXPECT_EQ( ( gi *= gint( 10 ) ).num_digits(), 14 );
}

TEST_F( GintTest, testGintToSizeTWorks )
{
    for ( size_t i = 0; i < 1234; ++i )
    {
        gint gi( i );
        EXPECT_EQ( i, gi.to_size_t() );
    }
}

TEST_F( GintTest, testGintPowWorks )
{
    EXPECT_EQ( gint( 2 ).pow( 2 ), gint( 4 ) );
    EXPECT_EQ( gint( 3 ).pow( 2 ), gint( 9 ) );
    EXPECT_EQ( gint( 2 ).pow( 10 ), gint( 1024 ) );
    EXPECT_EQ( gint( 3 ).pow( 5 ), gint( 243 ) );
}

TEST_F( GintTest, testGintDivide )
{
    EXPECT_ANY_THROW( gint( 100 ) / gint( 0 ) );
    EXPECT_EQ( gint( 100 ) / gint( 200 ), gint( 100 / 200 ) );
    EXPECT_EQ( gint( 100 ) / gint( 100 ), gint( 100 / 100 ) );
    EXPECT_EQ( gint( 200 ) / gint( 100 ), gint( 200 / 100 ) );
    EXPECT_EQ( gint( 100 ) / gint( ( -200 ) ), gint( 100 / ( -200 ) ) );
    EXPECT_EQ( gint( 100 ) / gint( ( -100 ) ), gint( 100 / ( -100 ) ) );
    EXPECT_EQ( gint( 200 ) / gint( ( -100 ) ), gint( 200 / ( -100 ) ) );
    EXPECT_EQ( gint( -100 ) / gint( 200 ), gint( ( -100 ) / 200 ) );
    EXPECT_EQ( gint( -100 ) / gint( 100 ), gint( ( -100 ) / 100 ) );
    EXPECT_EQ( gint( -200 ) / gint( 100 ), gint( ( -200 ) / 100 ) );
    EXPECT_EQ( gint( -100 ) / gint( ( -200 ) ), gint( ( -100 ) / ( -200 ) ) );
    EXPECT_EQ( gint( -100 ) / gint( ( -100 ) ), gint( ( -100 ) / ( -100 ) ) );
    EXPECT_EQ( gint( -200 ) / gint( ( -100 ) ), gint( ( -200 ) / ( -100 ) ) );

    gint self( 1234 );
    EXPECT_EQ( self.divide_by( self ), gint( 1234 / 1234 ) );
    EXPECT_EQ( gint( 999 ) / gint( 999999 ), gint( 999 / 999999 ) );
    EXPECT_EQ( gint( 999 ) / gint( 999 ), gint( 999 / 999 ) );
    EXPECT_EQ( gint( 999999 ) / gint( 999 ), gint( 999999 / 999 ) );

    for ( int i = -50; i < 50; ++i )
    {
        gint num( i );
        for ( int j = -50; j < 50; ++j )
        {
            if ( j == 0 )
            {
                EXPECT_ANY_THROW( num / gint( j ) );
            }
            else
            {
                EXPECT_EQ( gint( i / j ), num / gint( j ) );
            }
        }
    }
}
