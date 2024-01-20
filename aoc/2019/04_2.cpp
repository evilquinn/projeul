/**
 * An Elf just remembered one more important detail: the two adjacent matching digits are not
 * part of a larger group of matching digits.
 *
 * Given this additional criterion, but still ignoring the range rule, the following are now true:
 *
 * 112233 meets these criteria because the digits never decrease and all repeated digits are exactly two digits long.
 * 123444 no longer meets the criteria (the repeated 44 is part of a larger group of 444).
 * 111122 meets the criteria (even though 1 is repeated more than twice, it still contains a double 22).
 * How many different passwords within the range given in your puzzle input meet all of the criteria?
 *
 * Your puzzle input is still 147981-691423.
 *
 */

#include <iostream>
#include <vector>
#include <array>
#include <cstdint>

using password = std::array<uint8_t, 6>;

std::ostream& operator<< (std::ostream& os, const password& p)
{
    for ( int digit : p )
    {
        os << digit;
    }
    return os;
}

void advance(password& p)
{
    bool do_bump = true;
    for ( uint8_t idx = 0; idx < p.size() - 1; ++idx )
    {
        if ( p[idx] >= p[idx+1] )
        {
            if ( p[idx] != p[idx+1] )
            {
                do_bump = false;
                p[idx+1] = p[idx];
            }
        }
    }

    while(true)
    {
        if ( do_bump )
        {
            for ( uint8_t idx = p.size() - 1; idx < p.size(); --idx )
            {
                if ( p[idx] == 9 )
                {
                    continue;
                }

                ++p[idx];
                for ( uint8_t jdx = idx+1; jdx < p.size(); ++jdx )
                {
                    p[jdx] = p[idx];
                }
                break;
            }
        }
        // figure out meets pair criteria
        int count = 0;
        uint8_t last = p[0];
        for ( uint8_t i = 1; i < p.size(); ++i )
        {
            if ( p[i] == last )
            {
                ++count;
            }
            else if ( count == 1 )
            {
                break;
            }
            else
            {
                count = 0;
                last = p[i];
            }
        }
        if ( count == 1 ) return;
        do_bump = true;
    }
}

int main()
{
    std::vector<std::pair<password, password> > data = {
        { { 3, 3, 9, 9, 9, 9 }, { 3, 4, 4, 4, 5, 5 } }
    };

    for ( auto&& datum : data )
    {
        std::cout << "a: " << datum.first;
        advance(datum.first);
        std::cout << ", n: " << datum.first;
        if ( datum.first != datum.second )
        {
            std::cout << ", exp: " << datum.second << " : FAIL\n";
        }
        else
        {
            std::cout << " : OK\n";
        }
    }

    password limit = { 6, 9, 1, 4, 2, 3 };
    password candidate = { 1, 4, 7, 9, 8, 1 };
    int result = -1;
    do
    {
        ++result;
        advance(candidate);
        //std::cout << candidate << "\n";
    }
    while ( candidate <= limit );
    std::cout << "result: " << result << "\n";

    return 0;

}
