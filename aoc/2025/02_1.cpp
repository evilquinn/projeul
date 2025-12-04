
#include <algorithm>
#include <aoc/path_def.hpp>
#include <charconv>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

/**
 * part 1:
 *
 *
 *
 *
 *
 */

std::string test_string =
    "11-22,95-115,998-1012,1188511880-1188511890,222220-222224,"
    "1698522-1698528,446443-446449,38593856-38593862,565653-565659,"
    "824824821-824824827,2121212118-2121212124";

using range_t  = std::pair<size_t, size_t>;
using ranges_t = std::vector<range_t>;

ranges_t parse_ranges(std::istream& is)
{
    ranges_t result;
    std::string line;
    if (!std::getline(is, line))
        throw std::runtime_error("Failed to read line");

    const auto line_begin = line.c_str();
    const auto line_end   = line_begin + line.size();
    auto range_begin      = line_begin;
    while (range_begin != line_end)
    {
        auto range_end   = std::find(range_begin, line_end, ',');
        auto range_delim = std::find(range_begin, range_end, '-');
        if (range_delim == range_end)
            throw std::runtime_error("failed to find range delim");
        auto range = range_t{ 0, 0 };
        std::from_chars(range_begin, range_delim, range.first);
        std::from_chars(std::next(range_delim), range_end, range.second);
        result.push_back(std::move(range));
        range_begin = range_end == line_end ? line_end : std::next(range_end);
        range_end   = std::find(range_begin, line_end, ',');
    }
    return result;
}

bool is_invalid(size_t v)
{
    auto vstr = std::to_string(v);
    if ((vstr.size() % 2) == 1)
        return false;
    auto mid = vstr.size() / 2;
    return std::equal(vstr.data(), vstr.data() + mid, vstr.data() + mid, vstr.data() + vstr.size());
}

size_t count_invalid(const ranges_t& ranges)
{
    size_t result = 0;
    for (auto&& range : ranges)
    {
        for (auto i = range.first; i < range.second + 1; ++i)
        {
            if (is_invalid(i))
            {
                result += i;
            }
        }
    }
    return result;
}

int main()
{
    std::string input_path(PROJEUL_AOC_PATH "/02_input.txt");
    std::ifstream ifs(input_path);
    if (!ifs)
        throw std::runtime_error(std::string("Error reading input file: ").append(input_path));

    std::istringstream iss(test_string);

    auto data   = parse_ranges(ifs);
    auto result = count_invalid(data);

    std::cout << "part1: " << result << std::endl;

    std::cout << "hello" << std::endl;

    return 0;
}
