

#include <fstream>
#include <iostream>
#include <limits>
#include <map>
#include <queue>
#include <sstream>
#include <unordered_map>
#include <vector>

#include "../coord.hpp"
#include "../path_def.hpp"

std::string test_string =
    "###############\n"
    "#.......#....E#\n"
    "#.#.###.#.###.#\n"
    "#.....#.#...#.#\n"
    "#.###.#####.#.#\n"
    "#.#.#.......#.#\n"
    "#.#.#####.###.#\n"
    "#...........#.#\n"
    "###.#.#####.#.#\n"
    "#...#.....#.#.#\n"
    "#.#.#.###.#.#.#\n"
    "#.....#...#.#.#\n"
    "#.###.#.#.#.#.#\n"
    "#S..#.....#...#\n"
    "###############\n";

std::string test_string2 =
    "#################\n"
    "#...#...#...#..E#\n"
    "#.#.#.#.#.#.#.#.#\n"
    "#.#.#.#...#...#.#\n"
    "#.#.#.#.###.#.#.#\n"
    "#...#.#.#.....#.#\n"
    "#.#.#.#.#.#####.#\n"
    "#.#...#.#.#.....#\n"
    "#.#.#####.#.###.#\n"
    "#.#.#.......#...#\n"
    "#.#.###.#####.###\n"
    "#.#.#...#.....#.#\n"
    "#.#.#.#####.###.#\n"
    "#.#.#.........#.#\n"
    "#.#.#.#########.#\n"
    "#S#.............#\n"
    "#################\n";

using coord    = coord_util::basic_coord<int>;
using map_type = std::map<coord, char>;

const char north = '^';
const char east  = '>';
const char south = 'v';
const char west  = '<';
char turn_right(char d)
{
    switch (d)
    {
    case north:
        return east;
    case east:
        return south;
    case south:
        return west;
    case west:
        return north;
    default:
        throw std::runtime_error("unrecognised direction");
    }
}
char turn_left(char d)
{
    switch (d)
    {
    case north:
        return west;
    case west:
        return south;
    case south:
        return east;
    case east:
        return north;
    default:
        throw std::runtime_error("unrecognised direction");
    }
}
std::unordered_map<char, coord> dirmods = { { north, coord{ 0, -1 } },
                                            { east, coord{ 1, 0 } },
                                            { south, coord{ 0, 1 } },
                                            { west, coord{ -1, 0 } } };

std::ostream& operator<<(std::ostream& os, const map_type& map)
{
    int y = 0;
    for (auto&& tile : map)
    {
        if (y != tile.first.y)
        {
            os << "\n";
            ++y;
        }
        os << tile.second;
    }
    return os;
}

map_type read_input(std::istream& is)
{
    map_type result;
    std::string line;
    int y = 0;
    while (std::getline(is, line))
    {
        for (int x = 0; (unsigned)x < line.size(); ++x)
        {
            result[coord{ x, y }] = line[x];
        }
        ++y;
    }
    return result;
}

struct path
{
    path(const map_type& m, coord start, char dir) : map(m), pos(start), facing(dir), score(0) {}
    const map_type& map;
    map_type walked;
    coord pos;
    char facing;
    size_t score;
    bool step_forward()
    {
        coord next    = pos + dirmods[facing];
        auto next_pos = map.find(next);
        if (next_pos == map.end() || next_pos->second == '#')
        {
            return false;  // oob or wall
        }
        if (walked.count(next) > 0)
        {
            return false;  // already been here
        }
        ++score;
        walked[pos] = facing;
        pos         = next;
        return true;
    }
    void turn_right()
    {
        facing = ::turn_right(facing);
        score += 1000;
    }
    void turn_left()
    {
        facing = ::turn_left(facing);
        score += 1000;
    }
};

size_t solve(const map_type& start_map)
{
    coord start;
    coord end;
    for (auto&& cand : start_map)
    {
        if (cand.second == 'S')
        {
            start = cand.first;
        }
        else if (cand.second == 'E')
        {
            end = cand.first;
        }
    }
    std::map<std::pair<coord, char>, size_t> tracking;
    std::queue<path> exploring;
    path starting{ start_map, start, east };
    exploring.push(starting);
    tracking[{ starting.pos, starting.facing }] = starting.score;
    path starting2                              = starting;
    starting.turn_left();
    exploring.push(starting);
    tracking[{ starting.pos, starting.facing }] = starting.score;
    starting.turn_left();
    exploring.push(starting);
    tracking[{ starting.pos, starting.facing }] = starting.score;
    starting2.turn_right();
    exploring.push(starting2);
    tracking[{ starting2.pos, starting2.facing }] = starting2.score;

    std::vector<path> successes;

    while (exploring.size() > 0)
    {
        auto explore = exploring.front();
        exploring.pop();

        if (explore.step_forward())
        {
            if (explore.pos == end)
            {
                successes.push_back(std::move(explore));
            }
            else
            {
                auto best_for_pos = tracking.find({ explore.pos, explore.facing });
                if (best_for_pos == tracking.end() || explore.score < best_for_pos->second)
                {
                    tracking[{ explore.pos, explore.facing }] = explore.score;
                    exploring.push(std::move(explore));

                    auto left = explore;
                    left.turn_left();
                    exploring.push(std::move(left));
                    auto right = explore;
                    right.turn_right();
                    exploring.push(std::move(right));
                }
            }
        }
    }

    size_t best = std::numeric_limits<size_t>::max();
    for (auto&& success : successes)
    {
        if (success.score < best)
            best = success.score;
    }
    return best;
}

int main()
{
#if 0
    auto test_stream = std::stringstream(test_string2);
    auto test_input  = read_input(test_stream);
    std::cout << "Part 1 test: \n" << solve(test_input) << std::endl;
#else
    std::string input_path(PROJEUL_AOC_PATH "/16_input.txt");
    std::ifstream input_file(input_path);
    if (!input_file)
        throw std::runtime_error(std::string("Error reading input file: ").append(input_path));

    auto input = read_input(input_file);

    std::cout << "Part 1 result: \n" << solve(input) << std::endl;

#endif

    return 0;
}
