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
    static bool is_palindrome(const char* s, size_t length)
    {
        if ( !length ) return false;
        for ( size_t i = 0; i < length/2; ++i )
        {
            if ( s[i] != s[(length-1)-i] )
            {
                return false;
            }
        }
        return true;
    }
    static std::string longest_palindromic_substring(std::string s)
    {
        // sliding shrinking window
        for ( size_t l = s.size(); l <= s.size(); --l )
        {
            for ( size_t i = 0; i + l <= s.size(); ++i )
            {
                if ( is_palindrome(s.data()+i, l) ) return std::string(s.data()+i, l);
            }
        }
        return std::string(s.data(), 1);
    }
};

int main()
{
    std::vector<std::string> ins =
    {
        "hello", "bye", "jimym", "booboo", "eirujsdlkdvnsokc", " ", "",
        "abcabcbb", "bbbbb", "pwwkew", "dvdf", "aabaab!bb", "abba", "ababa"
    };
    for ( auto&& in : ins )
    {
        auto result = solution::longest_palindromic_substring(in);
        std::cout << in << ": " << result << std::endl;
    }
    return 0;
}
