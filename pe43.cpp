/*
 * pe43.cpp
 *
 *  Created on: 13 Jun 2015
 *      Author: evilquinn
 */

#include "pe43.hpp"
#include <iostream>
#include <cmath>
#include <map>
#include <set>
#include <boost/foreach.hpp>
#include "utils.hpp"
#include <stdio.h>
#include <ctype.h>

bool has_subdivisibility_property(size_t* nums, size_t num_nums);
size_t num_array_to_num(size_t* nums, size_t num_nums);

std::string& pe43::name()
{
    return name_;
}

void pe43::run()
{
    /*
     *
     * The number, 1406357289, is a 0 to 9 pandigital number because it is
     * made up of each of the digits 0 to 9 in some order, but it also has
     * a rather interesting sub-string divisibility property.
     *
     * Let d1 be the 1st digit, d2 be the 2nd digit, and so on. In this way,
     * we note the following:
     *
     * d2d3d4=406 is divisible by 2
     * d3d4d5=063 is divisible by 3
     * d4d5d6=635 is divisible by 5
     * d5d6d7=357 is divisible by 7
     * d6d7d8=572 is divisible by 11
     * d7d8d9=728 is divisible by 13
     * d8d9d10=289 is divisible by 17
     *
     * Find the sum of all 0 to 9 pandigital numbers with this property.
     */

    size_t result = 0;

    for(size_t first = 1; first <= 9; ++first)
    {
        for(size_t second = 0; second <= 9; ++second)
        {
            if(second == first)
            {
                continue;
            }
            for(size_t third = 0; third <= 9; ++third)
            {
                if(third == first ||
                   third == second )
                {
                    continue;
                }
                for(size_t fourth = 0; fourth <= 9; ++fourth)
                {
                    if(fourth == first ||
                       fourth == second ||
                       fourth == third )
                    {
                        continue;
                    }
                    for(size_t fifth = 0; fifth <= 9; ++fifth)
                    {
                        if(fifth == first ||
                           fifth == second ||
                           fifth == third ||
                           fifth == fourth )
                        {
                            continue;
                        }
                        for(size_t sixth=0;sixth<=9;++sixth)
                        {
                            if(sixth==first ||
                               sixth==second ||
                               sixth==third ||
                               sixth==fourth ||
                               sixth==fifth )
                            {
                                continue;
                            }
                            for(size_t seventh = 0; seventh<=9; ++seventh)
                            {
                                if(seventh == first ||
                                   seventh == second ||
                                   seventh == third ||
                                   seventh == fourth ||
                                   seventh == fifth ||
                                   seventh == sixth )
                                {
                                    continue;
                                }
                                for(size_t eighth = 0; eighth<=9; ++eighth)
                                {
                                    if(eighth == first ||
                                       eighth == second ||
                                       eighth == third ||
                                       eighth == fourth ||
                                       eighth == sixth ||
                                       eighth == seventh )
                                    {
                                        continue;
                                    }
                                    for(size_t ninth=0;ninth<=9;++ninth)
                                    {
                                        if(ninth==first ||
                                           ninth==second ||
                                           ninth==third ||
                                           ninth==fourth ||
                                           ninth==fifth ||
                                           ninth==sixth ||
                                           ninth==seventh ||
                                           ninth==eighth )
                                        {
                                            continue;
                                        }
                                        for(size_t tenth=0;tenth<=9;++tenth)
                                        {
                                            if(tenth==first ||
                                               tenth==second ||
                                               tenth==third ||
                                               tenth==fourth ||
                                               tenth==fifth ||
                                               tenth==sixth ||
                                               tenth==seventh ||
                                               tenth==eighth ||
                                               tenth==ninth )
                                            {
                                                continue;
                                            }

                                            // do something with each digit
                                            size_t nums[] = { first,
                                                              second,
                                                              third,
                                                              fourth,
                                                              fifth,
                                                              sixth,
                                                              seventh,
                                                              eighth,
                                                              ninth,
                                                              tenth };
                                            if(has_subdivisibility_property(
                                                   nums, 10) )
                                            {
                                                result += num_array_to_num(
                                                              nums, 10);
                                            }

                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    std::cout << "PE43 " << result << std::endl;
}



bool has_subdivisibility_property(size_t* nums, size_t num_nums)
{
    return false;
}
size_t num_array_to_num(size_t* nums, size_t num_nums)
{
    size_t result = 0;

    return result;
}
