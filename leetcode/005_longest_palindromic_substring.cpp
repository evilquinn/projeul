/*
 * Given a string s, find the longest palindromic substring in s.
 * You may assume that the maximum length of s is 1000.
 *
 * Example 1:
 *
 * Input: "babad"
 * Output: "bab"
 * Note: "aba" is also a valid answer.
 *
 * Example 2:
 *
 * Input: "cbbd"
 * Output: "bb"
 *
 */
#include <iostream>
#include <string>
#include <vector>

class solution {
public:
    static std::string longest_palindromic_substring(std::string s)
    {
        return s;
    }
};

int main()
{
    std::vector<std::string> ins =
    {
        "hello", "bye", "jimym", "booboo", "eirujsdlkdvnsokc", " ", "",
        "abcabcbb", "bbbbb", "pwwkew", "dvdf", "aabaab!bb", "abba"
    };
    for ( auto&& in : ins )
    {
        auto result = solution::longest_palindromic_substring(in);
        std::cout << in << ": " << result << std::endl;
    }
}
