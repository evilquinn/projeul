

#include <string.h>
#include <boost/dynamic_bitset.hpp>
#include <boost/foreach.hpp>
#include <cmath>
#include <iostream>
#include <prime_sieve.hpp>
#include <utils.hpp>

size_t gcd(size_t a, size_t b)
{
    return (b==0)?a:gcd(b,a%b);
}

std::vector<size_t> calc_prime_factors(size_t       num,
                                       prime_sieve& primes )
{
    // try dividing num by 2, then 3, then 5, etc, etc
    // each time a division works (no remainders), cache the
    // prime factor, and move on to working out the next prime
    // factor, starting dividing from the first prime again
    //
    size_t curr_num = num;
    std::vector<size_t> result;

    while ( curr_num > 1 )
    {
        if ( primes.is_prime( curr_num ) )
        {
            result.push_back( curr_num );
            break;
        }

        size_t try_prime = 2;
        while ( curr_num % try_prime != 0 )
        {
            try_prime = next_prime( primes, try_prime );
        }

        result.push_back( try_prime );
        curr_num /= try_prime;
    }

    return result;
}

int num_digits( long long unsigned n )
{
    int num_digits = 0;
    while ( n > 0 )
    {
        ++num_digits;
        n /= 10;
    }
    return num_digits;
}

size_t concat( size_t left, size_t right )
{
    int    mult   = pow( 10, num_digits( right ) );
    size_t result = left * mult;
    result += right;

    return result;
}

size_t next_prime( prime_sieve& primes, size_t n )
{
    if ( n < 2 )
    {
        return 2;
    }

    if ( ( n & 1 ) != 0u )
    {
        // odd
        n += 2;
    }
    else
    {
        ++n;
    }

    for ( ; !primes.is_prime( n ); n += 2 )
    {
    }
    return n;
}

bool is_prime( prime_sieve& primes, size_t n )
{
    if ( n < 2 )
    {
        // 0 and 1 aren't prime
        return false;
    }
    if ( n == 2 )
    {
        // 2 is prime
        return true;
    }

    for ( size_t i = 2; true; i = primes.next_prime( i ) )
    {
        // if any prime between 2 and sqrt(n) is a factor, then
        // n isn't prime
        if ( n % i == 0 )
        {
            return false;
        }
        if ( n / i < i )
        {
            // this means we've checked all prime i from 2 to sqrt(n)
            return true;
        }
    }
    return true;
}

void set_of_digits( size_t n, digit_set_t& digits )
{
    digits.clear();
    while ( n > 0 )
    {
        digits.insert( n % 10 );
        n /= 10;
    }
    return;
}

bool same_digits( size_t lhs, size_t rhs )
{
    std::multiset<uint8_t> lhs_digits;
    unsigned               expected_count = 0;
    unsigned               compare_count  = 0;
    while ( lhs > 0 )
    {
        lhs_digits.insert( lhs % 10 );
        lhs /= 10;
        ++expected_count;
    }

    while ( rhs > 0 )
    {
        auto it = lhs_digits.find( rhs % 10 );
        if ( it != lhs_digits.end() )
        {
            lhs_digits.erase( it );
            ++compare_count;
            rhs /= 10;
        }
        else
        {
            return false;
        }
    }

    return expected_count == compare_count;
}

size_t n_c_r( size_t n, size_t r )
{
    if ( r > n )
    {
        return 0;
    }

    if ( r == n )
    {
        return 1;
    }

    return ( n_c_r( n - 1, r ) + n_c_r( n - 1, r - 1 ) );
}

bool same_digits_old( size_t lhs, size_t rhs )
{
    digit_set_t lhs_digits;
    digit_set_t rhs_digits;
    set_of_digits( rhs, rhs_digits );
    set_of_digits( lhs, lhs_digits );

    return lhs_digits == rhs_digits;
}

size_t pattern_of_digits( size_t               num,
                          digit_count_map_t&   digit_count,
                          digit_pattern_map_t& digit_pattern )
{
    size_t working     = num;
    size_t mult_factor = 1;
    while ( working > 0 )
    {
        short curr = working % 10;
        ++digit_count[curr];
        digit_pattern[curr] += ( 1 * mult_factor );

        mult_factor *= 10;
        working /= 10;
    }

    return digit_count.size();
}

void mult_digit_array_by( int* mult, size_t mult_len, size_t mult_by )
{
    int add_to[mult_len];
    memset( add_to, 0, sizeof( add_to ) );

    for ( size_t i = 0; i < mult_by; ++i )
    {
        add_digit_arrays( add_to, mult_len, mult, mult_len );
    }

    for ( size_t i = 0; i < mult_len; ++i )
    {
        mult[i] = add_to[i];
    }
}

void add_digit_arrays( int*   add_to,
                       size_t add_to_len,
                       int*   add,
                       size_t add_len )
{
    int add_pos    = add_len - 1;
    int add_to_pos = add_to_len - 1;

    while ( add_pos >= 0 )
    {
        if ( add_to_pos >= 0 )
        {
            add_to[add_to_pos] += add[add_pos];

            size_t carry_on_pos = add_to_pos;
            while ( add_to[carry_on_pos] >= 10 )
            {
                add_to[carry_on_pos] %= 10;
                if ( carry_on_pos > 0 )
                {
                    --carry_on_pos;
                    ++add_to[carry_on_pos];
                }
            }
            --add_to_pos;
            --add_pos;
        }
    }
}
