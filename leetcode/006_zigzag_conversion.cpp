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
        return s.substr(0, numRows);
    }
};

int main()
{
    std::vector<std::pair<std::string, int> > data = {
        { "PAYPALISHIRING", 3 },
        { "PAYPALISHIRING", 4 }
    };
    for ( auto&& datum : data )
    {
        std::cout << datum.first << ", " << datum.second << "\n";
    }
    return 0;
}
