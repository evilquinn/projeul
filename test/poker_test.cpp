#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <poker.hpp>
#include <string>

using ::testing::Eq;
using ::testing::UnorderedElementsAre;
using ::testing::AllOf;
using ::testing::Field;

class PokerTest : public ::testing::Test
{
public:
    PokerTest()
    {
    }
    ~PokerTest(){}

    virtual void SetUp(){}
    virtual void TearDown(){}
protected:
};

TEST_F(PokerTest, testMakeHandWorksExpected)
{
    poker::hand player1;
    poker::hand player2;
    poker::make_hand("KH 2H 3H 4H 5H", player1);
    //poker::make_hand("JC 2D AH AC 5H", player2);

    EXPECT_THAT(player1, UnorderedElementsAre(
                             AllOf(Field(&card::value_, card::KING),
                                   Field(&card::suit_,  card::HEARTS)),
                             AllOf(Field(&card::value_, card::TWO),
                                   Field(&card::suit_,  card::HEARTS)),
                             AllOf(Field(&card::value_, card::THREE),
                                   Field(&card::suit_,  card::HEARTS)),
                             AllOf(Field(&card::value_, card::FOUR),
                                   Field(&card::suit_,  card::HEARTS)),
                             AllOf(Field(&card::value_, card::FIVE),
                                   Field(&card::suit_,  card::HEARTS))));

/*
    EXPECT_THAT(player2, UnorderedElementsAre(
                             AllOf(Field(&card::value_, card::JACK),
                                   Field(&card::suit_,  card::CLUBS)),
                             AllOf(Field(&card::value_, card::TWO),
                                   Field(&card::suit_,  card::DIAMONDS)),
                             AllOf(Field(&card::value_, card::ACE),
                                   Field(&card::suit_,  card::HEARTS)),
                             AllOf(Field(&card::value_, card::ACE),
                                   Field(&card::suit_,  card::CLUBS)),
                             AllOf(Field(&card::value_, card::FIVE),
                                   Field(&card::suit_,  card::HEARTS))));
                                   */
}

TEST_F(PokerTest, testScoredHandConstructorWorks)
{
    poker::hand player1;
    poker::make_hand("2H 3H 4H 5H 6H", player1);
    poker::scored_hand scored1(player1);
    EXPECT_THAT(scored1.rank_, Eq(poker::scored_hand::STRAIGHT_FLUSH));
    poker::make_hand("2H 3H 4H 5D 6H", player1);
    poker::scored_hand scored2(player1);
    EXPECT_THAT(scored2.rank_, Eq(poker::scored_hand::STRAIGHT));
    poker::make_hand("2H 3H 4H 5D 7H", player1);
    poker::scored_hand scored3(player1);
    EXPECT_THAT(scored3.rank_, Eq(poker::scored_hand::HIGH_CARD));
    poker::make_hand("2H 3H 4H 5H 7H", player1);
    poker::scored_hand scored4(player1);
    EXPECT_THAT(scored4.rank_, Eq(poker::scored_hand::FLUSH));
}

TEST_F(PokerTest, testScoredHandGameWorks)
{
    poker::hand p1;
    poker::hand p2;

    poker::make_hand("2H 3H 4H 5H 7H", p1);
    poker::make_hand("JH AH TH KH QH", p2);
    EXPECT_THAT(poker::game(p1, p2), Eq(1));

    poker::make_hand("JH AH TH KH QH", p1);
    poker::make_hand("JH AH TH KH QH", p2);
    EXPECT_THAT(poker::game(p1, p2), Eq(0));

    poker::make_hand("2H 2C 4H 5H AH", p1);
    poker::make_hand("2D 2S TH KH QH", p2);
    EXPECT_THAT(poker::game(p1, p2), Eq(-1));

    poker::make_hand("2H 2C 4H 5H 7H", p1);
    poker::make_hand("JH JD 4S 5S 7S", p2);
    EXPECT_THAT(poker::game(p1, p2), Eq(1));
}


