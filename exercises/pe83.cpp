/*
 * pe83.cpp
 *
 *  Created on: 13 Jun 2015
 *      Author: evilquinn
 */

#include <pe83.hpp>
#include <boost/foreach.hpp>
#include <boost/tokenizer.hpp>
#include <boost/lexical_cast.hpp>
#include <fstream>
#include <iostream>
#include <utils.hpp>
#include <sstream>

namespace { // anonymous

static pe83 ex;

} // end namespace anonymous

std::string& pe83::name() { return name_; }
void         pe83::run()
{
    /*
     * In the 5 by 5 matrix below, the minimal path sum from the
     * top left to the bottom right, by moving left, right, up,
     * and down, is indicated in bold red and is equal to 2297.
     *
     *  *131  673 *234 *103 *18
     *  *201 *96  *342  965 *150
     *   630  803  746 *422 *111
     *   537  699  497 *121  956
     *   805  732  524 *37  *331
     *
     * Find the minimal path sum, in matrix.txt containing a
     * 80 by 80 matrix, from the top left to the bottom right
     * by moving left, right, up, and down.
     */

    std::ifstream data_file;
    data_file.open( "/home/evilquinn/git/projeul/data/pe83_matrix_small.txt" );

    typedef std::vector<std::vector<size_t> > matrix_t;
    matrix_t matrix;

    std::string line;
    size_t row = 0;
    while ( std::getline(data_file, line ) )
    {
        std::istringstream is(line);
        std::string word;
        matrix.emplace_back();
        while ( std::getline(is, word, ',') )
        {
            matrix[row].emplace_back(
                boost::lexical_cast<size_t>(word));
        }
        ++row;
    }

    /*
     * rough plan:
     * expand the lowest paths across the diagonal starting from
     * the bottom right, i.e. assuming a 5 x 5 matrix
     *
     *   Diagonal  Coords
     *   0         4,4
     *
     *   1         4,3
     *   1         3,4
     *
     *   2         4,2
     *   2         3,3
     *   2         2,4
     *
     *   3         4,1
     *   3         3,2
     *   3         2,3
     *   3         1,4
     *
     *   4         4,0
     *   4         3,1
     *   4         2,2
     *   4         1,3
     *   4         0,4
     *
     *   5         3,0
     *   5         2,1
     *   5         1,2
     *   5         0,3
     *
     *   6         2,0
     *   6         1,1
     *   6         0,2
     *
     *   7         1,0
     *   7         0,1
     *
     *   8         0,0
     *
     * cache smallest path for each diagonal in separate matrix,
     * then save back after each layer before calcing the next.
     */

    size_t slimit = matrix.size()-1;
    int continuer = 1;
    for ( size_t i = 0; i <= slimit; i += continuer )
    {
        std::vector<size_t> mins;
        enum act { copy, calc, save };
        std::vector<enum act> acts = { copy, calc, save };

        for ( auto e : acts )
        {
            size_t row = continuer > 0 ? slimit : i;
            size_t col = continuer > 0 ? slimit - i : 0;

            size_t iilimit = i + 1;
            for ( size_t ii = 0; ii < iilimit; ++ii )
            {
                int switcher = row == col ? 0 :
                               row < col  ? 1 :
                                            -1;

                switch ( e )
                {
                case copy :
                {
                    mins.push_back(matrix[row][col]);
                    break;
                }
                case calc :
                {
                    size_t min_to_here = (size_t)-1;
                    // figure out smallest path to here, and write
                    // total to mins[ii]
                    std::cout << "testing " << row << "," << col << ", ";
                    size_t total_to_here = 0;
                    for ( size_t iii = 0; iii < i; ++iii )
                    {
                        ++total_to_here;
                        // test all paths to here, recording the
                        // lowest to min_to_here
                    }
                    std::cout << total_to_here << " times\n";
                    break;
                }
                case save :
                {
                    matrix[row][col] = mins[ii];
                    break;
                }
                default :
                {
                    std::cout << "WHA!?" << std::endl;
                    break;
                } // end default
                } // end switch
                --row;
                ++col;
            }

            if ( i == slimit )
            {
                continuer = -1;
            }
        }
    }

    std::cout << matrix[0][0] << std::endl;
}
