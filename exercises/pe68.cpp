/*
 * pe68.cpp
 *
 *  Created on: 13 Jun 2015
 *      Author: evilquinn
 */

#include <algorithm>
#include <iostream>
#include <iterator>
#include <map>
#include <pe68.hpp>
#include <set>
#include <vector>

std::string& pe68::name() { return name_; }
typedef std::multimap<size_t, std::vector<int> > magic_solution;

size_t element_pair( size_t n, size_t e )
{
    int interim = e % 3;
    int diff    = ( interim == 0 ? 0 : interim == 1 ? -2 : 2 );
    int result  = (int)e + diff;
    return ( result < 0 ? n - 1 : (size_t)result >= n ? 1 : result );
}

void set_solution_element( std::vector<int>& solution, size_t e, size_t v )
{
    solution[e]                                  = v;
    solution[element_pair( solution.size(), e )] = v;
}

bool sort_solution( std::vector<int>& solution )
{
    bool result  = false;
    int lowest   = solution[0];
    int lowest_i = 0;
    for ( size_t i = 3; i < solution.size(); i += 3 )
    {
        if ( solution[i] < lowest )
        {
            lowest   = solution[i];
            lowest_i = i;
        }
    }
    if ( lowest_i > 0 )
    {
        result = true;
        std::rotate(
            solution.begin(), solution.begin() + lowest_i, solution.end() );
    }
    return result;
}

magic_solution solve_magic_n_gon_for( size_t n )
{
    magic_solution result;

    size_t solution_length = n * 3;
    size_t num_digits      = n * 2;
    std::vector<int> solution( solution_length );
    std::set<int> available_digits;
    for ( size_t i = 1; i <= num_digits; ++i )
    {
        available_digits.insert( i );
    }
    size_t e       = 0;
    bool backtrack = false;
    while ( true )
    {
        if ( backtrack )
        {
            if ( available_digits.size() == num_digits )
            {
                // i think we're done done!
                break;
            }
            if ( available_digits.empty() )
            {
                while ( e >= solution.size() )
                {
                    // we might be past the end
                    --e;
                }
                available_digits.insert( solution[e] );
                set_solution_element( solution, e, 0 );
                do
                {
                    --e;
                } while ( solution[e] == 0 );
                continue;
            }
            else
            {
                auto it = available_digits.upper_bound( solution[e] );
                if ( it != available_digits.end() )
                {
                    int save = solution[e];
                    set_solution_element( solution, e, *it );
                    if ( save > 0 )
                    {
                        available_digits.insert( save );
                    }
                    available_digits.erase( it );
                    backtrack = false;
                    // intermediate test: is the digit we just added good?
                    size_t intermediate_total = 0;
                    size_t intermediate_last  = 0;
                    bool encountered_zero     = false;
                    for ( size_t i = 0; i < solution.size(); ++i )
                    {
                        encountered_zero = encountered_zero == true
                                               ? true
                                               : solution[i] == 0;
                        intermediate_total += solution[i];
                        if ( ( i + 1 ) % 3 == 0 )
                        {
                            if ( encountered_zero )
                            {
                                encountered_zero   = false;
                                intermediate_total = 0;
                                continue;
                            }
                            if ( intermediate_last == 0 )
                            {
                                intermediate_last  = intermediate_total;
                                intermediate_total = 0;
                            }
                            else if ( intermediate_total ==
                                      intermediate_last )
                            {
                                // all good
                                intermediate_total = 0;
                                continue;
                            }
                            else
                            {
                                backtrack = true;
                                break;
                            }
                        }
                    }
                    continue;
                }
                else
                {
                    available_digits.insert( solution[e] );
                    set_solution_element( solution, e, 0 );
                    do
                    {
                        --e;
                    } while ( e < solution.size() && solution[e] == 0 );
                    continue;
                }
            }
        }
        while ( e < solution.size() && solution[e] != 0 )
        {
            ++e;
        }

        if ( e >= solution.size() )
        {
            // full attempt, test
            size_t intermediate_total = 0;
            size_t intermediate_last  = 0;
            for ( size_t i = 0; i < num_digits; ++i )
            {
                intermediate_total += solution[i];
                if ( ( i + 1 ) % 3 == 0 )
                {
                    if ( intermediate_last == 0 )
                    {
                        intermediate_last  = intermediate_total;
                        intermediate_total = 0;
                    }
                    else if ( intermediate_total == intermediate_last )
                    {
                        // all good
                        intermediate_total = 0;
                        continue;
                    }
                    else
                    {
                        backtrack = true;
                        break;
                    }
                }
            }
            if ( backtrack )
            {
                continue;  // skip out again to backtrack
            }
            else
            {
                // winning solution???
                auto copy = solution;
                sort_solution( copy );
                int seen = 0;
                for ( auto walker = result.lower_bound( intermediate_last );
                      intermediate_last == walker->first;
                      ++walker )
                {
                    if ( copy == walker->second )
                    {
                        ++seen;
                    }
                }
                if ( seen == 0 )
                {
                    result.insert(
                        std::make_pair( intermediate_last, copy ) );
                }
                else
                {
                    // done now?
                    // break;
                }
                // keep going for more solutions!
                backtrack = true;
                continue;
            }
        }

        // select next
        int save = solution[e];
        set_solution_element( solution, e, *available_digits.begin() );
        if ( save > 0 )
        {
            available_digits.insert( save );
        }
        else
        {
            available_digits.erase( available_digits.begin() );
        }

        // intermediate test: is the digit we just added good?
        size_t intermediate_total = 0;
        size_t intermediate_last  = 0;
        bool encountered_zero     = false;
        for ( size_t i = 0; i < solution.size(); ++i )
        {
            encountered_zero =
                encountered_zero == true ? true : solution[i] == 0;
            intermediate_total += solution[i];
            if ( ( i + 1 ) % 3 == 0 )
            {
                if ( encountered_zero )
                {
                    encountered_zero   = false;
                    intermediate_total = 0;
                    continue;
                }
                if ( intermediate_last == 0 )
                {
                    intermediate_last  = intermediate_total;
                    intermediate_total = 0;
                }
                else if ( intermediate_total == intermediate_last )
                {
                    // all good
                    intermediate_total = 0;
                    continue;
                }
                else
                {
                    backtrack = true;
                    break;
                }
            }
        }
    }

    return result;
}

