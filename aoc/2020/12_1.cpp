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


const char north   = 'N';
const char south   = 'S';
const char east    = 'E';
const char west    = 'W';
const char left    = 'L';
const char right   = 'R';
const char forward = 'F';



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
        heading_(east)
    {}
    size_t take_actions(std::istream& is)
    {
        for ( std::string action_string; std::getline(is, action_string); )
        {
            auto action = to_action(action_string);
            //std::cout << "before: "; to_ostream(std::cout);
            //std::cout << " -> " << action;
            take_action(action);
            //std::cout << ", after: "; to_ostream(std::cout); std::cout << std::endl;
        }
        return pos_.x + pos_.y;
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
        case 'F' : move(heading_,   action.units); break;
        default  : throw std::runtime_error("take_action called with unexpected action.dir");
        }
    }
    void move(char dir, size_t units)
    {
        switch(dir)
        {
        case 'N' : pos_.y -= units; break;
        case 'S' : pos_.y += units; break;
        case 'E' : pos_.x += units; break;
        case 'W' : pos_.x -= units; break;
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
    void turn(char side)
    {
        if ( side != left && side != right ) throw std::runtime_error("turn called with unexpected side");
        switch(heading_)
        {
        case north : side == left ? heading_ = west  : heading_ = east;  break;
        case south : side == left ? heading_ = east  : heading_ = west;  break;
        case east  : side == left ? heading_ = north : heading_ = south; break;
        case west  : side == left ? heading_ = south : heading_ = north; break;
        default    : throw std::runtime_error("turn called but have unexpected heading_");
        }
    }
    void to_ostream(std::ostream& os)
    {
        os << "pos: " << pos_ << ", head: " << heading_;
    }
private:
    aoc::coord pos_;
    char heading_;
};

int main()
{
#if 1
    std::vector<std::string> data = {
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
