
#include <algorithm>
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>
#include <fstream>
#include <iostream>
#include <vector>
#include "../path_def.hpp"

std::string test_string =
    "47|53\n"
    "97|13\n"
    "97|61\n"
    "97|47\n"
    "75|29\n"
    "61|13\n"
    "75|53\n"
    "29|13\n"
    "97|29\n"
    "53|29\n"
    "61|53\n"
    "97|53\n"
    "61|29\n"
    "47|13\n"
    "75|47\n"
    "97|75\n"
    "47|61\n"
    "75|61\n"
    "47|29\n"
    "75|13\n"
    "53|13\n"
    "\n"
    "75,47,61,53,29\n"
    "97,61,53,29,13\n"
    "75,29,13\n"
    "75,97,47,61,53\n"
    "61,13,29\n"
    "97,13,75,29,47\n";

typedef std::pair<int, int> rule_type;
std::ostream& operator<<(std::ostream& os, const rule_type& rule)
{
    return os << "[ " << rule.first << ", " << rule.second << " ]";
}
typedef std::vector<rule_type> rules_type;
std::ostream& operator<<(std::ostream& os, const rules_type& rules)
{
    os << "[";
    std::string sep = " ";
    for (auto&& rule : rules)
    {
        os << sep << rule;
        sep = ", ";
    }
    return os << " ]";
}
typedef std::vector<int> update_type;
std::ostream& operator<<(std::ostream& os, const update_type& update)
{
    os << "[";
    std::string sep = " ";
    for (auto&& v : update)
    {
        os << sep << v;
        sep = ", ";
    }
    return os << " ]";
}
typedef std::vector<update_type> updates_type;
std::ostream& operator<<(std::ostream& os, const updates_type& updates)
{
    os << "[";
    std::string sep = " ";
    for (auto&& update : updates)
    {
        os << sep << update;
        sep = ", ";
    }
    return os << " ]";
}

typedef std::pair<rules_type, updates_type> input_type;
std::ostream& operator<<(std::ostream& os, const input_type& input)
{
    return os << "{ \"rules\": " << input.first
              << ", \"updates\": " << input.second << " }";
}

input_type read_input(std::istream& input_stream)
{
    input_type result;
    std::string line;
    while (std::getline(input_stream, line))
    {
        if (line.size() == 0)
        {
            break;
        }
        int first, second;
        auto scan_result =
            std::sscanf(line.c_str(), "%d|%d", &first, &second);
        if (scan_result == 2)
        {
            result.first.emplace_back(first, second);
        }
        else if (scan_result != EOF)
            throw std::runtime_error(std::string("Scanf failed on line: ") +
                                     line);
    }
    while (std::getline(input_stream, line))
    {
        result.second.push_back({});
        std::vector<std::string> toks;
        boost::split(toks, line, boost::is_any_of(","));
        for (auto&& tok : toks)
        {
            result.second.back().push_back(boost::lexical_cast<int>(tok));
        }
    }
    return result;
}

bool is_ordered(const rules_type& rules, const update_type& update)
{
    /**
     * Search update for the each rule's second, if not found, success.
     * Otherwise, search update remainder for the rule's first, if not found,
     * success. Otherwise fail.
     */
    for (auto&& rule : rules)
    {
        auto second_pos =
            std::find(update.begin(), update.end(), rule.second);
        if (second_pos != update.end())
        {
            auto first_pos = std::find(second_pos, update.end(), rule.first);
            if (first_pos != update.end())
            {
                return false;
            }
        }
    }
    return true;
}

bool fix_unordered(const rules_type& rules, update_type& update)
{
    /**
     * Similar to is_unordered, but instead if unordered, put a first_pos in
     * front of second_pos
     */
    bool result = false;
    while (true)
    {
        bool do_another_pass = false;
        for (auto&& rule : rules)
        {
            auto second_pos =
                std::find(update.begin(), update.end(), rule.second);
            if (second_pos != update.end())
            {
                auto first_pos =
                    std::find(second_pos, update.end(), rule.first);
                if (first_pos != update.end())
                {
                    // try a swap because it's easier, but maybe it's moving
                    // more than necessary...
                    std::iter_swap(first_pos, second_pos);
                    do_another_pass = true;
                    result = true;
                }
            }
        }
        if (!do_another_pass)
        {
            return result;
        }
    }
}

size_t sum_ordered_medians(input_type input)
{
    size_t result = 0;
    for (auto&& update : input.second)
    {
        //if (is_ordered(input.first, update))
        if (fix_unordered(input.first, update))
        {
            result += update.at(update.size() / 2);
        }
    }
    return result;
}

int main()
{
    std::stringstream test_stream(test_string);
    auto test_input = read_input(test_stream);
    std::cout << test_input << std::endl;
    std::string input_path(PROJEUL_AOC_PATH "/05_input.txt");
    std::ifstream input_stream(input_path);
    if (!input_stream)
        throw std::runtime_error(
            std::string("Error reading input file: ").append(input_path));
    auto input  = read_input(input_stream);
    auto result = sum_ordered_medians(input);
    std::cout << "Part 1 result: " << result << std::endl;
    return 0;
}
