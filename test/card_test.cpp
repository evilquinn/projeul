#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <card.hpp>

using ::testing::Eq;
using ::testing::Pair;

class CardTest : public ::testing::Test
{
public:
    CardTest()
        : two_hearts( "2H" ),
          three_hearts( "3H" ),
          four_hearts( "4H" ),
          five_hearts( "5H" ),
          six_hearts( "6H" ),
          seven_hearts( "7H" ),
          eight_hearts( "8H" ),
          nine_hearts( "9H" ),
          ten_hearts( "TH" ),
          jack_hearts( "JH" ),
          queen_hearts( "QH" ),
          king_hearts( "KH" ),
          ace_hearts( "AH" ),
          two_diamonds( "2D" ),
          three_diamonds( "3D" ),
          four_diamonds( "4D" ),
          five_diamonds( "5D" ),
          six_diamonds( "6D" ),
          seven_diamonds( "7D" ),
          eight_diamonds( "8D" ),
          nine_diamonds( "9D" ),
          ten_diamonds( "TD" ),
          jack_diamonds( "JD" ),
          queen_diamonds( "QD" ),
          king_diamonds( "KD" ),
          ace_diamonds( "AD" ),
          two_clubs( "2C" ),
          three_clubs( "3C" ),
          four_clubs( "4C" ),
          five_clubs( "5C" ),
          six_clubs( "6C" ),
          seven_clubs( "7C" ),
          eight_clubs( "8C" ),
          nine_clubs( "9C" ),
          ten_clubs( "TC" ),
          jack_clubs( "JC" ),
          queen_clubs( "QC" ),
          king_clubs( "KC" ),
          ace_clubs( "AC" ),
          two_spades( "2S" ),
          three_spades( "3S" ),
          four_spades( "4S" ),
          five_spades( "5S" ),
          six_spades( "6S" ),
          seven_spades( "7S" ),
          eight_spades( "8S" ),
          nine_spades( "9S" ),
          ten_spades( "TS" ),
          jack_spades( "JS" ),
          queen_spades( "QS" ),
          king_spades( "KS" ),
          ace_spades( "AS" )
    {
    }
    ~CardTest() {}
    virtual void SetUp() {}
    virtual void TearDown() {}
protected:
    card two_hearts;
    card three_hearts;
    card four_hearts;
    card five_hearts;
    card six_hearts;
    card seven_hearts;
    card eight_hearts;
    card nine_hearts;
    card ten_hearts;
    card jack_hearts;
    card queen_hearts;
    card king_hearts;
    card ace_hearts;
    card two_diamonds;
    card three_diamonds;
    card four_diamonds;
    card five_diamonds;
    card six_diamonds;
    card seven_diamonds;
    card eight_diamonds;
    card nine_diamonds;
    card ten_diamonds;
    card jack_diamonds;
    card queen_diamonds;
    card king_diamonds;
    card ace_diamonds;
    card two_clubs;
    card three_clubs;
    card four_clubs;
    card five_clubs;
    card six_clubs;
    card seven_clubs;
    card eight_clubs;
    card nine_clubs;
    card ten_clubs;
    card jack_clubs;
    card queen_clubs;
    card king_clubs;
    card ace_clubs;
    card two_spades;
    card three_spades;
    card four_spades;
    card five_spades;
    card six_spades;
    card seven_spades;
    card eight_spades;
    card nine_spades;
    card ten_spades;
    card jack_spades;
    card queen_spades;
    card king_spades;
    card ace_spades;
};

TEST_F( CardTest, testCardLessThanOperator )
{
    EXPECT_TRUE( king_spades < ace_spades );
    EXPECT_TRUE( king_spades < ace_hearts );
    EXPECT_TRUE( king_spades < ace_diamonds );
    EXPECT_FALSE( king_spades < king_hearts );
    EXPECT_TRUE( king_hearts < king_spades );
    EXPECT_TRUE( king_spades < king_clubs );
    EXPECT_FALSE( king_spades < queen_spades );
    EXPECT_FALSE( king_spades < queen_hearts );
    EXPECT_FALSE( king_spades < queen_diamonds );
    EXPECT_FALSE( king_spades < queen_clubs );
    card king_dup( king_spades );
    EXPECT_FALSE( king_spades < king_dup );
}

