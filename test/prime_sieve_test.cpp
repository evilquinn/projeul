#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <known_primes.hpp>
#include <prime_sieve.hpp>
#include <utils.hpp>

using ::testing::Eq;

#define PRIME_SIEVE_TEST_LIMIT 100000

class PrimeSieveTest : public ::testing::Test
{
public:
    PrimeSieveTest() : primes_( PRIME_SIEVE_TEST_LIMIT ) {}
    ~PrimeSieveTest() {}
    virtual void SetUp() {}
    virtual void TearDown() {}
protected:
    prime_sieve primes_;
};

TEST_F( PrimeSieveTest, testAgainstKnownPrimes )
{
    known_primes known;

    for ( size_t i = 0; i <= KNOWN_PRIMES_LIMIT; ++i )
    {
        // given that primes_.limit() < KNOWN_PRIMES_LIMIT, this therefore
        // tests the is prime algorithm for numbers > primes_.limit()
        EXPECT_THAT( known.set().find( i ) != known.set().end(),
                     Eq( primes_.is_prime( i ) ) );
        EXPECT_THAT( known.set().find( i ) != known.set().end(),
                     Eq( is_prime( primes_, i ) ) );
    }

    prime_sieve small_sieve( 10 );
    EXPECT_TRUE( small_sieve.is_prime( 113 ) );
}

TEST_F( PrimeSieveTest, testNextPrimeReturnsExpected )
{
    EXPECT_THAT( primes_.next_prime( 1 ), Eq( 2 ) );
    EXPECT_THAT( primes_.next_prime( 2 ), Eq( 3 ) );
    EXPECT_THAT( primes_.next_prime( 3 ), Eq( 5 ) );
    EXPECT_THAT( primes_.next_prime( 100 ), Eq( 101 ) );
    EXPECT_THAT( primes_.next_prime( 1000 ), Eq( 1009 ) );
    EXPECT_THAT( primes_.next_prime( PRIME_SIEVE_TEST_LIMIT ), Eq( 100003 ) );

    EXPECT_THAT( next_prime( primes_, 1 ), Eq( 2 ) );
    EXPECT_THAT( next_prime( primes_, 2 ), Eq( 3 ) );
    EXPECT_THAT( next_prime( primes_, 3 ), Eq( 5 ) );
    EXPECT_THAT( next_prime( primes_, 100 ), Eq( 101 ) );
    EXPECT_THAT( next_prime( primes_, 1000 ), Eq( 1009 ) );
    EXPECT_THAT( next_prime( primes_, PRIME_SIEVE_TEST_LIMIT ),
                 Eq( 100003 ) );

    prime_sieve small_sieve( 10 );
    EXPECT_THAT( next_prime( small_sieve, 110 ), Eq( 113 ) );
    EXPECT_THAT( next_prime( small_sieve, PRIME_SIEVE_TEST_LIMIT ),
                 Eq( 100003 ) );
    EXPECT_THAT( small_sieve.next_prime( PRIME_SIEVE_TEST_LIMIT ),
                 Eq( 100003 ) );
}

TEST_F( PrimeSieveTest, testPrevPrimeReturnsExpected )
{
    EXPECT_THAT( primes_.prev_prime( 1 ), Eq( 0 ) );
    EXPECT_THAT( primes_.prev_prime( 2 ), Eq( 0 ) );
    EXPECT_THAT( primes_.prev_prime( 3 ), Eq( 2 ) );
    EXPECT_THAT( primes_.prev_prime( 100 ), Eq( 97 ) );
    EXPECT_THAT( primes_.prev_prime( 1000 ), Eq( 997 ) );
    EXPECT_THAT( primes_.prev_prime( PRIME_SIEVE_TEST_LIMIT ), Eq( 99991 ) );
}

TEST_F( PrimeSieveTest, testSumRangeReturnsExpected )
{
    size_t num_in_range;
    EXPECT_THAT( primes_.sum_range( 0, 0, num_in_range ), Eq( 0 ) );
    EXPECT_THAT( primes_.sum_range( 1, 0, num_in_range ), Eq( 0 ) );
    EXPECT_THAT( primes_.sum_range( 2, 1, num_in_range ), Eq( 0 ) );
    EXPECT_THAT( primes_.sum_range( 2, 2, num_in_range ), Eq( 2 ) );
    EXPECT_THAT( primes_.sum_range( 2, 3, num_in_range ), Eq( 5 ) );
    EXPECT_THAT( primes_.sum_range( 2, 7, num_in_range ), Eq( 17 ) );
    EXPECT_THAT( primes_.sum_range( 2, 10, num_in_range ), Eq( 17 ) );
    EXPECT_THAT( primes_.sum_range( 2, 12, num_in_range ), Eq( 28 ) );
    EXPECT_THAT( primes_.sum_range( 2, PRIME_SIEVE_TEST_LIMIT, num_in_range ),
                 Eq( 454396537 ) );
    EXPECT_THAT(
        primes_.sum_range(
            PRIME_SIEVE_TEST_LIMIT, PRIME_SIEVE_TEST_LIMIT, num_in_range ),
        Eq( 0 ) );
}

TEST_F( PrimeSieveTest, testShitSumRangeReturnsExpected )
{
    std::deque<size_t> sumees;
    EXPECT_THAT( primes_.shit_sum_range( 0, 0, sumees ), Eq( 0 ) );
    EXPECT_THAT( primes_.shit_sum_range( 1, 0, sumees ), Eq( 0 ) );
    EXPECT_THAT( primes_.shit_sum_range( 2, 1, sumees ), Eq( 0 ) );
    EXPECT_THAT( primes_.shit_sum_range( 2, 2, sumees ), Eq( 2 ) );
    EXPECT_THAT( primes_.shit_sum_range( 2, 3, sumees ), Eq( 5 ) );
    EXPECT_THAT( primes_.shit_sum_range( 2, 7, sumees ), Eq( 17 ) );
    EXPECT_THAT( primes_.shit_sum_range( 2, 10, sumees ), Eq( 17 ) );
    EXPECT_THAT( primes_.shit_sum_range( 2, 12, sumees ), Eq( 28 ) );
    EXPECT_THAT( primes_.shit_sum_range( 2, PRIME_SIEVE_TEST_LIMIT, sumees ),
                 Eq( 454396537 ) );
    EXPECT_THAT( primes_.shit_sum_range(
                     PRIME_SIEVE_TEST_LIMIT, PRIME_SIEVE_TEST_LIMIT, sumees ),
                 Eq( 0 ) );
}

TEST_F( PrimeSieveTest, testNumInRangeReturnsExpected )
{
    EXPECT_THAT( primes_.num_in_range( 0, 0 ), Eq( 0 ) );
    EXPECT_THAT( primes_.num_in_range( 0, 1 ), Eq( 0 ) );
    EXPECT_THAT( primes_.num_in_range( 1, 1 ), Eq( 0 ) );
    EXPECT_THAT( primes_.num_in_range( 1, 2 ), Eq( 1 ) );
    EXPECT_THAT( primes_.num_in_range( 0, 2 ), Eq( 1 ) );
    EXPECT_THAT( primes_.num_in_range( 0, 3 ), Eq( 2 ) );
    EXPECT_THAT( primes_.num_in_range( 1, 3 ), Eq( 2 ) );
    EXPECT_THAT( primes_.num_in_range( 2, 3 ), Eq( 2 ) );
    EXPECT_THAT( primes_.num_in_range( 2, 5 ), Eq( 3 ) );
    EXPECT_THAT( primes_.num_in_range( 2, 10 ), Eq( 4 ) );
}
