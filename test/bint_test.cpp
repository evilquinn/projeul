#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <boost/format.hpp>
#include <utils.hpp>
#include <bint.hpp>

using ::testing::Eq;
using ::testing::Lt;
using ::testing::Le;
using ::testing::Gt;
using ::testing::Ge;
using ::testing::Ne;
using ::testing::StrCaseEq;

class BintTest : public ::testing::Test
{
public:
    BintTest()
    {
    }
    ~BintTest(){}

    virtual void SetUp(){}
    virtual void TearDown(){}
protected:
};

TEST_F(BintTest, testBintConstructorWorksExpected)
{
    std::string hex_string("1a2b3c4d5e6f7a8b9c0d");
    bint stock(hex_string.c_str());
    std::stringstream os;
    os << stock;
    EXPECT_THAT(os.str(), StrCaseEq(hex_string));
}

TEST_F(BintTest, testBintConstructFromBinWorks)
{
    size_t bin_data = 0x10F01F11FF11FF11;
    const unsigned char* bin_ptr =
        reinterpret_cast<const unsigned char*>(&bin_data);
    bint stock(bin_ptr, sizeof(bin_data));
    std::stringstream os;
    os << stock;
    EXPECT_THAT(os.str(), StrCaseEq("10F01F11FF11FF11"));
    stock.print();
    std::cout << stock << std::endl;
    std::cout << boost::format("%x") % bin_data << std::endl;
}

TEST_F(BintTest, testBintConstructFromSizeTWorks)
{
    size_t n = 0x10F01F11FF11FF11;
    bint stock(n);
    std::stringstream os;
    os << stock;
    EXPECT_THAT(os.str(), StrCaseEq("10F01F11FF11FF11"));
    stock.print();
    std::cout << stock << std::endl;
    std::cout << boost::format("%x") % n << std::endl;
}

TEST_F(BintTest, testBintConstructFromSizeTWorks2)
{
    bint stock;
    EXPECT_THAT(stock, Eq(0));
    EXPECT_THAT(stock, Lt(1));
    EXPECT_THAT(stock, Ne(1));
}

TEST_F(BintTest, testBintCopyConstructor)
{
    bint from_bint("a1b2c3d4e5f6a7b8c9daebfc");
    bint to_bint(from_bint);
    std::stringstream from_os;
    from_os << from_bint;
    std::stringstream to_os;
    to_os << to_bint;
    EXPECT_THAT(to_os.str(), StrCaseEq(from_os.str()));
}

TEST_F(BintTest, testAssignmentOperator)
{
    bint stock;
    stock = 1234;
    EXPECT_THAT(stock, Eq(1234));

    bint next = 2345;
    EXPECT_THAT(next, Eq(2345));
    next = stock;
    EXPECT_THAT(next, Eq(stock));
}

TEST_F(BintTest, testIncrementDecrementOperators)
{
    bint stock;
    EXPECT_THAT(++stock, Eq(1));
    EXPECT_THAT(stock++, Eq(1));
    EXPECT_THAT(stock, Eq(2));

    EXPECT_THAT(--stock, Eq(1));
    EXPECT_THAT(stock--, Eq(1));
    EXPECT_THAT(stock, Eq(0));
}

TEST_F(BintTest, testBintEquality)
{
    const char* hex = "abcdef123456";
    bint lhs(hex);
    bint rhs(hex);

    EXPECT_THAT(lhs, Eq(rhs));
    EXPECT_TRUE(lhs.equals(rhs));
}

TEST_F(BintTest, testBintComparativeOps)
{
    const char* hex                       = "102030405060708090a0b0c0d0e0f0";
    const char* less_than_same_length_hex = "102020405060708090a0b0c0d0e0f0";
    const char* less_than_hex             =   "102020405060708090a0b0c0d0e0";
    bint gt(hex);
    bint ltsl(less_than_same_length_hex);
    bint lt(less_than_hex);

    EXPECT_TRUE(ltsl.less_than(gt));
    EXPECT_TRUE(lt.less_than(gt));
    EXPECT_THAT(ltsl, Lt(gt));
    EXPECT_THAT(lt, Lt(gt));
    EXPECT_THAT(ltsl, Le(gt));
    EXPECT_THAT(lt, Le(gt));
    EXPECT_THAT(ltsl, Le(ltsl));
    EXPECT_THAT(lt, Le(lt));
    EXPECT_THAT(ltsl, Ne(gt));
    EXPECT_THAT(lt, Ne(gt));
    EXPECT_THAT(gt, Gt(ltsl));
    EXPECT_THAT(gt, Gt(lt));
    EXPECT_THAT(gt, Ge(ltsl));
    EXPECT_THAT(gt, Ge(lt));
    EXPECT_THAT(gt, Ge(lt));
    EXPECT_THAT(gt, Ge(gt));
}

