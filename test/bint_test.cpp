#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <utils.hpp>
#include <bint.hpp>

using ::testing::Eq;

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
    bint a("123456");
    std::cout << a << std::endl;
    a.print();
}
