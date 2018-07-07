/*
 * pe76.cpp
 *
 *  Created on: 13 Jun 2015
 *      Author: evilquinn
 */

#include <pe76.hpp>
#include <iostream>
#include <map>
#include <utils.hpp>
#include <boost/multiprecision/cpp_int.hpp>
#include <cmath>

std::string& pe76::name() { return name_; }

void print_terms(std::vector<size_t> terms)
{
    for ( const auto& term : terms )
    {
        std::cout << term << ", ";
    }
    std::cout << "\n";
}


void         pe76::run()
{
    /*
     * It is possible to write five as a sum in exactly six different ways:
     *
     *   4 + 1
     *   3 + 2
     *   3 + 1 + 1
     *   2 + 2 + 1
     *   2 + 1 + 1 + 1
     *   1 + 1 + 1 + 1 + 1
     *
     * How many different ways can one hundred be written as a sum of at
     * least two positive integers?
     *
     *
     */

    size_t limit = 5;

    size_t result = 0;

    for ( size_t first_term = 1; first_term < limit; ++first_term )
    {
        std::vector<size_t> terms = { first_term };
        std::copy(fixed_terms.begin(),
                  fixed_terms.end() - first_term,
                  std::back_inserter(terms));

        ++result;
        print_terms(terms);

        size_t toi = 1;
        size_t fromi = terms.size() - 1;
        while ( fromi > toi && terms[toi] + 1 <= first_term )
        {
            terms[toi] += 1;
            terms[fromi] -= 1;
            if ( terms[fromi] == 0 )
            {
                terms.pop_back();
                --fromi;
            }
            ++result;
            print_terms(terms);

            if ( terms[toi] == first_term )
            {
                ++toi;
            }
            if ( fromi <= toi )
            {
                toi = 1;
                fromi = terms.size() - 1;
            }
        }
    }


}
