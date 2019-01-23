
#include <sudoku/solver.hpp>

namespace evilquinn
{
namespace sudoku
{

std::pair<dimensions, dimensions> nonet_from_coord(const coord coord)
{
    size_t x_start = ( coord.x / 3 ) * 3;
    size_t y_start = ( coord.y / 3 ) * 3;
    return std::pair<dimensions, dimensions>({x_start, y_start}, {x_start+3, y_start+3});
}

} // end namespace sudoku
} // end namespace evilquinn

evilquinn::sudoku::solver::solver(grid& grid) :
    grid_(grid)
{
}

evilquinn::sudoku::solver::square_operation
evilquinn::sudoku::solver::for_each(coord start, coord end, square_operation op)
{
    for ( size_t x = start.x; x < end.x; ++x )
    {
        for ( size_t y = start.y; y < end.y; ++y )
        {
            op(grid_.at({x, y}));
        }
    }
    return std::move(op);
}

evilquinn::sudoku::solver::square_operation
evilquinn::sudoku::solver::for_each(square_operation op)
{
    return for_each({0, 0}, grid_.get_dimensions(), std::move(op));
}

void evilquinn::sudoku::solver::if_value_known_eliminate(square& sq)
{
    auto value = sq.value();
    if ( value )
    {
        auto dims = grid_.get_dimensions();
        auto eliminate_value =
            std::bind(static_cast<void(square::*)(size_t)>(&square::eliminate),
                      std::placeholders::_1,
                      *value);
        auto pos = sq.pos();
        // update the column
        for_each({pos.x, 0}, {pos.x+1, dims.y}, eliminate_value);
        // update the row
        for_each({0, pos.y}, {dims.x, pos.y+1}, eliminate_value);
        // update the nonet
        auto nonet_dims = nonet_from_coord({pos.x, pos.y});
        for_each(nonet_dims.first, nonet_dims.second, std::move(eliminate_value));
    }
}

bool evilquinn::sudoku::solver::solve()
{
    bool solved = false;

    const size_t limit = 10;
    auto dims = grid_.get_dimensions();
    for ( size_t i = 0; i < limit; ++i )
    {
        for_each(std::bind(&solver::if_value_known_eliminate, this, std::placeholders::_1));
        for_each({0, 0}, {1, dims.y}, [this,dims](square& sq)
        {
            auto start_pos = sq.pos();
            std::map<size_t, std::set<coord> > value_pos_stats;
            size_t value_stats_coord_count = 0;
            for_each({0, start_pos.y}, {dims.x, start_pos.y+1}, [&](square& sqi)
            {
                auto candidates = sqi.candidates();
                if ( candidates.size() > 1 )
                {
                    ++value_stats_coord_count;
                    std::for_each(candidates.begin(), candidates.end(), [&](const size_t value)
                    {
                        value_pos_stats[value].insert(sqi.pos());
                    });
                }
            });
            if ( value_stats_coord_count > 1 )
            {
                std::map<coord, std::pair<size_t, size_t> > coord_value_counts;
                for ( auto&& value_stat : value_pos_stats )
                {
                    if ( value_stat.second.size() == 1 )
                    {
                        auto& value_count = coord_value_counts[*value_stat.second.begin()];
                        value_count.first = value_stat.first;
                        value_count.second += 1;
                    }
                }
                for ( auto&& coord_count : coord_value_counts )
                {
                    if ( coord_count.second.second == 1 )
                    {
                        auto& solved = grid_.at(coord_count.first);
                        solved.set_value(coord_count.second.first);
                        if_value_known_eliminate(solved);
                    }
                }
            }
        });
    }

    return solved;
}
