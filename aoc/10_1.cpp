/**
 * You fly into the asteroid belt and reach the Ceres monitoring station. The Elves here
 * have an emergency: they're having trouble tracking all of the asteroids and can't
 * be sure they're safe.
 *
 * The Elves would like to build a new monitoring station in a nearby area of space;
 * they hand you a map of all of the asteroids in that region (your puzzle input).
 *
 * The map indicates whether each position is empty (.) or contains an asteroid (#).
 * The asteroids are much smaller than they appear on the map, and every asteroid is exactly
 * in the center of its marked position. The asteroids can be described with X,Y coordinates
 * where X is the distance from the left edge and Y is the distance from the top edge
 * (so the top-left corner is 0,0 and the position immediately to its right is 1,0).
 *
 * Your job is to figure out which asteroid would be the best place to build a new
 * monitoring station. A monitoring station can detect any asteroid to which it has
 * direct line of sight - that is, there cannot be another asteroid exactly between
 * them. This line of sight can be at any angle, not just lines aligned to the grid
 * or diagonally. The best location is the asteroid that can detect the largest number
 * of other asteroids.
 *
 * For example, consider the following map:
 *
 * .#..#
 * .....
 * #####
 * ....#
 * ...##
 * The best location for a new monitoring station on this map is the highlighted asteroid
 * at 3,4 because it can detect 8 asteroids, more than any other location. (The only asteroid
 * it cannot detect is the one at 1,0; its view of this asteroid is blocked by the asteroid
 * at 2,2.) All other asteroids are worse locations; they can detect 7 or fewer other asteroids.
 *
 * Here is the number of other asteroids a monitoring station on each asteroid could detect:
 *
 * .7..7
 * .....
 * 67775
 * ....7
 * ...87
 *
 * Here is an asteroid (#) and some examples of the ways its line of sight might be blocked.
 * If there were another asteroid at the location of a capital letter, the locations marked
 * with the corresponding lowercase letter would be blocked and could not be detected:
 *
 * #.........
 * ...A......
 * ...B..a...
 * .EDCG....a
 * ..F.c.b...
 * .....c....
 * ..efd.c.gb
 * .......c..
 * ....f...c.
 * ...e..d..c
 *
 * Here are some larger examples:
 *
 * Best is 5,8 with 33 other asteroids detected:
 * ......#.#.
 * #..#.#....
 * ..#######.
 * .#.#.###..
 * .#..#.....
 * ..#....#.#
 * #..#....#.
 * .##.#..###
 * ##...#..#.
 * .#....####
 *
 * Best is 1,2 with 35 other asteroids detected:
 * #.#...#.#.
 * .###....#.
 * .#....#...
 * ##.#.#.#.#
 * ....#.#.#.
 * .##..###.#
 * ..#...##..
 * ..##....##
 * ......#...
 * .####.###.
 *
 * Best is 6,3 with 41 other asteroids detected:
 * .#..#..###
 * ####.###.#
 * ....###.#.
 * ..###.##.#
 * ##.##.#.#.
 * ....###..#
 * ..#.#..#.#
 * #..#.#.###
 * .##...##.#
 * .....#.#..
 *
 * Best is 11,13 with 210 other asteroids detected:
 * .#..##.###...#######
 * ##.############..##.
 * .#.######.########.#
 * .###.#######.####.#.
 * #####.##.#.##.###.##
 * ..#####..#.#########
 * ####################
 * #.####....###.#.#.##
 * ##.#################
 * #####.##.###..####..
 * ..######..##.#######
 * ####.##.####...##..#
 * .#####..#.######.###
 * ##...#.##########...
 * #.##########.#######
 * .####.#.###.###.#.##
 * ....##.##.###..#####
 * .#.#.###########.###
 * #.#.#.#####.####.###
 * ###.##.####.##.#..##
 *
 * Find the best location for a new monitoring station. How many other asteroids can be detected from that location?
 **/

#include <iostream>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <numeric>
#include <boost/lexical_cast.hpp>

struct coord { size_t x = 0; size_t y = 0; };

std::ostream& operator<< (std::ostream& os, const coord& c)
{
    return os << "[ " << c.x << ", " << c.y << " ]";
}

bool within_limit(const coord& a, const coord& b)
{
    return a.x < b.x && a.y < b.y;
}
bool operator==(const coord& a, const coord& b)
{
    return a.x == b.x && a.y == b.y;
}

struct coord_incrementer
{
    size_t x_limit = 0;
    void operator()(coord& c, int by = 1) const
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
};

typedef std::pair<int, int> axis_type;


