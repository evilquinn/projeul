/*
 * pe81.cpp
 *
 *  Created on: 13 Jun 2015
 *      Author: evilquinn
 */

#include <pe81.hpp>
#include <boost/foreach.hpp>
#include <boost/tokenizer.hpp>
#include <boost/lexical_cast.hpp>
#include <fstream>
#include <iostream>
#include <utils.hpp>
#include <sstream>

namespace { // anonymous

static pe81 ex;

} // end namespace anonymous

std::string& pe81::name() { return name_; }
void         pe81::run()
{
    /*
     * In the 5 by 5 matrix below, the minimal path sum from the top left
     * to the bottom right, by only moving to the right and down, is
     * indicated in bold red and is equal to 2427.
     *
     *  *131  673  234  103  18
     *  *201 *96  *342  965  150
     *   630  803 *746 *422  111
     *   537  699  497 *121  956
     *   805  732  524 *37  *331
     *
     * Find the minimal path sum, in matrix.txt containing a
     * 80 by 80 matrix, from the top left to the bottom right
     * by only moving right and down.
     *
     */

    std::ifstream data_file;
    data_file.open( "/home/evilquinn/git/projeul/data/pe81_matrix.txt" );

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

    size_t i = matrix.size() - 1;
    while ( i < matrix.size() )
    {
        // converge from below or right walking the down the column
        auto irow = i;
        while ( irow < matrix.size() )
        {
            auto min = 0;
            if ( irow == matrix.size() - 1 &&
                 i == matrix[irow].size() - 1 )
            {
                min = 0;
            }
            else if ( i == matrix[irow].size() - 1 )
            {
                min = matrix[irow+1][i];
            }
            else if ( irow == matrix.size() - 1 )
            {
                min = matrix[irow][i+1];
            }
            else
            {
                min = matrix[irow+1][i] < matrix[irow][i+1] ?
                          matrix[irow+1][i] :
                          matrix[irow][i+1];
            }
            matrix[irow][i] += min;
            --irow;
        }
        // converge from below or right walking down the row
        auto icol = i - 1; // -1 so we don't double count this one
        while ( icol < matrix[i].size() )
        {
            auto min = 0;
            if ( i == matrix.size() - 1 &&
                 icol == matrix[i].size() - 1 )
            {
                min = 0;
            }
            else if ( i == matrix.size() - 1 )
            {
                min = matrix[i][icol+1];
            }
            else if ( icol == matrix[i].size() - 1 )
            {
                min = matrix[i+1][icol];
            }
            else
            {
                min = matrix[i+1][icol] < matrix[i][icol+1] ?
                          matrix[i+1][icol] :
                          matrix[i][icol+1];
            }
            matrix[i][icol] += min;
            --icol;
        }
        --i;
    }

    std::cout << matrix[0][0] << std::endl;
}
