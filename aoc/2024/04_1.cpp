
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <vector>
#include "../coord.hpp"
#include "../path_def.hpp"

const std::string test_string =
    "MMMSXXMASM\n"
    "MSAMXMSMSA\n"
    "AMXSXMAAMM\n"
    "MSAMASMSMX\n"
    "XMASAMXAMM\n"
    "XXAMMXXAMA\n"
    "SMSMSASXSS\n"
    "SAXAMASAAA\n"
    "MAMMMXMMMM\n"
    "MXMXAXMASX\n";

using std::size_t;
const std::string needle = "XMAS";

typedef coord_util::basic_coord<int> coord;
typedef std::map<coord, char> text_type;

const std::vector<coord> directions = { { -1, -1 }, { 0, -1 }, { 1, -1 },
                                        { -1, 0 },  { 1, 0 },  { -1, 1 },
                                        { 0, 1 },   { 1, 1 } };

const std::vector<coord> corners = { { -1, -1 },
                                     { 1, -1 },
                                     { -1, 1 },
                                     { 1, 1 } };

std::ostream& operator<<(std::ostream& os, const text_type& text)
{
    const auto limit = text.empty()
                           ? coord{ 0, 0 }
                           : std::prev(text.end())->first + coord{ 1, 1 };
    auto increment   = make_incrementer(limit);
    int last_y       = 0;
    for (coord c{ 0, 0 }; within_limit(c, limit); increment(c))
    {
        if (c.y != last_y)
        {
            os << "\n";
            last_y = c.y;
        }
        os << text.at(c);
    }
    return os;
}

text_type read_text(std::istream& input)
{
    text_type result;
    int y = 0;
    std::string line;
    while (std::getline(input, line))
    {
        for (int x = 0; x < static_cast<int>(line.size()); ++x)
        {
            result[{ x, y }] = line[x];
        }
        ++y;
    }
    return result;
}

size_t count_needles(const std::string& needle, const text_type& haystack)
{
    size_t result     = 0;
    const auto origin = coord{ 0, 0 };
    const auto olimit = origin - coord{ 1, 1 };
    const auto limit  = haystack.empty()
                            ? origin
                            : std::prev(haystack.end())->first + coord{ 1, 1 };
    auto increment    = make_incrementer(limit);
    /**
     * check every coordinate in the text for the first letter of needle
     * if found, apply each direction modifier for each of the remaining
     * letters in needles, and if each letter in needle is found in any
     * direction increment the count
     */
    for (coord c = origin; within_limit(c, limit); increment(c))
    {
        if (haystack.at(c) == needle.at(0))
        {
            for (auto&& direction : directions)
            {
                coord n_c  = c;
                bool match = true;
                for (size_t i = 1; i < needle.size(); ++i)
                {
                    n_c += direction;
                    if (!within_limit(olimit, n_c) ||
                        !within_limit(n_c, limit) ||
                        haystack.at(n_c) != needle.at(i))
                    {
                        match = false;
                        break;
                    }
                }
                if (match)
                {
                    ++result;
                }
            }
        }
    }
    return result;
}

size_t count_crossed_needles(const std::string& needle,
                             const text_type& haystack)
{
    if (needle.size() != 3)
        throw std::runtime_error("Unexpect size of needle");
    size_t result     = 0;
    const auto origin = coord{ 0, 0 };
    const auto olimit = origin - coord{ 1, 1 };
    const auto limit  = haystack.empty()
                            ? origin
                            : std::prev(haystack.end())->first + coord{ 1, 1 };
    auto increment    = make_incrementer(limit);
    /**
     * check every coordinate in the text for the middle letter of needle
     * if found, examine haystack at each corner modifier and count instances
     * of first or last letters of needle.  If there's exactly 2 of each AND
     * opposite corners aren't equal, increment the count
     */
    for (coord c = origin; within_limit(c, limit); increment(c))
    {
        if (haystack.at(c) == needle.at(1))
        {
            std::map<char, int> corner_counts;
            for (auto&& corner : corners)
            {
                coord c_c = c + corner;
                if (within_limit(olimit, c_c) && within_limit(c_c, limit))
                {
                    ++corner_counts[haystack.at(c_c)];
                }
            }
            if (corner_counts[needle.at(0)] == 2 &&
                corner_counts[needle.at(2)] == 2 &&
                haystack.at(c + corners[0]) != haystack.at(c + corners[3]))
            {
                ++result;
            }
        }
    }
    return result;
}

int main()
{
    std::stringstream test_input(test_string);
    auto test_text = read_text(test_input);

    std::string input_path(PROJEUL_AOC_PATH "/04_input.txt");
    std::ifstream input(input_path);
    if (!input)
        throw std::runtime_error(
            std::string("Error reading input file: ").append(input_path));
    auto text   = read_text(input);
    auto result = count_needles(needle, text);
    std::cout << "Part 1 result: " << result << std::endl;
    auto result2 = count_crossed_needles("MAS", text);
    std::cout << "Part 2 result: " << result2 << std::endl;
    return 0;
}
