
#include <algorithm>
#include <aoc/path_def.hpp>
#include <charconv>
#include <cstdio>
#include <fstream>
#include <iostream>
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

using bank_t  = std::vector<int>;
using banks_t = std::vector<bank_t>;

size_t largest_joltage(const bank_t& bank)
{
    if (bank.size() < 2)
        throw std::runtime_error("bank.size() is less than 2");
    auto last_element = std::prev(bank.end());
    auto max          = std::max_element(bank.begin(), bank.end());
    if (max != last_element)
    {
        auto next_max = std::max_element(std::next(max), bank.end());
        return *max * 10 + *next_max;
    }
    else
    {
        auto prev_max = std::max_element(bank.begin(), max);
        return *prev_max * 10 + *max;
    }
}

size_t count_joltages(const banks_t banks)
{
    size_t result = 0;
    for (auto&& bank : banks)
    {
        result += largest_joltage(bank);
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
    auto result = count_joltages(data);

    std::cout << "result: " << result << std::endl;

    std::cout << "hello" << std::endl;

    return 0;
}
