
#ifndef SUDOKU_GRID_HPP
#define SUDOKU_GRID_HPP

#include <sudoku/square.hpp>
#include <vector>

namespace evilquinn
{
namespace sudoku
{
using dimensions = coord;

class grid
{
public:
    grid( dimensions dim );
    using line   = std::vector<square>;
    using matrix = std::vector<line>;

    square& at( coord pos );
    dimensions get_dimensions() const;
    size_t count_remaining() const;
    bool solved() const;
    std::ostream& stream_out( std::ostream& os ) const;

private:
    dimensions dim_;
    matrix squares_;
};

}  // end namespace sudoku
}  // end namespace evilquinn

inline std::ostream& operator<<( std::ostream& os, const evilquinn::sudoku::grid& grid)
{
    return grid.stream_out(os);
}

#endif  // SUDOKU_GRID_HPP
