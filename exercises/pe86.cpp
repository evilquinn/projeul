/*
 * pe86.cpp
 *
 *  Created on: 13 Jun 2015
 *      Author: evilquinn
 */

#include <iostream>
#include <pe86.hpp>
#include <utils.hpp>

namespace
{  // anonymous

}  // namespace

std::string& pe86::name() { return name_; }
void pe86::run()
{
    long limit              = 1000000;
    long goal               = 1000000;
    long n                  = 1;
    std::vector<long> terms = { 1 };
    for ( ; n <= limit; ++n )
    {
        long subee = 1;
        long k     = 0;
        terms.push_back( 0 );
        while ( subee <= n )
        {
            long sign = ( k % 4 > 1 ) ? -1 : 1;
            terms[n] += sign * terms[n - subee];
            terms[n] %= goal;
            ++k;
            long next = ( k % 2 == 0 ) ? k / 2 + 1 : -1 * ( k / 2 + 1 );
            subee     = next * ( 3 * next - 1 ) / 2;
        }
        if ( terms[n] == 0 || n == limit )
        {
            std::cout << n << ", " << terms[n] << std::endl;
            break;
        }
    }
    size_t result = 0;
    std::cout << "result: " << result << std::endl;
}

/*
 *
 * A spider, S, sits in one corner of a cuboid room, measuring 6 by 5 by 3,
 * and a fly, F, sits in the opposite corner. By travelling on the surfaces
 * of the room the shortest "straight line" distance from S to F is 10 and
 * the path is shown on the diagram.
 *
 * However, there are up to three "shortest" path candidates for any
 * given cuboid and the shortest route doesn't always have integer length.
 *
 * It can be shown that there are exactly 2060 distinct cuboids, ignoring
 * rotations, with integer dimensions, up to a maximum size of M by M by M,
 * for which the shortest route has integer length when M = 100. This is the
 * least value of M for which the number of solutions first exceeds two
 * thousand; the number of solutions when M = 99 is 1975.
 *
 * Find the least value of M such that the number of solutions first
 * exceeds one million.
 *
 */
