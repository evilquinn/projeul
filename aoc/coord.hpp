
#ifndef AOC_COORD_HPP
#define AOC_COORD_HPP

#include <cstddef>
#include <iostream>

namespace coord_util
{

struct coord
{
    ptrdiff_t x = 0;
    ptrdiff_t y = 0;
    coord() : x(0), y(0) {}
    coord(ptrdiff_t x, ptrdiff_t y) : x(x), y(y) {}
};

bool operator< (const coord& a, const coord& b);
std::ostream& operator<< (std::ostream& os, const coord& c);
coord& operator+= (coord& lhs, coord rhs);
coord operator+ (coord lhs, coord rhs);
coord& operator-= (coord& lhs, coord rhs);
coord operator- (coord lhs, coord rhs);
bool within_limit(const coord& a, const coord& b);
bool operator==(const coord& a, const coord& b);

struct coord_incrementer
{
    ptrdiff_t x_limit = 0;
    void operator()(coord& c, ptrdiff_t by = 1) const;
};

// implementation - move to some included header perhaps?

inline std::ostream& operator<< (std::ostream& os, const coord& c)
{
    return os << "{ " << c.x << ", " << c.y << " }";
}
inline coord& operator+= (coord& lhs, coord rhs)
{
    lhs.x += rhs.x;
    lhs.y += rhs.y;
    return lhs;
}
inline coord operator+ (coord lhs, coord rhs)
{
    return lhs += rhs;
}
inline coord& operator-= (coord& lhs, coord rhs)
{
    lhs.x -= rhs.x;
    lhs.y -= rhs.y;
    return lhs;
}
inline coord operator- (coord lhs, coord rhs)
{
    return lhs -= rhs;
}

inline bool within_limit(const coord& a, const coord& b)
{
    return a.x < b.x && a.y < b.y;
}
inline bool operator<(const coord& a, const coord& b)
{
    if ( a.y < b.y ) return true;
    else if ( a.y > b.y ) return false;
    else return ( a.x < b.x );
}
inline bool operator==(const coord& a, const coord& b)
{
    return a.x == b.x && a.y == b.y;
}

inline void coord_incrementer::operator()(coord& c, ptrdiff_t by) const
{
    if ( by > 0 )
    {
        for ( ; by > 0; --by )
        {
            if ( ++c.x >= x_limit )
            {
                ++c.y;
                c.x = 0;
            }
        }
    }
    else
    {
        for ( ; by < 0; ++by )
        {
            if ( c.x == 0 )
            {
                --c.y;
                c.x = x_limit-1;
            }
            else
            {
                --c.x;
            }
        }
    }
}

} // end namaspace coord_util

#endif // AOC_COORD_HPP
