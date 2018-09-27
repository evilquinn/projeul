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
#include <algorithm>

namespace { // anonymous

typedef std::pair<size_t, size_t> coord;
std::string to_string(const coord& c)
{
    std::stringstream str;
    str << c.first << "," << c.second;
    return str.str();
}

std::set<coord> make_open_set(const coord& node,
                              const coord& bound,
                              const std::set<coord>& closed)
{
    std::set<coord> result;
    coord cand;
    // above
    if ( node.first > 0 )
    {
        cand = { node.first-1, node.second };
        if ( closed.count(cand) == 0 )
        {
            result.insert(cand);
        }
    }
    // left
    if ( node.second > 0 )
    {
        cand = {node.first, node.second-1};
        if ( closed.count(cand) == 0 )
        {
            result.insert(cand);
        }
    }
    // right
    if ( node.second < bound.second )
    {
        cand = {node.first, node.second+1};
        if ( closed.count(cand) == 0 )
        {
            result.insert(cand);
        }
    }
    // below
    if ( node.first < bound.first )
    {
        cand = {node.first+1, node.second};
        if ( closed.count(cand) == 0 )
        {
            result.insert(cand);
        }
    }

    return result;
}

template<typename Container>
size_t& value_at(Container& container, const coord& c)
{
    return container[c];
}

typedef std::map<coord, size_t> matrix_t;
coord next_shortest_not_closed(const matrix_t& distances,
                               const std::set<coord>& closed)
{
    coord result;
    size_t smallest_not_in_closed = -1;
    for ( auto& d : distances )
    {
        if ( closed.count(d.first) == 0 &&
             d.second < smallest_not_in_closed )
        {
            result = d.first;
            smallest_not_in_closed = d.second;
        }
    }
    return result;
}

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
    data_file.open( "/home/evilquinn/git/projeul/data/pe83_matrix.txt" );

    matrix_t matrix;

    std::string line;
    size_t row = 0;
    while ( std::getline(data_file, line ) )
    {
        std::istringstream is(line);
        std::string word;
        size_t col = 0;
        while ( std::getline(is, word, ',') )
        {
            matrix[coord{row, col}] = boost::lexical_cast<size_t>(word);
            ++col;
        }
        ++row;
    }

    /*
     * rough plan:
     * djikstra's algo, start with node and open set (start node and its
     * adjacents in open set), determine node in open set with smallest path
     * to node. call node closed, then make smallest open set node the node,
     * and open set becomes node's non-closed adjacent nodes. Finished when
     * end node calc'd. Hopefully.
     */

    coord bound = { matrix.rbegin()->first.first, matrix.rbegin()->first.second };

    // init solution matrix contains distance from start to each node
    auto distances = matrix;
    for ( auto& d : distances )
    {
        d.second = -1;
    }
    distances[bound] = matrix[bound];

    std::set<coord> closed;
    coord cnode;
    while ( true )
    {
        // pop next shortest distance
        cnode = next_shortest_not_closed(distances, closed);
        if ( cnode == coord{0, 0} )
        {
            std::cout << "algo! " << distances[cnode] << std::endl;
            break;
        }
        closed.insert(cnode);
        // update adjacents
        coord adj;
        size_t cand;
        if ( cnode.first > 0 )
        {
            adj = coord{cnode.first-1, cnode.second};
            cand = distances[cnode] + matrix[adj];
            if ( cand < distances[adj] )
            {
                distances[adj] = cand;
            }
        }
        if ( cnode.first < bound.first )
        {
            adj = coord{cnode.first+1, cnode.second};
            cand = distances[cnode] + matrix[adj];
            if ( cand < distances[adj] )
            {
                distances[adj] = cand;
            }
        }
        if ( cnode.second > 0 )
        {
            adj = coord{cnode.first, cnode.second-1};
            cand = distances[cnode] + matrix[adj];
            if ( cand < distances[adj] )
            {
                distances[adj] = cand;
            }
        }
        if ( cnode.second < bound.second )
        {
            adj = coord{cnode.first, cnode.second+1};
            cand = distances[cnode] + matrix[adj];
            if ( cand < distances[adj] )
            {
                distances[adj] = cand;
            }
        }
    }
}
