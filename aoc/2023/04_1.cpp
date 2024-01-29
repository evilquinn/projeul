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

struct card
{
    int id;
    std::vector<int> winning;
    std::vector<int> mine;
};
std::ostream& operator<<(std::ostream& os, std::vector<int> const& data)
{
    os << "[";
    std::string sep = " ";
    for ( auto&& number : data )
    {
        os << sep << number;
        sep = ", ";
    }
    return os << " ]";
}
std::ostream& operator<<(std::ostream& os, card const& data)
{
    return os << "{ \"id\": " << data.id << ", \"winning\": " << data.winning << ", \"mine\": " << data.mine << " }";
}

using cards_t = std::vector<card>;
std::ostream& operator<<(std::ostream& os, cards_t const& data)
{
    os << "[";
    std::string sep = " ";
    for ( auto&& card : data )
    {
        os << sep << card;
        sep = ", ";
    }
    return os << " ]";
}

card parse_card(std::string_view line)
{
    card result;
    std::vector<std::string> line_items;
    boost::split(line_items, line, boost::is_any_of(":|"));
    if ( line_items.size() != 3 ) throw std::runtime_error("line split failed");
    const char* id_pos = line_items[0].data() + std::distance(line_items[0].begin(), std::find_if(line_items[0].begin(), line_items[0].end(),
                                                                                                  [](char c){ return std::isdigit(c); }));
    const char* id_end = line_items[0].data() + line_items[0].size();
    std::from_chars(id_pos, id_end, result.id);
    std::vector<std::string> numbers;
    boost::split(numbers, line_items[1], boost::is_any_of(" "), boost::algorithm::token_compress_on);
    for ( auto&& number : numbers )
    {
        if ( number.size() == 0 ) continue;
        result.winning.push_back(boost::lexical_cast<int>(number));
    }
    numbers.clear();
    boost::split(numbers, line_items[2], boost::is_any_of(" "));
    for ( auto&& number : numbers )
    {
        if ( number.size() == 0 ) continue;
        result.mine.push_back(boost::lexical_cast<int>(number));
    }
    std::sort(result.winning.begin(), result.winning.end());
    std::sort(result.mine.begin(), result.mine.end());
    return result;
}
cards_t parse_cards(std::istream& is)
{
    cards_t result;
    std::string line;
    while ( std::getline(is, line) )
    {
        result.push_back(parse_card(line));
    }
    return result;
}

size_t count_cards_score(cards_t const& cards)
{
    size_t result = 0;
    for ( auto&& card : cards )
    {
        std::vector<int> matches;
        std::set_intersection(card.winning.begin(), card.winning.end(), card.mine.begin(), card.mine.end(), std::back_inserter(matches));
        if ( matches.size() == 0 ) continue;
        result += pow(2, matches.size() - 1);
    }
    return result;
}

size_t count_total_cards(cards_t const& cards)
{
    std::map<size_t, size_t> card_counts;
    for ( auto&& card : cards )
    {
        card_counts[card.id] += 1;
        std::vector<int> matches;
        std::set_intersection(card.winning.begin(), card.winning.end(), card.mine.begin(), card.mine.end(), std::back_inserter(matches));
        for ( size_t i = 1; i <= matches.size(); ++i )
        {
            card_counts[card.id+i] += card_counts[card.id];
        }
    }
    size_t result = 0;
    for ( auto&& count : card_counts )
    {
        result += count.second;
    }
    return result;
}

std::string example = "Card 1: 41 48 83 86 17 | 83 86  6 31 17  9 48 53\n"
                      "Card 2: 13 32 20 16 61 | 61 30 68 82 17 32 24 19\n"
                      "Card 3:  1 21 53 59 44 | 69 82 63 72 16 21 14  1\n"
                      "Card 4: 41 92 73 84 69 | 59 84 76 51 58  5 54 83\n"
                      "Card 5: 87 83 26 28 32 | 88 30 70 12 93 22 82 36\n"
                      "Card 6: 31 18 13 56 72 | 74 77 10 23 35 67 36 11\n";

int main()
{

    //std::istringstream is(example);
    std::ifstream is(PROJEUL_AOC_PATH "/04_input.txt");
    auto cards = parse_cards(is);
    std::cout << "Part 1 result: " << count_cards_score(cards) << std::endl;
    std::cout << "Part 2 result: " << count_total_cards(cards) << std::endl;
    //std::cout << cards << std::endl;

    return 0;
}
