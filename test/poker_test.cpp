#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <boost/foreach.hpp>
#include <poker.hpp>
#include <string>

using ::testing::Eq;

class PokerTest : public ::testing::Test
{
public:
    PokerTest()           = default;
    ~PokerTest() override = default;

protected:
};

TEST_F( PokerTest, testMakeHandWorksExpected )
{
    poker::hand player1;
    poker::make_hand( "KH 2H 3H 4H 5H", player1 );

    EXPECT_THAT( player1.size(), Eq( 5 ) );
}

TEST_F( PokerTest, testScoredHandConstructorWorks )
{
    poker::hand player1;
    poker::make_hand( "2H 3H 4H 5H 6H", player1 );
    poker::scored_hand scored1( player1 );
    EXPECT_THAT( scored1.rank_, Eq( poker::scored_hand::STRAIGHT_FLUSH ) );
    poker::make_hand( "2H 3H 4H 5D 6H", player1 );
    poker::scored_hand scored2( player1 );
    EXPECT_THAT( scored2.rank_, Eq( poker::scored_hand::STRAIGHT ) );
    poker::make_hand( "2H 3H 4H 5D 7H", player1 );
    poker::scored_hand scored3( player1 );
    EXPECT_THAT( scored3.rank_, Eq( poker::scored_hand::HIGH_CARD ) );
    poker::make_hand( "2H 3H 4H 5H 7H", player1 );
    poker::scored_hand scored4( player1 );
    EXPECT_THAT( scored4.rank_, Eq( poker::scored_hand::FLUSH ) );
    poker::make_hand( "KH 2H 3H 4H 5H", player1 );
    poker::scored_hand scored5( player1 );
    EXPECT_THAT( scored5.rank_, Eq( poker::scored_hand::FLUSH ) );

    poker::make_hand( "K0 KH KD KC KS", player1 );
    poker::scored_hand scored6( player1 );
    EXPECT_THAT( scored6.rank_, Eq( poker::scored_hand::RANK_UNINIT ) );

    poker::make_hand( "AH KH KD KC KS", player1 );
    poker::scored_hand scored7( player1 );
    EXPECT_THAT( scored7.rank_, Eq( poker::scored_hand::FOUR_OF_KIND ) );

    poker::make_hand( "AH AC KD KC KS", player1 );
    poker::scored_hand scored8( player1 );
    EXPECT_THAT( scored8.rank_, Eq( poker::scored_hand::FULL_HOUSE ) );

    poker::make_hand( "KH KC AD AC AS", player1 );
    poker::scored_hand scored9( player1 );
    EXPECT_THAT( scored9.rank_, Eq( poker::scored_hand::FULL_HOUSE ) );

    poker::make_hand( "KH KC AD AC 5S", player1 );
    poker::scored_hand scored10( player1 );
    EXPECT_THAT( scored10.rank_, Eq( poker::scored_hand::TWO_PAIRS ) );

    poker::make_hand( "KH NH KD KC KS", player1 );
    poker::scored_hand scored11( player1 );
    EXPECT_THAT( scored11.rank_, Eq( poker::scored_hand::FOUR_OF_KIND ) );
}

TEST_F( PokerTest, testScoredHandGameWorks )
{
    poker::hand p1;
    poker::hand p2;

    poker::make_hand( "2H 3H 4H 5H 7H", p1 );
    poker::make_hand( "JH AH TH KH QH", p2 );
    EXPECT_THAT( poker::game( p1, p2 ), Eq( 1 ) );

    poker::make_hand( "JH AH TH KH QH", p1 );
    poker::make_hand( "JH AH TH KH QH", p2 );
    EXPECT_THAT( poker::game( p1, p2 ), Eq( 0 ) );

    poker::make_hand( "2H 2C 4H 5H AH", p1 );
    poker::make_hand( "2D 2S TH KH QH", p2 );
    EXPECT_THAT( poker::game( p1, p2 ), Eq( -1 ) );

    poker::make_hand( "2D 2S TH KH QH", p1 );
    poker::make_hand( "2H 2C 4H 5H AH", p2 );
    EXPECT_THAT( poker::game( p1, p2 ), Eq( 1 ) );

    poker::make_hand( "2H 2C 4H 5H 7H", p1 );
    poker::make_hand( "JH JD 4S 5S 7S", p2 );
    EXPECT_THAT( poker::game( p1, p2 ), Eq( 1 ) );

    poker::make_hand( "JH JD JS 5S 7S", p1 );
    poker::make_hand( "2H 2C 4D 5H 7H", p2 );
    EXPECT_THAT( poker::game( p1, p2 ), Eq( -1 ) );
}
