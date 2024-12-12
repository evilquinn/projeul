
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <queue>
#include <sstream>
#include <vector>
#include "../coord.hpp"
#include "../path_def.hpp"

std::string trail1 =
"0123\n"
"1234\n"
"8765\n"
"9876\n";

std::string trail2 =
"...0...\n"
"...1...\n"
"...2...\n"
"6543456\n"
"7.....7\n"
"8.....8\n"
"9.....9\n";

std::string trail4 =
"..90..9\n"
"...1.98\n"
"...2..7\n"
"6543456\n"
"765.987\n"
"876....\n"
"987....\n";

std::string trail3 =
"10..9..\n"
"2...8..\n"
"3...7..\n"
"4567654\n"
"...8..3\n"
"...9..2\n"
".....01\n";

std::string test_string =
    "89010123\n"
    "78121874\n"
    "87430965\n"
    "96549874\n"
    "45678903\n"
    "32019012\n"
    "01329801\n"
    "10456732\n";

typedef coord_util::basic_coord<int> coord;
typedef std::map<coord, int> top_type;

// up, down, left, right
std::vector<coord> directions = { { 0, -1 }, { 0, 1 }, { -1, 0 }, { 1, 0 } };

top_type read_topography(std::istream& is)
{
    top_type result;
    std::string line;
    int y = 0;
    while (std::getline(is, line))
    {
        for (int x = 0; x < static_cast<int>(line.size()); ++x)
        {
            result[{ x, y }] = line[x] - '0';
        }
        ++y;
    }
    return result;
}

size_t count_trails(const top_type& topography, size_t& distinct_trails)
{
    distinct_trails = 0;
    typedef std::pair<coord, coord> trail_type;
    std::set<trail_type> trails;

    std::queue<trail_type> exploring;

    // find trailheads
    const auto olimit = coord{ -1, -1 };
    const auto limit = std::prev(topography.end())->first + coord{ 1, 1 };
    auto increment   = make_incrementer(limit);
    for (auto c = coord{ 0, 0 }; within_limit(c, limit); increment(c))
    {
        if (topography.at(c) == 0)
        {
            exploring.emplace(c, c);
        }
    }
    // now explore
    while (exploring.size() > 0)
    {
        auto trail = exploring.front();
        exploring.pop();
        for (auto&& direction : directions)
        {
            auto next = trail.second + direction;
            if (!within_limit(olimit, next) || !within_limit(next, limit))
            {
                continue;
            }
            auto next_height = topography.at(next);
            if (next_height == topography.at(trail.second) + 1)
            {
                if (next_height == 9)
                {
                    trails.emplace(trail.first, next);
                    ++distinct_trails;
                }
                else
                {
                    exploring.emplace(trail.first, next);
                }
            }
        }
    }
    return trails.size();
}

int main()
{
    std::string input_path(PROJEUL_AOC_PATH "/10_input.txt");
    std::ifstream input(input_path);
    if (!input)
        throw std::runtime_error(
            std::string("Error reading input file: ").append(input_path));
    auto map = read_topography(input);

    std::stringstream test_input(test_string);
    auto test_map = read_topography(test_input);

    size_t result2 = 0;
    auto result = count_trails(map, result2);
    std::cout << "Part 1 result: " << result << std::endl;
    std::cout << "Part 2 result: " << result2 << std::endl;

    return 0;
}
