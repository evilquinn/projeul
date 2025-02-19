
#ifndef AOC_COORD_HPP
#define AOC_COORD_HPP

#include <iostream>

namespace coord_util
{

template<typename T>
struct basic_coord
{
    typedef T value_type;
    T x = 0;
    T y = 0;
    basic_coord() : x(0), y(0) {}
    basic_coord(T x, T y) : x(x), y(y) {}
};

template<typename T>
struct basic_coord_incrementer
{
    T x_limit = 0;
    T x_origin = 0;
    void operator()(basic_coord<T>& c, T by = 1) const;
};

template<typename T>
basic_coord_incrementer<T> make_incrementer(const basic_coord<T>& limit, const basic_coord<T>& origin = { 0, 0 })
{
    return basic_coord_incrementer<T>(limit.x, origin.x);
}

template<typename T>
std::ostream& operator<< (std::ostream& os, const basic_coord<T>& c)
{
    return os << "{ " << c.x << ", " << c.y << " }";
}
template<typename T>
basic_coord<T>& operator+= (basic_coord<T>& lhs, basic_coord<T> rhs)
{
    lhs.x += rhs.x;
    lhs.y += rhs.y;
    return lhs;
}
template<typename T>
basic_coord<T> operator+ (basic_coord<T> lhs, basic_coord<T> rhs)
{
    return lhs += rhs;
}
template<typename T>
basic_coord<T>& operator-= (basic_coord<T>& lhs, basic_coord<T> rhs)
{
    lhs.x -= rhs.x;
    lhs.y -= rhs.y;
    return lhs;
}
template<typename T>
basic_coord<T> operator- (basic_coord<T> lhs, basic_coord<T> rhs)
{
    return lhs -= rhs;
}

template<typename T>
bool within_limit(const basic_coord<T>& a, const basic_coord<T>& b)
{
    return a.x < b.x && a.y < b.y;
}
template<typename T>
bool operator<(const basic_coord<T>& a, const basic_coord<T>& b)
{
    if ( a.y < b.y ) return true;
    else if ( a.y > b.y ) return false;
    else return ( a.x < b.x );
}
template<typename T>
bool operator==(const basic_coord<T>& a, const basic_coord<T>& b)
{
    return a.x == b.x && a.y == b.y;
}

template<typename T>
void basic_coord_incrementer<T>::operator()(basic_coord<T>& c, T by) const
{
    if ( by > 0 )
    {
        for ( ; by > 0; --by )
        {
            if ( ++c.x >= x_limit )
            {
                ++c.y;
                c.x = x_origin;
            }
        }
    }
    else
    {
        for ( ; by < 0; ++by )
        {
            if ( c.x == x_origin )
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

template<typename T>
struct std::hash<coord_util::basic_coord<T>>
{
    std::size_t operator()(const coord_util::basic_coord<T>& c) const noexcept
    {
        std::size_t h1 = std::hash<T>{}(c.x);
        std::size_t h2 = std::hash<T>{}(c.y);
        return h1 ^ (h2 << 1); // or use boost::hash_combine
    }
};

#endif // AOC_COORD_HPP
