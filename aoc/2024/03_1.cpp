
#include <boost/lexical_cast.hpp>
#include <fstream>
#include <iostream>
#include <regex>
#include "../path_def.hpp"

std::string test_string =
    "xmul(2,4)%&mul[3,7]!@^do_not_mul(5,5)+mul(32,64]then(mul(11,8)mul(8,5))";
std::regex pattern{ "do\\(\\)|don't\\(\\)|mul\\((\\d{1,3}),(\\d{1,3})\\)" };

size_t sum_ops(std::istream& input)
{
    size_t result = 0;
    std::string line;
    bool enabled = true;
    while (std::getline(input, line))
    {
        std::smatch matches;
        while (std::regex_search(line, matches, pattern))
        {
            if (matches[0] == "do()")
            {
                enabled = true;
            }
            else if(matches[0] == "don't()")
            {
                enabled = false;
            }
            else if(enabled)
            {
                result += boost::lexical_cast<size_t>(matches[1]) *
                          boost::lexical_cast<size_t>(matches[2]);
            }

            line = matches.suffix();
        }
    }
    return result;
}

int main()
{
    std::string input_path(PROJEUL_AOC_PATH "/03_input.txt");
    std::ifstream input(input_path);
    if (!input)
        throw std::runtime_error(
            std::string("Error reading input file: ").append(input_path));

    auto result = sum_ops(input);
    std::cout << "Part 1 result: " << result << std::endl;
    return 0;
}
