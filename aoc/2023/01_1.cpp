
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <algorithm>
#include <cctype>
#include <charconv>
#include <boost/lexical_cast.hpp>
#include <aoc/path_def.hpp>

int determine_calibration_value_for_line(std::string_view line)
{
    auto is_digit_func = [](unsigned char c){ return std::isdigit(c); };
    auto first_pos = std::find_if(line.begin(), line.end(), is_digit_func);
    if ( first_pos == line.end() ) throw std::runtime_error(std::string("Didn't find a digit in: ").append(line));
    auto last_pos = std::find_if(line.rbegin(), line.rend(), is_digit_func); // can't fail, otherwise we'd have thrown earlier
    auto cand_str = { *first_pos, *last_pos };
    auto cand_value = 0;
    auto parse_result = std::from_chars(cand_str.begin(), cand_str.end(), cand_value);
    if ( parse_result.ec != std::errc() ) throw std::runtime_error(std::string("Error parsing number from: ").append(cand_str).append(", ").append(std::make_error_code(parse_result.ec).message()));
    return cand_value;
}

int sum_calibration_values(std::istream& iss)
{

    std::string line;
    int result = 0;
    while ( std::getline(iss, line) )
    {
        result += determine_calibration_value_for_line(line);
    }
    return result;
}

void test()
{
    std::string example = "1abc2\npqr3stu8vwx\na1b2c3d4e5f\ntreb7uchet\n";
    std::istringstream iss(example);
    auto result = sum_calibration_values(iss);
    if ( result != 142 ) throw std::runtime_error(std::string("Unexpected result, expected: 142, got: ").append(boost::lexical_cast<std::string>(result)));
}

int main()
{
    std::string input_path(PROJEUL_AOC_PATH "/01_input.txt");
    std::ifstream input(input_path);
    if (!input ) throw std::runtime_error(std::string("Error reading input file: ").append(input_path));
    auto result = sum_calibration_values(input);
    std::cout << "Part 1 result: " << result << std::endl;
    return 0;
}
