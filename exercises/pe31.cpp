/*
 * pe31.cpp
 *
 *  Created on: 13 Jun 2015
 *      Author: evilquinn
 */

#include "pe31.hpp"
#include <boost/foreach.hpp>
#include <cmath>
#include <iostream>
#include <set>

int count_possibilities( int* coins, int num_coins, int target );

std::string& pe31::name() { return name_; }
void pe31::run()
{
    /*
     *
     * In England the currency is made up of pound, £, and pence, p, and
     * there are eight coins in general circulation:
     *
     *     1p, 2p, 5p, 10p, 20p, 50p, £1 (100p) and £2 (200p).
     *
     * It is possible to make £2 in the following way:
     *
     *     1×£1 + 1×50p + 2×20p + 1×5p + 1×2p + 3×1p
     *
     * How many different ways can £2 be made using any number of coins?
     *
     */
    // int coins[] = { 1, 2, 5, 10, 20, 50, 100, 200 };
    int coins[]         = { 200, 100, 50, 20, 10, 5, 2, 1 };
    const int num_coins = sizeof( coins ) / sizeof( int );
    std::cout << name() << ": "
              << count_possibilities( coins, num_coins, 200 ) << std::endl;
}

int count_possibilities( int* coins, int num_coins, int target )
{
    // base case: no coins in purse, no possibilities
    if ( num_coins < 1 )
    {
        return 0;
    };
    // can we make the target by adding up our single coin?
    if ( num_coins == 1 )
    {
        return target % num_coins == 0 ? 1 : 0;
    }

    // count amount of times
    // possibilities(coins+1, num_coins-1, target-n*coins[0])
    // where n*coins[0] < target
    int total    = 0;
    int curr_try = 0;
    while ( curr_try <= target )
    {
        total += count_possibilities(
            &coins[1], num_coins - 1, target - curr_try );
        curr_try += coins[0];
    }

    return total;
}
