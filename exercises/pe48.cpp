/*
 * pe48.cpp
 *
 *  Created on: 13 Jun 2015
 *      Author: evilquinn
 */

#include <pe48.hpp>
#include <boost/multiprecision/cpp_int.hpp>
#include <iostream>

std::string& pe48::name() { return name_; }
void         pe48::run()
{
    /*
     * The series:
     *
     *     1^1 + 2^2 + 3^3 + ... + 10^10 = 10405071317
     *
     * Find the last ten digits of the series:
     *
     *     1^1 + 2^2 + 3^3 + ... + 1000^1000
     */

    boost::multiprecision::cpp_int result = 0;
    for ( size_t i = 1; i <= 1000; ++i )
    {
        // i*i = i + i + i + ... + i ( i times )
        // i^i = i * i * i * ... * i ( i times )
        //
        // work out i * i
        boost::multiprecision::cpp_int mult = i;
        mult = boost::multiprecision::pow(mult, i);
        result += mult;
    }

    std::cout << name() << " " << result << std::endl;

}
