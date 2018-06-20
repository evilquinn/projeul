/*
 * pe66.cpp
 *
 *  Created on: 13 Jun 2015
 *      Author: evilquinn
 */

#include "pe66.hpp"
#include <iostream>
#include <vector>
#include <cmath>
#include <boost/multiprecision/cpp_int.hpp>

boost::multiprecision::cpp_int d_y_squared_plus_one(int d, int y)
{
    boost::multiprecision::cpp_int result = y;
    result *= result;
    result *= d;
    result += 1;
    return result;
}

bool pe66::is_square(boost::multiprecision::cpp_int n)
{
    boost::multiprecision::cpp_int test = boost::multiprecision::sqrt(n);
    return (test * test) == n;
}


std::string& pe66::name() { return name_; }
void         pe66::run()
{
    /*
     * Consider quadratic Diophantine equations of the form:
     *
     * x^2 – Dy^2 = 1
     *
     * For example, when D=13, the minimal solution in x is
     *   649^2 – 13×180^2 = 1.
     *
     * It can be assumed that there are no solutions in positive integers
     * when D is square.
     *
     * By finding minimal solutions in x for D = {2, 3, 5, 6, 7}, we obtain
     * the following:
     *
     *     3^2 – 2×2^2 = 1
     *     2^2 – 3×1^2 = 1
     * (!) 9^2 – 5×4^2 = 1
     *     5^2 – 6×2^2 = 1
     *     8^2 – 7×3^2 = 1
     *
     * Hence, by considering minimal solutions in x for D ≤ 7, the largest
     * x is obtained when D = 5.
     *
     * Find the value of D ≤ 1000 in minimal solutions of x for which the
     * largest value of x is obtained.
     *
     */

    boost::multiprecision::cpp_int biggest_x = 0;
    size_t result = 0;
    size_t limit = 1000;

    for ( size_t D = 2; D <= limit; ++D )
    {
        if ( is_square(D) )
        {
            continue;
        }
        int y = 1;
        boost::multiprecision::cpp_int dysqrdplus1 = 0;
        while(true)
        {
            dysqrdplus1 = d_y_squared_plus_one(D, y);
            if ( is_square( dysqrdplus1 ) )
            {
                break;
            }
            ++y;
        }
        boost::multiprecision::cpp_int x =
            boost::multiprecision::sqrt(dysqrdplus1);
        std::cout << "D=" << D << ", y=" << y << ", x=" << x;
        if ( x > biggest_x )
        {
            result = D;
            biggest_x = x;
            std::cout << ", BIGGEST!";
        }
        std::cout << "\n";
    }

    std::cout << "result : " << result << std::endl;
}
