
#ifndef SUDOKU_SOLVER_HPP
#define SUDOKU_SOLVER_HPP

#include <sudoku/grid.hpp>

namespace evilquinn
{
namespace sudoku
{

class solver
{
public:
    solver(grid& grid);
    bool solve();
    using square_operation = std::function<void(square& s)>;
    square_operation for_each(square_operation op);
    square_operation for_each(coord start, coord end, square_operation op);
    void if_value_known_eliminate(square& sq);
private:
    grid& grid_;
};

} // end namespace sudoku
} // end namespace evilquinn

#endif // SUDOKU_SOLVER_HPP

