#include <iostream>
#include <fstream>
#include <vector>
#include <set>

#include <aoc/path_def.hpp>
#include <aoc/coord.hpp>

using coord_util::coord;
using knots_type = std::vector<coord>;
using visited_type = std::set<coord>;

const coord right( 1, 0 );
const coord left( -1, 0 );
const coord up( 0, -1 );
const coord down( 0, 1 );

coord direction_coord(char d)
{
    switch (d)
    {
    case 'R' : return right;
    case 'L' : return left;
    case 'U' : return up;
    case 'D' : return down;
    default  : throw std::runtime_error("Unrecognised direction");
    }
}

void move(char d, knots_type& knots, visited_type& visits)
{
    if ( knots.size() < 2 ) throw std::runtime_error("Not enough knots!");
    coord dir = direction_coord(d);
    knots[0] += dir;
    for ( size_t i = 0; i < knots.size() - 1; ++i )
    {
        const coord diff = knots[i] - knots[1+i];
        coord move_by = diff;
        if ( move_by.x < -1 ) ++move_by.x;
        if ( move_by.x >  1 ) --move_by.x;
        if ( move_by.y < -1 ) ++move_by.y;
        if ( move_by.y >  1 ) --move_by.y;
        if ( diff == move_by ) break;

        knots[i+1] += move_by;
    }
    visits.insert(knots.back());
}

void apply_moves(std::istream& input, knots_type& knots, visited_type& visits)
{
    std::string line;
    while(std::getline(input, line))
    {
        char d = '.';
        int by = 0;
        sscanf(line.c_str(), "%c %d", &d, &by);
        for ( int i = 0; i < by; ++i )
        {
            move(d, knots, visits);
        }
    }
}


int main()
{
    std::ifstream input(PROJEUL_AOC_PATH "/09_input.txt");
    if ( !input ) throw std::runtime_error("Failed to open input file");

    knots_type p1_knots(2, coord( 0, 0 ));
    visited_type p1_visited = { p1_knots.back() };
    apply_moves(input, p1_knots, p1_visited);
    auto p1 = p1_visited.size();
    std::cout << "Part 1 result: " << p1 << std::endl;

    input.clear();
    input.seekg(0);
    knots_type p2_knots(10, coord( 0, 0 ));
    visited_type p2_visited = { p2_knots.back() };
    apply_moves(input, p2_knots, p2_visited);
    auto p2 = p2_visited.size();
    std::cout << "Part 2 result: " << p2 << std::endl;

    return 0;
}
