/*
 * https://adventofcode.com/2020/day/15
 */

#include <iostream>
#include <map>
#include <set>
#include <vector>
#include <algorithm>

#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>

struct coord
{
    ptrdiff_t x;
    ptrdiff_t y;
    ptrdiff_t z;
    ptrdiff_t w;
    coord() : x(0), y(0), z(0), w(0)
    {}
    coord(ptrdiff_t x, ptrdiff_t y, ptrdiff_t z) : x(x), y(y), z(z), w(0)
    {}
    coord(ptrdiff_t x, ptrdiff_t y, ptrdiff_t z, ptrdiff_t w) : x(x), y(y), z(z), w(w)
    {}
};
bool operator< (const coord& lhs, const coord& rhs)
{
    if ( lhs.w < rhs.w ) return true;
    if ( lhs.w > rhs.w ) return false;
    if ( lhs.z < rhs.z ) return true;
    if ( lhs.z > rhs.z ) return false;
    if ( lhs.y < rhs.y ) return true;
    if ( lhs.y > rhs.y ) return false;
    return lhs.x < rhs.x;
}
bool operator== (const coord& lhs, const coord& rhs)
{
    return lhs.x == rhs.x &&
           lhs.y == rhs.y &&
           lhs.z == rhs.z &&
           lhs.w == rhs.w;
}
coord& operator+= (coord& lhs, const coord& rhs)
{
    lhs.x += rhs.x;
    lhs.y += rhs.y;
    lhs.z += rhs.z;
    lhs.w += rhs.w;
    return lhs;
}
coord operator+ (coord lhs, const coord& rhs)
{
    return lhs += rhs;
}
std::ostream& operator<< (std::ostream& os, const coord& c)
{
    return os << "[ " << c.x << ", " << c.y << ", " << c.z << ", " << c.w << " ]";
}
enum map_char
{
    inactive = '.',
    active   = '#'
};
typedef std::map<coord, char> map_type;
map_type map_from_string(const std::string& str)
{
    map_type result;
    coord curr;
    for ( auto&& c : str )
    {
        if ( c == '\n' )
        {
            curr.x = 0;
            ++curr.y;
            continue;
        }
        if ( c == active ) result[curr] = c;
        ++curr.x;
    }
    return result;
}
std::set<coord> active_coords_from_string(const std::string& str)
{
    std::set<coord> result;
    coord curr;
    for ( auto&& c : str )
    {
        if ( c == '\n' )
        {
            curr.x = 0;
            ++curr.y;
            continue;
        }
        if ( c == active ) result.insert(curr);
        ++curr.x;
    }
    return result;
}
std::ostream& operator<< (std::ostream& os, const map_type& map)
{
    for ( auto&& pos : map )
    {
        std::cout << pos.first << ": " << pos.second << "\n";
    }
    return os;
}
std::ostream& operator<< (std::ostream& os, const std::set<coord>& coords)
{
    for ( auto&& c : coords )
    {
        std::cout << c << "\n";
    }
    return os;
}

