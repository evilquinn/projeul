#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <boost/format.hpp>
#include <utils.hpp>
#include <bint.hpp>

using ::testing::Eq;
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
    EXPECT_THAT(os.str(), StrCaseEq("11ff11ff111ff010"));
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
