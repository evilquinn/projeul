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
    static std::string longest_palindromic_substring(std::string s)
    {
        // ===============
        //  = = = = = = = 
        // =================
        //  = = = = = = = =

        std::vector<int> cache(( s.size() * 2 ) + 1 );
        int max_length = 0;
        int pos_max = 0;
        int most_right_right = -1;
        int most_right_center = 0;
        for ( int i = 0; i < (int)cache.size(); ++i )
        {
            if ( i < most_right_right )
            {
                cache[i] = std::min(cache[most_right_center - ( i - most_right_center )], most_right_right - i );
            }
            for ( bool no_point = ( i + cache[i] ) & 0x1;
                  no_point ||
                  ( i-cache[i]-1 >= 0 &&
                    i+cache[i]+1 < (int)cache.size() &&
                    s[(i-cache[i]-1)/2] == s[(i+cache[i]+1)/2] );
                  ++cache[i], no_point = !(no_point) )
            {
                // noop
            }
            if ( i + cache[i] > most_right_right )
            {
                most_right_right = i + cache[i];
                most_right_center = i;
            }
            if ( cache[i] > max_length )
            {
                max_length = cache[i];
                pos_max = i;
            }
        }
        return s.substr( ( pos_max - max_length ) / 2 , max_length);
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
        { "ababa", "ababa" },
        { "babcbabcbaccba", "abcbabcba" }
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
