#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <prime_sieve.hpp>
#include <known_primes.hpp>

using ::testing::Eq;

#define PRIME_SIEVE_TEST_LIMIT 104730

class PrimeSieveTest : public ::testing::Test
{
public:
    PrimeSieveTest() :
        primes_(PRIME_SIEVE_TEST_LIMIT)
    {
    }
    ~PrimeSieveTest(){}

    virtual void SetUp(){}
    virtual void TearDown(){}
protected:
    prime_sieve primes_;
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

TEST_F(PrimeSieveTest, testNextPrimeReturnsExpected)
{
    EXPECT_THAT(primes_.next_prime(1), Eq(2));
    EXPECT_THAT(primes_.next_prime(2), Eq(3));
    EXPECT_THAT(primes_.next_prime(3), Eq(5));
    EXPECT_THAT(primes_.next_prime(100), Eq(101));
    EXPECT_THAT(primes_.next_prime(1000), Eq(1009));
    EXPECT_THAT(primes_.next_prime(PRIME_SIEVE_TEST_LIMIT), Eq(-1));
}


TEST_F(PrimeSieveTest, testPrevPrimeReturnsExpected)
{
    EXPECT_THAT(primes_.prev_prime(1), Eq(0));
    EXPECT_THAT(primes_.prev_prime(2), Eq(0));
    EXPECT_THAT(primes_.prev_prime(3), Eq(2));
    EXPECT_THAT(primes_.prev_prime(100), Eq(97));
    EXPECT_THAT(primes_.prev_prime(1000), Eq(997));
    EXPECT_THAT(primes_.prev_prime(PRIME_SIEVE_TEST_LIMIT), Eq(104729));
}
