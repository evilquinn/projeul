
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <vector>
#include "../coord.hpp"
#include "../path_def.hpp"

std::string test_string =
    "............\n"
    "........0...\n"
    ".....0......\n"
    ".......0....\n"
    "....0.......\n"
    "......A.....\n"
    "............\n"
    "............\n"
    "........A...\n"
    ".........A..\n"
    "............\n"
    "............\n";

typedef coord_util::basic_coord<int> coord;
typedef std::map<coord, char> map_type;
typedef std::map<char, std::vector<coord>> ants_type;

std::ostream& operator<<(std::ostream& os, const map_type& map)
{
    const auto limit = std::prev(map.end())->first + coord{ 1, 1 };
    auto increment   = make_incrementer(limit);
    int last_y       = 0;
    for (auto c = coord{ 0, 0 }; within_limit(c, limit); increment(c))
    {
        if (last_y != c.y)
        {
            os << "\n";
            last_y = c.y;
        }
        os << map.at(c);
    }
    return os;
}

map_type read_map(std::istream& is)
{
    map_type result;
    std::string line;
    int y = 0;
    while (std::getline(is, line))
    {
        for (int x = 0; x < static_cast<int>(line.size()); ++x)
        {
            result[{ x, y }] = line[x];
        }
        ++y;
    }
    return result;
}

ants_type map_antennas(const map_type& map)
{
    ants_type result;
    const auto limit = std::prev(map.end())->first + coord{ 1, 1 };
    auto increment   = make_incrementer(limit);
    for (auto c = coord{ 0, 0 }; within_limit(c, limit); increment(c))
    {
        auto& cand = map.at(c);
        if (cand != '.')
        {
            result[cand].push_back(c);
        }
    }
    return result;
}

size_t count_antinodes(const map_type& map)
{
    const auto olimit = coord{ -1, -1 };
    const auto limit  = std::prev(map.end())->first + coord{ 1, 1 };
    auto ants         = map_antennas(map);
    std::set<coord> antinodes;
    for (auto&& antenna : ants)
    {
        auto& ant_locs = antenna.second;
        for (size_t i = 0; i < ant_locs.size() - 1; ++i)
        {
            for (size_t j = i + 1; j < ant_locs.size(); ++j)
            {
                auto distance = ant_locs[j] - ant_locs[i];
                auto anti1    = ant_locs[i] - distance;
                if (within_limit(olimit, anti1) && within_limit(anti1, limit))
                {
                    antinodes.insert(anti1);
                }
                auto anti2 = ant_locs[j] + distance;
                if (within_limit(olimit, anti2) && within_limit(anti2, limit))
                {
                    antinodes.insert(anti2);
                }
            }
        }
    }
    return antinodes.size();
}

int main()
{
    std::string input_path(PROJEUL_AOC_PATH "/08_input.txt");
    std::ifstream input(input_path);
    if (!input)
        throw std::runtime_error(
            std::string("Error reading input file: ").append(input_path));
    auto map = read_map(input);

    std::stringstream test_input(test_string);
    auto test_map = read_map(test_input);

    auto result = count_antinodes(map);
    std::cout << "Part 1 result: " << result << std::endl;
    return 0;
}
