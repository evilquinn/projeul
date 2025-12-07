
#include <algorithm>
#include <aoc/path_def.hpp>
#include <format>
#include <fstream>
#include <iostream>
#include <queue>
#include <sstream>

#include <map>
#include <vector>

#include "../coord.hpp"

/**
 * part 1:
 *
 *
 *
 *
 *
 */

std::string test_string =
    ".......S.......\n"
    "...............\n"
    ".......^.......\n"
    "...............\n"
    "......^.^......\n"
    "...............\n"
    ".....^.^.^.....\n"
    "...............\n"
    "....^.^...^....\n"
    "...............\n"
    "...^.^...^.^...\n"
    "...............\n"
    "..^...^.....^..\n"
    "...............\n"
    ".^.^.^.^.^...^.\n"
    "...............\n";

using value_t = int;
using coord_t = coord_util::basic_coord<value_t>;
using map_t   = std::map<coord_t, char>;

std::ostream& operator<<(std::ostream& os, const map_t map)
{
    value_t y = 0;
    for (auto&& tile : map)
    {
        if (tile.first.y != y)
        {
            os << "\n";
            y = tile.first.y;
        }
        os << tile.second;
    }
    return os;
}

auto below = coord_t{ 0, 1 };
auto left  = coord_t{ -1, 0 };
auto right = coord_t{ 1, 0 };

map_t read_input(std::istream& is)
{
    map_t result;
    std::string line;
    value_t y = 0;
    while (std::getline(is, line))
    {
        for (value_t x = 0; x < static_cast<value_t>(line.size()); ++x)
        {
            result[coord_t{ x, y }] = line[x];
        }
        ++y;
    }
    return result;
}

size_t count_splits(const map_t& map)
{
    size_t result = 0;
    auto ubound   = std::prev(map.end())->first + coord_t{ 1, 1 };
    auto start    = coord_t{ 0, 0 };
    for (auto&& tile : map)
    {
        if (tile.second == 'S')
        {
            start = tile.first;
            break;
        }
    }

    auto traces = map;
    std::queue<coord_t> trace_paths;
    trace_paths.push(start + below);
    traces[start + below] = '|';
    while (trace_paths.size() > 0)
    {
        // std::cout << traces << "\n" << std::endl;
        auto pos = trace_paths.front();
        trace_paths.pop();
        auto below_pos = pos + below;
        if (!within_limit(below_pos, ubound))
        {
            continue;
        }
        if (traces[below_pos] == '^')
        {
            bool split = false;
            if (traces[below_pos + left] == '.')
            {
                traces[below_pos + left] = '|';
                trace_paths.push(below_pos + left);
                split = true;
            }
            if (traces[below_pos + right] == '.')
            {
                traces[below_pos + right] = '|';
                trace_paths.push(below_pos + right);
                split = true;
            }
            if (split)
            {
                ++result;
            }
        }
        else
        {
            traces[below_pos] = '|';
            trace_paths.push(below_pos);
        }
    }

    return result;
}

int main()
{
    std::string input_path(PROJEUL_AOC_PATH "/07_input.txt");
    std::ifstream ifs(input_path);
    if (!ifs)
        throw std::runtime_error(std::string("Error reading input file: ").append(input_path));

    std::istringstream iss(test_string);

    auto data = read_input(ifs);
    auto result = count_splits(data);

    std::cout << "result: " << result << std::endl;

    std::cout << "hello" << std::endl;

    return 0;
}