void pe68::run()
{
    /*
     * Consider a "magic" 3-gon ring, filled with the numbers 1 to 6, and
     * each line adding to nine.
     *
     * Working clockwise, and starting from the group of three with the
     * numerically lowest external node (4,3,2 in this example), each
     * solution can be described uniquely. For example, the above
     * solution can be described by the set: 4,3,2; 6,2,1; 5,1,3.
     *
     * It is possible to complete the ring with four different totals:
     * 9, 10, 11, and 12. There are eight solutions in total.
     *
     * Total    Solution Set
     * 9        4,2,3; 5,3,1; 6,1,2
     * 9        4,3,2; 6,2,1; 5,1,3
     * 10       2,3,5; 4,5,1; 6,1,3
     * 10       2,5,3; 6,3,1; 4,1,5
     * 11       1,4,6; 3,6,2; 5,2,4
     * 11       1,6,4; 5,4,2; 3,2,6
     * 12       1,5,6; 2,6,4; 3,4,5
     * 12       1,6,5; 3,5,4; 2,4,6
     *
     * By concatenating each group it is possible to form 9-digit strings;
     * the maximum string for a 3-gon ring is 432621513.
     *
     * Using the numbers 1 to 10, and depending on arrangements, it is
     * possible to form 16- and 17-digit strings. What is the maximum
     * 16-digit string for a "magic" 5-gon ring?
     *
     */

    auto temp = solve_magic_n_gon_for( 5 );

    for ( const auto& sol : temp )
    {
        std::cout << sol.first << " : ";
        std::copy( sol.second.begin(),
                   sol.second.end(),
                   std::ostream_iterator<int>( std::cout ) );
        std::cout << "\n";
    }
}
