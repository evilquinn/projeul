
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string_view>

#include <aoc/path_def.hpp>

size_t pos_of_first_duplicate(std::string_view line)
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

size_t find_som(std::string const& line, size_t marker_size)
{
    size_t sosom = 0;
    const size_t limit = line.size() - marker_size;
    while ( sosom < limit )
    {
        std::string_view window(line.data() + sosom, marker_size);
        auto duped = pos_of_first_duplicate(window);
        if ( duped == marker_size ) return sosom + marker_size;
        sosom += duped + 1;
    }
    throw std::runtime_error("Couldn't find end of som marker");
}
std::vector<size_t> find_soms(std::istream& input, size_t marker_size)
{
    std::vector<size_t> soms;
    std::string line;
    while(std::getline(input, line))
    {
        soms.push_back(find_som(line, marker_size));
    }
    return soms;
}

int main()
{
    std::ifstream input(PROJEUL_AOC_PATH "/06_input.txt");
    if ( !input ) throw std::runtime_error("Failed to open input file");

    auto p1 = find_soms(input, 4);
    if ( p1.size() == 0 ) throw std::runtime_error("Didn't find any soms!");
#if 0
    for ( auto&& som : p1 )
    {
        std::cout << "Found som: " << som << std::endl;
    }
#endif
    std::cout << "Part 1 result: " << p1[0] << std::endl;

    input.clear();
    input.seekg(0);
    auto p2 = find_soms(input, 14);
    if ( p2.size() == 0 ) throw std::runtime_error("Didn't find any soms!");
#if 0
    for ( auto&& som : p2 )
    {
        std::cout << "Found som: " << som << std::endl;
    }
#endif
    std::cout << "Part 2 result: " << p2[0] << std::endl;

    return 0;
}
