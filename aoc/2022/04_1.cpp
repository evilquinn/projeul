
#include <iostream>
#include <fstream>
#include <cstdio>

#include <aoc/path_def.hpp>

using section_range_type = std::pair<int, int>;
bool is_fully_contained(std::string const& line)
{
    section_range_type lhs = { 0, 0 }, rhs = { 0, 0 };
    std::sscanf(line.c_str(), "%d-%d,%d-%d", &lhs.first, &lhs.second, &rhs.first, &rhs.second);
    if ( lhs.first <= rhs.first && lhs.second >= rhs.second ) return true;
    if ( rhs.first <= lhs.first && rhs.second >= lhs.second ) return true;
    return false;
}

int count_fully_contained_pairs(std::istream& is)
{
    int result = 0;
    std::string line;
    while(std::getline(is, line))
    {
        if ( is_fully_contained(line) ) ++result;
    }
    return result;
}

int main()
{
    std::ifstream input(PROJEUL_AOC_PATH "/04_input.txt");
    if ( !input ) throw std::runtime_error("Failed to open input file");

    int p1 = count_fully_contained_pairs(input);
    std::cout << "Part 1 result: " << p1 << std::endl;

    return 0;
}
