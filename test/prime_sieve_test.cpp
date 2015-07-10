#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <prime_sieve.hpp>
#include <known_primes.hpp>

using ::testing::Eq;

class PrimeSieveTest : public ::testing::Test
{
public:
    PrimeSieveTest(){}
    ~PrimeSieveTest(){}

    virtual void SetUp(){}
    virtual void TearDown(){}
protected:
};

TEST_F(PrimeSieveTest, testAgainstKnownPrimes)
{
    size_t limit = 104730;
    prime_sieve primes(limit);
    known_primes known;

    for(size_t i = 0; i < limit; ++i)
    {
        EXPECT_THAT(known.set().find(i) != known.set().end(),
                    Eq(primes.is_prime(i)));
    }
}
