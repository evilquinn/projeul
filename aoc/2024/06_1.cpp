
#include <boost/algorithm/string/classification.hpp>
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <sstream>
#include <vector>
#include "../coord.hpp"
#include "../path_def.hpp"

std::string test_string =
    "....#.....\n"
    ".........#\n"
    "..........\n"
    "..#.......\n"
    ".......#..\n"
    "..........\n"
    ".#..^.....\n"
    "........#.\n"
    "#.........\n"
    "......#...\n";

std::string test1 =
    "#.\n"
    ".#\n"
    "..\n"
    "^.\n";

typedef coord_util::basic_coord<int> coord;
typedef std::pair<coord, char> pos_type;
typedef std::map<coord, char> map_type;

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

const std::string directions                            = "^>v<";
std::vector<std::pair<char, coord>> direction_modifiers = {
    { '^', { 0, -1 } },  // up
    { '>', { 1, 0 } },   // right
    { 'v', { 0, 1 } },   // down
    { '<', { -1, 0 } }   // left
};

std::pair<coord, char> guard_move(const map_type& map, pos_type pos)
{
    // assume still in map and valid direction, meh
    auto dirmod =
        std::find_if(direction_modifiers.begin(),
                     direction_modifiers.end(),
                     [&pos](const auto& p) { return p.first == pos.second; });
    const auto orig_dirmod = dirmod;
    auto cand              = pos.first + dirmod->second;
    while (map.contains(cand) && map.at(cand) == '#')
    {
        // turn right
        dirmod = std::next(dirmod);
        if (dirmod == direction_modifiers.end())
        {
            dirmod = direction_modifiers.begin();
        }
        if (orig_dirmod == dirmod)
        {
            throw std::runtime_error("Blocked in every direction");
        }
        cand = pos.first + dirmod->second;
    }
    return { cand, dirmod->first };
}

size_t track_guard(map_type& map)
{
    size_t result   = 0;
    auto start_iter = std::find_if(map.begin(), map.end(), [](const auto& p) {
        return boost::is_any_of(directions)(p.second);
    });
    if (start_iter == map.end())
    {
        throw std::runtime_error("can't find starting position!");
    }
    const auto start_pos = *start_iter;
    const coord unit{ 1, 1 };
    const coord olimit = coord{ 0, 0 } - unit;
    const coord limit  = std::prev(map.end())->first + unit;
    for (std::pair<coord, char> pos = start_pos;
         within_limit(olimit, pos.first) && within_limit(pos.first, limit);
         pos = guard_move(map, pos))
    {
        auto pres = std::exchange(map[pos.first], 'x');
        if (pres != 'x')
            ++result;
    }
    map[start_pos.first] = start_pos.second;
    return result;
}

bool detect_trapped(const map_type& map, pos_type pos)
{
    const coord olimit      = coord{ -1, -1 };
    const coord limit       = std::prev(map.end())->first + coord{ 1, 1 };
    std::set<pos_type> been = { pos };
    while (within_limit(olimit, pos.first) && within_limit(pos.first, limit))
    {
        pos = guard_move(map, pos);
        if (been.contains(pos))
        {
            return true;
        }
        been.insert(pos);
    }
    return false;
}

size_t count_trap_candidates(map_type map)
{
    size_t result = 0;

    auto start_iter = std::find_if(map.begin(), map.end(), [](const auto& p) {
        return boost::is_any_of(directions)(p.second);
    });
    if (start_iter == map.end())
    {
        throw std::runtime_error("can't find starting position!");
    }
    const auto start_pos = *start_iter;
    pos_type trap_start  = start_pos;

    map[start_pos.first] = '.';
    const coord olimit   = coord{ -1, -1 };
    const coord limit    = std::prev(map.end())->first + coord{ 1, 1 };
    std::unordered_set<coord> skip_obstacle = {start_pos.first};
    while (within_limit(olimit, trap_start.first) &&
           within_limit(trap_start.first, limit))
    {
        auto obstacle_candidate = guard_move(map, trap_start);
        if (!within_limit(olimit, obstacle_candidate.first) ||
            !within_limit(obstacle_candidate.first, limit))
        {
            // think we're done?
            break;
        }
        if (skip_obstacle.contains(obstacle_candidate.first))
        {
            trap_start = obstacle_candidate;
            continue;
        }
        // std::cout << "detecting trapped with obstable at: " <<
        // obstacle_candidate.first << ", starting from: " << trap_start.first
        // << std::endl;
        map[obstacle_candidate.first] = '#';
        if (detect_trapped(map, start_pos))
        {
            ++result;
        }
        map[obstacle_candidate.first] = '.';
        skip_obstacle.insert(obstacle_candidate.first);
        trap_start                    = obstacle_candidate;
    }

    return result;
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

int main()
{
    std::string input_path(PROJEUL_AOC_PATH "/06_input.txt");
    std::ifstream input_stream(input_path);
    if (!input_stream)
        throw std::runtime_error(
            std::string("Error reading input file: ").append(input_path));
    auto map      = read_map(input_stream);
    auto tracked  = map;
    auto result   = track_guard(tracked);
    std::cout << "Part 1 result: " << result << std::endl;


    std::stringstream test_input(test1);
    auto test_map = read_map(test_input);
    auto result2 = count_trap_candidates(map);
    std::cout << "Part 2 result: " << result2 << std::endl;

    return 0;
}
