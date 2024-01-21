#include <iostream>
#include <fstream>

#include "../coord.hpp"
#include "../map.hpp"
#include "../path_def.hpp"

namespace status
{
static const char tree = '#';
} // end namespace status

namespace
{
struct coord_stepper
{
    coord_util::basic_coord<std::ptrdiff_t> boundary = { 0, 0 };
    coord_util::basic_coord<std::ptrdiff_t> step(const coord_util::basic_coord<std::ptrdiff_t>& step_from, const coord_util::basic_coord<std::ptrdiff_t>& step_by)
    {
        coord_util::basic_coord<std::ptrdiff_t> dest = step_from + step_by;
        dest.x %= boundary.x;
        return dest;
    }
};
size_t count_trees_on_path(const map_util::map_type& map, const coord_util::basic_coord<std::ptrdiff_t>& step)
{
    size_t result = 0;
    coord_stepper stepper = { map_util::limit(map) };
    coord_util::basic_coord<std::ptrdiff_t> pos = { 0, 0 };
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
size_t tree_path_product(const map_util::map_type& map, const std::vector<coord_util::basic_coord<std::ptrdiff_t>>& paths)
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
    size_t result = count_trees_on_path(slope_map, coord_util::basic_coord<std::ptrdiff_t>{ 3, 1 } );
    std::cout << "result: " << result << std::endl;

    std::vector<coord_util::basic_coord<std::ptrdiff_t>> paths = {
        coord_util::basic_coord<std::ptrdiff_t>{ 1, 1 },
        coord_util::basic_coord<std::ptrdiff_t>{ 3, 1 },
        coord_util::basic_coord<std::ptrdiff_t>{ 5, 1 },
        coord_util::basic_coord<std::ptrdiff_t>{ 7, 1 },
        coord_util::basic_coord<std::ptrdiff_t>{ 1, 2 }
    };
    size_t product = tree_path_product(slope_map, paths);
    std::cout << "product: " << product << std::endl;
    return 0;
}
