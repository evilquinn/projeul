/*
 * pe82.cpp
 *
 *  Created on: 13 Jun 2015
 *      Author: evilquinn
 */

#include <boost/foreach.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/multiprecision/cpp_int.hpp>
#include <boost/tokenizer.hpp>
#include <fstream>
#include <iostream>
#include <pe82.hpp>
#include <sstream>
#include <utils.hpp>

namespace
{  // anonymous

static pe82 ex;

}  // namespace

std::string& pe82::name() { return name_; }
void pe82::run()
{
    /*
     * The minimal path sum in the 5 by 5 matrix below, by
     * starting in any cell in the left column and finishing in
     * any cell in the right column, and only moving up, down,
     * and right, is indicated in red and bold; the sum is equal
     * to 994.
     *
     *   131  673 *234 *103 *18
     *  *201 *96  *342  965  150
     *   630  803  746  422  111
     *   537  699  497  121  956
     *   805  732  524  37   331
     *
     * Find the minimal path sum, in pe82_matrix.txt containing a
     * 80 by 80 matrix, from the left column to the right column.
     */

    std::ifstream data_file;
    data_file.open( "/home/evilquinn/git/projeul/data/pe82_matrix.txt" );

    namespace bmp = boost::multiprecision;
    typedef std::vector<std::vector<size_t> > matrix_t;
    matrix_t matrix;

    std::string line;
    size_t row = 0;
    while ( std::getline( data_file, line ) )
    {
        std::istringstream is( line );
        std::string word;
        matrix.emplace_back();
        while ( std::getline( is, word, ',' ) )
        {
            matrix[row].emplace_back( boost::lexical_cast<size_t>( word ) );
        }
        ++row;
    }

    // start from the second-to-last column
    for ( size_t col = matrix.size() - 2; col < matrix.size(); --col )
    {
        // create working copy of this column
        std::vector<size_t> mins;
        for ( size_t row = 0; row < matrix.size(); ++row )
        {
            mins.push_back( matrix[row][col] );
        }
        // calculate the best candidate for each row in this column
        // and save it in mins for the moment
        for ( size_t row = 0; row < matrix.size(); ++row )
        {
            // find the smallest path from any row in the prev col
            size_t min = matrix[row][col + 1];
            for ( size_t i = 0; i < matrix.size(); ++i )
            {
                size_t cand = matrix[i][col + 1];
                for ( size_t ii = i; ii < row; ++ii )
                {
                    cand += matrix[ii][col];
                }
                for ( size_t ii = i; ii > row; --ii )
                {
                    cand += matrix[ii][col];
                }
                if ( cand < min )
                {
                    min = cand;
                }
            }
            mins[row] += min;
        }
        // mins now contains all the best current paths for each
        // row in this col, copy it back in
        for ( size_t row = 0; row < matrix.size(); ++row )
        {
            matrix[row][col] = mins[row];
        }
    }

    // find the lowest value in the first column
    size_t min = (size_t)-1;
    for ( size_t row = 0; row < matrix.size(); ++row )
    {
        if ( matrix[row][0] < min )
        {
            min = matrix[row][0];
        }
    }

    std::cout << min << std::endl;
}
