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
#include <array>

class solution {
public:
    static bool is_palindrome(const char* s, size_t l)
    {
        return std::equal(s, s + l/2, std::reverse_iterator<const char*>(s+l));
    }
    static std::string longest_palindromic_substring(std::string s)
    {
        // ===============
        //  = = = = = = = 
        // =================
        //  = = = = = = = =
        size_t max_length = 0;
        size_t pos_max = 0;
        for ( size_t i = 0; i < ( s.size() * 2 ) + 1; ++i )
        {
            size_t curr_max = 0;
            bool no_point = i & 0x1;
            for ( size_t j = i - 1; j < i; --j )
            {
                size_t idist = i - j;
                if ( no_point || s[(i-idist)/2] == s[(i+idist)/2] )
                {
                    no_point = !(no_point);
                    curr_max = idist;
                }
                else
                {
                    break;
                }
            }
            if ( curr_max > max_length )
            {
                max_length = curr_max;
                pos_max = i;
            }
        }
        return s.substr(pos_max/2 - max_length/2, max_length+1/2);
    }
};

int main()
{
    std::vector<std::pair<std::string, std::string> > ins =
    {
        { "hello", "ll" },
        { "bye", "b" },
        { "jimym", "mym" },
        { "booboo", "ooboo" },
        { "eirujsdlkdvnsokc", "e" },
        { " ", " " },
        { "", "" },
        { "abcabcbb", "bcb" },
        { "bbbbb", "bbbbb" },
        { "pwwkew", "ww" },
        { "dvdf", "dvd" },
        { "aabaab!bb", "aabaa" },
        { "abba", "abba" },
        { "ababa", "ababa" }
    };
    for ( auto&& in : ins )
    {
        auto result = solution::longest_palindromic_substring(in.first);
        std::cout << in.first << ": " << result << std::endl;
        if ( result != in.second )
        {
            throw std::runtime_error("Failed to determine correct result, in: " + in.first +
                                     ", expected: " + in.second + ", got: " + result);
        }
    }
    return 0;
}
