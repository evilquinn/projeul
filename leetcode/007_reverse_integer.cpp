/*
 * Given a 32-bit signed integer, reverse digits of an integer.
 *
 * Example 1:
 *
 * Input: 123
 * Output: 321
 * Example 2:
 *
 * Input: -123
 * Output: -321
 * Example 3:
 *
 * Input: 120
 * Output: 21
 * Note:
 * Assume we are dealing with an environment which could only store integers within the 32-bit signed integer range:
 * [−2^31,  2^31 − 1].
 * For the purpose of this problem, assume that your function returns 0 when the reversed integer overflows.
 *
 */
#include <iostream>
#include <vector>
#include <cmath>
#include <limits>
#include <functional>
#include <boost/bind.hpp>
#include <boost/function.hpp>

class solution {
public:
    static int reverse(int x)
    {
        int limit_modifier = -1;
        std::function<int()> limiter = std::bind(std::numeric_limits<int>::max);
        std::function<bool(int, int)> cmp = std::bind(std::greater<int>(), std::placeholders::_1, std::placeholders::_2);
        if ( x < 0 )
        {
            limiter = std::bind(std::numeric_limits<int>::min);
            cmp = std::bind(std::less<int>(), std::placeholders::_1, std::placeholders::_2);
            limit_modifier = 1;
        }
        const int max_before = ( limiter() / 10 ) + limit_modifier;
        int result = 0;
        while ( cmp(x, 0) )
        {
            int xmod = x % 10;
            if ( cmp(result, max_before+xmod) ) return 0;
            result *= 10;
            result += xmod;
            x /= 10;
        }
        return result;
    }
};

int main()
{
    std::vector<std::pair<int, int> > data = {
        { 123, 321 },
        { -123, -321 },
        { 120, 21 },
        { 1534236469, 0 },
        { -2147483412, -2143847412 },
        { 1563847412, 0 },
        { -1563847412, 0 },
    };
    for ( auto&& datum : data )
    {
        int res = solution::reverse(datum.first);
        std::cout << datum.first << " -> " << res << " : " << ( res == datum.second ? "OK" : "FAIL" ) << "\n";
    }
    return 0;
}
