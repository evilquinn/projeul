
#ifndef SUDOKU_SOLVER_HPP
#define SUDOKU_SOLVER_HPP

#include <boost/variant.hpp>
#include <sudoku/grid.hpp>

namespace evilquinn
{
namespace sudoku
{
class solver
{
public:
    solver( grid& grid );
    bool solve();

    enum class axis
    {
        row,
        column,
        nonet,
        gridwise_nonets
    };

    using square_operation = std::function<void( square& s )>;
    using coord_range      = std::pair<coord, coord>;
    using coord_sequence   = std::vector<coord>;
    square_operation for_each( const coord_sequence& sequence,
                               square_operation op );
    void naked_hidden_tuples();
    void naked_tuples_in_axis( square& sq, axis ax );
    void hidden_tuples_in_axis( square& sq, axis ax );
    void x_wing();
    void x_wing_in_axis(axis ax);

private:
    grid& grid_;
};

}  // end namespace sudoku
}  // end namespace evilquinn

#endif  // SUDOKU_SOLVER_HPP
