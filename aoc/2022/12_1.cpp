
#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

#include <aoc/coord.hpp>

#include <aoc/path_def.hpp>

using map_type = std::vector<std::vector<int> >;
using coord = coord_util::coord;

const coord up    = coord( 0, -1);
const coord down  = coord( 0,  1);
const coord left  = coord(-1,  0);
const coord right = coord( 1,  0);
const std::vector<coord> explorables = { up, down, left, right };

coord map_limit_coord(map_type const& map)
{
    if ( map.size() == 0 ) throw std::runtime_error("empty map!");
    return coord(map.back().size(), map.size());
}

map_type::value_type::value_type const& map_at(map_type const& map, coord c)
{
    if ( ! ( c < map_limit_coord(map) ) ) throw std::runtime_error("c not in map");
    return map[c.y][c.x];
}

map_type::value_type::value_type& map_at(map_type& map, coord c)
{
    return const_cast<map_type::value_type::value_type&>(
               map_at(const_cast<map_type const&>(map), c));
}

map_type read_map(std::istream& is)
{
    map_type result;
    std::string line;
    while(std::getline(is, line))
    {
        result.emplace_back(line.begin(), line.end());
    }
    return result;
}

struct path_finder
{
    struct exploring_state
    {
        coord pos;
        int cost;
    };
    int find_shortest_path(map_type& map)
    {
        map_type exploring_map = init_explore(map);

        auto start = find_start(map);
        map_at(map, start) = 'a';
        auto target = find_first(map, 'E');
        map_at(map, target) = 'z';
        auto lower_limit = coord(-1, -1);
        auto upper_limit = map_limit_coord(map);

        auto explore_queue = std::queue<exploring_state>({ { start, 0 } });
        do
        {
            // pop off next to explore
            auto current_explore = explore_queue.front();
            explore_queue.pop();
            // explore it
            auto& current_cost = map_at(exploring_map, current_explore.pos);
            if ( current_cost != 0 )
            {
                // already got here before, nothing further to explore on this path
                continue;
            }
            current_cost = current_explore.cost;
            // pop on where to explore next
            for ( auto&& explorable : explorables )
            {
                auto cand = current_explore.pos + explorable;

                if ( coord_util::within_limit(lower_limit, cand) // not outside lower bound
                  && coord_util::within_limit(cand, upper_limit) // not outside upper bound
                  && map_at(exploring_map, cand) == 0 //not already explored
                  && map_at(map, cand) <= map_at(map, current_explore.pos) + 1 //isn't too high
                )
                {
                    // have we won!?
                    if ( cand == target ) return current_cost + 1;
                    // no, keep going
                    explore_queue.push( { cand, current_cost + 1 } );
                }
            }
        } while ( explore_queue.size() > 0 );

        throw std::runtime_error("Failed to find target!?");
    }

    coord find_start(map_type const& map)
    {
        return find_first(map, 'S');
    }

    coord find_first(map_type const& map, int target)
    {
        coord limit = map_limit_coord(map);
        coord_util::coord_incrementer incr{limit.x};
        for ( coord i = coord(0, 0); i < limit; incr(i) )
        {
            if ( map[i.y][i.x] == target ) return i;
        }
        throw std::runtime_error("Failed to find target");
    }

    map_type init_explore(map_type const& map)
    {
        map_type result = map;
        coord limit = map_limit_coord(map);
        coord_util::coord_incrementer incr{limit.x};
        for ( coord i = coord(0, 0); within_limit(i, limit); incr(i) )
        {
            map_at(result, i) = 0;
        }
        return result;
    }
};

int main()
{
    std::ifstream input(PROJEUL_AOC_PATH "/12_input.txt");
    if ( !input ) throw std::runtime_error("Failed to open input file");

    auto map = read_map(input);
    path_finder hero;
    auto result = hero.find_shortest_path(map);
    std::cout << "Result: " << result << std::endl;

    return 0;
}
