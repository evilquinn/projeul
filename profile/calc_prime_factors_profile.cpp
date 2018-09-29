#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <prime_sieve.hpp>
#include <utils.hpp>

#define CALC_PRIME_FACTORS_PROFILE_NUMBER 10000000

class CalcPrimeFactorsProfile : public ::testing::Test
{
protected:
    CalcPrimeFactorsProfile()
        : primes( new prime_sieve( CALC_PRIME_FACTORS_PROFILE_NUMBER ) )
    {
    }
    ~CalcPrimeFactorsProfile() override { delete primes; }
    prime_sieve* primes;
};

TEST_F( CalcPrimeFactorsProfile, profileCalcingPrimeFactors )
{
    std::vector<size_t> prime_factors;
    for ( size_t i = 100000; i <= 130000; ++i )
    {
        calc_prime_factors( i, prime_factors, *primes );
    }
    calc_prime_factors( 100003, prime_factors, *primes );
}
