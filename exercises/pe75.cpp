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
    size_t limit = 1500000;

    std::map<struct triplet, size_t> resultm;

    for( struct triplet t = { 3 }; t.a <= limit; ++t.a )
    {
        if ( t.a & 0x01 )
        {
            t.b = (t.a*t.a - 1)/2;
            t.c = t.b + 1;
        }
        else
        {
            t.b = ( t.a*t.a / 4 ) - 1;

            if ( t.a > t.b )
            {
                continue;
            }

            t.c = t.b + 2;
        }

        t.l = t.a + t.b + t.c;

        for ( size_t i = 1; i < limit; ++i )
        {
            if ( t.l*i <= limit )
            {
                struct triplet td = { t.a*i, t.b*i, t.c*i, t.l*i };
                resultm[td] += 1;
                //std::cout << td.l << ": " << td.a << ", " << td.b << ", " << td.c << "\n";
            }
            else
            {
                break;
            }
        }

    }

    std::map<size_t, size_t> rr;
    for ( auto e: resultm )
    {
        rr[e.first.l] += 1;

    }

    for ( auto e: rr )
    {
        if ( e.second == 1 )
        {
            ++result;
        }
        //std::cout << e.first << ": " << e.second << "\n";
    }

    std::cout << result << std::endl;

}
