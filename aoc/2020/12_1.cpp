/*
 * https://adventofcode.com/2020/day/12
 */

#include <iostream>
#include <fstream>
#include <sstream>

#include <boost/lexical_cast.hpp>

#include <aoc/path_def.hpp>
#include <aoc/coord.hpp>
namespace aoc = coord_util;


const char left    = 'L';
const char right   = 'R';

enum quadrant
{
    pospos = 0,
    posneg = 1,
    negpos = 2,
    negneg = 3
};
struct action
{
    char dir;
    size_t units;
};
struct action to_action(const std::string& action_string)
{
    static const std::string all_action_directions = "NSEWLRF";
    if ( action_string.empty() ) throw std::runtime_error("failed to parse action_string: empty");
    if ( all_action_directions.find(action_string.front()) == all_action_directions.npos ) throw std::runtime_error("failed to parse action_string: unexpexted action direction");
    try
    {
        size_t units = boost::lexical_cast<size_t>(action_string.data() + 1, action_string.size() - 1);
        return { action_string.front(), units };
    }
    catch ( std::exception& ex )
    {
        throw std::runtime_error("failed to parse action_string: couldn't convert units");
    }
}
std::ostream& operator<< (std::ostream& os, const struct action action)
{
    return os << "( " << action.dir << ", " << action.units << " )";
}
class ship
{
public:
    ship() :
        pos_(),
        waypoint_({ 10, -1 })
    {}
    size_t take_actions(std::istream& is)
    {
        for ( std::string action_string; std::getline(is, action_string); )
        {
            auto action = to_action(action_string);
            take_action(action);
        }
        return ::abs(pos_.x) + ::abs(pos_.y);
    }
    void take_action(const action& action)
    {
        // blah blah
        switch(action.dir)
        {
        case 'N' : move(action.dir, action.units); break;
        case 'S' : move(action.dir, action.units); break;
        case 'E' : move(action.dir, action.units); break;
        case 'W' : move(action.dir, action.units); break;
        case 'L' : turn(action.dir, action.units); break;
        case 'R' : turn(action.dir, action.units); break;
        case 'F' : forward(action.units); break;
        default  : throw std::runtime_error("take_action called with unexpected action.dir");
        }
    }
    void move(char dir, size_t units)
    {
        switch(dir)
        {
        case 'N' : waypoint_.y -= units; break;
        case 'S' : waypoint_.y += units; break;
        case 'E' : waypoint_.x += units; break;
        case 'W' : waypoint_.x -= units; break;
        default  : throw std::runtime_error("move called with unexpected direction");
        }
    }
    void turn(char side, size_t units)
    {
        if ( side != left && side != right ) throw std::runtime_error("turn called with unexpected side");
        size_t turns = units / 90;
        for ( size_t i = 0; i < turns; ++i )
        {
            turn(side);
        }
    }
    quadrant get_quadrant(const aoc::coord& c)
    {
        if ( c.x < 0 && c.y < 0 ) return negneg;
        else if ( c.x < 0 && c.y >= 0 ) return negpos;
        else if ( c.x >= 0 && c.y >= 0 ) return pospos;
        else return posneg; // ( c.x >= 0 && c.y < 0 )
    }
    void turn(char side)
    {
        if ( side != left && side != right ) throw std::runtime_error("turn called with unexpected side");
        auto prev = waypoint_;
        switch(get_quadrant(prev))
        {
        case posneg :
        {
            if ( side == left )
            {
                waypoint_.x = prev.y;
                waypoint_.y = -prev.x;
            }
            else // ( side == right )
            {
                waypoint_.x = ::abs(prev.y);
                waypoint_.y = prev.x;
            }
            break;
        }
        case negpos :
        {
            if ( side == left )
            {
                waypoint_.x = prev.y;
                waypoint_.y = ::abs(prev.x);
            }
            else // ( side == right )
            {
                waypoint_.x = -prev.y;
                waypoint_.y = prev.x;
            }
            break;
        }
        case pospos :
        {
            if ( side == left )
            {
                waypoint_.x = prev.y;
                waypoint_.y = -prev.x;
            }
            else // ( side == right )
            {
                waypoint_.x = -prev.y;
                waypoint_.y = prev.x;
            }
            break;
        }
        case negneg :
        {
            if ( side == left )
            {
                waypoint_.x = prev.y;
                waypoint_.y = ::abs(prev.x);
            }
            else // ( side == right )
            {
                waypoint_.x = ::abs(prev.y);
                waypoint_.y = prev.x;
            }
            break;
        }
        default    : throw std::runtime_error("turn called but have unexpected heading_");
        }
    }
    void forward(size_t units)
    {
        for ( size_t i = 0; i < units; ++i )
        {
            pos_ += waypoint_;
        }
    }
private:
    aoc::coord pos_;
    aoc::coord waypoint_;
};

int main()
{
#if 1
    std::vector<std::string> data = {
        "L90\n"
        "L90\n"
        "L90\n"
        "L90\n"
        "L90\n"
        "R90\n"
        "R90\n"
        "R90\n"
        "R90\n"
        "R90\n"
        "R90\n"
        "L90",
        "F10\n"
        "N3\n"
        "F7\n"
        "R90\n"
        "F11"
    };
    for ( auto&& datum : data )
    {
        std::istringstream iss(datum);
        ship boaty;
        auto result = boaty.take_actions(iss);
        std::cout << "result: " << result << std::endl;
    }
#endif
#if 1
    std::ifstream inf(PROJEUL_AOC_PATH "/12_input.txt");
    ship boaty;
    auto result = boaty.take_actions(inf);
    std::cout << "result: " << result << std::endl;
#endif
    return 0;
}
