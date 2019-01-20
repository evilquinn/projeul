
#ifndef SUDOKU_GRID_HPP
#define SUDOKU_GRID_HPP

#include <vector>
#include <sudoku/square.hpp>

namespace evilquinn {

namespace sudoku {

using dimensions = coord;

class grid
{
public:
    grid(dimensions dim);
    using line = std::vector<square>;
    using matrix = std::vector<line>;

    std::string to_string() const;

private:
    dimensions dim_;
    matrix squares_;
};



} // end namespace sudoku
} // end namespace evilquinn

#endif // SUDOKU_GRID_HPP
