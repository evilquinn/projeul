
#include <algorithm>
#include <aoc/path_def.hpp>
#include <charconv>
#include <cmath>
#include <cstdio>
#include <format>
#include <fstream>
#include <iostream>
#include <span>
#include <sstream>
#include <vector>

/**
 * part 1:
 *
 *
 *
 *
 *
 */

std::string test_string =
    "987654321111111\n"
    "811111111111119\n"
    "234234234234278\n"
    "818181911112111\n";

using bank_t      = std::vector<int>;
using banks_t     = std::vector<bank_t>;
using bank_span_t = std::span<const bank_t::value_type>;

size_t largest_joltage(bank_span_t bank, size_t num_batteries = 2)
{
    if (bank.size() < num_batteries)
    {
        throw std::runtime_error(std::format("bank.size() is less than {}", num_batteries));
    }
    auto next_num_batteries = num_batteries - 1;
    auto search_end         = std::prev(bank.end(), next_num_batteries);
    auto max                = std::max_element(bank.begin(), search_end);
    if (next_num_batteries == 0)
    {
        return *max;
    }
    auto next_begin = std::next(max);
    auto next_size  = bank.size() - std::distance(bank.begin(), next_begin);
    return *max * std::pow(10, next_num_batteries) +
           largest_joltage(bank_span_t{ next_begin, next_size }, next_num_batteries);
}

size_t count_joltages(const banks_t banks, size_t num_batteries = 2)
{
    size_t result = 0;
    for (auto&& bank : banks)
    {
        result += largest_joltage(bank_span_t{ bank.data(), bank.size() }, num_batteries);
    }
    return result;
}

banks_t parse_banks(std::istream& is)
{
    banks_t result;
    std::string line;
    while (std::getline(is, line))
    {
        bank_t bank;
        for (auto&& digit : line)
        {
            bank.push_back(digit - '0');
        }
        result.push_back(std::move(bank));
    }
    return result;
}

int main()
{
    std::string input_path(PROJEUL_AOC_PATH "/03_input.txt");
    std::ifstream ifs(input_path);
    if (!ifs)
        throw std::runtime_error(std::string("Error reading input file: ").append(input_path));

    std::istringstream iss(test_string);

    auto data   = parse_banks(ifs);
    auto result = count_joltages(data, 12);

    std::cout << "result: " << result << std::endl;

    std::cout << "hello" << std::endl;

    return 0;
}
