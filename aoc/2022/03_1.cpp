
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

#include <aoc/path_def.hpp>

int priority(char type)
{
    if (std::islower(type)) return type - 96;
    return type - 38;
}

int sum_priorities(std::istream& input)
{
    int result = 0;
    std::string line;
    while(std::getline(input, line))
    {
        if ( line == "" ) continue;
        if ( line.size() & 0x1 ) throw std::runtime_error("line.size() is odd");
        auto middle = std::next(line.begin(), line.size()/2);
        auto find_result = std::find_first_of(line.begin(), middle, middle, line.end());
        if ( find_result == line.end() ) throw std::runtime_error("Failed to find double packed type");
        result += priority(*find_result);
    }
    return result;
}


int main()
{
    std::ifstream input(PROJEUL_AOC_PATH "/03_input.txt");
    if ( !input ) throw std::runtime_error("Failed to open input file");

    int p1 = sum_priorities(input);
    std::cout << "Part 1 result: " << p1 << std::endl;

    return 0;
}
