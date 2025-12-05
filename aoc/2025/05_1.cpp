
#include <aoc/path_def.hpp>
#include <format>
#include <fstream>
#include <iostream>
#include <sstream>

#include <map>
#include <vector>

#include <aoc/coord.hpp>

/**
 * part 1:
 *
 *
 *
 *
 *
 */
std::string test_string =
    "3-5\n"
    "10-14\n"
    "16-20\n"
    "12-18\n"
    "\n"
    "1\n"
    "5\n"
    "8\n"
    "11\n"
    "17\n"
    "32;\n";

using fresh_range_t  = std::pair<size_t, size_t>;
using fresh_ranges_t = std::vector<fresh_range_t>;
using availables_t   = std::vector<size_t>;

struct database_t
{
    fresh_ranges_t fresh_ranges;
    availables_t availables;
};

database_t read_database(std::istream& is)
{
    database_t result;
    std::string line;
    while (std::getline(is, line))
    {
        if (line.size() == 0)
        {
            break;
        }
        fresh_range_t range;
        std::sscanf(line.c_str(), "%zu-%zu", &range.first, &range.second);
        result.fresh_ranges.push_back(std::move(range));
    }
    while (std::getline(is, line))
    {
        size_t available;
        std::sscanf(line.c_str(), "%zu", &available);
        result.availables.push_back(available);
    }
    return result;
}

bool is_within_range(size_t available, const fresh_range_t& range)
{
    if (available >= range.first && available <= range.second)
    {
        return true;
    }
    return false;
}

size_t count_fresh(const database_t& database)
{
    size_t result = 0;
    for (auto&& available : database.availables)
    {
        for (auto&& range : database.fresh_ranges)
        {
            if (is_within_range(available, range))
            {
                ++result;
                break;
            }
        }
    }
    return result;
}

int main()
{
    std::string input_path(PROJEUL_AOC_PATH "/05_input.txt");
    std::ifstream ifs(input_path);
    if (!ifs)
        throw std::runtime_error(std::string("Error reading input file: ").append(input_path));

    std::istringstream iss(test_string);

    auto data   = read_database(ifs);
    auto result = count_fresh(data);

    std::cout << "result: " << result << std::endl;

    std::cout << "hello" << std::endl;

    return 0;
}
