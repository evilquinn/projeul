/*
 * https://adventofcode.com/2020/day/13
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <vector>
#include <algorithm>

#include <boost/regex.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string.hpp>

#include <aoc/path_def.hpp>

struct rule
{
    std::string name;
    std::pair<size_t, size_t> range_1;
    std::pair<size_t, size_t> range_2;
};
struct rule rule_from_string(const std::string& str)
{
    struct rule result;
    static const boost::regex pattern("([a-zA-Z ]+): ([\\d]+)-([\\d]+) or ([\\d]+)-([\\d]+)$");
    // capture[0] -> match!
    // capture[1] -> name
    // capture[2] -> first range first
    // capture[3] -> first range last
    // capture[4] -> second range first
    // capture[5] -> second range last
    boost::smatch groups;
    if ( boost::regex_search(str, groups, pattern) )
    {
        result.name = groups[1];
        result.range_1 = { boost::lexical_cast<size_t>(groups[2]), boost::lexical_cast<size_t>(groups[3]) };
        result.range_2 = { boost::lexical_cast<size_t>(groups[4]), boost::lexical_cast<size_t>(groups[5]) };
        return result;
    }
    throw std::runtime_error("failed to parse rule");
}
typedef std::vector<size_t> ticket_type;
ticket_type ticket_from_string(const std::string& str)
{
    ticket_type result;
    std::vector<std::string> toks;
    boost::split(toks, str, boost::is_any_of(","));
    for ( auto&& tok : toks )
    {
        result.push_back(boost::lexical_cast<size_t>(tok));
    }
    return result;
}
class scanner
{
public:
    scanner(std::istream& is)
    {
        parse_input(is);
    }
    void parse_input(std::istream& is)
    {
        enum section_type { rules, my_ticket, other_tickets };
        section_type section = rules;
        for ( std::string line; std::getline(is, line); )
        {
            if ( line.empty() ) continue;
            if ( line == "your ticket:" ) { section = my_ticket; continue; }
            if ( line == "nearby tickets:") { section = other_tickets; continue; }
            switch ( section )
            {
            case rules : rules_.push_back(rule_from_string(line)); break;
            case my_ticket : my_ticket_ = ticket_from_string(line); break;
            case other_tickets : other_tickets_.push_back(ticket_from_string(line)); break;
            default : throw std::runtime_error("unexpected section");
            }
        }
    }
    size_t calc_error_rate()
    {
        size_t result = 0;
        for ( auto&& ticket : other_tickets_ )
        {
            result += sum_invalid_fields(ticket);
        }
        return result;
    }
    size_t sum_invalid_fields(const ticket_type& ticket)
    {
        size_t result = 0;
        for ( auto&& field : ticket )
        {
            bool valid = false;
            for ( auto&& rule : rules_ )
            {
                if ( is_valid_for_rule(field, rule) )
                {
                    valid = true;
                    break;
                }
            }
            if ( ! valid ) result += field;
        }
        return result;
    }
    bool is_valid_for_rule(size_t field, const rule& rule)
    {
        return ( field >= rule.range_1.first && field <= rule.range_1.second ) ||
               ( field >= rule.range_2.first && field <= rule.range_2.second );
    }
private:
    std::vector<rule> rules_;
    ticket_type my_ticket_;
    std::vector<ticket_type> other_tickets_;
};

int main()
{
#if 1
    std::vector<std::string> data = {
        "class: 1-3 or 5-7\n"
        "row: 6-11 or 33-44\n"
        "seat: 13-40 or 45-50\n\n"
        "your ticket:\n"
        "7,1,14\n\n"
        "nearby tickets:\n"
        "7,3,47\n"
        "40,4,50\n"
        "55,2,20\n"
        "38,6,12\n"
    };
    for ( auto&& datum : data )
    {
        std::istringstream iss(datum);
        scanner scanny(iss);
        auto result  = scanny.calc_error_rate();
        std::cout << "result: " << result << std::endl;
    }
#endif
#if 1
    std::ifstream inf(PROJEUL_AOC_PATH "/16_input.txt");
    scanner scanny(inf);
    auto result  = scanny.calc_error_rate();
    std::cout << "result: " << result << std::endl;
#endif
    return 0;
}
