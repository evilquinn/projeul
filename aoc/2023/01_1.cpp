
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <regex>
#include <algorithm>
#include <cctype>
#include <charconv>
#include <boost/lexical_cast.hpp>
#include <aoc/path_def.hpp>

int determine_calibration_value_for_line(const std::string& line)
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

int value_from_string(std::string_view str)
{
    if(str.size() == 0) throw std::runtime_error("Unexpected empty string");
    auto cand_value = 0;
    if(str.size() == 1)
    {
        auto parse_result = std::from_chars(str.begin(), str.end(), cand_value);
        if ( parse_result.ec != std::errc() ) throw std::runtime_error(std::string("Error parsing number from: ").append(str).append(", ").append(std::make_error_code(parse_result.ec).message()));
        return cand_value;
    }

    // some kind of switch instead perhaps? djb2a?
    if(str == "one")   return 1;
    if(str == "two")   return 2;
    if(str == "three") return 3;
    if(str == "four")  return 4;
    if(str == "five")  return 5;
    if(str == "six")   return 6;
    if(str == "seven") return 7;
    if(str == "eight") return 8;
    if(str == "nine")  return 9;

    throw std::runtime_error(std::string("Error parsing number from: ").append(str));
}

int determine_calibration_value_for_line_2(const std::string& line)
{
    std::string needles("one|two|three|four|five|six|seven|eight|nine|[1-9]");
    std::regex needles_regex(needles);
    std::smatch matches;
    if ( std::regex_search(line.cbegin(), line.cend(), matches, needles_regex) == false )
    {
        throw std::runtime_error(std::string("Failed to match regex: ").append(needles).append(", in: ").append(line));
    }
    auto first = matches.str(0);
    auto last = first;
    while ( std::regex_search(std::next(matches[0].first), std::cend(line), matches, needles_regex) )
    // start searching again at std::next(matches[0].first)
    // need to look immediately after the start of a previous match _just in case_
    // e.g.they do a "twone" and we need to detect "one"
    {
        last = matches.str(0);
    }

    return (value_from_string(first) * 10) + value_from_string(last);
}

int sum_calibration_values(std::istream& iss, std::function<int(const std::string&)> line_func = determine_calibration_value_for_line)
{

    std::string line;
    int result = 0;
    while ( std::getline(iss, line) )
    {
        result += line_func(line);
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

void test_2()
{
    std::string example = "two1nine\neightwothree\nabcone2threexyz\nxtwone3four\n4nineeightseven2\nzoneight234\n7pqrstsixteen";
    std::istringstream iss(example);
    auto result = sum_calibration_values(iss, determine_calibration_value_for_line_2);
    if ( result != 281 ) throw std::runtime_error(std::string("Unexpected result, expected: 281, got: ").append(boost::lexical_cast<std::string>(result)));

}

int main()
{
    //test();
    //test_2();
    std::string input_path(PROJEUL_AOC_PATH "/01_input.txt");
    std::ifstream input(input_path);
    if (!input ) throw std::runtime_error(std::string("Error reading input file: ").append(input_path));
    //std::cout << "Part 1 result: " << sum_calibration_values(input) << std::endl;
    std::cout << "Part 2 result: " << sum_calibration_values(input, determine_calibration_value_for_line_2) << std::endl;
    return 0;
}
