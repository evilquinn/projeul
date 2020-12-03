#include <iostream>
#include <fstream>

#include "../coord.hpp"
#include "../map.hpp"
#include "../path_def.hpp"

namespace status
{
static const char tree = '#';
static const char empty = '.';
} // end namespace status

namespace
{
struct coord_stepper
{
    coord_util::coord boundary = { 0, 0 };
    coord_util::coord step(const coord_util::coord& step_from, const coord_util::coord& step_by)
    {
        coord_util::coord dest = step_from + step_by;
        dest.x %= boundary.x;
        return dest;
    }
};
size_t count_trees_on_path(const map_util::map_type& map, const coord_util::coord& step)
{
    size_t result = 0;
    coord_stepper stepper = { map_util::limit(map) };
    coord_util::coord pos = { 0, 0 };
    while ( coord_util::within_limit(pos, stepper.boundary) )
    {
        if ( map_util::at(map, pos) == status::tree )
        {
            ++result;
        }
        pos = stepper.step(pos, step);
    }
    return result;
}
size_t tree_path_product(const map_util::map_type& map, const std::vector<coord_util::coord>& paths)
{
    size_t result = 1;
    for ( auto&& path : paths )
    {
        result *= count_trees_on_path(map, path);
    }
    return result;
}

}


int main()
{
    using map_util::operator<<;

    std::string test_input = "..##.......\n"
                             "#...#...#..\n"
                             ".#....#..#.\n"
                             "..#.#...#.#\n"
                             ".#...##..#.\n"
                             "..#.##.....\n"
                             ".#.#.#....#\n"
                             ".#........#\n"
                             "#.##...#...\n"
                             "#...##....#\n"
                             ".#..#...#.#";
    std::ifstream inf(PROJEUL_AOC_PATH "/03_input.txt");
    auto slope_map = map_util::to_map(inf);
    size_t result = count_trees_on_path(slope_map, coord_util::coord{ 3, 1 } );
    std::cout << "result: " << result << std::endl;

    std::vector<coord_util::coord> paths = {
        coord_util::coord{ 1, 1 },
        coord_util::coord{ 3, 1 },
        coord_util::coord{ 5, 1 },
        coord_util::coord{ 7, 1 },
        coord_util::coord{ 1, 2 }
    };
    size_t product = tree_path_product(slope_map, paths);
    std::cout << "product: " << product << std::endl;
    return 0;
}