TEST_F(BintTest, testAssigmentOperator)
{
    bint rhs("abcdef");
    bint lhs = rhs;

    EXPECT_THAT(rhs, Eq(lhs));
}

TEST_F(BintTest, testSwapWorks)
{
    bint first("123456");
    bint second("abcdef");

    bint second_copy(second);
    bint first_copy(first);

    using std::swap;
    swap(first, second);

    EXPECT_THAT(first, Eq(second_copy));
    EXPECT_THAT(second, Eq(first_copy));
}

TEST_F(BintTest, testAdd)
{
    bint lhs(1234);
    bint rhs(2468);

    EXPECT_THAT(lhs.add(lhs), Eq(rhs));
}

TEST_F(BintTest, testBitwise)
{
    bint lhs(1234);
    bint rhs(2468);

    EXPECT_THAT(lhs ^ rhs, Eq(1234 ^ 2468));
    EXPECT_THAT(lhs & rhs, Eq(1234 & 2468));
    EXPECT_THAT(lhs | rhs, Eq(1234 | 2468));
    EXPECT_THAT(~lhs, Eq(~1234));
}

TEST_F(BintTest, testSubtract)
{
    bint lhs(1234);
    bint rhs(2468);

    EXPECT_THAT(lhs-rhs, Eq(1234-2468));
    EXPECT_THAT(rhs-lhs, Eq(2468-1234));

    uint8_t base = 0xaa;
    bint bshort(reinterpret_cast<unsigned char*>(&base), sizeof(base));

    EXPECT_THAT(bshort, Eq(base));
    EXPECT_THAT(bshort - lhs, Eq(base - 1234ul));
    EXPECT_THAT(lhs - bshort, Eq(1234 - base));
}

TEST_F(BintTest, testMultiply)
{
    bint lhs(1234);
    bint rhs(2468);

    EXPECT_THAT(lhs*rhs, Eq(1234*2468));
    EXPECT_THAT(rhs*lhs, Eq(2468*1234));
}

TEST_F(BintTest, testBitShift)
{
    bint lhs(1000);
    bint rhs(1234567);
    bint test1(1234567);
    bint test2(1234567);
    bint test3(192837);

    EXPECT_THAT(lhs.bitshift_left(11), Eq(1000 << 11));
    EXPECT_THAT(rhs.bitshift_left(15), Eq(1234567ul << 15));
    EXPECT_THAT(test1.bitshift_left(5), Eq(1234567ul << 5));
    EXPECT_THAT(test2.bitshift_left(8), Eq(1234567ul << 8));
    for ( size_t i = 0; i < 30; ++i )
    {
        EXPECT_THAT(test3 << i, Eq(192837ul << i));
    }

    bint rshift1(1234567);
    bint rshift2(1234567);
    bint rshift3(1234567123456712345ul);

    EXPECT_THAT(rshift1.bitshift_right(3), Eq(1234567ul >> 3));
    EXPECT_THAT(rshift2.bitshift_right(5), Eq(1234567ul >> 5));
    for ( size_t i = 0; i < 30; ++i )
    {
        EXPECT_THAT(rshift3 >> i, Eq(1234567123456712345ul >> i));
    }
}

TEST_F(BintTest, testDivision)
{
    size_t base = 1234567890;
    bint stock(base);

    EXPECT_THAT(stock / 7, Eq(base / 7));
    EXPECT_THAT(stock / 12, Eq(base / 12));
    EXPECT_THAT(stock / -34, Eq(base / -34));
    EXPECT_THAT(stock / 65478, Eq(base / 65478));
    EXPECT_THAT(stock / 999001122, Eq(base / 999001122));
    EXPECT_THAT(stock / 1234567890, Eq(base / 1234567890));

    EXPECT_THAT(stock % 7, Eq(base % 7));
    EXPECT_THAT(stock % 12, Eq(base % 12));
    EXPECT_THAT(stock % -34, Eq(base % -34));
    EXPECT_THAT(stock % 65478, Eq(base % 65478));
    EXPECT_THAT(stock % 999001122, Eq(base % 999001122));
    EXPECT_THAT(stock % 1234567890, Eq(base % 1234567890));
}




