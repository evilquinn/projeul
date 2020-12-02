#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <boost/lexical_cast.hpp>
#include "../aoc/path_def.hpp"

int main()
{
    std::ifstream inf(PROJEUL_AOC_PATH "/01_input.txt");
    std::vector<size_t> data;
    for (std::string line; std::getline(inf, line); )
    {
        data.push_back(boost::lexical_cast<size_t>(line));
    }
    std::sort(data.begin(), data.end());
    for ( auto it = data.begin(); it != data.end(); ++it )
    {
        size_t cand = 2020 - *it;
        if ( std::binary_search(std::next(it), data.end(), cand) )
        {
            std::cout << "answer: " << *it * cand << std::endl;
        }
    }
    return 0;
}