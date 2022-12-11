#include <iostream>
#include <fstream>
#include <map>
#include <algorithm>

#include <aoc/path_def.hpp>
#include <aoc/coord.hpp>

struct tree_type
{
    int height;
    bool visible;
    int scenic_score;
    tree_type() : height(0), visible(false), scenic_score(1) {}
    tree_type(int height) : height(height), visible(false), scenic_score(1) {}
};
bool operator< (tree_type const& lhs, tree_type const& rhs)
{
    return lhs.height < rhs.height;
}
using coord_util::coord;
using map_type = std::map<coord, tree_type>;

map_type read_map(std::istream& input)
{
    map_type result;
    std::string line;
    int y = 0;
    while(std::getline(input, line))
    {
        for ( int x = 0; (unsigned)x < line.size(); ++x )
        {
            result[coord{x, y}] = tree_type(line[x] - '0');
        }
        ++y;
    }

    return result;
}

coord max_coord(map_type const& tree_map)
{
    return std::max_element(tree_map.begin(), tree_map.end())->first;
}

size_t count_visible(map_type& tree_map)
{
    size_t result = 0;
    coord boundary = max_coord(tree_map);
    coord limit = boundary + coord{1, 1};
    if ( limit.x != limit.y ) throw std::runtime_error("Not a square...");
    //magic
    for ( int i = 0; i < limit.x; ++i )
    {
        int highest = -1;
        // do the row from left
        for ( coord c = coord{ 0, i }; c.x < limit.x; ++c.x )
        {
            tree_type& tree = tree_map[c];
            if ( tree.height > highest )
            {
                if ( ! tree.visible ) ++result;
                tree.visible = true;
                highest = tree.height;
            }
        }
        highest = -1;
        // do the row from right
        for ( coord c = coord{ boundary.x, i }; c.x >= 0; --c.x )
        {
            tree_type& tree = tree_map[c];
            if ( tree.height > highest )
            {
                if ( ! tree.visible ) ++result;
                tree.visible = true;
                highest = tree.height;
            }
        }
        highest = -1;
        // do the column from top
        for ( coord c = coord{ i, 0 }; c.y < limit.y; ++c.y )
        {
            tree_type& tree = tree_map[c];
            if ( tree.height > highest )
            {
                if ( ! tree.visible ) ++result;
                tree.visible = true;
                highest = tree.height;
            }
        }
        highest = -1;
        // do the column from bottom
        for ( coord c = coord{ i, boundary.y }; c.y >= 0; --c.y )
        {
            tree_type& tree = tree_map[c];
            if ( tree.height > highest )
            {
                if ( ! tree.visible ) ++result;
                tree.visible = true;
                highest = tree.height;
            }
        }
    }
    return result;
}

int max_scenic(map_type& tree_map)
{
    int result = 0;
    coord boundary = max_coord(tree_map);
    for ( auto&& entry : tree_map )
    {
        if ( entry.first.x == 0 || entry.first.x == boundary.x || entry.first.y == 0 || entry.first.y == boundary.y )
        {
            entry.second.scenic_score = 0;
            continue;
        }
        // go right
        int distance = 0;
        for ( coord c = coord{ entry.first.x + 1, entry.first.y }; c.x <= boundary.x; ++c.x )
        {
            ++distance;
            if ( tree_map[c].height >= entry.second.height ) break;
        }
        entry.second.scenic_score *= distance;
        // go left
        distance = 0;
        for ( coord c = coord{ entry.first.x - 1, entry.first.y }; c.x >= 0; --c.x )
        {
            ++distance;
            if ( tree_map[c].height >= entry.second.height ) break;
        }
        entry.second.scenic_score *= distance;
        // go down
        distance = 0;
        for ( coord c = coord{ entry.first.x, entry.first.y + 1}; c.y <= boundary.y; ++c.y )
        {
            ++distance;
            if ( tree_map[c].height >= entry.second.height ) break;
        }
        entry.second.scenic_score *= distance;
        // go up
        distance = 0;
        for ( coord c = coord{ entry.first.x, entry.first.y - 1}; c.y >= 0; --c.y )
        {
            ++distance;
            if ( tree_map[c].height >= entry.second.height ) break;
        }
        entry.second.scenic_score *= distance;

        if ( entry.second.scenic_score > result ) result = entry.second.scenic_score;
    }
    return result;
}

int main()
{
    std::ifstream input(PROJEUL_AOC_PATH "/08_input.txt");
    if ( !input ) throw std::runtime_error("Failed to open input file");

    auto tree_map = read_map(input);

    auto p1 = count_visible(tree_map);
    std::cout << "Part 1 result: " << p1 << std::endl;

    auto p2 = max_scenic(tree_map);
    std::cout << "Part 2 result: " << p2 << std::endl;

    return 0;
}
