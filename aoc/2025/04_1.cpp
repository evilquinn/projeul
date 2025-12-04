
#include <aoc/path_def.hpp>
#include <format>
#include <fstream>
#include <iostream>
#include <sstream>

#include <map>
#include <vector>

#include <aoc/coord.hpp>

/**
 * part 1:
 *
 *
 *
 *
 *
 */
std::string test_string =
    "..@@.@@@@.\n"
    "@@@.@.@.@@\n"
    "@@@@@.@.@@\n"
    "@.@@@@..@.\n"
    "@@.@@@@.@@\n"
    ".@@@@@@@.@\n"
    ".@.@.@.@@@\n"
    "@.@@@.@@@@\n"
    ".@@@@@@@@.\n"
    "@.@.@@@.@.\n";

using coord_t = coord_util::basic_coord<int>;
using map_t   = std::map<coord_t, char>;

std::vector<coord_t> surrounding_coords = { { -1, -1 }, { 0, -1 }, { 1, -1 }, { -1, 0 },
                                            { +1, 0 },  { -1, 1 }, { 0, 1 },  { 1, 1 } };

const coord_t lbound{ -1, -1 };

size_t remove_accessible(map_t& map)
{
    size_t result = 0;
    if (map.size() == 0)
    {
        return result;
    }
    std::vector<coord_t> accessible;
    const auto ubound = std::prev(map.end())->first + coord_t{ 1, 1 };
    for (auto&& tile : map)
    {
        auto& c = tile.first;
        if (map.at(c) != '@')
        {
            continue;
        }
        auto cand_count = 0;
        for (auto&& d : surrounding_coords)
        {
            auto cand = c + d;
            if (within_limit(lbound, cand) && within_limit(cand, ubound))
            {
                if (map.at(cand) == '@')
                {
                    ++cand_count;
                }
            }
        }
        if (cand_count < 4)
        {
            accessible.push_back(c);
            ++result;
        }
    }
    for (auto&& removable : accessible)
    {
        map[removable] = '.';
    }
    return result;
}

size_t remove_all(map_t& map)
{
    size_t result     = 0;
    bool some_removed = true;
    while (some_removed)
    {
        auto removed = remove_accessible(map);
        if (removed == 0)
        {
            some_removed = false;
        }
        result += removed;
    }
    return result;
}

map_t read_input(std::istream& is)
{
    map_t result;
    std::string line;
    int y = 0;
    while (std::getline(is, line))
    {
        for (int x = 0; x < static_cast<int>(line.size()); ++x)
        {
            result[coord_t{ x, y }] = line[x];
        }
        ++y;
    }
    return result;
}

int main()
{
    std::string input_path(PROJEUL_AOC_PATH "/04_input.txt");
    std::ifstream ifs(input_path);
    if (!ifs)
        throw std::runtime_error(std::string("Error reading input file: ").append(input_path));

    std::istringstream iss(test_string);

    auto data   = read_input(ifs);
    auto result = remove_all(data);

    std::cout << "result: " << result << std::endl;

    std::cout << "hello" << std::endl;

    return 0;
}
