/**
 * --- Day 4: Secure Container ---
 *  You arrive at the Venus fuel depot only to discover it's protected by a password.
 *  The Elves had written the password on a sticky note, but someone threw it out, obvs.
 *
 *  However, they do remember a few key facts about the password:
 *
 *  It is a six-digit number.
 *  The value is within the range given in your puzzle input.
 *  Two adjacent digits are the same (like 22 in 122345).
 *  Going from left to right, the digits never decrease; they only ever increase or stay the same
 *  (like 111123 or 135679).
 *
 *  Other than the range rule, the following are true:
 *
 *  111111 meets these criteria (double 11, never decreases).
 *  223450 does not meet these criteria (decreasing pair of digits 50).
 *  123789 does not meet these criteria (no double).
 *  How many different passwords within the range given in your puzzle input meet these criteria?
 *
 *  Your puzzle input is 147981-691423.
 *
 */

#include <iostream>
#include <vector>
#include <array>

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
    bool done = false;
    uint8_t consec = p.size();
    for ( uint8_t idx = 0; idx < p.size() - 1; ++idx )
    {
        if ( p[idx] >= p[idx+1] )
        {
            if ( p[idx] != p[idx+1] )
            {
                done = true;
                p[idx+1] = p[idx];
            }
            if ( consec == p.size() ) consec = idx+1;
        }
    }
    if ( done ) return;

    do
    {
        for ( uint8_t idx = p.size() - 1; idx < p.size(); --idx )
        {
            if ( p[idx] == 9 )
            {
                continue;
            }

            ++p[idx];
            if ( consec == idx ) consec = p.size();
            for ( uint8_t jdx = idx+1; jdx < p.size(); ++jdx )
            {
                if ( consec == p.size() ) consec = jdx;
                p[jdx] = p[idx];
            }
            break;
        }
    }
    while ( consec == p.size() );
}

int main()
{
    std::vector<std::pair<password, password> > data = {
        { { 3, 3, 9, 9, 9, 9 }, { 3, 4, 4, 4, 4, 4 } }
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
