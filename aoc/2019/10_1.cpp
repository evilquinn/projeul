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
#include <set>
#include <map>
#include <iterator>
#include <numeric>
#include <cmath>
#include <boost/lexical_cast.hpp>

#include "../coord.hpp"
#include "../map.hpp"

//temp
using coord = coord_util::basic_coord<std::ptrdiff_t>;
using coord_incrementer = coord_util::basic_coord_incrementer<std::ptrdiff_t>;


typedef std::pair<int, int> axis_type;
axis_type to_axis(coord c)
{
    return { static_cast<int>(c.x), static_cast<int>(c.y) };
}

axis_type axis_step(coord from, coord to)
{
    axis_type dist = { to.x - from.x, to.y - from.y };
    const auto gcdiv = std::gcd(dist.first, dist.second);
    dist = { dist.first/gcdiv, dist.second/gcdiv };
    return dist;
}

class foob_walker
{
public:
    foob_walker(coord origin, coord bound) :
        origin_(origin),
        bound_(bound),
        first_({ origin.x, 0 }),
        angles_(sort_by_angles(origin_, bound_))
    {}
    axis_type first() const
    {
        if ( angles_.size() == 0 )
        {
            return to_axis(bound_);
        }
        return angles_.begin()->second;
    }
    void advance(axis_type& a) const
    {
        auto pos = angles_.find(axis_to_angle(a));
        if ( pos != angles_.end() )
        {
            std::advance(pos, 1);
            if ( pos != angles_.end() )
            {
                a = pos->second;
            }
            else
            {
                a = first();
            }
        }
    }
    axis_type next(axis_type a) const
    {
        advance(a);
        return a;
    }
    coord bound() const { return bound_; }
private:
    typedef std::map<ptrdiff_t, axis_type> angles_type;
    static angles_type sort_by_angles(coord origin, coord bound)
    {
        angles_type result;
        coord_incrementer incr = { bound.x };
        for ( coord i = { 0, 0 }; within_limit(i, bound); incr(i) )
        {
            if ( i == origin ) continue;
            axis_type dist = axis_step(origin, i);
            result[axis_to_angle(dist)] = dist;
        }
        return result;
    }
    static ptrdiff_t axis_to_angle(const axis_type& a)
    {
        // don't even look at this
        static const size_t fac = 100000;
        ptrdiff_t qpi = static_cast<ptrdiff_t>( std::acos(-1) * fac );
        qpi += qpi/2;
        double op = 0;
        double adj = 0;
        ptrdiff_t mult = 0;
        if ( a.first < 0 && a.second < 0 )
        {
            adj = std::abs(a.first);
            op = std::abs(a.second);
            mult = qpi * 3;
        }
        else if ( a.first < 0 && a.second > 0 )
        {
            op = std::abs(a.first);
            adj = std::abs(a.second);
            mult = qpi * 2;
        }
        else if ( a.first > 0 && a.second > 0 )
        {
            adj = std::abs(a.first);
            op = std::abs(a.second);
            mult = qpi * 1;
        }
        else if ( a.first > 0 && a.second < 0 )
        {
            op = std::abs(a.first);
            adj = std::abs(a.second);
        }
        else if ( a.first == 0 && a.second == 0 )
        {
            throw std::runtime_error("it's origin!");
        }
        else if ( a.first == 0 )
        {
            if ( a.second < 0 )
            {
                return 0;
            }
            else return qpi * 2;
        }
        else
        {
            if ( a.first < 0 )
            {
                return qpi * 3;
            }
            else return qpi;
        }

        auto ratio = op / adj;
        auto atangent = std::atan(ratio);
        auto intangent = static_cast<ptrdiff_t>(atangent * fac) + mult;
        return intangent;
    }

    coord origin_;
    coord bound_;
    coord first_;
    angles_type angles_;
};

namespace map_util
{

namespace status
{
static const char occd = '#';
static const char unoccd = '.';
static const char org = 'O';
static const char hidden = 'x';
static const char vapd = '*';
} // end namespace status

bool is_clear(const map_type& map, coord c)
{
    return at(map, c) == status::unoccd;
}

} // end namespace map_util

namespace asteroid_map
{
using namespace map_util; // someday..

map_type eliminate_obstructed(const map_type& map, const coord origin)
{
    coord_incrementer incr = { map.empty() ? 0 : static_cast<ptrdiff_t>(map[0].size()) };
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
    auto count = std::min(map.empty()?0: map_util::count(map, status::occd) - 1, n);
    if ( count < n )
    {
        std::cout << "trimming n: " << n << " down to only the available: " << count << "\n";
    }

    coord bound = limit(map);
    foob_walker walker = { origin, bound };

    for ( auto i = walker.first(); i.first != (int)bound.x && i.second != (int)bound.y; walker.advance(i) )
    {
        // laser the closest asteroid on this axis
        for ( coord j = { origin.x + i.first, origin.y + i.second };
              within_limit(j, bound);
              j = { j.x + i.first, j.y + i.second })
        {
            if ( at(map, j) == status::occd )
            {
                at(map, j) = status::vapd;
                if ( --count == 0 ) return j;
                break;
            }
        }
    }
    throw std::runtime_error("no more asteroids to vape");
}
size_t count_asteroids(const map_type& map)
{
    return count(map, status::occd);
}
coord find_best(const map_type& map)
{
    coord_incrementer incr = { map.empty() ? 0 : static_cast<ptrdiff_t>(map[0].size()) };
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

} // end namespace asteroid_map

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

        auto map = map_util::to_map(datum);

        // 10_1
        auto best_coord = asteroid_map::find_best(map);

        // 10_2
        auto result = asteroid_map::vapourise(map, best_coord, 200);

        std::cout << "finished at: " << result << "\n";
    }

    return 0;
}
