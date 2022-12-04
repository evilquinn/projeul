
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

int sum_priorities_mispacked_types(std::istream& input)
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

int sum_priorities_group_badges(std::istream& input)
{
    int result = 0;
    while(input)
    {
        std::vector<std::string> group;
        for(int i = 0; i < 3; ++i)
        {
            std::string line;
            std::getline(input, line);
            if ( line == "" || !input ) continue;
            if ( line.size() & 0x1 ) throw std::runtime_error("line.size() is odd");
            std::sort(line.begin(), line.end());
            group.push_back(line);
        }

        if ( int(group.size()) != 3 ) continue;

        std::string common_0_1;
        std::set_intersection(group[0].begin(), group[0].end(), group[1].begin(), group[1].end(), std::back_inserter(common_0_1));
        if ( common_0_1.size() == 0 ) throw std::runtime_error("Didn't match anything in group[0] and group[1]");

        common_0_1.erase(std::unique(common_0_1.begin(), common_0_1.end()), common_0_1.end());

        std::string common_0_1_2;
        std::set_intersection(group[2].begin(), group[2].end(), common_0_1.begin(), common_0_1.end(), std::back_inserter(common_0_1_2));
        if ( common_0_1_2.size() == 0 ) throw std::runtime_error("Didn't match anything among groups group[0], group[1] and group[2]");
        if ( common_0_1_2.size() > 1 ) throw std::runtime_error("Matched more than one thing among groups group[0], group[1] and group[2]");

        result += priority(*common_0_1_2.begin());
    }
    return result;

}


int main()
{
    std::ifstream input(PROJEUL_AOC_PATH "/03_input.txt");
    if ( !input ) throw std::runtime_error("Failed to open input file");

    int p1 = sum_priorities_mispacked_types(input);
    std::cout << "Part 1 result: " << p1 << std::endl;

    input.clear();
    input.seekg(0);
    if ( !input ) throw std::runtime_error("Failed to rewind input file");
    int p2 = sum_priorities_group_badges(input);
    std::cout << "Part 2 result: " << p2 << std::endl;

    return 0;
}
