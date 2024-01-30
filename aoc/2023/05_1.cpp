#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <charconv>

#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>


#include <aoc/path_def.hpp>

enum class category
{
    seed,
    soil,
    fertilizer,
    water,
    light,
    temperature,
    humidity,
    location
};
std::ostream& operator<<(std::ostream& os, const category& cat)
{
    switch ( cat )
    {
    case category::seed:        return os << "seed";
    case category::soil:        return os << "soil";
    case category::fertilizer:  return os << "fertilizer";
    case category::water:       return os << "water";
    case category::light:       return os << "light";
    case category::temperature: return os << "temperature";
    case category::humidity:    return os << "humidity";
    case category::location:    return os << "location";
    default: throw std::runtime_error("unrecognised category");
    }
}
struct map_range_t
{
    size_t key_start;
    size_t value_start;
    size_t size;
};
std::ostream& operator<<(std::ostream& os, const map_range_t& range)
{
    return os << "{ \"key_start\": " << range.key_start << ", \"value_start\": " << range.value_start << ", \"size\": " << range.size << " }";
}
struct map_t
{
    category key_category;
    category value_category;
    std::vector<map_range_t> ranges;
};
std::ostream& operator<<(std::ostream& os, const map_t& map)
{
    os << "{ \"key_category\": \"" << map.key_category << "\", \"value_category\": \"" << map.value_category << "\", \"ranges\": [";
    std::string sep = " ";
    for ( auto&& range : map.ranges )
    {
        os << sep << range;
        sep = ", ";
    }
    return os << " ] }";
}
using mapped_seed_t = std::map<category, size_t>;
std::ostream& operator<<(std::ostream& os, const mapped_seed_t& seed)
{
    os << "[";
    std::string sep = " ";
    for ( auto&& value : seed )
    {
        os << sep << "{ \"" << value.first << "\": " << value.second << " }";
        sep = ", ";
    }
    return os << "]";
}
struct almanac_t
{
    std::vector<size_t> seeds;
    std::vector<mapped_seed_t> mapped_seeds;
    std::map<category, map_t> maps;
};
std::ostream& operator<<(std::ostream& os, const almanac_t& almanac)
{
    os << "{ \"seeds\": [";
    std::string sep = " ";
    for ( auto&& seed : almanac.seeds )
    {
        os << sep << seed;
        sep = ", ";
    }
    os << " ], \"mapped_seeds\": [";
    sep = " ";
    for ( auto&& s : almanac.mapped_seeds )
    {
        os << sep << s;
        sep = ", ";
    }
    os << " ], \"maps\": [";
    sep = " ";
    for ( auto&& map : almanac.maps )
    {
        os << sep << map.second;
        sep = ", ";
    }
    return os << " ] }";
}

std::vector<size_t> parse_seeds(std::string_view line)
{
    std::vector<size_t> result;
    std::vector<std::string> parts;
    boost::split(parts, line, boost::is_any_of(" "));
    for ( size_t i = 1; i < parts.size(); ++i )
    {
        size_t val = 0;
        std::from_chars(parts[i].data(), parts[i].data() + parts[i].size(), val);
        result.push_back(val);
    }
    return result;
}
almanac_t parse_almanac(std::istream& input)
{
    almanac_t result;
    std::string line;
    std::getline(input, line); // seeds line
    result.seeds = parse_seeds(line);
    std::getline(input, line); // discard empty
    auto parse_map_line = [&](category key, category value)
    {
        auto& pos = result.maps[key] = map_t{ key, value, {} };
        while( std::getline(input, line) )
        {
            if( line.size() == 0 ) break; // empty line discarded
            std::vector<std::string> parts;
            boost::split(parts, line, boost::is_any_of(" "));
            pos.ranges.emplace_back(boost::lexical_cast<size_t>(parts[1]),
                                    boost::lexical_cast<size_t>(parts[0]),
                                    boost::lexical_cast<size_t>(parts[2]));
        }
    };
    std::getline(input, line); // discard "seed-to-soil map:"
    parse_map_line(category::seed, category::soil);
    std::getline(input, line); // discard "soil-to-fertilizer map:"
    parse_map_line(category::soil, category::fertilizer);
    std::getline(input, line); // discard "fertilizer-to-water map:"
    parse_map_line(category::fertilizer, category::water);
    std::getline(input, line); // discard "water-to-light map:"
    parse_map_line(category::water, category::light);
    std::getline(input, line); // discard "light-to-temperature map:"
    parse_map_line(category::light, category::temperature);
    std::getline(input, line); // discard "temperature-to-humidity map:"
    parse_map_line(category::temperature, category::humidity);
    std::getline(input, line); // discard "humidity-to-location map:"
    parse_map_line(category::humidity, category::location);

    return result;
}
std::string example =
"seeds: 79 14 55 13\n"
"\n"
"seed-to-soil map:\n"
"50 98 2\n"
"52 50 48\n"
"\n"
"soil-to-fertilizer map:\n"
"0 15 37\n"
"37 52 2\n"
"39 0 15\n"
"\n"
"fertilizer-to-water map:\n"
"49 53 8\n"
"0 11 42\n"
"42 0 7\n"
"57 7 4\n"
"\n"
"water-to-light map:\n"
"88 18 7\n"
"18 25 70\n"
"\n"
"light-to-temperature map:\n"
"45 77 23\n"
"81 45 19\n"
"68 64 13\n"
"\n"
"temperature-to-humidity map:\n"
"0 69 1\n"
"1 0 69\n"
"\n"
"humidity-to-location map:\n"
"60 56 37\n"
"56 93 4\n";

void process_seeds(almanac_t& almanac)
{
    for ( auto&& seed : almanac.seeds )
    {
        almanac.mapped_seeds.push_back( { { category::seed, seed } } );
        for ( auto&& map : almanac.maps )
        {
            auto key = map.second.key_category;
            auto value = map.second.value_category;
            auto mapped = almanac.mapped_seeds.back()[key];
            for ( auto&& range : map.second.ranges )
            {
                if ( mapped >= range.key_start &&
                     mapped < ( range.key_start + range.size ) )
                {
                    mapped = range.value_start + mapped - range.key_start;
                    break;
                }
            }
            almanac.mapped_seeds.back()[value] = mapped;
        }
    }
}

size_t lowest_location(const almanac_t& almanac)
{
    size_t result = std::numeric_limits<int>::max();
    for ( auto&& seed : almanac.mapped_seeds )
    {
        auto cand = seed.at(category::location); // undefined behaviour? meh.
        if ( cand < result ) result = cand;
    }
    return result;
}

int main()
{

    //std::istringstream is(example);
    std::ifstream is(PROJEUL_AOC_PATH "/05_input.txt");
    auto almanac = parse_almanac(is);
    process_seeds(almanac);
    std::cout << "Part 1 result: " << lowest_location(almanac) << std::endl;
    //std::cout << almanac << std::endl;

    return 0;
}