struct perim_walker
{
    coord origin;
    coord bound;
    mutable coord first_ = { origin.x, 0 };
    coord first() const
    {
        first_ = { origin.x, 0 };
        if ( first_ == origin ) return next(first_);
        return first_;
    }
    void advance(coord& c) const
    {
        if ( c.x == 0 )
        {
            if ( --c.y >= bound.y )
            {
                ++c.x;
                c.y = 0;
            }
        }
        else if ( c.y == 0 )
        {
            if ( ++c.x >= bound.x )
            {
                ++c.y;
                c.x = bound.x - 1;
            }
        }
        else if ( c.x == bound.x - 1 )
        {
            if ( ++c.y >= bound.y )
            {
                --c.x;
                c.y = bound.y - 1;
            }
        }
        else if ( c.y == bound.y - 1 )
        {
            if ( --c.x >= bound.x )
            {
                --c.y;
                c.x = 0;
            }
        }
        // now goes round for ever
        //if ( c == first_ ) c = bound;
        if ( c == origin ) advance(c);
    }
    coord next(coord c) const
    {
        advance(c);
        return c;
    }

};

enum class status {
    occd = '#',
    unoccd = '.',
    org = 'O',
    hidden = 'x',
    vapd = '*'
};
typedef std::vector<status> line_type;
typedef std::vector<line_type> map_type;

std::ostream& operator<<(std::ostream& os, const line_type& line)
{
    for ( auto&& stat : line )
    {
        os << static_cast<char>(stat);
    }
    return os;
}

std::ostream& operator<<(std::ostream& os, const map_type& map)
{
    for ( auto&& line : map )
    {
        os << line << "\n";
    }
    return os;
}

namespace asteroid_map
{

coord limit(const map_type& map)
{
    if ( map.empty() ) return { 0, 0 };
    return { map[0].size(), map.size() };
}
const map_type::value_type::value_type& at(const map_type& map, coord c)
{
    auto bound = limit(map);
    if ( ! within_limit( c, bound ) )
    {
        std::ostringstream msg;
        msg << "coord " << c << " not within bounds of map, bound: " << bound;
        throw std::runtime_error(msg.str());
    }
    return map[c.y][c.x];
}
map_type::value_type::value_type& at(map_type& map, coord c)
{
    return const_cast< map_type::value_type::value_type& >(at(
               const_cast< const map_type& >(map), c));
}
bool is_set(const map_type& map, coord c, status v)
{
    return at(map, c) == v;
}
bool is_clear(const map_type& map, coord c)
{
    return at(map, c) == status::unoccd;
}
void set(map_type& map, coord c, status v)
{
    at(map, c) = v;
}
axis_type axis_step(coord from, coord to)
{
    axis_type dist = { to.x - from.x, to.y - from.y };
    const auto gcdiv = std::gcd(dist.first, dist.second);
    dist = { dist.first/gcdiv, dist.second/gcdiv };
    return dist;
}
map_type eliminate_obstructed(const map_type& map, const coord origin)
{
    coord_incrementer incr = { map.empty() ? 0 : map[0].size() };
    const coord lim = limit(map);
    auto result = map;
    // go right, then left
    auto i = origin;
    set(result, i, status::org);
    for ( incr(i); within_limit( i, lim ); incr(i) )
    {
        if ( at(result, i) == status::occd )
        {
            axis_type dist = axis_step(origin, i);
            //std::cout << "DIST: " << dist.first << " : " << dist.second << "\n";
            for ( coord cant_see = { i.x + dist.first, i.y + dist.second };
                  within_limit(cant_see, lim);
                  cant_see = { cant_see.x + dist.first, cant_see.y + dist.second } )
            {
                set(result, cant_see, status::hidden);
            }
        }
    }
    i = origin;
    for ( incr(i, -1); within_limit( i, limit(result) ); incr(i, -1) ) // coord and incr overflows like unsigned
    {
        if ( at(result, i) == status::occd )
        {
            axis_type dist = axis_step(origin, i);
            for ( coord cant_see = { i.x + dist.first, i.y + dist.second };
                  within_limit(cant_see, lim);
                  cant_see = { cant_see.x + dist.first, cant_see.y + dist.second } )
            {
                if ( ! is_clear(result, cant_see) ) set(result, cant_see, status::hidden);
            }
        }
    }
    return result;
}
coord vapourise(map_type map, coord origin, const size_t n)
{
    coord result;
    set(map, origin, status::org);
    auto count = std::min(map.empty()?0:map[0].size()*map.size() - 1, n);
    std::cout << "trimming n: " << n << " down to only the available: " << count << "\n";

    perim_walker walker = { origin, limit(map) };

    axis_type last_axis;
    for ( auto i = walker.first(); within_limit(i, walker.bound); walker.advance(i) )
    {
        // laser the closest asteroid on this axis
        axis_type dist = axis_step(origin, i);
        if ( last_axis == dist ) continue;
        for ( coord j = { origin.x + dist.first, origin.y + dist.second };
              within_limit(j, walker.bound);
              j = { j.x + dist.first, j.y + dist.second })
        {
            if ( at(map, j) == status::occd )
            {
                at(map, j) = status::vapd;
                if ( --count == 0 ) return j; else std::cout << map << "\n\n";
                std::cout << "vapd: " << j << ", to go: " << count << "\n";
                break;
            }
        }
        last_axis = dist;
    }
    return result;
}
size_t count(const map_type& map, status v)
{
    size_t total = 0;
    for ( auto&& line : map )
    {
        total += std::count(line.begin(), line.end(), v);
    }
    return total;
}
size_t count_asteroids(const map_type& map)
{
    return count(map, status::occd);
}
coord find_best(const map_type& map)
{
    coord_incrementer incr = { map.empty() ? 0 : map[0].size() };
    size_t best_count = 0;
    coord best_coord;
    std::cout << "map:\n" << map << "\n";
    for ( coord i = { 0, 0 }; within_limit(i, limit(map)); incr(i) )
    {
        if ( ! is_clear(map, i) )
        {
            auto observable = eliminate_obstructed(map, i);
            size_t count = count_asteroids(observable);
            if ( count > best_count )
            {
                best_count = count;
                best_coord = i;
            }
        }
    }
    return best_coord;
}
map_type to_map(std::istream& map_input)
{
    map_type result;
    // something
    std::string line_str;
    while ( map_input >> line_str )
    {
        line_type line;
        std::transform(line_str.begin(), line_str.end(), std::back_inserter(line), [](char c){ return static_cast<status>(c); });
        result.emplace_back(std::move(line));
    }
    return result;
}
map_type to_map(const std::string& s)
{
    std::istringstream input(s);
    return to_map(input);
}

}

