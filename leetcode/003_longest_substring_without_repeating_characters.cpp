/*
 * Given a string, find the length of the longest substring without repeating characters.
 *
 * Example 1:
 *
 * Input: "abcabcbb"
 * Output: 3
 * Explanation: The answer is "abc", with the length of 3.
 * Example 2:
 *
 * Input: "bbbbb"
 * Output: 1
 * Explanation: The answer is "b", with the length of 1.
 * Example 3:
 *
 * Input: "pwwkew"
 * Output: 3
 * Explanation: The answer is "wke", with the length of 3.
 *              Note that the answer must be a substring, "pwke" is a subsequence and not a substring.
 *
 */
#include <iostream>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>
#include <vector>

class solution {
public:
    static int length_of_longest_substring(std::string s)
    {
        std::unordered_map<char, size_t> cache;
        size_t result = 0;
        size_t curr = 0;
        size_t sidx = 0;
        for(size_t i = 0; i < s.size(); ++i)
        {
            if ( cache.find(s[i]) != cache.end() && cache[s[i]] >= sidx )
            {
                result = std::max(result, curr);
                curr = i - cache[s[i]];
                sidx = cache[s[i]] + 1;
            }
            else
            {
                ++curr;
            }
            cache[s[i]] = i;
        }
        return std::max(result, curr);
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
        int result = solution::length_of_longest_substring(in);
        std::cout << in << ": " << result << std::endl;
    }
}
