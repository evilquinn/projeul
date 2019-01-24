
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
    using coord_variant    = boost::variant<coord_range, coord_sequence>;
    square_operation for_each( square_operation op );
    square_operation for_each( coord_range range, square_operation op );
    square_operation for_each( const coord_sequence& sequence,
                               square_operation op );
    void eliminate_knowns_from_ranges();
    void if_value_known_eliminate( square& sq );
    void solve_if_candidate_unique_in_ranges();
    void if_candidate_unique_in_axis_solve( square& sq, axis ax );

private:
    grid& grid_;
};

}  // end namespace sudoku
}  // end namespace evilquinn

#endif  // SUDOKU_SOLVER_HPP
