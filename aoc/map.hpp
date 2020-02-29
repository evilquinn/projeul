#ifndef AOC_MAP_HPP
#define AOC_MAP_HPP

#include <iosfwd>
#include <vector>

#include "coord.hpp"

namespace map_util
{

typedef std::string line_type;
typedef std::vector<line_type> map_type;

std::ostream& operator<<(std::ostream& os, const line_type& line);
std::ostream& operator<<(std::ostream& os, const map_type& map);
coord_util::coord limit(const map_type& map);
const map_type::value_type::value_type& at(const map_type& map, coord_util::coord c);
map_type::value_type::value_type& at(map_type& map, coord_util::coord c);
bool is_set(const map_type& map, coord_util::coord c, map_type::value_type::value_type v);
void set(map_type& map, coord_util::coord c, map_type::value_type::value_type v);
size_t count(const map_type& map, map_type::value_type::value_type v);
map_type to_map(std::istream& map_input);
map_type to_map(const std::string& s);

} // end namespace map_util


#endif // AOC_MAP_HPP
