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
    poker::make_hand("JC 2D AH AC 5H", player2);

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
}

