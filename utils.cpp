

#include <utils.hpp>
#include <string.h>
#include <prime_sieve.hpp>
#include <boost/foreach.hpp>


int num_digits(long long unsigned n)
{
    int num_digits = 0;
    while(n>0)
    {
        ++num_digits;
        n/=10;
    }
    return num_digits;
}

int num_digits_matching(long long unsigned n, short d)
{
    int num_digits = 0;
    while(n>0)
    {
        int curr_digit = n%10;
        if(curr_digit == d)
        {
            ++num_digits;
        }
        n/=10;
    }
    return num_digits;
}


size_t pattern_of_digits(size_t num,
                         digit_count_map_t& digit_count,
                         digit_pattern_map_t& digit_pattern)
{
    size_t working = num;
    size_t mult_factor = 1;
    while ( working > 0 )
    {
        short curr = working % 10;
        ++digit_count[curr];
        digit_pattern[curr] += (1 * mult_factor);

        mult_factor *= 10;
        working /= 10;
    }

    return digit_count.size();
}


size_t next_prime(size_t i, prime_sieve& primes)
{
    size_t primes_limit = primes.limit();
    if ( i >= primes_limit )
    {
        return 0;
    }

    do
    {
        ++i;
    }
    while( i < primes_limit && ! primes.is_prime(i) );

    return i;
}

void num_to_digit_array(size_t  num,
                        int*&   digit_array,
                        size_t& digit_array_length)
{
    digit_array_length = num_digits(num);
    digit_array = new int[digit_array_length];
    for(int i = digit_array_length - 1; i >= 0; --i)
    {
        digit_array[i] = num % 10;
        num /= 10;
    }
}

void add_to_digit_array(int* add_to, size_t add_to_len, size_t add)
{
    int add_to_pos = add_to_len - 1;

    while(add>0)
    {
        if(add_to_pos >= 0)
        {
            add_to[add_to_pos] += add % 10;

            size_t carry_on_pos = add_to_pos;
            while(add_to[carry_on_pos] >= 10)
            {
                add_to[carry_on_pos] %= 10;
                if(carry_on_pos > 0)
                {
                    --carry_on_pos;
                    ++add_to[carry_on_pos];
                }
                else
                {
                    // no more array to carry on with
                    break;
                }
            }
            --add_to_pos;
            add /= 10;
        }
        else
        {
            break;
        }
    }
}

void mult_digit_array_by(int* mult, size_t mult_len, size_t mult_by)
{
    int add_to[mult_len];
    memset(add_to, 0, sizeof(add_to));

    for(size_t i = 0; i < mult_by; ++i)
    {
        add_digit_arrays(add_to, mult_len, mult, mult_len);
    }

    for(size_t i = 0; i < mult_len; ++i)
    {
        mult[i] = add_to[i];
    }
}



void add_digit_arrays(int* add_to, size_t add_to_len, int* add, size_t add_len)
{

    int add_pos = add_len - 1;
    int add_to_pos = add_to_len - 1;

    while(add_pos >= 0)
    {
        if(add_to_pos >= 0)
        {
            add_to[add_to_pos] += add[add_pos];

            size_t carry_on_pos = add_to_pos;
            while(add_to[carry_on_pos] >= 10)
            {
                add_to[carry_on_pos] %= 10;
                if(carry_on_pos > 0)
                {
                    --carry_on_pos;
                    ++add_to[carry_on_pos];
                }
                else
                {
                    // no more array to carry on with
                    break;
                }
            }
            --add_to_pos;
            --add_pos;
        }
        else
        {
            // no array to add to, finished
            break;
        }
    }
}


