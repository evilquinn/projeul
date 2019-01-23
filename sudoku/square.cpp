
#include <iostream>
#include <sudoku/square.hpp>


evilquinn::sudoku::square::square(coord pos, const size_t num_candidates) :
    pos_(pos),
    candidates_()
{
    for ( size_t candidate = num_candidates; candidate > 0; --candidate )
    {
        candidates_.insert(candidate);
    }
    validate();
}

boost::optional<size_t> evilquinn::sudoku::square::value() const
{
    if ( candidates_.size() == 1 )
    {
        return *candidates_.begin();
    }
    return boost::optional<size_t>{};
}

evilquinn::sudoku::coord evilquinn::sudoku::square::pos() const
{
    return pos_;
}

const evilquinn::sudoku::square::candidate_set& evilquinn::sudoku::square::candidates() const
{
    return candidates_;
}

void evilquinn::sudoku::square::eliminate(size_t candidate)
{
    if ( candidates_.size() == 1 && *candidates_.begin() == candidate )
    {
        return;
    }
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

void evilquinn::sudoku::square::set_value(size_t value)
{
    if ( value == 0 )
    {
        return;
    }
    auto cands_copy = candidates_;
    cands_copy.erase(value);
    eliminate(cands_copy);
}

std::string evilquinn::sudoku::square::to_string() const
{
    std::ostringstream as_string;
    as_string << sudoku::to_string(pos_)
              << "("
              << candidates_.size()
              << ",";
    if ( candidates_.size() == 1 )
    {
        as_string << *candidates_.begin();
    }
    else
    {
        as_string << "*";
    }
    as_string << ")";
    return as_string.str();
}

std::string evilquinn::sudoku::to_string(const coord& c)
{
    std::ostringstream as_string;
    as_string << "[" << c.x << "," << c.y << "]";
    return as_string.str();
}
