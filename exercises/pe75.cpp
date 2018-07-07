/*
 * pe75.cpp
 *
 *  Created on: 13 Jun 2015
 *      Author: evilquinn
 */

#include <pe75.hpp>
#include <iostream>
#include <map>
#include <utils.hpp>
#include <boost/multiprecision/cpp_int.hpp>
#include <cmath>

std::string& pe75::name() { return name_; }

struct triplet
{
    size_t a;
    size_t b;
    size_t c;
    size_t l;
};

bool operator< (const struct triplet& lhs, const struct triplet& rhs)
{
    return lhs.a == rhs.a ? lhs.b == rhs.b ? lhs.c < rhs.c : lhs.b < rhs.b : lhs.a < rhs.a;
}

void         pe75::run()
{
    /*
     *
     *
     * It turns out that 12 cm is the smallest length of wire that can be
     * bent to form an integer sided right angle triangle in exactly one way,
     * but there are many more examples:
     *
     * 12 cm: (3,4,5)
     * 24 cm: (6,8,10)
     * 30 cm: (5,12,13)
     * 36 cm: (9,12,15)
     * 40 cm: (8,15,17)
     * 48 cm: (12,16,20)
     *
     * In contrast, some lengths of wire, like 20 cm, cannot be bent to form
     * an integer sided right angle triangle, and other lengths allow more
     * than one solution to be found; for example, using 120 cm it is possible
     * to form exactly three different integer sided right angle triangles:
     *
     * 120 cm: (30,40,50), (20,48,52), (24,45,51)
     *
     * Given that L is the length of the wire, for how many values of
     * L ≤ 1,500,000 can exactly one integer sided right angle triangle be
     * formed?
     *
     */

    size_t result = 0;
    size_t plimit = 1000;
    size_t llimit = 1500000;

    std::map<size_t, size_t> resultm;
    std::set<struct triplet> resultt;
    for ( size_t p = 2; p < plimit; ++p )
    {
        for ( size_t q = 1; q < p; ++q )
        {
            if ( p & 0x1 && q & 0x1 )
            {
                continue;
            }

            size_t a = 2 * p * q;
            size_t b = p*p - q*q;
            size_t c = p*p + q*q;
            size_t l = a+b+c;
            if ( l > llimit )
            {
                break;
            }

            if ( a > b )
            {
                std::swap(a, b);
            }

            for ( size_t i = 1; l*i <= llimit; ++i )
            {
                resultt.insert({ a*i, b*i, c*i, l*i });
            }

        }
    }

    for ( const auto& e : resultt )
    {
        resultm[e.l] += 1;
    }

    for ( const auto& e : resultm )
    {
        if ( e.second == 1 )
        {
            ++result;
        }
    }

    std::cout << result << std::endl;

}
