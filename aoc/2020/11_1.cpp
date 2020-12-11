/*
 * https://adventofcode.com/2020/day/10
 */

#include <iostream>
#include <fstream>
#include <map>
#include <vector>

#include <aoc/coord.hpp>
#include <aoc/path_def.hpp>

namespace aoc = coord_util;

static const aoc::coord coord_zero = {  0,  0 };
static const aoc::coord up         = {  0, -1 };
static const aoc::coord up_right   = {  1, -1 };
static const aoc::coord right      = {  1,  0 };
static const aoc::coord down_right = {  1,  1 };
static const aoc::coord down       = {  0,  1 };
static const aoc::coord down_left  = { -1,  1 };
static const aoc::coord left       = { -1,  0 };
static const aoc::coord up_left    = { -1, -1 };
static const std::vector<aoc::coord> directions = { up, up_right, right, down_right, down, down_left, left, up_left };

enum spot
{
    floor = '.',
    empty = 'L',
    occd  = '#'
};

class churner
{
public:
    churner(std::istream& is)
    {
        parse_floor_plan(is);
    }
    void parse_floor_plan(std::istream& is)
    {
        ptrdiff_t y = 0;
        for ( std::string line; std::getline(is, line); )
        {
            ptrdiff_t x = 0;
            for ( auto&& ch : line )
            {
                floor_plan_[{ x, y }] = ch;
                ++x;
            }
            x = 0;
            ++y;
        }
    }

    size_t churn()
    {
        while ( churn_one() > 0 )
        {
        }
        size_t result = 0;
        for ( auto&& position : floor_plan_ )
        {
            if ( position.second == occd )
            {
                ++result;
            }
        }
        return result;
    }

    size_t churn_one()
    {
        size_t result = 0;
        auto next = floor_plan_;
        for ( auto&& position : floor_plan_ )
        {
            if ( position.second == empty )
            {
                if ( count_adj_occd(position.first) == 0 )
                {
                    next[position.first] = occd;
                    ++result;
                }
            }
            else if ( position.second == occd )
            {
                if ( count_adj_occd(position.first) >= 5 )
                {
                    next[position.first] = empty;
                    ++result;
                }
            }
        }
        floor_plan_ = std::move(next);
        return result;
    }
    size_t count_adj_occd(aoc::coord c)
    {
        size_t result = 0;
        for ( auto&& direction : directions )
        {
            for ( auto cand = c + direction; floor_plan_.count(cand) != 0; cand += direction )
            {
                if ( floor_plan_[cand] == floor ) continue;
                if ( floor_plan_[cand] == occd ) ++result;
                break;
            }
        }
        return result;
    }
private:
    std::map<aoc::coord, char> floor_plan_;
};

int main()
{
#if 0
    std::vector<std::string> data = {
    };
    for ( auto&& datum : data )
    {
    }
#endif
#if 1
    std::ifstream inf(PROJEUL_AOC_PATH "/11_input.txt");
    churner churny(inf);
    auto result = churny.churn();
    std::cout << "result: " << result << std::endl;
#endif
    return 0;
}
