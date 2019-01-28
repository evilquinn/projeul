
#include <sudoku/grid.hpp>
#include <cmath>

static size_t determine_number_of_candidates(
    evilquinn::sudoku::dimensions dim )
{
    size_t larger = dim.x;
    if ( larger < dim.y )
    {
        larger = dim.y;
    }
    return larger;
}

evilquinn::sudoku::grid::grid( dimensions dim ) : dim_( dim ), squares_()
{
    const size_t num_candidates = determine_number_of_candidates( dim );

    for ( size_t y = 0; y < dim_.y; ++y )
    {
        for ( size_t x = 0; x < dim_.x; ++x )
        {
            // either start a new row else bolt onto back of existing row
            if ( squares_.size() == x )
            {
                squares_.emplace_back ( line{ square( coord{ x, y }, num_candidates ) } );
            }
            else
            {
                squares_[x].emplace_back ( square( coord{ x, y }, num_candidates ) );
            }
        }
    }
}

evilquinn::sudoku::dimensions evilquinn::sudoku::grid::get_dimensions() const
{
    return dim_;
}

evilquinn::sudoku::square& evilquinn::sudoku::grid::at( const coord pos )
{
    return squares_[pos.x][pos.y];
}

std::ostream& evilquinn::sudoku::grid::stream_out( std::ostream& os ) const
{
    static const char* underline = "\033[4m";
    static const char* underline_off = "\033[0m";
    bool underlining = false;
    const size_t nonet_side = std::sqrt(dim_.x);

    for ( size_t y = 0; y < dim_.y; ++y )
    {
        if ( ( ( y + 1 ) / nonet_side ) * nonet_side == y + 1 )
        {
            // if next line is beginning of a nonet, underline this line
            underlining = true;
            os << underline;
        }
        for ( size_t x = 0; x < dim_.x; ++x )
        {
            os << squares_[x][y];
            if ( ( ( x + 1 ) / nonet_side ) * nonet_side == x + 1 )
            {
                // if next column is beginning of nonet, put a bar after this
                // column
                // but don't underline last bar
                if ( underlining && x + 1 == dim_.x )
                {
                    underlining = false;
                    os << underline_off;
                }
                os << "|";
            }
            else
            {
                os << " ";
            }
        }
        os << "\n";
    }
    return os;
}

size_t evilquinn::sudoku::grid::count_remaining() const
{
    size_t total = 0;
    for ( auto&& line : squares_ )
    {
        for ( auto&& square : line )
        {
            total += square.candidates().size();
        }
    }
    total -= 81;
    return total;
}

bool evilquinn::sudoku::grid::solved() const
{
    return count_remaining() == 0;
}
