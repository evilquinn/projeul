/*
 * Determine whether an integer is a palindrome. An integer is a palindrome when it reads the same backward as forward.
 *
 * Example 1:
 * Input: 121
 * Output: true
 *
 * Example 2:
 * Input: -121
 * Output: false
 * Explanation: From left to right, it reads -121. From right to left, it becomes 121-.
 *              Therefore it is not a palindrome.
 *
 * Example 3:
 * Input: 10
 * Output: false
 * Explanation: Reads 01 from right to left. Therefore it is not a palindrome.
 *
 * Follow up:
 * Could you solve it without converting the integer to a string?
 */
#include <iostream>
#include <vector>

class solution {
public:
    static bool is_palindrome(int x) {
        if ( x < 0 ) return false;
        if ( x < 10 ) return true;
        int comp = 0;
        while ( comp < x )
        {
            int dig = x % 10;
            x /= 10;
            if ( x == comp ) return true; // odd length win
            comp *= 10;
            comp += dig;
            if ( comp == 0 ) return false; // last digit 0 fail
            if ( x == comp ) return true; // even length win
        }
        return false;
    }
};

int main()
{
    std::vector<std::pair<int, bool> > data = {
        { 1, true },
        { 121, true },
        { -121, false },
        { 10, false },
        { 0, true },
        { 22, true }
    };
    for ( auto&& datum : data )
    {
        auto res = solution::is_palindrome(datum.first);
        std::cout << datum.first << " -> " << res << " : " << ( res == datum.second ? "OK" : "FAIL" ) << "\n";
    }
    return 0;
}
