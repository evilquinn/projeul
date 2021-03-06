
#ifndef SUDOKU_SQUARE_HPP
#define SUDOKU_SQUARE_HPP

#include <boost/optional.hpp>
#include <map>
#include <set>
#include <sstream>
#include <stdexcept>

namespace evilquinn
{
namespace sudoku
{
struct coord
{
    size_t x;
    size_t y;
    bool operator<( const coord& rhs ) const
    {
        return x < rhs.x ? true : x == rhs.x && y < rhs.y ? true : false;
    }
    bool operator==( const coord& rhs ) const
    {
        return x == rhs.x && y == rhs.y;
    }
    bool operator<=( const coord& rhs ) const
    {
        return operator<(rhs) || operator==(rhs);
    }
    bool operator>( const coord& rhs ) const
    {
        return  ! operator<=(rhs);
    }
};
std::string to_string( const coord& c );

class square
{
public:
    square( coord pos, size_t num_candidates );
    using candidate_set = std::set<size_t>;
    void eliminate( size_t candidate );
    void eliminate( candidate_set candidates );
    void set( candidate_set candidates );
    void set( size_t value );
    boost::optional<size_t> value() const;
    coord pos() const;
    const candidate_set& candidates() const;

    std::ostream& stream_out(std::ostream& os) const;

    class illegal_square : public std::runtime_error
    {
    public:
        illegal_square( std::string what )
            : std::runtime_error( std::move( what ) )
        {
        }
    };

private:
    void validate();

    coord pos_;
    candidate_set candidates_;
};

}  // end namespace sudoku
}  // namespace evilquinn

inline std::ostream& operator<<( std::ostream& os, const evilquinn::sudoku::square& sq)
{
    return sq.stream_out(os);
}

#endif  // SUDOKU_SQUARE_HPP
