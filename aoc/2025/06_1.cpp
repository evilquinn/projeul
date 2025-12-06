
#include <algorithm>
#include <aoc/path_def.hpp>
#include <format>
#include <fstream>
#include <iostream>
#include <sstream>

#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/trim_all.hpp>
#include <map>
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
    "123 328  51 64\n"
    " 45 64  387 23\n"
    "  6 98  215 314\n"
    "*   +   *   +\n";

struct sum_t
{
    std::vector<size_t> nums;
    char op;
    size_t calc() const
    {
        switch (op)
        {
        case '+':
            return add();
        case '*':
            return mult();
        default:
            throw std::runtime_error("unrecognised op");
        }
    }
    size_t add() const
    {
        size_t result = 0;
        for (auto&& num : nums)
        {
            result += num;
        }
        return result;
    }
    size_t mult() const
    {
        size_t result = 1;
        for (auto&& num : nums)
        {
            result *= num;
        }
        return result;
    }
};

using sums_t = std::vector<sum_t>;

sums_t read_sums(std::istream& is)
{
    sums_t result;
    std::string line;
    while (std::getline(is, line))
    {
        std::vector<std::string> line_nums;
        boost::algorithm::trim_all(line);
        boost::algorithm::split(line_nums, line, boost::is_any_of(" \n"), boost::token_compress_on);
        if (line_nums.size() == 0)
            throw std::runtime_error("empty line?");
        if (result.size() < line_nums.size())
        {
            result.resize(line_nums.size());
        }
        if (boost::is_any_of("+*")(line_nums.front().front()))
        {
            for (size_t i = 0; i < line_nums.size(); ++i)
            {
                result[i].op = line_nums[i].front();
            }
        }
        else
        {
            for (size_t i = 0; i < line_nums.size(); ++i)
            {
                size_t num = 0;
                std::sscanf(line_nums[i].c_str(), "%zu", &num);
                result[i].nums.push_back(num);
            }
        }
    }
    return result;
}

size_t count_sums(const sums_t& sums) {
    size_t result = 0;
    for (auto&& sum : sums)
    {
        result += sum.calc();
    }
    return result;
}

int main()
{
    std::string input_path(PROJEUL_AOC_PATH "/06_input.txt");
    std::ifstream ifs(input_path);
    if (!ifs)
        throw std::runtime_error(std::string("Error reading input file: ").append(input_path));

    std::istringstream iss(test_string);

    auto data = read_sums(ifs);
    size_t result = count_sums(data);

    std::cout << "result: " << result << std::endl;

    std::cout << "hello" << std::endl;

    return 0;
}