TEST_F( CardTest, testCardConstruction )
{
    EXPECT_THAT( std::make_pair( two_clubs.value_, two_clubs.suit_ ),
                 Pair( card::TWO, card::CLUBS ) );
    EXPECT_THAT( std::make_pair( three_clubs.value_, three_clubs.suit_ ),
                 Pair( card::THREE, card::CLUBS ) );
    EXPECT_THAT( std::make_pair( four_clubs.value_, four_clubs.suit_ ),
                 Pair( card::FOUR, card::CLUBS ) );
    EXPECT_THAT( std::make_pair( five_clubs.value_, five_clubs.suit_ ),
                 Pair( card::FIVE, card::CLUBS ) );
    EXPECT_THAT( std::make_pair( six_clubs.value_, six_clubs.suit_ ),
                 Pair( card::SIX, card::CLUBS ) );
    EXPECT_THAT( std::make_pair( seven_clubs.value_, seven_clubs.suit_ ),
                 Pair( card::SEVEN, card::CLUBS ) );
    EXPECT_THAT( std::make_pair( eight_clubs.value_, eight_clubs.suit_ ),
                 Pair( card::EIGHT, card::CLUBS ) );
    EXPECT_THAT( std::make_pair( nine_clubs.value_, nine_clubs.suit_ ),
                 Pair( card::NINE, card::CLUBS ) );
    EXPECT_THAT( std::make_pair( ten_clubs.value_, ten_clubs.suit_ ),
                 Pair( card::TEN, card::CLUBS ) );
    EXPECT_THAT( std::make_pair( jack_clubs.value_, jack_clubs.suit_ ),
                 Pair( card::JACK, card::CLUBS ) );
    EXPECT_THAT( std::make_pair( queen_clubs.value_, queen_clubs.suit_ ),
                 Pair( card::QUEEN, card::CLUBS ) );
    EXPECT_THAT( std::make_pair( king_clubs.value_, king_clubs.suit_ ),
                 Pair( card::KING, card::CLUBS ) );
    EXPECT_THAT( std::make_pair( ace_clubs.value_, ace_clubs.suit_ ),
                 Pair( card::ACE, card::CLUBS ) );
    EXPECT_THAT( std::make_pair( two_spades.value_, two_spades.suit_ ),
                 Pair( card::TWO, card::SPADES ) );
    EXPECT_THAT( std::make_pair( three_spades.value_, three_spades.suit_ ),
                 Pair( card::THREE, card::SPADES ) );
    EXPECT_THAT( std::make_pair( four_spades.value_, four_spades.suit_ ),
                 Pair( card::FOUR, card::SPADES ) );
    EXPECT_THAT( std::make_pair( five_spades.value_, five_spades.suit_ ),
                 Pair( card::FIVE, card::SPADES ) );
    EXPECT_THAT( std::make_pair( six_spades.value_, six_spades.suit_ ),
                 Pair( card::SIX, card::SPADES ) );
    EXPECT_THAT( std::make_pair( seven_spades.value_, seven_spades.suit_ ),
                 Pair( card::SEVEN, card::SPADES ) );
    EXPECT_THAT( std::make_pair( eight_spades.value_, eight_spades.suit_ ),
                 Pair( card::EIGHT, card::SPADES ) );
    EXPECT_THAT( std::make_pair( nine_spades.value_, nine_spades.suit_ ),
                 Pair( card::NINE, card::SPADES ) );
    EXPECT_THAT( std::make_pair( ten_spades.value_, ten_spades.suit_ ),
                 Pair( card::TEN, card::SPADES ) );
    EXPECT_THAT( std::make_pair( jack_spades.value_, jack_spades.suit_ ),
                 Pair( card::JACK, card::SPADES ) );
    EXPECT_THAT( std::make_pair( queen_spades.value_, queen_spades.suit_ ),
                 Pair( card::QUEEN, card::SPADES ) );
    EXPECT_THAT( std::make_pair( king_spades.value_, king_spades.suit_ ),
                 Pair( card::KING, card::SPADES ) );
    EXPECT_THAT( std::make_pair( ace_spades.value_, ace_spades.suit_ ),
                 Pair( card::ACE, card::SPADES ) );
    EXPECT_THAT( std::make_pair( two_hearts.value_, two_hearts.suit_ ),
                 Pair( card::TWO, card::HEARTS ) );
    EXPECT_THAT( std::make_pair( three_hearts.value_, three_hearts.suit_ ),
                 Pair( card::THREE, card::HEARTS ) );
    EXPECT_THAT( std::make_pair( four_hearts.value_, four_hearts.suit_ ),
                 Pair( card::FOUR, card::HEARTS ) );
    EXPECT_THAT( std::make_pair( five_hearts.value_, five_hearts.suit_ ),
                 Pair( card::FIVE, card::HEARTS ) );
    EXPECT_THAT( std::make_pair( six_hearts.value_, six_hearts.suit_ ),
                 Pair( card::SIX, card::HEARTS ) );
    EXPECT_THAT( std::make_pair( seven_hearts.value_, seven_hearts.suit_ ),
                 Pair( card::SEVEN, card::HEARTS ) );
    EXPECT_THAT( std::make_pair( eight_hearts.value_, eight_hearts.suit_ ),
                 Pair( card::EIGHT, card::HEARTS ) );
    EXPECT_THAT( std::make_pair( nine_hearts.value_, nine_hearts.suit_ ),
                 Pair( card::NINE, card::HEARTS ) );
    EXPECT_THAT( std::make_pair( ten_hearts.value_, ten_hearts.suit_ ),
                 Pair( card::TEN, card::HEARTS ) );
    EXPECT_THAT( std::make_pair( jack_hearts.value_, jack_hearts.suit_ ),
                 Pair( card::JACK, card::HEARTS ) );
    EXPECT_THAT( std::make_pair( queen_hearts.value_, queen_hearts.suit_ ),
                 Pair( card::QUEEN, card::HEARTS ) );
    EXPECT_THAT( std::make_pair( king_hearts.value_, king_hearts.suit_ ),
                 Pair( card::KING, card::HEARTS ) );
    EXPECT_THAT( std::make_pair( ace_hearts.value_, ace_hearts.suit_ ),
                 Pair( card::ACE, card::HEARTS ) );
    EXPECT_THAT( std::make_pair( two_diamonds.value_, two_diamonds.suit_ ),
                 Pair( card::TWO, card::DIAMONDS ) );
    EXPECT_THAT(
        std::make_pair( three_diamonds.value_, three_diamonds.suit_ ),
        Pair( card::THREE, card::DIAMONDS ) );
    EXPECT_THAT( std::make_pair( four_diamonds.value_, four_diamonds.suit_ ),
                 Pair( card::FOUR, card::DIAMONDS ) );
    EXPECT_THAT( std::make_pair( five_diamonds.value_, five_diamonds.suit_ ),
                 Pair( card::FIVE, card::DIAMONDS ) );
    EXPECT_THAT( std::make_pair( six_diamonds.value_, six_diamonds.suit_ ),
                 Pair( card::SIX, card::DIAMONDS ) );
    EXPECT_THAT(
        std::make_pair( seven_diamonds.value_, seven_diamonds.suit_ ),
        Pair( card::SEVEN, card::DIAMONDS ) );
    EXPECT_THAT(
        std::make_pair( eight_diamonds.value_, eight_diamonds.suit_ ),
        Pair( card::EIGHT, card::DIAMONDS ) );
    EXPECT_THAT( std::make_pair( nine_diamonds.value_, nine_diamonds.suit_ ),
                 Pair( card::NINE, card::DIAMONDS ) );
    EXPECT_THAT( std::make_pair( ten_diamonds.value_, ten_diamonds.suit_ ),
                 Pair( card::TEN, card::DIAMONDS ) );
    EXPECT_THAT( std::make_pair( jack_diamonds.value_, jack_diamonds.suit_ ),
                 Pair( card::JACK, card::DIAMONDS ) );
    EXPECT_THAT(
        std::make_pair( queen_diamonds.value_, queen_diamonds.suit_ ),
        Pair( card::QUEEN, card::DIAMONDS ) );
    EXPECT_THAT( std::make_pair( king_diamonds.value_, king_diamonds.suit_ ),
                 Pair( card::KING, card::DIAMONDS ) );
    EXPECT_THAT( std::make_pair( ace_diamonds.value_, ace_diamonds.suit_ ),
                 Pair( card::ACE, card::DIAMONDS ) );
}
