/*
 * pe77.cpp
 *
 *  Created on: 13 Jun 2015
 *      Author: evilquinn
 */

#include <boost/multiprecision/cpp_int.hpp>
#include <cmath>
#include <iostream>
#include <map>
#include <pe77.hpp>
#include <utils.hpp>
#include <prime_sieve.hpp>

std::string& pe77::name() { return name_; }
void print_terms( std::vector<size_t> terms );

void pe77::run()
{
    /*
     * It is possible to write ten as the sum of primes in exactly five
     * different ways:
     *
     *   7 + 3
     *   5 + 5
     *   5 + 3 + 2
     *   3 + 3 + 2 + 2
     *   2 + 2 + 2 + 2 + 2
     *
     * What is the first value which can be written as the sum of primes
     * in over five thousand different ways?
     *
     */

    size_t limit = 10;
    prime_sieve primes(limit*2);

    size_t result = 0;

    std::vector<size_t> terms = { limit };

    size_t front = 0;
    size_t back  = front + 1;
    while ( true )
    {
        if ( terms[front] == 2 )
        {
            // backtrack
            --front;
            --back;
            continue;
        }
        else if ( terms[front] > 3 )
        {
            terms[front] -= 1;
            if ( back >= terms.size() )
            {
                terms.push_back( 1 );
            }
            else
            {
                terms[back] += 1;
                while ( back < terms.size() && terms[back] <= terms[front] )
                {
                    if ( back == terms.size() - 1 )
                    {
                        break;
                    }

                    if ( terms[back] == terms[front] )
                    {
                        ++back;
                        ++front;
                        continue;
                    }

                    terms[back] += 1;
                    if ( terms[terms.size() - 1] == 1 )
                    {
                        terms.pop_back();
                    }
                    else
                    {
                        terms[terms.size() - 1] -= 1;
                    }
                }
            }
            ++front;
            ++back;
            // print_terms(terms);
            ++result;
        }
        else if ( terms[front] == 3 )
        {
            terms[front] -= 1;
            terms.push_back( 1 );
            // print_terms(terms);
            ++result;

            if ( front == 0 )
            {
                // we're done
                break;
            }
            --front;
            --back;
        }
    }

    std::cout << result << std::endl;
}
