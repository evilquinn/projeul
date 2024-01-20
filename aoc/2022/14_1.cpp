
#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <algorithm>

#include <boost/algorithm/string.hpp>

#include <aoc/path_def.hpp>
#include <aoc/coord.hpp>


using coord_util::coord;
using map_type = std::map<coord, char>;

const coord down(0, 1);
const coord down_left(-1, 1);
const coord down_right(1, 1);

const char rock = '#';
const char sand = 'o';

bool is_clear(map_type& map, coord const& c)
{
    auto& v = map[c];
    return v != rock && v != sand;
}

void read_line(std::string const& line, map_type& map)
{
    // get coords as strings
    std::vector<std::string> line_tokens;
    boost::split(line_tokens,
                 line,
                 boost::is_any_of(" ->"),
                 boost::algorithm::token_compress_on);
    // convert strings to coords
    std::vector<coord> line_coords;
    std::transform(line_tokens.begin(), line_tokens.end(),
                   std::back_inserter(line_coords),
                   [](std::string const& token) -> coord
        {
            coord result;
            sscanf(token.data(), "%ld,%ld", &result.x, &result.y);
            return result;
        });
    // put all coords between the points into the map
    for ( size_t i = 1; i < line_coords.size(); ++i )
    {
        coord distance = line_coords[i] - line_coords[i-1];
        coord unit( distance.x == 0 ? 0 : distance.x / labs(distance.x),
                    distance.y == 0 ? 0 : distance.y / labs(distance.y) );
        for ( coord j = line_coords[i-1]; !(j == line_coords[i]); j += unit )
        {
            map[j] = rock;
        }
    }
    // and don't forget the last one
    map[line_coords.back()] = rock;
}

map_type read_map(std::istream& is)
{
    map_type result;
    std::string line;
    while ( std::getline(is, line) )
    {
        read_line(line, result);
    }
    return result;
}

int fill_map(map_type map, bool with_floor = false)
{
    int result = 0;
    /**
     * find the lowest y coord (largest y value!)
     * There's no rocks below this, so if any sand reaches this
     * y-value, it's falling into the abyss
     */
    auto coord_with_lowest_y = std::max_element(map.begin(), map.end(),
        [](map_type::value_type const& lhs, map_type::value_type const& rhs)
        {
            return lhs.first.y < rhs.first.y;
        });
    auto y_limit = coord_with_lowest_y->first.y;
    auto floor_limit = y_limit + 2;

    const coord sand_from(500, 0);

    bool abyss = false;
    while( !abyss )
    {
        if ( ! is_clear(map, sand_from) ) break;
        auto unit = sand_from;
        bool falling = true;
        while( falling )
        {
            if ( ! with_floor )
            {
                if ( unit.y == y_limit )
                {
                    abyss = true;
                    break;
                }
            }
            auto next = unit + down;
            if ( is_clear(map, next) && next.y != floor_limit )
            {
                unit = next;
                continue;
            }
            next = unit + down_left;
            if ( is_clear(map, next) && next.y != floor_limit  )
            {
                unit = next;
                continue;
            }
            next = unit + down_right;
            if ( is_clear(map, next) && next.y != floor_limit  )
            {
                unit = next;
                continue;
            }

            map[unit] = sand;
            ++result;
            falling = false;
        }
    }
    return result;
}

int main()
{
    std::ifstream input(PROJEUL_AOC_PATH "/14_input.txt");
    if ( !input ) throw std::runtime_error("Failed to open input file");

    auto map = read_map(input);
    auto result = fill_map(map);
    std::cout << "Result: " << result << std::endl;

    auto result2 = fill_map(map, true);
    std::cout << "Result2: " << result2 << std::endl;

    return 0;
}
