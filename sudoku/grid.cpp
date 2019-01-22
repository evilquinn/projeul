
#include <sudoku/grid.hpp>

static size_t determine_number_of_candidates(evilquinn::sudoku::dimensions dim)
{
    size_t larger = dim.x;
    if (larger < dim.y )
    {
        larger = dim.y;
    }
    return larger;
}

evilquinn::sudoku::grid::grid(dimensions dim) :
    dim_(dim),
    squares_()
{
    const size_t num_candidates = determine_number_of_candidates(dim);

    for ( size_t y = 0; y < dim_.y; ++y )
    {
        line row;
        for ( size_t x = 0; x < dim_.x; ++x )
        {
            row.emplace_back(square(coord{x, y}, num_candidates));
        }
        squares_.emplace_back(std::move(row));
    }
}

evilquinn::sudoku::square& evilquinn::sudoku::grid::at(const coord pos)
{
    return squares_[pos.y][pos.x];
}

void evilquinn::sudoku::grid::set(const coord pos, const size_t value)
{
    at(pos).set_value(value);
}

std::string evilquinn::sudoku::grid::to_string() const
{
    std::ostringstream as_string;
    for ( auto&& row : squares_ )
    {
        for ( auto&& square : row )
        {
            as_string << square.to_string() << ",";
        }
        as_string << "\n";
    }
    return as_string.str();
}

