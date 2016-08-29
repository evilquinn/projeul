#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <utils.hpp>
#include <gint.hpp>

using ::testing::Eq;

class GintTest : public ::testing::Test
{
public:
    GintTest()
    {
    }
    ~GintTest(){}

    virtual void SetUp(){}
    virtual void TearDown(){}
protected:
};

TEST_F(GintTest, testGintConstructorWorksExpected)
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

    size_t largest = static_cast<size_t>(-1);
    EXPECT_EQ(largest, gint(largest));
}


TEST_F(GintTest, testGintIsPalindromeWorksExpected)
{
    gint p1(1234);
    gint p2(1221);
    gint p3(1);
    EXPECT_FALSE(p1.is_palindrome());
    EXPECT_TRUE(p2.is_palindrome());
    EXPECT_TRUE(p3.is_palindrome());
}

TEST_F(GintTest, testGintMultiplyBy)
{
    gint g1(1234);
    g1.multiply_by(28456212);
    g1.print();
    size_t expected = 1234ll * 28456212;
    std::cout << expected << std::endl;
}

TEST_F(GintTest, testGintOperatorEquals)
{
    EXPECT_EQ(gint(1), 1);
    EXPECT_EQ(gint(1234), 1234);
    EXPECT_EQ(gint(3957264503), 3957264503);
    EXPECT_EQ(gint(81792879281171948), 81792879281171948);
    EXPECT_NE(gint(1), 1234);
    EXPECT_NE(gint(1234), 1);
    EXPECT_NE(gint(395764503), 3957264503);
    EXPECT_NE(gint(81692879281171948), 81792879281171948);
    EXPECT_NE(gint(81792879281171948), 81792879281172948);
    EXPECT_NE(gint(81792879281171948), 8179287928117948);
    EXPECT_NE(gint(81892879281171948), 81792879281171948);
}


TEST_F(GintTest, testGintOperatorLessThan)
{
    EXPECT_LT(gint(1), 2);
    EXPECT_LT(gint(1224), 1234);
    EXPECT_LT(gint(3954503), 3957264503);
    EXPECT_LT(gint(817929281171948), 81792879281171948);
}



TEST_F(GintTest, testGintOperators)
{
    EXPECT_LE(gint(1), 1);
    EXPECT_LE(gint(1234), 1234);
    EXPECT_LE(gint(3957264503), 3957264503);
    EXPECT_LE(gint(81792879281171948), 81792879281171948);
}


TEST_F(GintTest, testGintIncrementDecrementWorks)
{
    gint gi(-5);
    --gi;
    --gi;
    EXPECT_EQ(--gi, -8);
    ++gi;
    ++gi;
    ++gi;
    ++gi;
    ++gi;
    ++gi;
    ++gi;
    EXPECT_EQ(++gi, 0);
    EXPECT_EQ(gi++, 0);
    ++gi;
    ++gi;
    ++gi;
    ++gi;
    ++gi;
    EXPECT_EQ(--gi, 5);
    EXPECT_EQ(gi--, 5);
    --gi;
    --gi;
    --gi;
    EXPECT_EQ(--gi, 0);
    EXPECT_EQ(gi--, 0);
    --gi;
    EXPECT_EQ(--gi, -3);
}



TEST_F(GintTest, testGintAddSubtractWorks)
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

    EXPECT_EQ(gint(100) + 200, 100 + 200);
    EXPECT_EQ(gint(100) + 100, 100 + 100);
    EXPECT_EQ(gint(200) + 100, 200 + 100);
    EXPECT_EQ(gint(100) + (-200), 100 + (-200));
    EXPECT_EQ(gint(100) + (-100), 100 + (-100));
    EXPECT_EQ(gint(200) + (-100), 200 + (-100));
    EXPECT_EQ(gint(-100) + 200, (-100) + 200);
    EXPECT_EQ(gint(-100) + 100, (-100) + 100);
    EXPECT_EQ(gint(-200) + 100, (-200) + 100);
    EXPECT_EQ(gint(-100) + (-200), (-100) + (-200));
    EXPECT_EQ(gint(-100) + (-100), (-100) + (-100));
    EXPECT_EQ(gint(-200) + (-100), (-200) + (-100));
    EXPECT_EQ(gint(100) - 200, 100 - 200);
    EXPECT_EQ(gint(100) - 100, 100 - 100);
    EXPECT_EQ(gint(200) - 100, 200 - 100);
    EXPECT_EQ(gint(100) - (-200), 100 - (-200));
    EXPECT_EQ(gint(100) - (-100), 100 - (-100));
    EXPECT_EQ(gint(200) - (-100), 200 - (-100));
    EXPECT_EQ(gint(-100) - 200, (-100) - 200);
    EXPECT_EQ(gint(-100) - 100, (-100) - 100);
    EXPECT_EQ(gint(-200) - 100, (-200) - 100);
    EXPECT_EQ(gint(-100) - (-200), (-100) - (-200));
    EXPECT_EQ(gint(-100) - (-100), (-100) - (-100));
    EXPECT_EQ(gint(-200) - (-100), (-200) - (-100));

    gint self(1234);
    EXPECT_EQ(self.subtract(self), 0);
    self = 1234;
    EXPECT_EQ(self.add_reverse_of(self), 5555);
    EXPECT_EQ(self.add_reverse_of(9999999999), 9999999999 + 5555);
    EXPECT_EQ(self.add_reverse_of(12), 9999999999 + 5555 + 21);
}


TEST_F(GintTest, testGintMultiplyWorks)
{
    EXPECT_EQ(gint(100) * 0, 0);
    EXPECT_EQ(gint(100) * 200, 100 * 200);
    EXPECT_EQ(gint(100) * 100, 100 * 100);
    EXPECT_EQ(gint(200) * 100, 200 * 100);
    EXPECT_EQ(gint(100) * (-200), 100 * (-200));
    EXPECT_EQ(gint(100) * (-100), 100 * (-100));
    EXPECT_EQ(gint(200) * (-100), 200 * (-100));
    EXPECT_EQ(gint(-100) * 200, (-100) * 200);
    EXPECT_EQ(gint(-100) * 100, (-100) * 100);
    EXPECT_EQ(gint(-200) * 100, (-200) * 100);
    EXPECT_EQ(gint(-100) * (-200), (-100) * (-200));
    EXPECT_EQ(gint(-100) * (-100), (-100) * (-100));
    EXPECT_EQ(gint(-200) * (-100), (-200) * (-100));

    gint self(1234);
    EXPECT_EQ(self.multiply_by(self), 1234 * 1234);
    EXPECT_EQ(gint(999) * 999999, 999 * 999999);
    EXPECT_EQ(gint(999) * 999, 999 * 999);
    EXPECT_EQ(gint(999999) * 999, 999 * 999999);
}

TEST_F(GintTest, testSumDigitsWorks)
{
    EXPECT_EQ(gint(1234).sum_digits(), 10);
}



TEST_F(GintTest, testGintStreamOutWorks)
{
    gint g1(1234);
    std::cout << g1 * 2 << std::endl;
    std::cout << g1 - 2 << std::endl;
    std::cout << g1 - 2000 << std::endl;

}
