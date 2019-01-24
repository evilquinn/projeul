
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
    solver( grid& grid );
    bool solve();

    enum class axis
    {
        row,
        column,
        nonet
    };
    using square_operation = std::function<void( square& s )>;
    using coord_range      = std::pair<coord, coord>;
    square_operation for_each( square_operation op );
    square_operation for_each( coord_range range, square_operation op );
    void if_value_known_eliminate( square& sq );
    void if_candidate_unique_in_axis_solve( square& sq, axis ax );
    // void walk_axis_and(square& sq, axis ax, square_operation op);
    void get_coord_for_candidates(
        square& sq,
        std::map<size_t, std::set<coord> >& candidate_coord_map );
    void solve_axis_for_unique_candidate( square& sq, axis as );

private:
    grid& grid_;
};

}  // end namespace sudoku
}  // end namespace evilquinn

#endif  // SUDOKU_SOLVER_HPP
