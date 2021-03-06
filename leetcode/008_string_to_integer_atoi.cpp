/*
 * Implement atoi which converts a string to an integer.
 *
 * The function first discards as many whitespace characters as necessary until the first non-whitespace
 * character is found. Then, starting from this character, takes an optional initial plus or minus sign
 * followed by as many numerical digits as possible, and interprets them as a numerical value.
 *
 * The string can contain additional characters after those that form the integral number, which are ignored
 * and have no effect on the behavior of this function.
 *
 * If the first sequence of non-whitespace characters in str is not a valid integral number, or if no such
 * sequence exists because either str is empty or it contains only whitespace characters, no conversion is performed.
 *
 * If no valid conversion could be performed, a zero value is returned.
 *
 * Note:
 *
 * Only the space character ' ' is considered as whitespace character.
 * Assume we are dealing with an environment which could only store integers within the 32-bit signed integer range:
 * [−2^31,  2^31 − 1]. If the numerical value is out of the range of representable values, INT_MAX (2^31 − 1) or
 * INT_MIN (−2^31) is returned.
 *
 * Example 1:
 * Input: "42"
 * Output: 42
 *
 * Example 2:
 * Input: "   -42"
 * Output: -42
 * Explanation: The first non-whitespace character is '-', which is the minus sign.
 *              Then take as many numerical digits as possible, which gets 42.
 *
 * Example 3:
 * Input: "4193 with words"
 * Output: 4193
 * Explanation: Conversion stops at digit '3' as the next character is not a numerical digit.
 *
 * Example 4:
 * Input: "words and 987"
 * Output: 0
 * Explanation: The first non-whitespace character is 'w', which is not a numerical 
 *              digit or a +/- sign. Therefore no valid conversion could be performed.
 *
 * Example 5:
 * Input: "-91283472332"
 * Output: -2147483648
 * Explanation: The number "-91283472332" is out of the range of a 32-bit signed integer.
 *              Thefore INT_MIN (−231) is returned.
 */
#include <iostream>
#include <vector>
#include <boost/lexical_cast.hpp>

class solution {
public:
    static int myAtoi(std::string str)
    {
        // eat spaces
        auto start = str.begin();
        for ( ; *start == ' '; ++start );
        // negative?
        int sign_mult = ( *start == '-' ? -1 : 1 );
        // eat sign
        if ( sign_mult < 0 || *start == '+' )
        {
            ++start;
        }
        // determine limits
        int limit = std::numeric_limits<int>::max();
        int digl = 7;
        std::function<bool(int, int)> cmp = std::bind(std::greater<int>(), std::placeholders::_1, std::placeholders::_2);
        if ( sign_mult < 0 )
        {
            limit = std::numeric_limits<int>::min();
            digl = -8;
            cmp = std::bind(std::less<int>(), std::placeholders::_1, std::placeholders::_2);
        }
        int max_before = ( limit / 10 );
        int result = 0;
        for ( ; start != str.end() && std::isdigit(*start); ++start )
        {
            int dig = ( *start - '0' ) * sign_mult;
            if ( cmp(result, max_before) || ( result == max_before && cmp(dig, digl) ) ) return limit;
            result *= 10;
            result += dig;
        }
        return result;
    }
};

int main()
{
    std::vector<std::pair<std::string, int> > data = {
        { "123", 123 },
        { "-123", -123 },
        { "120", 120 },
        { "1534236469", 1534236469 },
        { "-2147483412", -2147483412 },
        { "1563847412", 1563847412 },
        { "-1563847412", -1563847412 },
        { "42", 42 },
        { "    -42", -42 },
        { "4193 with words", 4193 },
        { "words and 987", 0 },
        { "-91283472332", -2147483648 },
        { "2147483648", 2147483647 },
        { "2147483646", 2147483646 }
    };
    for ( auto&& datum : data )
    {
        int res = solution::myAtoi(datum.first);
        std::cout << datum.first << " -> " << res << " : " << ( res == datum.second ? "OK" : "FAIL" ) << "\n";
    }
    return 0;
}
