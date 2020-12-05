/*
 * https://adventofcode.com/2020/day/5
 */

#include <iostream>
#include <fstream>
#include <vector>

#include <aoc/path_def.hpp>
#include <aoc/coord.hpp>

namespace
{

static const int lowest = 0;
static const int num_rows = 128;
static const int num_cols = 8;

coord_util::coord find_seat(const std::string& seat_spec)
{
    int seat_row_begin = lowest;
    int seat_row_end = num_rows;
    int seat_col_begin = lowest;
    int seat_col_end = num_cols;
    for ( size_t i = 0; i < seat_spec.size(); ++i )
    {
        switch ( seat_spec.at(i) )
        {
        case 'F' : seat_row_end -= ( seat_row_end - seat_row_begin ) / 2; break;
        case 'B' : seat_row_begin += ( seat_row_end - seat_row_begin ) / 2; break;
        case 'L' : seat_col_end -= ( seat_col_end - seat_col_begin ) / 2; break;
        case 'R' : seat_col_begin += ( seat_col_end - seat_col_begin ) / 2; break;
        default  : throw 42;
        }
    }
    return coord_util::coord{ seat_row_begin, seat_col_begin };
}

size_t find_seat_id(const std::string& seat_spec)
{
    static const int row_factor = 8;
    auto pos = find_seat(seat_spec);
    return ( pos.x * row_factor ) + pos.y;
}

}

int main()
{
    std::ifstream inf(PROJEUL_AOC_PATH "/05_input.txt");
    std::vector<std::string> data;
    for ( std::string line; std::getline(inf, line); )
    {
        data.emplace_back(std::move(line));
    }
    size_t max = 0;
    for ( auto&& datum : data )
    {
        auto result = find_seat_id(datum);
        if ( result > max ) max = result;
        std::cout << "spec: " << datum << ", seat id: " << result << "\n";
    }
    std::cout << "max: " << max << "\n";
    return 0;
}
