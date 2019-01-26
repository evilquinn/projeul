
#include <iostream>
#include <sudoku/square.hpp>
#include <sudoku/util.hpp>


evilquinn::sudoku::square::square( coord pos, const size_t num_candidates )
    : pos_( pos ), candidates_()
{
    for ( size_t candidate = num_candidates; candidate > 0; --candidate )
    {
        candidates_.insert( candidate );
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

const evilquinn::sudoku::square::candidate_set&
evilquinn::sudoku::square::candidates() const
{
    return candidates_;
}

void evilquinn::sudoku::square::eliminate( size_t candidate )
{
    if ( candidates_.size() == 1 && *candidates_.begin() == candidate )
    {
        return;
    }
    candidates_.erase( candidate );
    validate();
}

void evilquinn::sudoku::square::validate()
{
    if ( candidates_.empty() )
    {
        std::ostringstream error;
        error << pos_ << " candidate list is empty";
        throw illegal_square( error.str() );
    }
}

void evilquinn::sudoku::square::eliminate( candidate_set candidates )
{
    if ( candidates_ == candidates )
    {
        std::ostringstream error;
        error << pos_ << " eliminating candidates " << candidates << " would result in no candidates";
        throw illegal_square( error.str() );
    }
    for ( auto&& candidate : candidates )
    {
        candidates_.erase( candidate );
    }
    validate();
}

void evilquinn::sudoku::square::set( candidate_set candidates )
{
    candidate_set intersection;
    std::set_intersection(candidates_.begin(), candidates_.end(),
                          candidates.begin(),  candidates.end(),
                          std::inserter(intersection, intersection.begin()));
    std::swap(candidates_, intersection);
    validate();
}

void evilquinn::sudoku::square::set( size_t value )
{
    if ( value == 0 )
    {
        return;
    }
    auto cands_copy = candidates_;
    cands_copy.erase( value );
    eliminate( cands_copy );
}

std::ostream& evilquinn::sudoku::square::stream_out(std::ostream& os) const
{
//    os << pos_ << "(" << candidates_.size() << ",";
    if ( candidates_.size() == 1 )
    {
        os << *candidates_.begin();
    }
    else
    {
        os << "*";
    }
    os << "|";
    return os;
}