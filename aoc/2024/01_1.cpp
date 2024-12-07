
#include <algorithm>
#include <iostream>
#include <fstream>
#include <numeric>
#include <vector>
#include <aoc/path_def.hpp>


/**
 * Initial test data
 * 3   4
 * 4   3
 * 2   5
 * 1   3
 * 3   9
 * 3   3
 *
 * Sum of the differences between index pairs when sorted should equal 11.
 *
 */
typedef std::vector<int> list_type;
std::ostream& operator<<(std::ostream& os, const list_type& list)
{
    os << "{";
    std::string sep = " ";
    for (auto&& i : list)
    {
        os << sep << i;
        sep = ", ";
    }
    return os << " }";
}
typedef std::pair<list_type, list_type> list_pair_type;
std::ostream& operator<<(std::ostream& os, const list_pair_type& lists)
{
    return os << "{ " << lists.first << ", " << lists.second << " }";
}

list_pair_type test_lists = { { 3, 4, 2, 1, 3, 3 }, { 4, 3, 5, 3, 9, 3 } };

/**
 * sort lists, then sum difference between each pair of elements at each index
 */
int sort_then_sum_differences(const list_pair_type& lists)
{
    auto sorted = lists;
    // someday I'll do this stuff with ranges.  imagine..
    std::sort(sorted.first.begin(), sorted.first.end());
    std::sort(sorted.second.begin(), sorted.second.end());
    auto sum_differences = std::transform_reduce(
        sorted.first.begin(),
        sorted.first.end(),
        sorted.second.begin(),
        0L,
        std::plus{},
        [](const int& lhs, const int& rhs) { return std::abs(rhs - lhs); });
    return sum_differences;
}

list_pair_type read_lists(std::istream& input)
{
    list_pair_type result;
    std::string line;
    while (std::getline(input, line))
    {
        int lhs, rhs;
        auto scan_result = std::sscanf(line.c_str(), "%d %d", &lhs, &rhs);
        if ( scan_result == 2 )
        {
            result.first.push_back(lhs);
            result.second.push_back(rhs);
        }
        else if (scan_result != EOF) throw std::runtime_error(std::string("Scanf failed on line: ") + line);
    }
    return result;
}

int main()
{
    std::string input_path(PROJEUL_AOC_PATH "/01_input.txt");
    std::ifstream input(input_path);
    if (!input ) throw std::runtime_error(std::string("Error reading input file: ").append(input_path));
    auto lists = read_lists(input);

    auto result = sort_then_sum_differences(lists);
    std::cout << "Part 1 result: " << result << std::endl;
    return 0;
}