const std::vector<coord> neighbour_units = {
    // time -1
    // z-layer below
    coord{ -1, -1, -1, -1 },
    coord{ -1,  0, -1, -1 },
    coord{ -1,  1, -1, -1 },
    coord{  0, -1, -1, -1 },
    coord{  0,  0, -1, -1 },
    coord{  0,  1, -1, -1 },
    coord{  1, -1, -1, -1 },
    coord{  1,  0, -1, -1 },
    coord{  1,  1, -1, -1 },

    // current z-layer
    coord{ -1, -1,  0, -1 },
    coord{ -1,  0,  0, -1 },
    coord{ -1,  1,  0, -1 },
    coord{  0, -1,  0, -1 },
    coord{  0,  0,  0, -1 },
    coord{  0,  1,  0, -1 },
    coord{  1, -1,  0, -1 },
    coord{  1,  0,  0, -1 },
    coord{  1,  1,  0, -1 },

    // z-layer above
    coord{ -1, -1,  1, -1 },
    coord{ -1,  0,  1, -1 },
    coord{ -1,  1,  1, -1 },
    coord{  0, -1,  1, -1 },
    coord{  0,  0,  1, -1 },
    coord{  0,  1,  1, -1 },
    coord{  1, -1,  1, -1 },
    coord{  1,  0,  1, -1 },
    coord{  1,  1,  1, -1 },

    // time 0
    // z-layer below
    coord{ -1, -1, -1,  0 },
    coord{ -1,  0, -1,  0 },
    coord{ -1,  1, -1,  0 },
    coord{  0, -1, -1,  0 },
    coord{  0,  0, -1,  0 },
    coord{  0,  1, -1,  0 },
    coord{  1, -1, -1,  0 },
    coord{  1,  0, -1,  0 },
    coord{  1,  1, -1,  0 },

    // current z-layer
    coord{ -1, -1,  0,  0 },
    coord{ -1,  0,  0,  0 },
    coord{ -1,  1,  0,  0 },
    coord{  0, -1,  0,  0 },
    coord{  0,  0,  0,  0 }, // me!
    coord{  0,  1,  0,  0 },
    coord{  1, -1,  0,  0 },
    coord{  1,  0,  0,  0 },
    coord{  1,  1,  0,  0 },

    // z-layer above
    coord{ -1, -1,  1,  0 },
    coord{ -1,  0,  1,  0 },
    coord{ -1,  1,  1,  0 },
    coord{  0, -1,  1,  0 },
    coord{  0,  0,  1,  0 },
    coord{  0,  1,  1,  0 },
    coord{  1, -1,  1,  0 },
    coord{  1,  0,  1,  0 },
    coord{  1,  1,  1,  0 },

    // z-layer below
    coord{ -1, -1, -1,  1 },
    coord{ -1,  0, -1,  1 },
    coord{ -1,  1, -1,  1 },
    coord{  0, -1, -1,  1 },
    coord{  0,  0, -1,  1 },
    coord{  0,  1, -1,  1 },
    coord{  1, -1, -1,  1 },
    coord{  1,  0, -1,  1 },
    coord{  1,  1, -1,  1 },

    // current z-layer
    coord{ -1, -1,  0,  1 },
    coord{ -1,  0,  0,  1 },
    coord{ -1,  1,  0,  1 },
    coord{  0, -1,  0,  1 },
    coord{  0,  0,  0,  1 },
    coord{  0,  1,  0,  1 },
    coord{  1, -1,  0,  1 },
    coord{  1,  0,  0,  1 },
    coord{  1,  1,  0,  1 },

    // z-layer above
    coord{ -1, -1,  1,  1 },
    coord{ -1,  0,  1,  1 },
    coord{ -1,  1,  1,  1 },
    coord{  0, -1,  1,  1 },
    coord{  0,  0,  1,  1 },
    coord{  0,  1,  1,  1 },
    coord{  1, -1,  1,  1 },
    coord{  1,  0,  1,  1 },
    coord{  1,  1,  1,  1 }
};

class cycler
{
public:
    cycler(const std::string& str) :
        map_(map_from_string(str)),
        actives_(active_coords_from_string(str))
    {}
    void cycle()
    {
        static const coord zeroc = { 0, 0, 0, 0 };
        std::set<coord> cands;
        std::set<coord> next_actives;
        for ( auto&& a : actives_ )
        {
            for ( auto&& n : neighbour_units )
            {
                cands.insert( a + n );
            }
        }
        for ( auto&& cand : cands )
        {
            size_t active_neighbours = 0;
            for ( auto&& n : neighbour_units )
            {
                if ( n == zeroc ) continue;
                if ( actives_.count(cand + n) > 0 ) ++active_neighbours;
            }
            switch ( actives_.count(cand) )
            {
            case 0 : if (active_neighbours == 3 ) next_actives.insert(cand); break;
            case 1 : if ( active_neighbours == 2 || active_neighbours == 3 ) next_actives.insert(cand); break;
            default : throw std::runtime_error("std::set<coord>::count() returned neither 0 or 1, wtf");
            }
        }
        actives_ = std::move(next_actives);
    }
    void cycle(size_t n)
    {
        while ( n-- > 0 )
        {
            cycle();
        }
    }
    size_t count_actives() const
    {
        return actives_.size();
    }
private:
    map_type map_;
    std::set<coord> actives_;
};

int main()
{
#if 1
    std::vector<std::string> data = {
        ".#.\n"
        "..#\n"
        "###",
        "...#..#.\n"
        "#..#...#\n"
        ".....###\n"
        "##....##\n"
        "......##\n"
        "........\n"
        ".#......\n"
        "##...#.."
    };
    for ( auto&& datum : data )
    {
        cycler cyc(datum);
        //cyc.cycle(6);
        for ( size_t i = 0; i < 6; ++i )
        {
            cyc.cycle();
            auto count = cyc.count_actives();
        }
        auto result = cyc.count_actives();
        std::cout << "result: " << result << std::endl;
    }
#endif
    return 0;
}
