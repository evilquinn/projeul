
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

size_t count_timelines(const map_t& map)
{
    auto ubound = std::prev(map.end())->first + coord_t{ 1, 1 };
    auto start  = coord_t{ 0, 0 };
    for (auto&& tile : map)
    {
        if (tile.second == 'S')
        {
            start = tile.first;
            break;
        }
    }

    std::map<coord_t, size_t> timelines;
    std::queue<coord_t> next_tile;
    timelines[start + below] = 1;
    next_tile.push(start + below);
    while (next_tile.size() > 0)
    {
        auto pos = next_tile.front();
        next_tile.pop();
        auto below_pos = pos + below;
        if (!within_limit(below_pos, ubound))
        {
            continue;
        }
        if (map.at(below_pos) == '^')
        {
            auto below_left = below_pos + left;
            if (!timelines.contains(below_left))
            {
                next_tile.push(below_left);
            }
            timelines[below_left] += timelines[pos];

            auto below_right = below_pos + right;
            if (!timelines.contains(below_right))
            {
                next_tile.push(below_right);
            }
            timelines[below_right] += timelines[pos];
        }
        else
        {
            if (!timelines.contains(below_pos))
            {
                next_tile.push(below_pos);
            }
            timelines[below_pos] += timelines[pos];
        }
    }
    size_t result = 0;
    for (coord_t bottom{ 0, ubound.y - 1 }; within_limit(bottom, ubound); ++bottom.x)
    {
        result += timelines[bottom];
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

    auto data   = read_input(ifs);
    auto result = count_timelines(data);

    std::cout << "result: " << result << std::endl;

    std::cout << "hello" << std::endl;

    return 0;
}
