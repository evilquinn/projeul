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

    size_t limit = 100;

    boost::multiprecision::cpp_int result = 0;

    std::vector<size_t> terms = { limit };

    size_t front = 0;
    size_t back = front + 1;
    while ( true )
    {
        if ( terms[front] == 1 )
        {
            // backtrack
            --front;
            --back;
            continue;
        }
        else if ( terms[front] > 2 )
        {
            terms[front] -= 1;
            if ( back >= terms.size() )
            {
                terms.push_back(1);
            }
            else
            {
                terms[back] += 1;
                while ( back < terms.size() && terms[back] < terms[front] )
                {
                    if ( back == terms.size() - 1 )
                    {
                        break;
                    }
                    terms[back] += 1;
                    if ( terms[terms.size()-1] == 1 )
                    {
                        terms.pop_back();
                    }
                    else
                    {
                        terms[terms.size()-1] -= 1;
                    }
                    if ( terms[back] == terms[front] )
                    {
                        ++back;
                        ++front;
                    }
                }
            }
            ++front;
            ++back;
            //print_terms(terms);
            ++result;
        }
        else if ( terms[front] == 2 )
        {
            terms[front] -= 1;
            terms.push_back(1);
            //print_terms(terms);
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
