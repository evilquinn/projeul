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
    static bool is_match(std::string s, std::string p)
    {
        auto its = std::mismatch(s.begin(), s.end(), p.begin(), p.end());
        auto bt = its.first;
        for ( ;
              its.second != p.end();
              its = std::mismatch(its.first, s.end(), its.second, p.end()) )
        {
            if ( *its.second == '.' )
            {
                // skip a dot
                if ( its.first == s.end() )
                {
                    return false;
                }
                ++its.first;
                ++its.second;
                continue;
            }
            if ( *its.second == '*' )
            {
                // handle asterisk
                if ( its.second == p.begin() ) throw std::runtime_error("asterisk has no preceding element");
                auto match = *std::prev(its.second);
                ++its.second;
                for ( ; its.first != s.end() && ( match == '.' || match == *its.first ); ++its.first );
                bt = std::prev(its.first, std::distance(its.second, p.end()));
                continue;
            }
            if ( its.second != std::prev(p.end()) && *std::next(its.second) == '*' )
            {
                // skip a zeroable element
                std::advance(its.second, 2);
                continue;
            }
            return false;
        }
        while ( its.second != p.end() && std::next(its.second) != p.end() && *std::next(its.second) == '*' )
        {
            // skip a zeroable element
            std::advance(its.second, 2);
            continue;
        }
        // backtrack


        return its.first == s.end() && its.second == p.end();
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
        { { "aaa", "a*a" }, true },
        { { "aaaaa", "a*a" }, true },
        { { "aaaab", ".*ab" }, true },
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
