
#include <iostream>
#include <fstream>
#include <vector>
#include <variant>
#include <string_view>
#include <algorithm>

#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>

#include <aoc/path_def.hpp>

struct packet_value;
using list_type = std::vector<packet_value>;
struct packet_value
{
    std::variant<int, list_type> value;
};
bool operator< (packet_value const& lhs, packet_value const& rhs)
{
    // both ints or both vectors
    if ( lhs.value.index() == rhs.value.index() )
    {
        return lhs.value < rhs.value;
    }

    // vector vs int
    // promote the int one to a vector
    if ( lhs.value.index() == 0 )
    {
        packet_value nlhs{std::vector<packet_value>(1, lhs)};
        return nlhs.value < rhs.value;
    }
    else
    {
        packet_value nrhs{std::vector<packet_value>(1, rhs)};
        return lhs.value < nrhs.value;
    }
}

struct packet_pair
{
    packet_value left;
    packet_value right;
};

using packets_type = std::vector<packet_value>;

const std::string_view::value_type* find_term_end(std::string_view line)
{
    // empty term
    if ( line.size() == 0 ) return line.data();

    // int, find the first ','
    if ( *line.data() != '[' ) return std::find(line.data(), line.data() + line.size(), ',');

    // list, find the matching close
    int num_opens = 0;
    for ( size_t i = 0; i < line.size(); ++i )
    {
        if ( line[i] == '[' ) ++num_opens;
        if ( line[i] == ']' ) --num_opens;
        if ( num_opens == 0 ) return line.data() + i + 1;
    }
    return line.data() + line.size();
}

packet_value read_value(std::string_view line)
{
    packet_value result;
    if ( line.size() == 0 )
    {
        result.value = std::vector<packet_value>();
        return result;
    }

    if ( line[0] == '[' )
    {
        // subtring, split, foreach read_value(split thing)
        line = line.substr(1, line.size() - 2);
        result.value = std::vector<packet_value>();
        auto limit = line.data() + line.size();
        auto term_start = line.data();
        while (term_start < limit)
        {
            auto term_end = find_term_end(std::string_view(term_start, limit - term_start));
            std::get<list_type>(result.value).push_back(
                read_value(std::string_view(term_start, term_end - term_start)));
            if ( term_end == limit ) break;
            term_start = term_end + 1;
        }
        return result;
    }

    // int
    result.value = boost::lexical_cast<int>(line);
    return result;
}
packets_type read_packets(std::istream& is)
{
    packets_type result;
    std::string line;
    while(std::getline(is, line))
    {
        if (line == "") continue;
        result.push_back(read_value(line));
    }
    return result;
}


int main()
{
    std::ifstream input(PROJEUL_AOC_PATH "/13_input.txt");
    if ( !input ) throw std::runtime_error("Failed to open input file");

    auto packets = read_packets(input);
    auto result = 0;
    for ( size_t i = 1; i < packets.size(); i += 2 )
    {
        if ( packets[i-1] < packets[i] )
        {
            result += ( i / 2 ) + 1;
        }
    }
    std::cout << "Result: " << result << std::endl;

    return 0;
}
