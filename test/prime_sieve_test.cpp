#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <prime_sieve/prime_sieve.hpp>

using ::testing::Eq;

class PrimeSieveTest : public ::testing::Test
{
protected:
    PrimeSieveTest(){}
    ~PrimeSieveTest(){}

    virtual void SetUp(){}
    virtual void TearDown(){}

};

TEST_F(PrimeSieveTest, constructor_createsEmptyList)
{
    EXPECT_THAT(0, Eq(size_t(0)));
}
