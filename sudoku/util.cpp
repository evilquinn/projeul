
#include <iostream>
#include <string>
#include <sudoku/util.hpp>


std::ostream& operator<<( std::ostream& os, const evilquinn::sudoku::coord& c )
{
    os << "[" << c.x << "," << c.y << "]";
    return os;
}

std::ostream& operator<<( std::ostream& os, const evilquinn::sudoku::square::candidate_set& c )
{
    os << "(";
    for ( auto it = c.begin(); it != c.end(); ++it )
    {
        os << *it;
        if ( std::next(it) != c.end() )
        {
            os << ",";
        }
    }
    os << ")";
    return os;
}
