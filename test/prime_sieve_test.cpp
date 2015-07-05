#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <prime_sieve/prime_sieve.hpp>
#include <known_primes.hpp>

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
    size_t limit = 104730;
    prime_sieve primes(limit);
    std::set<size_t>::iterator past_the_end = known_primes.end();

    for(size_t i = 0; i < limit; ++i)
    {
        if(known_primes.find(i) != past_the_end)
        {
            EXPECT_THAT(true, Eq(primes.is_prime(i)));
        }
        else
        {
            EXPECT_THAT(false, Eq(primes.is_prime(i)));
        }
    }
}
