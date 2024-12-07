
#include <algorithm>
#include <aoc/path_def.hpp>
#include <fstream>
#include <iostream>
#include <numeric>
#include <unordered_set>
#include <vector>

/**
 * Initial test data
 * 3   4
 * 4   3
 * 2   5
 * 1   3
 * 3   9
 * 3   3
 *
 * part 1:
 * Sum of the differences between index pairs when sorted should equal 11.
 *
 * part 2:
 * Sum of each product of element in lhs multiplied by its count in rhs,
 * should equal 31.
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

typedef std::unordered_multiset<int> set_type;
std::ostream& operator<<(std::ostream& os, const set_type& set)
{
    os << "{";
    std::string sep = " ";
    for (auto&& v : set)
    {
        os << sep << v;
        sep = ", ";
    }
    return os << " }";
}
typedef std::pair<list_type, set_type> list_set_type;
std::ostream& operator<<(std::ostream& os, const list_set_type& list_set)
{
    return os << "{ " << list_set.first << ", " << list_set.second << " }";
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
        if (scan_result == 2)
        {
            result.first.push_back(lhs);
            result.second.push_back(rhs);
        }
        else if (scan_result != EOF)
            throw std::runtime_error(std::string("Scanf failed on line: ") +
                                     line);
    }
    return result;
}

std::string test_input =
    "3   4\n"
    "4   3\n"
    "2   5\n"
    "1   3\n"
    "3   9\n"
    "3   3\n";

list_set_type parse_lists(const list_pair_type& lists)
{
    list_set_type result = {
        lists.first, set_type{ lists.second.begin(), lists.second.end() }
    };
    return result;
}

int sum_products_element_by_count(const list_set_type& list_set)
{
    auto sum_differences = std::transform_reduce(
        list_set.first.begin(),
        list_set.first.end(),
        0L,
        std::plus{},
        [&list_set](const int& v) { return v * list_set.second.count(v); });
    return sum_differences;
}

int main()
{
    std::string input_path(PROJEUL_AOC_PATH "/01_input.txt");
    std::ifstream input(input_path);
    if (!input)
        throw std::runtime_error(
            std::string("Error reading input file: ").append(input_path));
    auto lists = read_lists(input);

    auto result = sort_then_sum_differences(lists);
    std::cout << "Part 1 result: " << result << std::endl;

    auto list_counts = parse_lists(lists);
    auto result2 = sum_products_element_by_count(list_counts);
    std::cout << "Part 2 result: " << result2 << std::endl;

    return 0;
}
