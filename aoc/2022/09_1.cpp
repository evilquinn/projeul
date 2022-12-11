#include <iostream>
#include <fstream>
#include <set>

#include <aoc/path_def.hpp>
#include <aoc/coord.hpp>

using coord_util::coord;

coord head( 0, 0 );
coord tail = head;

const coord right( 1, 0 );
const coord left( -1, 0 );
const coord up( 0, -1 );
const coord down( 0, 1 );

std::set<coord> visited = { tail };

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

void move(char d)
{
    coord dir = direction_coord(d);
    head += dir;
    coord diff = head - tail;

    if      ( diff.x < -1 ) ++diff.x;
    else if ( diff.x >  1 ) --diff.x;
    else if ( diff.y < -1 ) ++diff.y;
    else if ( diff.y >  1 ) --diff.y;
    else
    {
        if ( diff.x < 0 ) ++diff.x;
        if ( diff.x > 0 ) --diff.x;
        if ( diff.y < 0 ) ++diff.y;
        if ( diff.y > 0 ) --diff.y;
    }
    tail += diff;
    visited.insert(tail);
}

void apply_moves(std::istream& input)
{
    std::string line;
    while(std::getline(input, line))
    {
        char d = '.';
        int by = 0;
        sscanf(line.c_str(), "%c %d", &d, &by);
        for ( int i = 0; i < by; ++i )
        {
            move(d);
        }
    }
}


int main()
{
    std::ifstream input(PROJEUL_AOC_PATH "/09_input.txt");
    if ( !input ) throw std::runtime_error("Failed to open input file");

    apply_moves(input);
    auto p1 = visited.size();
    std::cout << "Part 1 result: " << p1 << std::endl;

    return 0;
}
