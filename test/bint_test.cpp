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
    size_t n = 1001;
    bint stock(n);
    std::stringstream os;
    os << stock;
    EXPECT_THAT(os.str(), StrCaseEq("00000000000003e9"));
    stock.print();
    std::cout << stock << std::endl;
    std::cout << boost::format("%016x") % n << std::endl;
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