int main()
{
    std::vector<std::string> data = {
/**
 * #######
 * #######
 * #######
 * #######
 * #######
 * #######
 * #######
 */
        "#######\n#######\n#######\n#######\n#######\n#######\n#######\n",
/**
 * .#..#
 * .....
 * #####
 * ....#
 * ...##
 */
        ".#..#\n.....\n#####\n....#\n...##",
/**
 * Best is 5,8 with 33 other asteroids detected:
 * ......#.#.
 * #..#.#....
 * ..#######.
 * .#.#.###..
 * .#..#.....
 * ..#....#.#
 * #..#....#.
 * .##.#..###
 * ##...#..#.
 * .#....####
 **/
        "......#.#.\n#..#.#....\n..#######.\n.#.#.###..\n.#..#.....\n..#....#.#\n#..#....#.\n.##.#..###\n##...#..#.\n.#....####",
/**
 * Best is 1,2 with 35 other asteroids detected:
 * #.#...#.#.
 * .###....#.
 * .#....#...
 * ##.#.#.#.#
 * ....#.#.#.
 * .##..###.#
 * ..#...##..
 * ..##....##
 * ......#...
 * .####.###.
 **/
        "#.#...#.#.\n.###....#.\n.#....#...\n##.#.#.#.#\n....#.#.#.\n.##..###.#\n..#...##..\n..##....##\n......#...\n.####.###.",
/**
 * Best is 6,3 with 41 other asteroids detected:
 * .#..#..###
 * ####.###.#
 * ....###.#.
 * ..###.##.#
 * ##.##.#.#.
 * ....###..#
 * ..#.#..#.#
 * #..#.#.###
 * .##...##.#
 * .....#.#..
 **/
        ".#..#..###\n####.###.#\n....###.#.\n..###.##.#\n##.##.#.#.\n....###..#\n..#.#..#.#\n#..#.#.###\n.##...##.#\n.....#.#..",
/**
 * Best is 11,13 with 210 other asteroids detected:
 * .#..##.###...#######
 * ##.############..##.
 * .#.######.########.#
 * .###.#######.####.#.
 * #####.##.#.##.###.##
 * ..#####..#.#########
 * ####################
 * #.####....###.#.#.##
 * ##.#################
 * #####.##.###..####..
 * ..######..##.#######
 * ####.##.####...##..#
 * .#####..#.######.###
 * ##...#.##########...
 * #.##########.#######
 * .####.#.###.###.#.##
 * ....##.##.###..#####
 * .#.#.###########.###
 * #.#.#.#####.####.###
 * ###.##.####.##.#..##
 *
 */
        ".#..##.###...#######\n"
        "##.############..##.\n"
        ".#.######.########.#\n"
        ".###.#######.####.#.\n"
        "#####.##.#.##.###.##\n"
        "..#####..#.#########\n"
        "####################\n"
        "#.####....###.#.#.##\n"
        "##.#################\n"
        "#####.##.###..####..\n"
        "..######..##.#######\n"
        "####.##.####...##..#\n"
        ".#####..#.######.###\n"
        "##...#.##########...\n"
        "#.##########.#######\n"
        ".####.#.###.###.#.##\n"
        "....##.##.###..#####\n"
        ".#.#.###########.###\n"
        "#.#.#.#####.####.###\n"
        "###.##.####.##.#..##\n",

/**
 *
 * #..#....#...#.#..#.......##.#.####
 * #......#..#.#..####.....#..#...##.
 * .##.......#..#.#....#.#..#.#....#.
 * ###..#.....###.#....##.....#...#..
 * ...#.##..#.###.......#....#....###
 * .####...##...........##..#..#.##..
 * ..#...#.#.#.###....#.#...##.....#.
 * ......#.....#..#...##.#..##.#..###
 * ...###.#....#..##.#.#.#....#...###
 * ..#.###.####..###.#.##..#.##.###..
 * ...##...#.#..##.#............##.##
 * ....#.##.##.##..#......##.........
 * .#..#.#..#.##......##...#.#.#...##
 * .##.....#.#.##...#.#.#...#..###...
 * #.#.#..##......#...#...#.......#..
 * #.......#..#####.###.#..#..#.#.#..
 * .#......##......##...#..#..#..###.
 * #.#...#..#....##.#....#.##.#....#.
 * ....#..#....##..#...##..#..#.#.##.
 * #.#.#.#.##.#.#..###.......#....###
 * ...#.#..##....###.####.#..#.#..#..
 * #....##..#...##.#.#.........##.#..
 * .#....#.#...#.#.........#..#......
 * ...#..###...#...#.#.#...#.#..##.##
 * .####.##.#..#.#.#.#...#.##......#.
 * .##....##..#.#.#.......#.....####.
 * #.##.##....#...#..#.#..###..#.###.
 * ...###.#..#.....#.#.#.#....#....#.
 * ......#...#.........##....#....##.
 * .....#.....#..#.##.#.###.#..##....
 * .#.....#.#.....#####.....##..#....
 * .####.##...#.......####..#....##..
 * .#.#.......#......#.##..##.#.#..##
 * ......##.....##...##.##...##......
 **/
        "#..#....#...#.#..#.......##.#.####\n"
        "#......#..#.#..####.....#..#...##.\n"
        ".##.......#..#.#....#.#..#.#....#.\n"
        "###..#.....###.#....##.....#...#..\n"
        "...#.##..#.###.......#....#....###\n"
        ".####...##...........##..#..#.##..\n"
        "..#...#.#.#.###....#.#...##.....#.\n"
        "......#.....#..#...##.#..##.#..###\n"
        "...###.#....#..##.#.#.#....#...###\n"
        "..#.###.####..###.#.##..#.##.###..\n"
        "...##...#.#..##.#............##.##\n"
        "....#.##.##.##..#......##.........\n"
        ".#..#.#..#.##......##...#.#.#...##\n"
        ".##.....#.#.##...#.#.#...#..###...\n"
        "#.#.#..##......#...#...#.......#..\n"
        "#.......#..#####.###.#..#..#.#.#..\n"
        ".#......##......##...#..#..#..###.\n"
        "#.#...#..#....##.#....#.##.#....#.\n"
        "....#..#....##..#...##..#..#.#.##.\n"
        "#.#.#.#.##.#.#..###.......#....###\n"
        "...#.#..##....###.####.#..#.#..#..\n"
        "#....##..#...##.#.#.........##.#..\n"
        ".#....#.#...#.#.........#..#......\n"
        "...#..###...#...#.#.#...#.#..##.##\n"
        ".####.##.#..#.#.#.#...#.##......#.\n"
        ".##....##..#.#.#.......#.....####.\n"
        "#.##.##....#...#..#.#..###..#.###.\n"
        "...###.#..#.....#.#.#.#....#....#.\n"
        "......#...#.........##....#....##.\n"
        ".....#.....#..#.##.#.###.#..##....\n"
        ".#.....#.#.....#####.....##..#....\n"
        ".####.##...#.......####..#....##..\n"
        ".#.#.......#......#.##..##.#.#..##\n"
        "......##.....##...##.##...##......\n"
    };

    for ( auto&& datum : data )
    {

        auto map = asteroid_map::to_map(datum);

        // 10_1
        auto best_coord = asteroid_map::find_best(map);

        // 10_2
        auto result = asteroid_map::vapourise(map, best_coord, 200);

        std::cout << "best count: " << result << "\n";
        break;
    }

    return 0;
}
