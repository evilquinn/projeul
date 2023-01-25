
#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <algorithm>

#include <aoc/coord.hpp>

#include <aoc/path_def.hpp>

using coord = coord_util::coord;

const coord up    = coord( 0, -1);
const coord down  = coord( 0,  1);
const coord left  = coord(-1,  0);
const coord right = coord( 1,  0);
const std::vector<coord> explorables = { up, down, left, right };

struct map_type
{
    typedef std::vector<std::vector<int> > value_type;
    value_type map;

    map_type() {}
    map_type(coord dimensions) : map(dimensions.y, std::vector<int>(dimensions.x, 0))
    {
    }

    coord dimensions() const
    {
        if ( map.size() == 0 ) return coord(0, 0);
        return coord(map.back().size(), map.size());
    }

    value_type::value_type::value_type const& at(coord c) const
    {
        if ( ! ( c < dimensions() ) ) throw std::runtime_error("c not in map");
        return map[c.y][c.x];
    }

    value_type::value_type::value_type& at(coord c)
    {
        return const_cast<value_type::value_type::value_type&>(
                   const_cast<map_type const&>(*this).at(c));
    }

    static map_type read_map(std::istream& is)
    {
        map_type result;
        std::string line;
        while(std::getline(is, line))
        {
            result.map.emplace_back(line.begin(), line.end());
        }
        return result;
    }

    coord find_next(value_type::value_type::value_type target, coord start_pos = coord(0, 0)) const
    {
        coord limit = dimensions();
        coord_util::coord_incrementer incr{limit.x};
        for ( coord i = start_pos; within_limit(i, limit); incr(i) )
        {
            if ( at(i) == target ) return i;
        }
        throw std::runtime_error("Failed to find target");
    }

    coord incr(coord c, int by) const
    {
        coord limit = dimensions();
        coord_util::coord_incrementer incrementer{limit.x};
        incrementer(c, by);
        return c;
    }
};

struct path_finder
{
    struct exploring_state
    {
        coord pos;
        int cost;
    };
    int find_shortest_path(map_type map)
    {
        auto start = map.find_next('S');
        map.at(start) = 'a';
        return find_shortest_path_from(map, start);
    }

    std::vector<int> find_shortest_paths(map_type map)
    {
        std::vector<int> results;
        auto start = map.find_next('S');
        map.at(start) = 'a';
        start = map.find_next('a');
        auto limit = map.dimensions();
        coord_util::coord_incrementer incr{limit.x};
        while ( within_limit(start, limit) )
        {
            try
            {
                results.push_back(find_shortest_path_from(map, start));
            }
            catch(const std::exception& ex)
            {
                // blocked path? meh
            }
            incr(start);
            try
            {
                start = map.find_next('a', start);
            }
            catch(const std::exception& e)
            {
                // we're done
                break;
            }
        }
        return results;
    }
    int find_shortest_path_from(map_type map, coord from)
    {
        map_type exploring_map(map.dimensions());

        try
        {
            auto start = map.find_next('S');
            map.at(start) = 'a';
        }
        catch ( std::exception const& ex)
        {
            // meh, fine
        }
        auto target = map.find_next('E');
        map.at(target) = 'z';
        auto lower_limit = coord(-1, -1);
        auto upper_limit = map.dimensions();

        auto explore_queue = std::queue<exploring_state>({ { from, 0 } });
        do
        {
            // pop off next to explore
            auto current_explore = explore_queue.front();
            explore_queue.pop();
            // explore it
            auto& current_cost = exploring_map.at(current_explore.pos);
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
                  && exploring_map.at(cand) == 0 //not already explored
                  && map.at(cand) <= map.at(current_explore.pos) + 1 //isn't too high
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
};

int main()
{
    std::ifstream input(PROJEUL_AOC_PATH "/12_input.txt");
    if ( !input ) throw std::runtime_error("Failed to open input file");

    auto map = map_type::read_map(input);
    path_finder hero;
    auto result = hero.find_shortest_path(map);
    std::cout << "Result: " << result << std::endl;

    auto results = hero.find_shortest_paths(map);
    std::sort(results.begin(), results.end());
    std::cout << "Result: " << results[0] << std::endl;

    return 0;
}
