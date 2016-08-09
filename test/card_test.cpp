#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <card.hpp>

using ::testing::Eq;
using ::testing::Pair;

class CardTest : public ::testing::Test
{
public:
    CardTest()
    {
    }
    ~CardTest(){}

    virtual void SetUp(){}
    virtual void TearDown(){}
protected:
};

TEST_F(CardTest, testCardConstruction)
{
    card two_hearts("2H");
    card three_hearts("3H");
    card four_hearts("4H");
    card five_hearts("5H");
    card six_hearts("6H");
    card seven_hearts("7H");
    card eight_hearts("8H");
    card nine_hearts("9H");
    card ten_hearts("TH");
    card jack_hearts("JH");
    card queen_hearts("QH");
    card king_hearts("KH");
    card ace_hearts("AH");
    card two_diamonds("2D");
    card three_diamonds("3D");
    card four_diamonds("4D");
    card five_diamonds("5D");
    card six_diamonds("6D");
    card seven_diamonds("7D");
    card eight_diamonds("8D");
    card nine_diamonds("9D");
    card ten_diamonds("TD");
    card jack_diamonds("JD");
    card queen_diamonds("QD");
    card king_diamonds("KD");
    card ace_diamonds("AD");
    card two_clubs("2C");
    card three_clubs("3C");
    card four_clubs("4C");
    card five_clubs("5C");
    card six_clubs("6C");
    card seven_clubs("7C");
    card eight_clubs("8C");
    card nine_clubs("9C");
    card ten_clubs("TC");
    card jack_clubs("JC");
    card queen_clubs("QC");
    card king_clubs("KC");
    card ace_clubs("AC");
    card two_spades("2S");
    card three_spades("3S");
    card four_spades("4S");
    card five_spades("5S");
    card six_spades("6S");
    card seven_spades("7S");
    card eight_spades("8S");
    card nine_spades("9S");
    card ten_spades("TS");
    card jack_spades("JS");
    card queen_spades("QS");
    card king_spades("KS");
    card ace_spades("AS");


    EXPECT_THAT(std::make_pair(two_hearts.value_,
                               two_hearts.suit_ ),
                Pair(card::TWO, card::HEARTS) );
    EXPECT_THAT(std::make_pair(three_hearts.value_,
                               three_hearts.suit_),
                Pair(card::THREE, card::HEARTS) );
    EXPECT_THAT(std::make_pair(four_hearts.value_,
                               four_hearts.suit_),
                Pair(card::FOUR, card::HEARTS) );
    EXPECT_THAT(std::make_pair(five_hearts.value_,
                               five_hearts.suit_),
                Pair(card::FIVE, card::HEARTS) );
    EXPECT_THAT(std::make_pair(six_hearts.value_,
                               six_hearts.suit_),
                Pair(card::SIX, card::HEARTS) );
    EXPECT_THAT(std::make_pair(seven_hearts.value_,
                               seven_hearts.suit_),
                Pair(card::SEVEN, card::HEARTS) );
    EXPECT_THAT(std::make_pair(eight_hearts.value_,
                               eight_hearts.suit_),
                Pair(card::EIGHT, card::HEARTS) );
    EXPECT_THAT(std::make_pair(nine_hearts.value_,
                               nine_hearts.suit_),
                Pair(card::NINE, card::HEARTS) );
    EXPECT_THAT(std::make_pair(ten_hearts.value_,
                               ten_hearts.suit_),
                Pair(card::TEN, card::HEARTS) );
    EXPECT_THAT(std::make_pair(jack_hearts.value_,
                               jack_hearts.suit_),
                Pair(card::JACK, card::HEARTS) );
    EXPECT_THAT(std::make_pair(queen_hearts.value_,
                               queen_hearts.suit_),
                Pair(card::QUEEN, card::HEARTS) );
    EXPECT_THAT(std::make_pair(king_hearts.value_,
                               king_hearts.suit_),
                Pair(card::KING, card::HEARTS) );
    EXPECT_THAT(std::make_pair(ace_hearts.value_,
                               ace_hearts.suit_),
                Pair(card::ACE, card::HEARTS) );
    EXPECT_THAT(std::make_pair(two_diamonds.value_,
                               two_diamonds.suit_),
                Pair(card::TWO, card::DIAMONDS) );
    EXPECT_THAT(std::make_pair(three_diamonds.value_,
                               three_diamonds.suit_),
                Pair(card::THREE, card::DIAMONDS) );
    EXPECT_THAT(std::make_pair(four_diamonds.value_,
                               four_diamonds.suit_),
                Pair(card::FOUR, card::DIAMONDS) );
    EXPECT_THAT(std::make_pair(five_diamonds.value_,
                               five_diamonds.suit_),
                Pair(card::FIVE, card::DIAMONDS) );
    EXPECT_THAT(std::make_pair(six_diamonds.value_,
                               six_diamonds.suit_),
                Pair(card::SIX, card::DIAMONDS) );
    EXPECT_THAT(std::make_pair(seven_diamonds.value_,
                               seven_diamonds.suit_),
                Pair(card::SEVEN, card::DIAMONDS) );
    EXPECT_THAT(std::make_pair(eight_diamonds.value_,
                               eight_diamonds.suit_),
                Pair(card::EIGHT, card::DIAMONDS) );
    EXPECT_THAT(std::make_pair(nine_diamonds.value_,
                               nine_diamonds.suit_),
                Pair(card::NINE, card::DIAMONDS) );
    EXPECT_THAT(std::make_pair(ten_diamonds.value_,
                               ten_diamonds.suit_),
                Pair(card::TEN, card::DIAMONDS) );
    EXPECT_THAT(std::make_pair(jack_diamonds.value_,
                               jack_diamonds.suit_),
                Pair(card::JACK, card::DIAMONDS) );
    EXPECT_THAT(std::make_pair(queen_diamonds.value_,
                               queen_diamonds.suit_),
                Pair(card::QUEEN, card::DIAMONDS) );
    EXPECT_THAT(std::make_pair(king_diamonds.value_,
                               king_diamonds.suit_),
                Pair(card::KING, card::DIAMONDS) );
    EXPECT_THAT(std::make_pair(ace_diamonds.value_,
                               ace_diamonds.suit_),
                Pair(card::ACE, card::DIAMONDS) );

    /*
    EXPECT_THAT(std::make_pair(two_clubs.value_,
                               three_hearts.suit_),
                Pair(card::THREE, card::CLUBS) );
    EXPECT_THAT(std::make_pair(three_clubs.value_,
                               three_hearts.suit_),
                Pair(card::THREE, card::CLUBS) );
    EXPECT_THAT(std::make_pair(four_clubs.value_,
                               three_hearts.suit_),
                Pair(card::THREE, card::CLUBS) );
    EXPECT_THAT(std::make_pair(five_clubs.value_,
                               three_hearts.suit_),
                Pair(card::THREE, card::CLUBS) );
    EXPECT_THAT(std::make_pair(six_clubs.value_,
                               three_hearts.suit_),
                Pair(card::THREE, card::CLUBS) );
    EXPECT_THAT(std::make_pair(seven_clubs.value_,
                               three_hearts.suit_),
                Pair(card::THREE, card::CLUBS) );
    EXPECT_THAT(std::make_pair(eight_clubs.value_,
                               three_hearts.suit_),
                Pair(card::THREE, card::CLUBS) );
    EXPECT_THAT(std::make_pair(nine_clubs.value_,
                               three_hearts.suit_),
                Pair(card::THREE, card::CLUBS) );
    EXPECT_THAT(std::make_pair(ten_clubs.value_,
                               three_hearts.suit_),
                Pair(card::THREE, card::CLUBS) );
    EXPECT_THAT(std::make_pair(jack_clubs.value_,
                               three_hearts.suit_),
                Pair(card::THREE, card::CLUBS) );
    EXPECT_THAT(std::make_pair(queen_clubs.value_,
                               three_hearts.suit_),
                Pair(card::THREE, card::CLUBS) );
    EXPECT_THAT(std::make_pair(king_clubs.value_,
                               three_hearts.suit_),
                Pair(card::THREE, card::CLUBS) );
    EXPECT_THAT(std::make_pair(ace_clubs.value_,
                               three_hearts.suit_),
                Pair(card::THREE, card::CLUBS) );
    EXPECT_THAT(std::make_pair(two_spades.value_,
                               three_hearts.suit_),
                Pair(card::THREE, card::SPADES) );
    EXPECT_THAT(std::make_pair(three_spades.value_,
                               three_hearts.suit_),
                Pair(card::THREE, card::SPADES) );
    EXPECT_THAT(std::make_pair(four_spades.value_,
                               three_hearts.suit_),
                Pair(card::THREE, card::SPADES) );
    EXPECT_THAT(std::make_pair(five_spades.value_,
                               three_hearts.suit_),
                Pair(card::THREE, card::SPADES) );
    EXPECT_THAT(std::make_pair(six_spades.value_,
                               three_hearts.suit_),
                Pair(card::THREE, card::SPADES) );
    EXPECT_THAT(std::make_pair(seven_spades.value_,
                               three_hearts.suit_),
                Pair(card::THREE, card::SPADES) );
    EXPECT_THAT(std::make_pair(eight_spades.value_,
                               three_hearts.suit_),
                Pair(card::THREE, card::SPADES) );
    EXPECT_THAT(std::make_pair(nine_spades.value_,
                               three_hearts.suit_),
                Pair(card::THREE, card::SPADES) );
    EXPECT_THAT(std::make_pair(ten_spades.value_,
                               three_hearts.suit_),
                Pair(card::THREE, card::SPADES) );
    EXPECT_THAT(std::make_pair(jack_spades.value_,
                               three_hearts.suit_),
                Pair(card::THREE, card::SPADES) );
    EXPECT_THAT(std::make_pair(queen_spades.value_,
                               three_hearts.suit_),
                Pair(card::THREE, card::SPADES) );
    EXPECT_THAT(std::make_pair(king_spades.value_,
                               three_hearts.suit_),
                Pair(card::THREE, card::SPADES) );
    EXPECT_THAT(std::make_pair(ace_spades.value_,
                               three_hearts.suit_),
                Pair(card::THREE, card::SPADES) );

    */

}
