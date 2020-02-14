/*
 * Given an input string (s) and a pattern (p), implement regular expression matching with support for '.' and '*'.
 *
 * '.' Matches any single character.
 * '*' Matches zero or more of the preceding element.
 * The matching should cover the entire input string (not partial).
 *
 * Note:
 *
 * s could be empty and contains only lowercase letters a-z.
 * p could be empty and contains only lowercase letters a-z, and characters like . or *.
 *
 * Example 1:
 * Input:
 * s = "aa"
 * p = "a"
 * Output: false
 * Explanation: "a" does not match the entire string "aa".
 *
 * Example 2:
 * Input:
 * s = "aa"
 * p = "a*"
 * Output: true
 * Explanation: '*' means zero or more of the preceding element, 'a'. Therefore, by repeating 'a' once, it becomes "aa".
 *
 * Example 3:
 * Input:
 * s = "ab"
 * p = ".*"
 * Output: true
 * Explanation: ".*" means "zero or more (*) of any character (.)".
 *
 * Example 4:
 * Input:
 * s = "aab"
 * p = "c*a*b"
 * Output: true
 * Explanation: c can be repeated 0 times, a can be repeated 1 time. Therefore, it matches "aab".
 *
 * Example 5:
 * Input:
 * s = "mississippi"
 * p = "mis*is*p*."
 * Output: false
 */
#include <iostream>
#include <vector>

class solution {
public:
    static bool is_match(std::string s, std::string p) {
        return s == p;
    }
};

int main()
{
    std::vector<std::pair<std::pair<std::string, std::string>, bool> > data = {
        { { "aa", "a" }, false },
        { { "aa", "a*" }, true },
        { { "ab", ".*" }, true },
        { { "aab", "c*a*b" }, true },
        { { "mississippi", "mis*is*p*." }, false },
        { { "", "" }, true }
    };
    for ( auto&& datum : data )
    {
        auto res = solution::is_match(datum.first.first, datum.first.second);
        std::cout << "\"" << datum.first.first << "\""
                  << " x "
                  << "\"" << datum.first.second << "\""
                  << " -> " << res
                  << " : " << ( res == datum.second ? "OK" : "FAIL" ) << "\n";
    }
    return 0;
}
