/*
 * https://adventofcode.com/2019/day/18
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <set>
#include <deque>
#include <memory>
#include <vector>
#include <algorithm>
#include <boost/dynamic_bitset.hpp>

#include <aoc/path_def.hpp>
#include <aoc/coord.hpp>

namespace aoc = coord_util; // ffs

aoc::coord map_end(const std::map<aoc::coord, char>& map)
{
    aoc::coord result;
    if ( map.empty() ) return result;
    return map.rbegin()->first + aoc::coord{ 1, 1 };
}


static const aoc::coord up = { -1, 0 };
static const aoc::coord down = { 1, 0 };
static const aoc::coord left = { 0, -1 };
static const aoc::coord right = { 0, 1 };
static const std::vector<aoc::coord> explore_directions = { up, right, down, left };
static const aoc::coord coord_zero = { 0, 0 };

std::ostream& operator<<(std::ostream& os, std::map<aoc::coord, char> map)
{
    if ( map.empty() || !os ) return os;
    auto map_boundary = map_end(map);
    for ( int y = 0; y < map_boundary.y; ++y )
    {
        for ( int x = 0; x < map_boundary.x; ++x )
        {
            os << map[{ x, y }];
        }
        os << '\n';
    }
    return os;
}

static std::map<char, uint32_t> goalbits = {
    { '@', ( 1 <<  0 ) },
    { 'a', ( 1 <<  1 ) },
    { 'b', ( 1 <<  2 ) },
    { 'c', ( 1 <<  3 ) },
    { 'd', ( 1 <<  4 ) },
    { 'e', ( 1 <<  5 ) },
    { 'f', ( 1 <<  6 ) },
    { 'g', ( 1 <<  7 ) },
    { 'h', ( 1 <<  8 ) },
    { 'i', ( 1 <<  9 ) },
    { 'j', ( 1 << 10 ) },
    { 'k', ( 1 << 11 ) },
    { 'l', ( 1 << 12 ) },
    { 'm', ( 1 << 13 ) },
    { 'n', ( 1 << 14 ) },
    { 'o', ( 1 << 15 ) },
    { 'p', ( 1 << 16 ) },
    { 'q', ( 1 << 17 ) },
    { 'r', ( 1 << 18 ) },
    { 's', ( 1 << 19 ) },
    { 't', ( 1 << 20 ) },
    { 'u', ( 1 << 21 ) },
    { 'v', ( 1 << 22 ) },
    { 'w', ( 1 << 23 ) },
    { 'x', ( 1 << 24 ) },
    { 'y', ( 1 << 25 ) },
    { 'z', ( 1 << 26 ) }
};
static const size_t max_cost = std::numeric_limits<size_t>::max();
struct goal_path
{
    size_t cost;
    uint32_t goals;
    uint32_t gates;
    goal_path() : goal_path(max_cost)
    {}
    goal_path(size_t cost) : goal_path(cost, 0, 0)
    {}
    goal_path(size_t cost, uint32_t goals, uint32_t gates) : cost(cost), goals(goals), gates(gates)
    {}
};
std::string goals_to_string(uint32_t goals, bool to_upper = false)
{
    std::string result;
    for ( auto&& goalbit : goalbits )
    {
        if ( goalbit.first == '*' ) continue;
        if ( goals & goalbit.second ) result.push_back( to_upper ? toupper(goalbit.first) : goalbit.first );
    }
    return result;
}
std::string gates_to_string(uint32_t gates)
{
    return goals_to_string(gates, true);
}
std::ostream& operator<< (std::ostream& os, struct goal_path goal_path)
{
    return os << " { " << goal_path.cost
              << ", \"" << goals_to_string(goal_path.goals)
              << "\", \"" << gates_to_string(goal_path.gates)
              << "\" }";
}
typedef std::map<uint32_t, std::map<uint32_t, goal_path> > goal_paths_type;
std::ostream& operator<< ( std::ostream& os, const goal_paths_type& goal_paths)
{
    if ( !os ) return os;
    for ( auto&& from_goal_data : goal_paths )
    {
        os << " { '" << goals_to_string(from_goal_data.first) << "' : {";
        std::string sep = " ";
        for ( auto&& to_goal_data : from_goal_data.second )
        {
            os << sep << "{ '" << goals_to_string(to_goal_data.first) << "' : " << to_goal_data.second << " }";
            sep = ", ";
        }
        os << " }\n";
    }
    return os;
}
class maze_wanker
{
public:
    maze_wanker(std::istream& is)
    {
        parse_map(is);
        std::cout << map_ << std::endl;
        explore_targets();
        std::cout << goal_paths_ << std::endl;
        solve_maze();
    }
    void parse_map(std::istream& is)
    {
        aoc::coord pos;
        for ( std::string line; std::getline(is, line); )
        {
            for ( auto&& square : line )
            {
                map_[pos] = square;
                if ( islower(square) )
                {
                    targets_[square] = pos;
                }
                else if ( square == '@' )
                {
                    targets_[square] = pos;
                    origin_ = pos;
                }
                ++pos.x;
            }
            pos.x = 0;
            ++pos.y;
        }
        goalbits['*'] = 0;
        for ( auto&& target : targets_ )
        {
            goalbits['*'] |= goalbits[target.first];
        }
    }
    void explore_targets()
    {
        auto targets_copy = targets_;
        for ( auto&& from_target : targets_ )
        {
            explore_paths_from(from_target.first);
        }
    }
    void explore_paths_from(char from)
    {
        aoc::coord pos = targets_[from];
        goal_path pos_data(0);
        std::map<aoc::coord, size_t> costs;
        std::deque<std::pair<std::pair<aoc::coord, aoc::coord>, goal_path> > to_explore = { { { pos, pos }, pos_data } };
        // to_explore[n].first.first -> coord (from)
        // to_explore[n].first.second -> coord (to)
        // to_explore[n].second -> goal_path: cost, goals passed and gates passed on the way to here
        while ( to_explore.size() > 0 )
        {
            auto explore_pos = to_explore.front();
            to_explore.pop_front();
            for ( auto&& direction : explore_directions )
            {
                auto cand = explore_pos.first.second + direction;
                if ( aoc::within_limit(cand, coord_zero) || aoc::within_limit(map_.rbegin()->first, cand) ) continue; // not on map
                if ( cand == explore_pos.first.first ) continue; // came this way
                if ( map_[cand] == '#' ) continue; // wall
                auto cand_goal_path = explore_pos.second;
                cand_goal_path.cost += 1;
                if ( costs[cand] != 0 && costs[cand] <= cand_goal_path.cost ) continue; // we've already shorter path to here
                costs[cand] = cand_goal_path.cost;
                if ( islower(map_[cand]) )
                {
                    cand_goal_path.goals |= goalbits[map_[cand]];
                    auto path_key = std::pair{ goalbits[map_[targets_[from]]], goalbits[map_[cand]] };
                    if ( goal_paths_[path_key.first][path_key.second].cost > cand_goal_path.cost )
                    {
                        goal_paths_[path_key.first][path_key.second] = cand_goal_path;
                    }
                }
                if ( isupper(map_[cand]) ) cand_goal_path.gates |= goalbits[tolower(map_[cand])];
                to_explore.push_back( { { explore_pos.first.second, cand }, cand_goal_path } );
            }
        }
    }
    void solve_maze()
    {
        char start = '@';
        uint32_t start_bit = goalbits['@'];
        std::deque<std::pair<uint32_t, goal_path> > to_explore = { { start_bit, { 0, start_bit, 0 } } };
        // to_explore[].first -> char (exploring from here)
        // to_explore[].second.cost -> cost to here
        // to_explore[].second.goals -> keys to here

        std::map<std::pair<uint32_t, uint32_t>, goal_path> costs = { { { start_bit, start_bit }, 0 } };
        // costs[pair{goal_bit, keys}].cost -> best cost so far to get to this goal with these keys

        while ( to_explore.size() > 0 )
        {
            auto explore_pos = to_explore.front();
            to_explore.pop_front();
            auto curr_bit = explore_pos.first; // my bit
            auto cand_targets = ( goalbits['*'] & ~(explore_pos.second.goals) ); // all other bits i haven't been to yet
            for ( uint32_t i = 0; i < goalbits.size(); ++i )
            {
                uint32_t cand_bit = ( 1 << i ); // next potential bit
                if ( curr_bit == cand_bit ) continue; // the pos we're on isn't a candidate
                if ( ! ( cand_targets & cand_bit ) ) continue; // it's not a candidate
                auto gates = ( goal_paths_[curr_bit][cand_bit].gates & ~(explore_pos.second.goals) );
                if ( gates != 0 ) continue; // there are gates we don't yet have keys to
                auto cand_goal_path = explore_pos.second; // prepare next cand details
                cand_goal_path.cost += goal_paths_[curr_bit][cand_bit].cost; // update the cost
                cand_goal_path.goals |= goal_paths_[curr_bit][cand_bit].goals; // update the keys we've collected
                if ( costs[{ cand_bit, cand_goal_path.goals }].cost <= cand_goal_path.cost ) continue; // already same/better path to here
                costs[{ cand_bit, cand_goal_path.goals }] = cand_goal_path; // record new best path
                to_explore.push_back({ cand_bit, cand_goal_path }); // remember to explore from there
            }
        }

        auto smallest_all_keys = std::numeric_limits<size_t>::max();
        auto final_goal = goalbits['@'];
        for ( auto&& cost : costs )
        {
            if ( cost.first.second != goalbits['*'] ) continue; // doesn't have all keys
            if ( smallest_all_keys > cost.second.cost )
            {
                smallest_all_keys = cost.second.cost;
                final_goal = cost.first.first;
            }
        }
        std::cout << "WIN? finished at: " << goals_to_string(final_goal) << ", cost: " << smallest_all_keys << std::endl;
    }
private:
    std::map<aoc::coord, char> map_;
    aoc::coord origin_;
    std::map<char, aoc::coord> targets_;
    goal_paths_type goal_paths_;
};


int main()
{
#if 1
    std::vector<std::string> data = {
        "#########\n"
        "#b.A.@.a#\n"
        "#########",
        "########################\n"
        "#f.D.E.e.C.b.A.@.a.B.c.#\n"
        "######################.#\n"
        "#d.....................#\n"
        "########################",
        "########################\n"
        "#@..............ac.GI.b#\n"
        "###d#e#f################\n"
        "###A#B#C################\n"
        "###g#h#i################\n"
        "########################",
        "#################\n"
        "#i.G..c...e..H.p#\n"
        "########.########\n"
        "#j.A..b...f..D.o#\n"
        "########@########\n"
        "#k.E..a...g..B.n#\n"
        "########.########\n"
        "#l.F..d...h..C.m#\n"
        "#################"
    };
    for ( auto&& datum : data )
    {
        std::istringstream iss(datum);
        maze_wanker maisy(iss);
    }
#endif
#if 1

    std::ifstream inf(PROJEUL_AOC_PATH "/18_input.txt");
    maze_wanker maisy(inf);
#endif

    return 0;
}
