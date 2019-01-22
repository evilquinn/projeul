
#include <sudoku/solver.hpp>

// DELETEME
using namespace evilquinn::sudoku;
void eliminate_from_range(grid& grid,
                          const coord coord_start,
                          const coord coord_end,
                          const size_t value)
{
    for ( size_t x = coord_start.x; x < coord_end.x; ++x )
    {
        for ( size_t y = coord_start.y; y < coord_end.y; ++y )
        {
            grid.at({x, y}).eliminate(value);
        }
    }
}

std::pair<dimensions, dimensions> nonet_from_coord(const coord coord)
{
    size_t x_start = ( coord.x / 3 ) * 3;
    size_t y_start = ( coord.y / 3 ) * 3;
    return std::pair<dimensions, dimensions>({x_start, y_start}, {x_start+3, y_start+3});
}

void scan_all_and_eliminate_knowns(grid& grid)
{
    auto dims = grid.get_dimensions();
    for ( size_t x = 0; x < dims.x; ++x )
    {
        for ( size_t y = 0; y < dims.y; ++y )
        {
            auto value = grid.at({x, y}).value();
            if ( value )
            {
                // update the column
                eliminate_from_range(grid, {x, 0}, {x+1, dims.y}, *value);
                // update the row
                eliminate_from_range(grid, {0, y}, {dims.x, y+1}, *value);
                // update the nonet
                auto nonet_dims = nonet_from_coord({x, y});
                eliminate_from_range(grid, nonet_dims.first, nonet_dims.second, *value);
            }
        }
    }
}

bool evilquinn::sudoku::solver::solve(grid& grid)
{
    bool solved = false;

    const size_t limit = 10;
    for ( size_t i = 0; i < limit; ++i )
    {
        scan_all_and_eliminate_knowns(grid);
    }

    return solved;
}
