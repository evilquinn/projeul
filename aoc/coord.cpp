#include <ostream>
#include "coord.hpp"

namespace coord_util
{

std::ostream& operator<< (std::ostream& os, const coord& c)
{
    return os << "[ " << c.x << ", " << c.y << " ]";
}
coord& operator+= (coord& lhs, coord rhs)
{
    lhs.x += rhs.x;
    lhs.y += rhs.y;
    return lhs;
}
coord operator+ (coord lhs, coord rhs)
{
    return lhs += rhs;
}
coord& operator-= (coord& lhs, coord rhs)
{
    lhs.x -= rhs.x;
    lhs.y -= rhs.y;
    return lhs;
}
coord operator- (coord lhs, coord rhs)
{
    return lhs -= rhs;
}

bool within_limit(const coord& a, const coord& b)
{
    return a.x < b.x && a.y < b.y;
}
bool operator<(const coord& a, const coord& b)
{
    if ( a.y < b.y ) return true;
    else if ( a.y > b.y ) return false;
    else return ( a.x < b.x );
}
bool operator==(const coord& a, const coord& b)
{
    return a.x == b.x && a.y == b.y;
}

void coord_incrementer::operator()(coord& c, int by) const
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

} // end namespace coord
