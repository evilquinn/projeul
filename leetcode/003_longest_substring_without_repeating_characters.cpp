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
#include <algorithm>
#include <vector>

class solution {
public:
    static int length_of_longest_substring(std::string s)
    {
        std::vector<char> cache;
        size_t result = 0;
        std::for_each(s.begin(), s.end(), [&cache, &result](char c)
        {
            auto in_cache = std::find(cache.begin(), cache.end(), c);
            if ( in_cache != cache.end() )
            {
                result = std::max(result, cache.size());
                cache.erase(cache.begin(), ++in_cache);
            }
            cache.emplace_back(c);
            return;
        });
        result = std::max(result, cache.size());
        return result;
    }
};

int main()
{
    std::vector<std::string> ins =
    {
        "hello", "bye", "jimym", "booboo", "eirujsdlkdvnsokc", "abcabcbb", "bbbbb", "pwwkew", "dvdf", "aabaab!bb"
    };
    for ( auto&& in : ins )
    {
        int result = solution::length_of_longest_substring(in);
        std::cout << in << ": " << result << std::endl;
    }
}
