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
        os << " }";
    }
    return os;
}
typedef std::map<size_t, goal_paths_type> robot_goal_paths_type;
std::ostream& operator<< (std::ostream& os, const robot_goal_paths_type robot_goals)
{
    if ( !os ) return os;
    for ( auto&& robot : robot_goals )
    {
        os << "{ " << robot.first << ": " << robot.second << " }";
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
        //std::cout << goal_paths_ << std::endl;
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
                    origins_.push_back(pos);
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
        for ( size_t robot = 0; robot < origins_.size(); ++robot )
        {
            explore_paths_from(origins_[robot], robot);
            for ( auto&& from_target : targets_ )
            {
                if ( goal_paths_[robot][goalbits['@']].count(goalbits[from_target.first]) == 0 ) continue; // bypass unless this target can be seen by this robot
                explore_paths_from(from_target.second, robot);
            }
        }
    }
    void explore_paths_from(aoc::coord from, size_t robot)
    {
        goal_path pos_data(0);
        std::map<aoc::coord, size_t> costs;
        std::deque<std::pair<std::pair<aoc::coord, aoc::coord>, goal_path> > to_explore = { { { from, from }, pos_data } };
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
                    auto path_key = std::pair{ goalbits[map_[from]], goalbits[map_[cand]] };
                    if ( goal_paths_[robot][path_key.first][path_key.second].cost > cand_goal_path.cost )
                    {
                        goal_paths_[robot][path_key.first][path_key.second] = cand_goal_path;
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
        uint32_t start_bit = goalbits[start];
        //std::deque<std::pair<aoc::coord, goal_path> > to_explore;
        // to_explore[].first -> coord (exploring from here)
        // to_explore[].second.cost -> cost to here
        // to_explore[].second.goals -> keys to here
        std::deque<std::pair<std::vector<std::pair<aoc::coord, size_t> >, uint32_t> > to_explore;
        // to_explore[].first -> position of each robot and cost to that point, and their collected keys
        // to_explore[].first[].first -> a coord of a robot at this state
        // to_explore[].first[].second -> cost to reach associated coord
        // to_explore[].second -> keys collected by robot(s) so far
        std::map<std::pair<aoc::coord, uint32_t>, size_t> costs;
        // costs[pair{goal_coord, keys}] -> best cost so far to get to this goal with these keys

        std::vector<std::pair<aoc::coord, size_t> > start_spots;
        for ( size_t i = 0; i < origins_.size(); ++i )
        {
            aoc::coord start_coord = origins_[i];
            start_spots.push_back( { start_coord, 0 } );
            costs[{ start_coord, start_bit}] = 0;
        }
        to_explore.push_back( { start_spots, start_bit } );

        while ( to_explore.size() > 0 )
        {
            auto explore_pos = to_explore.front();
            to_explore.pop_front();
            bool explored = false;
            for ( size_t ri = 0; ri < explore_pos.first.size(); ++ri )
            {
                auto& robot = explore_pos.first[ri];
                auto curr_coord = robot.first; // my coord
                auto curr_bit = goalbits[map_[curr_coord]]; // my bit
                auto cand_targets = ( goalbits['*'] & ~(explore_pos.second) ); // all other bits i haven't been to yet
                for ( uint32_t i = 0; i < goalbits.size(); ++i )
                {
                    uint32_t cand_bit = ( 1 << i ); // next potential bit
                    auto cand_coord = targets_[std::next(goalbits.begin(), i + 1)->first]; // next potential coord
                    if ( curr_bit == cand_bit ) continue; // the pos we're on isn't a candidate
                    if ( goal_paths_[ri][goalbits['@']].count(cand_bit) == 0 ) continue; // bypass unless this target can be seen by this robot
                    if ( ! ( cand_targets & cand_bit ) ) continue; // not a candidate, seen it already
                    auto gates = ( goal_paths_[ri][curr_bit][cand_bit].gates & ~(explore_pos.second) );
                    if ( gates != 0 ) continue; // there are gates we don't yet have keys to
                    goal_path cand_goal_path;
                    cand_goal_path.cost = robot.second + goal_paths_[ri][curr_bit][cand_bit].cost; // update the cost
                    cand_goal_path.goals = explore_pos.second | goal_paths_[ri][curr_bit][cand_bit].goals; // update the keys we've collected
                    auto new_robot_state = explore_pos;
                    new_robot_state.first[ri].first = cand_coord;
                    new_robot_state.first[ri].second = cand_goal_path.cost;
                    new_robot_state.second |= cand_goal_path.goals;
                    size_t cand_total_cost = 0;
                    for ( auto&& coord_cost : new_robot_state.first )
                    {
                        cand_total_cost += coord_cost.second;
                    }
                    auto costkey = std::pair{cand_coord, new_robot_state.second };
                    if ( costs.count(costkey) > 0 && costs[costkey] <= cand_total_cost ) continue; // already same/better path to here
                    costs[costkey] = cand_total_cost; // record new best path
                    to_explore.push_back(new_robot_state); // remember to explore from there
                    explored = true;
                }
                if ( explored ) break;
            }
        }

        auto smallest_all_keys = std::numeric_limits<size_t>::max();
        auto final_goal = origins_[0];
        for ( auto&& cost : costs )
        {
            if ( cost.first.second != goalbits['*'] ) continue; // doesn't have all keys
            size_t cand_cost = cost.second;
            if ( smallest_all_keys > cand_cost )
            {
                smallest_all_keys = cand_cost;
                final_goal = cost.first.first;
            }
        }
        std::cout << "WIN? finished at: '" << map_[final_goal] << "' " << final_goal << ", cost: " << smallest_all_keys << std::endl;
    }
private:
    std::map<aoc::coord, char> map_;
    std::vector<aoc::coord> origins_;
    std::map<char, aoc::coord> targets_;
    robot_goal_paths_type goal_paths_;
};


int main()
{
#if 0
=======
aoc::coord map_end(const map_type& map)
{
    aoc::coord result;
    if ( map.empty() ) return result;
    return map.rbegin()->first + aoc::coord{ 1, 1 };
}

struct path_node
{
    aoc::coord pos;
    char value;
    path_node* parent;
    size_t score;
    std::vector<std::unique_ptr<path_node> > paths;

    path_node(aoc::coord pos, char value) : path_node(pos, value, nullptr)
    {}
    path_node(aoc::coord pos,
              char value,
              path_node* parent) : pos(pos), value(value), parent(parent), score(1)
    {}
};
std::ostream& operator<< (std::ostream& os, const path_node* from)
{
    if ( !os ) return os;
    std::map<aoc::coord, char> path;
    while ( from )
    {
        path[from->pos] = from->value;
        from = from->parent;
    }
    auto path_rend = path.rend();
    std::string sep;
    for ( auto rit = path.rbegin(); rit != path_rend; ++rit)
    {
        os << sep << rit->second << rit->first;
        sep = "->";
    }
    return os;
}
void print_tree(std::ostream& os, const path_node* origin)
{
    
}

typedef std::pair<int, std::vector<char> > goal_distance_score_type;
typedef std::map<char, std::map<char, goal_distance_score_type> > goal_dist_type;
std::ostream& operator<< ( std::ostream& os, const goal_dist_type& goal_distances)
{
    if ( !os ) return os;
    for ( auto&& goal_distance : goal_distances )
    {
        os << goal_distance.first << " : {";
        for ( auto&& distance : goal_distance.second )
        {
            os << " { " << distance.first << ", " << distance.second.first << ", {";
            std::string sep = " ";
            for ( auto&& dependency : distance.second.second )
            {
                os << sep << dependency;
                sep = ", ";
            }
            os << " }";
        }
        os << " }\n";
    }
    return os;
}

static const aoc::coord up = { -1, 0 };
static const aoc::coord down = { 1, 0 };
static const aoc::coord left = { 0, -1 };
static const aoc::coord right = { 0, 1 };
static const std::vector<aoc::coord> explore_directions = { up, right, down, left };

std::ostream& operator<< ( std::ostream& os, const std::vector<aoc::coord> coords)
{
    if ( !os ) return os;
    std::string sep;
    for ( auto&& coord : coords )
    {
        os << sep << coord;
        sep = ", ";
    }
    return os;
}

class maze_walker
{
public:
    std::unique_ptr<path_node> root;
    std::unique_ptr<path_node> goal_root;

    maze_walker(map_type& map, aoc::coord origin) :
        root(),
        map_(map),
        coord_to_node_()
    {
        root = explore_maze(map, origin);
        goal_posies_ = find_goals(map);
        std::cout << "goal_posies:\n" << goal_posies_ << std::endl;
        goal_scores_ = find_goal_distances(goal_posies_);
        std::cout << "goal_scores:\n" << goal_scores_ << std::endl;
    }
    std::vector<aoc::coord> solve_maze()
    {
        std::vector<aoc::coord> result;
        std::vector<char> gates;
        std::vector<char> targets;
        for ( auto&& key : goal_posies_ )
        {
            if ( isupper(key.first) ) gates.push_back(key.first);
            else if ( key.first == '@' ) continue;
            else targets.push_back(key.first);
        }

        std::map<char, int> goal_guesses_;
        for ( auto&& goal : goal_posies_ )
        {
            for ( auto&& other_goal : goal_posies_ )
            {
                if ( other_goal == goal ) continue;

            }
        }

        char curr = '@';
        while ( targets.size() > 1 )
        {
            std::map<char, int> option_scores;
            for ( auto&& target : targets )
            {
                if ( goal_scores_[curr][target].second.size() > 0 ) continue;
                int h = 0;
                option_scores[target] = goal_scores_[curr][target].first + h;
            }
        }





        return result;
    }
    std::vector<char> options_for();
    std::unique_ptr<path_node> explore_maze(map_type& map, aoc::coord origin)
    {
        std::unique_ptr<path_node> root_node = std::make_unique<path_node>(origin, map[origin]);
        goal_root = std::make_unique<path_node>(origin, map[origin]);

        std::map<path_node*, std::vector<aoc::coord> > unexplored = {
            { root_node.get(), explore_directions }
        };
        coord_to_node_[root_node->pos] = root_node.get();
        path_node* pos = unexplored.begin()->first;
        path_node* goal_pos = goal_root.get();
        while ( pos )
        {
            if ( unexplored[pos].size() == 0 )
            {
                // backtrack
                pos = pos->parent;
                if ( !pos || !islower(pos->value) ) continue;
                goal_pos = goal_pos->parent;
                continue;
            }
            aoc::coord dir = unexplored[pos].back(); unexplored[pos].pop_back();
            aoc::coord cand = pos->pos + dir;
            if ( map[cand] == '#' ) continue;
            if ( pos->parent && cand == pos->parent->pos ) continue; // we came this way..
            pos->paths.emplace_back(std::make_unique<path_node>(cand, map[cand], pos));
            pos = pos->paths.rbegin()->get();
            unexplored.insert({ pos, explore_directions }); // no change if already there
            coord_to_node_[pos->pos] = pos;

            // goal?
            if ( !islower(pos->value) ) continue;
            goal_pos->paths.emplace_back(std::make_unique<path_node>(pos->pos, pos->value, goal_pos));
            goal_pos = goal_pos->paths.rbegin()->get();
        }
        return root_node;
    }

    static goal_pos_type find_goals(const map_type& map)
    {
        goal_pos_type result;
        for ( auto&& position : map )
        {
            if ( position.second == '.' ||
                 position.second == '#' ) continue;
            result[position.second] = position.first;
        }
        return result;
    }
    
    goal_dist_type find_goal_distances(goal_pos_type& goal_positions)
    {
        goal_dist_type result;
        for ( auto&& goal_pos : goal_positions )
        {
            if ( isupper(goal_pos.first) ) continue;
            result[goal_pos.first] = find_goal_distances_for_goal(goal_pos.first, goal_positions, result);
        }
        return result;
    }
    std::map<char, goal_distance_score_type> find_goal_distances_for_goal(char goal, goal_pos_type& goal_positions, goal_dist_type& cache_)
    {
        std::map<char, goal_distance_score_type> result;
        for ( auto&& goal_pos : goal_positions )
        {
            if ( isupper(goal_pos.first) ) continue;
            if ( goal_pos.first == goal ) continue;
            // in the cache??
            if ( cache_.count(goal_pos.first) )
            {
                result[goal_pos.first] = cache_[goal_pos.first][goal];
            }
            else
            {
                result[goal_pos.first] = distance_from(goal_positions[goal], goal_pos.second, cache_);
            }
        }
        return result;
    }
    goal_distance_score_type distance_from(aoc::coord from, aoc::coord to, goal_dist_type& cache_)
    {
        if ( cache_.count(map_[from]) > 0 &&
             cache_[map_[from]].count(map_[to]) )
        {
            return cache_[map_[from]][map_[to]];
        }
        std::vector<aoc::coord> from_path = path_from(from, to);
        std::vector<char> gates;
        for ( auto&& step : from_path )
        {
            if ( goal_posies_.count(map_[step]) == 0 ) continue;
            if ( !isupper(map_[step]) ) continue;
            gates.push_back(map_[step]);
        }
        return { from_path.size() - 1, std::move(gates) };
    }
    std::vector<aoc::coord> path_from(aoc::coord from, aoc::coord to)
    {
        std::vector<aoc::coord> result;
        if ( from == to ) return result;

        if ( from == root->pos )
        {
            path_node* cur = coord_to_node_[to]; // be nice
            while ( cur )
            {
                result.push_back(cur->pos);
                cur = cur->parent;
            }
            std::reverse(result.begin(), result.end());
            return result;
        }

        std::cout << "working path from: " << from << " to: " << to << "\n";
        std::vector<aoc::coord> from_path = path_from(root->pos, from);
        std::cout << "path to from: " << from_path << "\n";
        std::vector<aoc::coord> to_path = path_from(root->pos, to);
        std::cout << "path to to: " << to_path << "\n";

        auto diff_point = std::mismatch(from_path.begin(), from_path.end(),
                                        to_path.begin(), to_path.end());
        from_path.erase(from_path.begin(), diff_point.first - 1);
        to_path.erase(to_path.begin(), diff_point.second);
        result.insert(result.end(), from_path.rbegin(), from_path.rend());
        std::cout << "result.1: " << result << "\n";
        result.insert(result.end(), to_path.begin(), to_path.end());
        std::cout << "result.2: " << result << "\n";

        return result;
    }

private:
    map_type& map_;
    std::map<aoc::coord, path_node*> coord_to_node_;
    goal_pos_type goal_posies_;
    goal_dist_type goal_scores_;
    
};


class maze
{
public:
    
    maze(std::istream& is) :
        map_(map_from_input(is)),
        map_boundary_(map_end(map_)),
        goals_(find_goals(map_)),
        origin_(goals_['@']),
        maze_runner_(map_, origin_)
    {
    }
    static map_type map_from_input(std::istream& is)
    {
        aoc::coord pos;
        map_type result;
        for ( std::string line; std::getline(is, line); )
        {
            for ( auto&& square : line )
            {
                result[pos] = square;
                ++pos.y;
            }
            pos.y = 0;
            ++pos.x;
        }
        return result;
    }
    static goal_pos_type find_goals(const map_type& map)
    {
        goal_pos_type result;
        for ( auto&& position : map )
        {
            if ( position.second == '.' ||
                 position.second == '#' ) continue;
            result[position.second] = position.first;
        }
        return result;
    }
    std::ostream& to_ostream(std::ostream& os)
    {
        if ( !os ) return os;
        for ( int i = 0; i < map_boundary_.x; ++i )
        {
            for ( int j = 0; j < map_boundary_.y; ++j )
            {
                os << map_[{ i, j }];
            }
            os << '\n';
        }
        for ( auto&& goal : goals_ )
        {
            os << "[ " << goal.first << " -> " << goal.second << " ]\n";
        }
        return os;
    }
private:
    map_type map_;
    aoc::coord map_boundary_;
    goal_pos_type goals_;
    aoc::coord origin_;
    maze_walker maze_runner_;
};

int main()
{
>>>>>>> 0ed1cf2... aoc 2019 day 18, lots of mechanics, no solution
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
<<<<<<< HEAD
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
    std::vector<std::string> data = {
        "#######\n"
        "#a.#Cd#\n"
        "##@#@##\n"
        "#######\n"
        "##@#@##\n"
        "#cB#Ab#\n"
        "#######"
    };
    for ( auto&& datum : data )
    {
        std::istringstream iss(datum);
        maze_wanker maisy(iss);
    }
#endif
#if 1
    std::ifstream inf(PROJEUL_AOC_PATH "/18_2_input.txt");
    maze_wanker maisy(inf);
#endif

    return 0;
}
