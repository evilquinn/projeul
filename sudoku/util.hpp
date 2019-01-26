#ifndef SUDOKU_UTIL_HPP
#define SUDOKU_UTIL_HPP

#include <iosfwd>
#include <sudoku/square.hpp>

std::ostream& operator<<( std::ostream& os, const evilquinn::sudoku::coord& c );

std::ostream& operator<<( std::ostream& os, const evilquinn::sudoku::square::candidate_set& c );

#endif // SUDOKU_UTIL_HPP

