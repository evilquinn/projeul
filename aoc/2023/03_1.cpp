#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <charconv>
#include <functional>

#include <aoc/coord.hpp>
#include <aoc/path_def.hpp>

using coord = coord_util::basic_coord<int>;
using coord_incrementer = coord_util::basic_coord_incrementer<coord::value_type>;
using schematic_t = std::map<coord, char>;

coord max_coord(const schematic_t& schematic)
{
    coord result;
    for ( auto&& c : schematic )
    {
        if ( c.first.x > result.x ) result.x = c.first.x;
        if ( c.first.y > result.y ) result.y = c.first.y;
    }
    return result;
}
coord limit_coord(const schematic_t& schematic)
{
    return max_coord(schematic) + coord{ 1, 1 };
}
std::ostream& operator<< (std::ostream& os, const schematic_t& schematic)
{
    auto limit = limit_coord(schematic);
    for(coord::value_type y = 0; y < limit.y; ++y)
    {
        for(coord::value_type x = 0; x < limit.x; ++x)
        {
            os << schematic.at({ x, y });
        }
        os << std::endl;
    }
    return os;
}

schematic_t parse_schematic(std::istream& is)
{
    schematic_t result;
    std::string line;
    coord::value_type y = 0;
    while ( std::getline(is, line) )
    {
        for( coord::value_type x = 0; x < static_cast<coord::value_type>(line.size()); ++x )
        {
            result[{ x, y }] = line[x];
        }
        ++y;
    }
    return result;
}

bool is_symbol(unsigned char c)
{
    return !std::isdigit(c) && c != '.';
}
bool is_gear(unsigned char c)
{
    return c == '*';
}
bool has_adjacent_symbol(const schematic_t& schematic, const coord& c, int size, std::function<bool(unsigned char)> predicate, coord* symbol_location)
{
    // check schematic for a symbol at any position around the provided coord/size
    auto origin = c - coord{ 1, 1 };
    auto limit = c + coord{ size + 1, 2 }; // trust me, I think
    auto incrementer = coord_util::make_incrementer(limit, origin);
    // no need to examine the coords that are part of the number, but meh
    for ( auto i = origin; coord_util::within_limit(i, limit); incrementer(i) )
    {
        if ( ! schematic.contains(i) ) continue;
        if ( predicate(schematic.at(i)) )
        {
            if ( symbol_location ) *symbol_location = i;
            return true;
        }
    }
    return false;
}
bool has_adjacent_symbol(const schematic_t& schematic, const coord& c, int size)
{
    return has_adjacent_symbol(schematic, c, size, is_symbol, nullptr);
}
size_t part1(const schematic_t& schematic)
{
    size_t result = 0;
    auto limit = limit_coord(schematic);
    auto incrementer = coord_util::make_incrementer(limit);
    std::string curr_num;
    coord curr_num_start{ 0, 0 };
    auto process_gathered_number = [&]()
    {
        if ( has_adjacent_symbol(schematic, curr_num_start, static_cast<int>(curr_num.size())) )
        {
            size_t num = 0;
            std::from_chars(curr_num.data(), curr_num.data() + curr_num.size(), num);
            result += num;
        }
        curr_num = "";
    };
    for ( coord i{ 0, 0 }; coord_util::within_limit(i, limit); incrementer(i) )
    {
        // have we crossed a newline while having gathered a number? process it
        if ( curr_num.size() != 0 && i.y != curr_num_start.y )
        {
            process_gathered_number();
        }
        // as you were..
        auto value = schematic.at(i);
        if ( std::isdigit(value) )
        {
            if ( curr_num.size() == 0 ) curr_num_start = i;
            curr_num.push_back(value);
        }
        else if ( curr_num.size() != 0 )
        {
            process_gathered_number();
        }
    }
    return result;
}

size_t part2(const schematic_t& schematic)
{
    auto limit = limit_coord(schematic);
    auto incrementer = coord_util::make_incrementer(limit);
    std::string curr_num;
    coord curr_num_start{ 0, 0 };
    std::map<coord, std::vector<size_t> > gear_ratios;
    auto process_gathered_number = [&]()
    {
        coord gear_location;
        if ( has_adjacent_symbol(schematic, curr_num_start, static_cast<int>(curr_num.size()), is_gear, &gear_location) )
        {
            size_t num = 0;
            std::from_chars(curr_num.data(), curr_num.data() + curr_num.size(), num);
            gear_ratios[gear_location].push_back(num);
        }
        curr_num = "";
    };
    for ( coord i{ 0, 0 }; coord_util::within_limit(i, limit); incrementer(i) )
    {
        // have we crossed a newline while having gathered a number? process it
        if ( curr_num.size() != 0 && i.y != curr_num_start.y )
        {
            process_gathered_number();
        }
        // as you were..
        auto value = schematic.at(i);
        if ( std::isdigit(value) )
        {
            if ( curr_num.size() == 0 ) curr_num_start = i;
            curr_num.push_back(value);
        }
        else if ( curr_num.size() != 0 )
        {
            process_gathered_number();
        }
    }
    size_t result = 0;
    for ( auto&& gear_ratio : gear_ratios )
    {
        if ( gear_ratio.second.size() == 2 )
        {
            // could probably do a reduce algo with multiply, but meh, there's only 2..
            size_t ratio = gear_ratio.second[0] * gear_ratio.second[1];
            result += ratio;
        }
    }
    return result;
}

std::string example = "467..114..\n"
                      "...*......\n"
                      "..35..633.\n"
                      "......#...\n"
                      "617*......\n"
                      ".....+.58.\n"
                      "..592.....\n"
                      "......755.\n"
                      "...$.*....\n"
                      ".664.598..\n";

int main()
{

    //std::istringstream iss(example);
    std::ifstream ifs(PROJEUL_AOC_PATH "/03_input.txt");
    auto schema = parse_schematic(ifs);
    std::cout << "Part 1 result: " << part1(schema) << std::endl;
    std::cout << "Part 2 result: " << part2(schema) << std::endl;

    return 0;
}
