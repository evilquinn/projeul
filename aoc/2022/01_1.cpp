
#include <iostream>
#include <fstream>
#include <vector>
#include <boost/lexical_cast.hpp>

#include <aoc/path_def.hpp>

using calories_count_type = std::vector<int>;

calories_count_type count_calories(std::istream& input)
{
    calories_count_type result;
    std::string line;
    bool next_elf = true;
    while(std::getline(input, line))
    {
        if ( line == "" )
        {
            next_elf = true;
            continue;
        }
        if ( next_elf )
        {
            next_elf = false;
            result.push_back(0);
        }
        result.back() += boost::lexical_cast<calories_count_type::value_type>(line);
    }
    return result;
}

int main()
{
    std::ifstream input(PROJEUL_AOC_PATH "/01_input.txt");
    if ( !input ) throw std::runtime_error("Failed to open input file");

    calories_count_type calories = count_calories(input);
    auto max_pos = std::max_element(calories.begin(), calories.end());
    if (max_pos == calories.end()) throw std::runtime_error("Failed to find max");
    auto max = *max_pos;
    std::cout << "result: " << max << std::endl;
    return 0;
}
