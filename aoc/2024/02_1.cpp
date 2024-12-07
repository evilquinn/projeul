
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>
#include <fstream>
#include <iostream>
#include <iterator>
#include <numeric>
#include <vector>
#include "../path_def.hpp"

std::string test_string =
    "7 6 4 2 1\n"
    "1 2 7 8 9\n"
    "9 7 6 2 1\n"
    "1 3 2 4 5\n"
    "8 6 4 4 1\n"
    "1 3 6 7 9\n";

typedef std::vector<int> report_type;
std::ostream& operator<<(std::ostream& os, const report_type& report)
{
    os << "[";
    std::string sep = " ";
    for (auto&& v : report)
    {
        os << sep << v;
        sep = ", ";
    }
    return os << " ]";
}
typedef std::vector<report_type> reports_type;
std::ostream& operator<<(std::ostream& os, const reports_type& reports)
{
    os << "[";
    std::string sep = " ";
    for (auto&& report : reports)
    {
        os << sep << report;
        sep = ", ";
    }
    return os << " ]";
}

reports_type read_reports(std::istream& input)
{
    reports_type result;
    std::string line;
    while (std::getline(input, line))
    {
        result.push_back({});
        std::vector<std::string> toks;
        boost::split(toks, line, boost::is_any_of(" "));
        for (auto&& tok : toks)
        {
            result.back().push_back(boost::lexical_cast<int>(tok));
        }
    }
    return result;
}

/**
 * A report only counts as safe if both of the following are true:
 *
 *  - The levels are either all increasing or all decreasing.
 *  - Any two adjacent levels differ by at least one and at most three.
 *
 * In the example above, the reports can be found safe or unsafe by checking
 * those rules:
 *
 * 7 6 4 2 1: Safe because the levels are all decreasing by 1 or 2.
 * 1 2 7 8 9: Unsafe because 2 7 is an increase of 5.
 * 9 7 6 2 1: Unsafe because 6 2 is a decrease of 4.
 * 1 3 2 4 5: Unsafe because 1 3 is increasing but 3 2 is decreasing.
 * 8 6 4 4 1: Unsafe because 4 4 is neither an increase or a decrease.
 * 1 3 6 7 9: Safe because the levels are all increasing by 1, 2, or 3.
 * So, in this example, 2 reports are safe.
 *
 * NQ: I think adjacent_difference to generate list of differences between
 * subsequent elements, then walk that generated list to check each
 * difference's direction and magnitude...
 *
 */

bool check_is_safe(const report_type& report, int dampen)
{
    std::vector<int> diffs;
    std::adjacent_difference(
        report.begin(), report.end(), std::back_inserter(diffs));
    // is there a std algorithm that'll help with this instead of handrolling?
    // maybe a adjacent_difference again but with custom binary_op?
    // ...but I'd want binary_op to see/reference/use the acc...
    // ...maybe a transform_reduce..
    int dir = 0;
    for (auto i = 1U; i < diffs.size(); ++i)
    {
        if (dir == 0)
        {
            dir = diffs[i];
        }

        if ((dir < 0 && diffs[i] < 0) || (dir > 0 && diffs[i] > 0))
        {
            auto mag = std::abs(diffs[i]);
            if (mag == std::clamp(mag, 1, 3))
            {
                // still safe
            }
            else
            {
                if (dampen > 0)
                {
                    auto reduced_report_a = report;
                    reduced_report_a.erase(reduced_report_a.begin());
                    auto reduced_report_b = report;
                    reduced_report_b.erase(reduced_report_b.begin() + i - 1);
                    auto reduced_report_c = report;
                    reduced_report_c.erase(reduced_report_c.begin() + i);
                    --dampen;
                    return check_is_safe(reduced_report_a, dampen) ||
                           check_is_safe(reduced_report_b, dampen) ||
                           check_is_safe(reduced_report_c, dampen);
                }
                else
                    return false;
            }
        }
        else
        {
            if (dampen > 0)
            {
                auto reduced_report_a = report;
                reduced_report_a.erase(reduced_report_a.begin());
                auto reduced_report_b = report;
                reduced_report_b.erase(reduced_report_b.begin() + i - 1);
                auto reduced_report_c = report;
                reduced_report_c.erase(reduced_report_c.begin() + i);
                --dampen;
                return check_is_safe(reduced_report_a, dampen) ||
                       check_is_safe(reduced_report_b, dampen) ||
                       check_is_safe(reduced_report_c, dampen);
            }
            else
                return false;
        }
    }

    return true;
}

int count_safe_reports(const reports_type& reports, const int dampen = 0)
{
    int result = 0;
    for (auto&& report : reports)
    {
        if (check_is_safe(report, dampen))
        {
            ++result;
        }
    }
    return result;
}

int main()
{
    std::stringstream test_input(test_string);
    auto test_reports = read_reports(test_input);
    std::string input_path(PROJEUL_AOC_PATH "/02_input.txt");
    std::ifstream input(input_path);
    if (!input)
        throw std::runtime_error(
            std::string("Error reading input file: ").append(input_path));
    auto reports = read_reports(input);

    auto result = count_safe_reports(reports);
    std::cout << "Part 1 result: " << result << std::endl;
    auto result2 = count_safe_reports(reports, 1);
    std::cout << "Part 2 result: " << result2 << std::endl;
    return 0;
}
