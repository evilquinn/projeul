/*
 * The string "PAYPALISHIRING" is written in a zigzag pattern on a given number of rows like this:
 *
 * P   A   H   N
 * A P L S I I G
 * Y   I   R
 *
 * And then read line by line: "PAHNAPLSIIGYIR"
 *
 * Write the code that will take a string and make this conversion given a number of rows:
 *
 * string convert(string s, int numRows);
 *
 * Example 1:
 * Input: s = "PAYPALISHIRING", numRows = 3
 * Output: "PAHNAPLSIIGYIR"
 *
 * Example 2:
 *
 * Input: s = "PAYPALISHIRING", numRows = 4
 * Output: "PINALSIGYAHRPI"
 * Explanation:
 *
 * P     I    N
 * A   L S  I G
 * Y A   H R
 * P     I
 *
 */
#include <iostream>
#include <string>
#include <vector>

class solution {
public:
    static std::string convert(std::string s, int numRows)
    {
        auto r = std::string();
        int bound = ( numRows - 1 ) * 2;
        if ( bound == 0 ) return s;
        for ( int i = 0; i < numRows; ++i )
        {
            // i represents the index to begin each line with
            // step represents the gap to the next char
            std::pair<int, int> step = { bound - ( i * 2 ), i * 2 };
            if ( step.first <= 0 )
            {
                step.first = step.second;
            }
            else if ( step.second == 0 )
            {
                step.second = step.first;
            }
            bool first = true;
            for ( int j = i;
                  j < (int)s.size();
                  r.push_back(s[j]), j += ( first ? step.first : step.second ), first = !(first));
        }
        return r;
    }
};

int main()
{
    std::vector<std::pair<std::string, int> > data = {
        { "PAYPALISHIRING", 3 },
        { "PAYPALISHIRING", 4 },
        { "A", 1 },
        { "AB", 1 }
    };
    for ( auto&& datum : data )
    {
        std::cout << datum.first << ", " << datum.second << ": " << solution::convert(datum.first, datum.second) << "\n";
    }
    return 0;
}
