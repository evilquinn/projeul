#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>

#include "coord.hpp"
#include <aoc/map.hpp>

namespace map_util
{

std::ostream& operator<<(std::ostream& os, const line_type& line)
{
    for ( auto&& stat : line )
    {
        os << static_cast<char>(stat);
    }
    return os;
}

std::ostream& operator<<(std::ostream& os, const map_type& map)
{
    for ( auto&& line : map )
    {
        os << line << "\n";
    }
    return os;
}

coord_util::coord limit(const map_type& map)
{
    if ( map.empty() ) return { 0, 0 };
    return { static_cast<ptrdiff_t>(map[0].size()), static_cast<ptrdiff_t>(map.size()) };
}

const map_type::value_type::value_type& at(const map_type& map, coord_util::coord c)
{
    auto bound = limit(map);
    if ( ! within_limit( c, bound ) )
    {
        std::ostringstream msg;
        msg << "coord_util::coord " << c << " not within bounds of map, bound: " << bound;
        throw std::runtime_error(msg.str());
    }
    return map[c.y][c.x];
}
map_type::value_type::value_type& at(map_type& map, coord_util::coord c)
{
    return const_cast< map_type::value_type::value_type& >(at(
               const_cast< const map_type& >(map), c));
}
bool is_set(const map_type& map, coord_util::coord c, map_type::value_type::value_type v)
{
    return at(map, c) == v;
}
void set(map_type& map, coord_util::coord c, map_type::value_type::value_type v)
{
    at(map, c) = v;
}
size_t count(const map_type& map, map_type::value_type::value_type v)
{
    size_t total = 0;
    for ( auto&& line : map )
    {
        total += std::count(line.begin(), line.end(), v);
    }
    return total;
}
map_type to_map(std::istream& map_input)
{
    map_type result;
    // something
    std::string line_str;
    while ( map_input >> line_str )
    {
        line_type line;
        std::transform(line_str.begin(), line_str.end(),
                       std::back_inserter(line),
                       [](char c){ return static_cast<map_type::value_type::value_type>(c); });
        result.emplace_back(std::move(line));
    }
    return result;
}
map_type to_map(const std::string& s)
{
    std::istringstream input(s);
    return to_map(input);
}

} // end namespace map_util
