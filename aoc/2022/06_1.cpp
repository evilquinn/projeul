
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string_view>

#include <aoc/path_def.hpp>

int pos_of_first_duplicate(std::string_view line)
{
    size_t test_pos = 0;
    size_t test_end = line.size();
    while ( test_pos < test_end )
    {
        auto find_result = std::find(std::next(line.begin(), test_pos + 1), line.end(), line[test_pos]);
        if ( find_result != line.end() ) return test_pos;
        ++test_pos;
    }
    return test_pos;
}

int find_sob(std::string const& line)
{
    size_t sosob = 0;
    const size_t marker_size = 4;
    const size_t limit = line.size() - marker_size;
    while ( sosob < limit )
    {
        std::string_view window(line.data() + sosob, marker_size);
        auto duped = pos_of_first_duplicate(window);
        if ( duped == marker_size ) return sosob + marker_size;
        sosob += duped + 1;
    }
    throw std::runtime_error("Couldn't find end of sob marker");
}
std::vector<int> find_sobs(std::istream& input)
{
    std::vector<int> sobs;
    std::string line;
    while(std::getline(input, line))
    {
        sobs.push_back(find_sob(line));
    }
    return sobs;
}

int main()
{
    std::ifstream input(PROJEUL_AOC_PATH "/06_input.txt");
    if ( !input ) throw std::runtime_error("Failed to open input file");

    auto p1 = find_sobs(input);
    if ( p1.size() == 0 ) throw std::runtime_error("Didn't find any sobs!");
#if 0
    for ( auto&& sob : p1 )
    {
        std::cout << "Found sob: " << sob << std::endl;
    }
#endif
    std::cout << "Part 1 result: " << p1[0] << std::endl;

    return 0;
}
