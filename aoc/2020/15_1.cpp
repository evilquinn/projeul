/*
 * https://adventofcode.com/2020/day/15
 */

#include <iostream>
#include <map>
#include <vector>
#include <algorithm>

#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>

typedef std::vector<size_t> start_numbers_type;

class game
{
public:
    game(const std::string& input) :
        start_numbers_(start_numbers_from_string(input))
    {
    }

    start_numbers_type start_numbers_from_string(const std::string& str)
    {
        start_numbers_type result;
        std::vector<std::string> toks;
        boost::split(toks, str, boost::is_any_of(","));
        for ( auto&& tok : toks )
        {
            result.push_back(boost::lexical_cast<size_t>(tok));
        }
        std::reverse(result.begin(), result.end());
        return result;
    }

    size_t game_term(size_t n)
    {
        size_t result = 0;
        size_t last_result = 0;
        for ( size_t i = 0; i < n; ++i )
        {
            last_result = result;
            if ( start_numbers_.size() > 0 )
            {
                result = start_numbers_.back();
                start_numbers_.pop_back();
            }
            else if ( answers_.count(last_result) == 0 )
            {
                result = 0;
            }
            else
            {
                result = i - answers_[last_result] - 1;
            }
            answers_[last_result] = i - 1;
            //std::cout << "f(" << i << ") = " << result << std::endl;
        }
        return result;
    }
private:
    start_numbers_type start_numbers_;
    std::map<size_t, size_t> answers_;
};

int main()
{
#if 1
    std::vector<std::string> data = {
        "0,3,6",
        "2,0,6,12,1,3"
    };
    for ( auto&& datum : data )
    {
        game g(datum);
        auto result = g.game_term(30000000);
        std::cout << "result: " << result << std::endl;
    }
#endif
    return 0;
}
