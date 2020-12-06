/*
 * https://adventofcode.com/2020/day/6
 */

#include <iostream>
#include <fstream>
#include <set>
#include <algorithm>

#include <aoc/path_def.hpp>
#include <aoc/coord.hpp>

int count_group(std::istream& is)
{
    std::set<char> questions;
    for ( std::string line; std::getline(is, line); )
    {
        if ( line.empty() ) break;
        questions.insert(line.begin(), line.end());
    }
    return questions.size();
}

int count_groups(std::istream& is)
{
    int result = 0;
    while ( is )
    {
        result += count_group(is);
    }
    return result;
}


int main()
{
    std::ifstream inf(PROJEUL_AOC_PATH "/06_input.txt");
    int result = count_groups(inf);
    std::cout << "result: " << result << std::endl;
    return 0;
}
