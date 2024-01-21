#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <unordered_map>
#include <string>
#include <vector>
#include <string_view>
#include <algorithm>
#include <charconv>

#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>

#include <aoc/path_def.hpp>

using subset_t = std::unordered_map<std::string, int>;
std::ostream& operator<< (std::ostream& os, const subset_t& subset)
{
    os << "[";
    std::string sep = " ";
    for ( auto&& element : subset )
    {
        os << sep << "[ " << element.second << ", " << std::quoted(element.first) << " ]";
        sep = ", ";
    }
    return os << " ]";
}
// returns true if all colour and counts in lhs are available in rhs, otherwise false.
bool is_within(const subset_t& lhs, const subset_t& rhs)
{
    for ( auto&& colour : lhs )
    {
        if ( ! rhs.contains(colour.first) ) return false;
        if ( colour.second > rhs.at(colour.first) ) return false;
    }
    return true;
}

using subsets_t = std::vector<subset_t>;
std::ostream& operator<< (std::ostream& os, const subsets_t& subsets)
{
    os << "[";
    std::string sep = " ";
    for ( auto&& subset : subsets )
    {
        os << sep << subset;
        sep = ", ";
    }
    return os << " ]";
}
subset_t smallest_subset_for(const subsets_t& subsets)
{
    subset_t result;
    for ( auto&& subset : subsets )
    {
        for ( auto&& colour : subset )
        {
            if ( colour.second > result[colour.first] ) result[colour.first] = colour.second;
        }
    }
    return result;
}
size_t power_of(const subset_t& subset)
{
    if ( subset.size() == 0 ) return 0;
    size_t result = 1;
    for ( auto&& colour : subset )
    {
        result *= colour.second;
    }
    return result;
}
struct game
{
    int id;
    subsets_t subsets;
};
std::ostream& operator<< (std::ostream& os, const game& g)
{
    return os << "{ \"id\": " << g.id << ", \"subsets\": " << g.subsets << " }";
}
using games_t = std::vector<game>;
std::ostream& operator<< (std::ostream& os, const games_t& games)
{
    os << "[";
    std::string sep = " ";
    for ( auto&& game : games )
    {
        os << sep << game;
        sep = ", ";
    }
    return os << " ]";
}
size_t games_power_sum(const games_t& games)
{
    size_t result = 0;
    for ( auto&& game : games )
    {
        result += power_of(smallest_subset_for(game.subsets));
    }
    return result;
}

game parse_game_line(std::string_view line)
{
    game result;
    // magic
    std::vector<std::string> id_and_subsets;
    boost::split(id_and_subsets, line, boost::is_any_of(":"));
    if(id_and_subsets.size() != 2) throw std::runtime_error(std::string("Expected two elements spliting on colon (:) : ").append(line));
    std::from_chars(id_and_subsets[0].data()+5, id_and_subsets[0].data() + id_and_subsets[0].size(), result.id);
    std::vector<std::string> subsets;
    //throw away spaces first, they're annoying
    id_and_subsets[1].erase(std::remove(id_and_subsets[1].begin(), id_and_subsets[1].end(), ' '), id_and_subsets[1].end());
    boost::split(subsets, id_and_subsets[1], boost::is_any_of(";"));
    for ( auto&& subset : subsets )
    {
        std::vector<std::string> colours;
        boost::split(colours, subset, boost::is_any_of(","));
        subset_t colour_set;
        for ( auto&& colour : colours )
        {
            int colour_count = 0;
            auto parse_result = std::from_chars(colour.data(), colour.data() + colour.size(), colour_count);
            if ( parse_result.ec != std::errc() ) throw std::runtime_error(std::string("Failed parsing number from: ").append(colour));
            colour_set[parse_result.ptr] = colour_count;
        }
        result.subsets.push_back(colour_set);
    }
    return result;
}

games_t parse_game_lines(std::istream& is)
{
    games_t result;
    std::string line;
    while ( std::getline(is, line) )
    {
        result.push_back(parse_game_line(line));
    }
    return result;
}


std::string example = "Game 1: 3 blue, 4 red; 1 red, 2 green, 6 blue; 2 green\n"
                      "Game 2: 1 blue, 2 green; 3 green, 4 blue, 1 red; 1 green, 1 blue\n"
                      "Game 3: 8 green, 6 blue, 20 red; 5 blue, 4 red, 13 green; 5 green, 1 red\n"
                      "Game 4: 1 green, 3 red, 6 blue; 3 green, 6 red; 3 green, 15 blue, 14 red\n"
                      "Game 5: 6 red, 1 blue, 3 green; 2 blue, 1 red, 2 green\n";

int main()
{
    std::istringstream is(example);

    std::ifstream ifs(PROJEUL_AOC_PATH "/02_input.txt");
    auto games = parse_game_lines(ifs);
    //std::cout << games << std::endl;

    auto candidate_bag = subset_t{ { "red", 12 }, { "green", 13 }, { "blue", 14 } };
    //std::cout << candidate_bag << std::endl;

    size_t result = 0;
    for ( auto&& game : games )
    {
        auto to_sum = game.id;
        for ( auto&& subset : game.subsets )
        {
            if ( !is_within(subset, candidate_bag) )
            {
                to_sum = 0;
                break;
            }
        }
        result += to_sum;
    }
    std::cout << "Part 1 result: " << result << std::endl;
    std::cout << "Part 2 result: " << games_power_sum(games) << std::endl;

    return 0;
}
