

#include <cstdio>
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <unordered_map>
#include <utility>
#include <vector>

#include "../coord.hpp"
#include "../path_def.hpp"

const std::string test_string =
    "#######\n"
    "#...#.#\n"
    "#.....#\n"
    "#..OO@#\n"
    "#..O..#\n"
    "#.....#\n"
    "#######\n"
    "\n"
    "<vv<<^^<<^^\n";

using coord      = coord_util::basic_coord<int>;
using map_type   = std::map<coord, char>;
using moves_type = std::vector<char>;

const std::unordered_map<char, coord> dir_modifiers = { { '^', coord{ 0, -1 } },
                                                        { '>', coord{ 1, 0 } },
                                                        { 'v', coord{ 0, 1 } },
                                                        { '<', coord{ -1, 0 } } };
const std::unordered_map<char, coord> inv_modifiers = { { '^', coord{ 0, 1 } },
                                                        { '>', coord{ -1, 0 } },
                                                        { 'v', coord{ 0, -1 } },
                                                        { '<', coord{ 1, 0 } } };

struct map_moves
{
    map_type map;
    coord pos;
    moves_type moves;
};

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

std::ostream& operator<<(std::ostream& os, const moves_type& moves)
{
    for (auto&& move : moves)
    {
        os << move;
    }
    return os;
}

std::ostream& operator<<(std::ostream& os, const map_moves& data)
{
    return os << data.map << "\n\n" << data.moves << "\n\n" << data.pos << std::endl;
}

map_moves read_input(std::istream& is)
{
    map_moves result;
    std::string line;
    int y = 0;
    while (std::getline(is, line))
    {
        if (line.size() == 0)
            break;  // go to parse the next section
        for (int x = 0; (unsigned)x < line.size(); ++x)
        {
            auto ch = line[x];
            if (ch == 'O')
            {
                ch = '[';
            }
            result.map[coord{ 2 * x, y }] = ch;
            if (ch == '@')
            {
                result.pos = coord{ 2 * x, y };
            }
            if (ch == '[')
            {
                ch = ']';
            }
            else if (ch == '@')
            {
                ch = '.';
            }
            result.map[coord{ 1 + (2 * x), y }] = ch;
        }
        ++y;
    }
    while (std::getline(is, line))
    {
        for (auto&& move : line)
        {
            result.moves.push_back(move);
        }
    }
    return result;
}

class mover
{
public:
    mover() : i_(0), data_(), o_limit_(0, 0), limit_(0, 0) {}
    mover(map_moves data)
        : i_(0), data_(std::move(data)), o_limit_(1, 0), limit_(std::prev(std::prev(std::end(data_.map)))->first)
    {
    }

    bool move(size_t n = 1)
    {
        bool more = i_ < data_.moves.size();
        for (size_t i = 0; i < n && more; ++i)
        {
            more = move_one();
        }
        return more;
    }
    bool move_one()
    {
        auto dir              = data_.moves[i_++];
        auto dirmod           = dir_modifiers.at(dir);
        bool is_space_to_move = false;
        std::vector<coord> spaces;
        std::vector<std::vector<coord>> needs_moved = { { data_.pos } };
        for (
            std::vector<coord> cands = { data_.pos + dirmod }; [&]() {
                for (auto&& cand : cands)
                {
                    if (!within_limit(o_limit_, cand) || !within_limit(cand, limit_))
                        return false;
                }
                return true;
            }();
            [&]() {
                for (auto&& cand : cands)
                {
                    cand += dirmod;
                }
            }())
        {
            spaces.clear();
            std::set<coord> next_cands;
            for (auto&& cand : cands)
            {
                auto& ch = data_.map[cand];
                if (ch == '.')
                {
                    spaces.push_back(cand);
                    continue;
                }
                else if (ch == '#')
                {
                    // poison cands so we break out next
                    next_cands.insert(o_limit_);
                    break;
                }
                else if (ch == '[')
                {
                    next_cands.insert(cand);
                    if (dir == '^' || dir == 'v')
                    {
                        next_cands.insert(cand + dir_modifiers.at('>'));
                    }
                    continue;
                }
                else if (ch == ']')
                {
                    next_cands.insert(cand);
                    if (dir == '^' || dir == 'v')
                    {
                        next_cands.insert(cand + dir_modifiers.at('<'));
                    }
                    continue;
                }
            }
            if (spaces == cands)
            {
                is_space_to_move = true;
                break;
            }
            // next_cands.insert(spaces.begin(), spaces.end());
            cands = std::vector<coord>(next_cands.begin(), next_cands.end());
            needs_moved.push_back(cands);
        }
        if (is_space_to_move)
        {
            // now work back from needs_moved, and pull in everything between them and original pos.
            for (auto needs_riter = needs_moved.rbegin(); needs_riter != needs_moved.rend(); ++needs_riter)
            {
                for (auto&& tile : *needs_riter)
                {
                    data_.map[tile + dirmod] = std::exchange(data_.map[tile], '.');
                }
            }
            data_.pos += dirmod;
        }
        return i_ != data_.moves.size();
    }

    size_t calc_gps()
    {
        size_t result = 0;
        for (auto&& tile : data_.map)
        {
            if (tile.second == '[')
            {
                result += (tile.first.x + (tile.first.y * 100));
            }
        }
        return result;
    }
    friend std::ostream& operator<<(std::ostream&, const mover&);

    // private:
    size_t i_;
    map_moves data_;
    coord o_limit_;
    coord limit_;
};

std::ostream& operator<<(std::ostream& os, const mover& data)
{
    return os << data.data_.map << "\n\n"
              << data.data_.moves << "\n\n"
              << data.data_.pos << ", next: " << data.i_ << std::endl;
}

int main()
{
#if 0
    auto test_stream = std::stringstream(test_string);
    auto test_input  = read_input(test_stream);
    auto test_mover  = mover(std::move(test_input));

    bool more = true;
    while (more)
    {
        more = test_mover.move_one();
        std::cout << test_mover << std::endl;
    }
    std::cout << "Part 1 test: \n" << test_mover.calc_gps() << std::endl;
#else
    std::string input_path(PROJEUL_AOC_PATH "/15_input.txt");
    std::ifstream input_file(input_path);
    if (!input_file)
        throw std::runtime_error(std::string("Error reading input file: ").append(input_path));

    auto input   = read_input(input_file);
    auto mr_move = mover(std::move(input));

    while (mr_move.move_one())
    {
    }

    std::cout << "Part 1 result: \n" << mr_move.calc_gps() << std::endl;

#endif

    return 0;
}
