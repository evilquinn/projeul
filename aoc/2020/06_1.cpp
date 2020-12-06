/*
 * https://adventofcode.com/2020/day/6
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <set>
#include <vector>
#include <string>
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

int count_group_everyone(std::istream& is)
{
    std::string common = "*";
    for ( std::string line; std::getline(is, line); )
    {
        if ( line.empty() ) break;
        std::sort(line.begin(), line.end());
        if ( common == "*" )
        {
            common = line;
            continue;
        }
        auto erase_from = std::remove_if(common.begin(), common.end(), [&line](char c){ return line.find(c) == line.npos; });
        common.erase(erase_from, common.end());
    }
    return common.size();
}

int count_groups(std::istream& is)
{
    int result = 0;
    while ( is )
    {
        auto res = count_group_everyone(is);
        result += res;
    }
    return result;
}


int main()
{
#if 0
    std::vector<std::string> data = {
        "abc\n\na\nb\nc\n\nab\nac\n\na\na\na\na\n\nb"
    };
    for ( auto&& datum : data )
    {
        std::istringstream iss(datum);
        auto res = count_groups(iss);
        std::cout << "res: " << res << std::endl;
    }
#endif
    std::ifstream inf(PROJEUL_AOC_PATH "/06_input.txt");
    int result = count_groups(inf);
    std::cout << "result: " << result << std::endl;
    return 0;
}
