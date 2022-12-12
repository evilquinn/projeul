#include <iostream>
#include <fstream>
#include <map>
#include <algorithm>

#include <aoc/path_def.hpp>

using register_type = std::map<int, int>;

register_type read_instructions(std::istream& input)
{
    register_type result;
    std::string line;
    int cycles = 0;
    int value = 1;
    while(std::getline(input, line))
    {
        if ( line == "" ) continue;
        if ( line == "noop" )
        {
            ++cycles;
            continue;
        }
        int add_by = 0;
        sscanf(line.c_str(), "addx %d", &add_by);
        cycles += 2;
        value += add_by;
        result[cycles] = value;
    }
    return result;
}

int sum_signal_strengths(register_type reg)
{
    int result = 0;
    const int num_signals = 6;
    for ( int i = 0; i < num_signals; ++i )
    {
        int interesting_signal = ( i * 40 ) + 20;
        auto find_result = reg.lower_bound(interesting_signal);
        if ( find_result == reg.begin() ) throw std::runtime_error("Didn't expect find first element");
        if ( find_result == reg.end() ) throw std::runtime_error("Didn't expect to get end");
        std::advance(find_result, -1);
        result += ( interesting_signal * find_result->second );
    }
    return result;
}

int main()
{
    std::ifstream input(PROJEUL_AOC_PATH "/10_input.txt");
    if ( !input ) throw std::runtime_error("Failed to open input file");

    auto reg = read_instructions(input);
    auto p1 = sum_signal_strengths(reg);
    std::cout << "Part 1 result: " << p1 << std::endl;

    return 0;
}
