
#include <iostream>
#include <sudoku/square.hpp>


evilquinn::sudoku::square::square(coord pos, size_t num_candidates) :
    pos_(pos),
    candidates_()
{
    for ( ; num_candidates > 0; --num_candidates )
    {
        candidates_.insert(num_candidates);
    }
    validate();
}

void evilquinn::sudoku::square::eliminate(size_t candidate)
{
    candidates_.erase(candidate);
    validate();
}

void evilquinn::sudoku::square::validate()
{
    if ( candidates_.empty() )
    {
        std::string error(sudoku::to_string(pos_).append(
                              " candidate list is empty."));
        throw illegal_square(error);
    }
}

void evilquinn::sudoku::square::eliminate(candidate_set candidates)
{
    for ( auto&& candidate : candidates )
    {
        candidates_.erase(candidate);
    }
    validate();
}

std::string evilquinn::sudoku::square::to_string() const
{
    std::ostringstream as_string;
    as_string << sudoku::to_string(pos_) << "(" << candidates_.size() << ")";
    return as_string.str();
}

std::string evilquinn::sudoku::to_string(const coord& c)
{
    std::ostringstream as_string;
    as_string << "[" << c.x << "," << c.y << "]";
    return as_string.str();
}
