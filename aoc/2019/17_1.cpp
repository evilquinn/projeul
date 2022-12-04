/*
 * https://adventofcode.com/2019/day/17
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <iterator>
#include <map>

#include <boost/bind/bind.hpp>

#include <aoc/path_def.hpp>
#include <aoc/computer.hpp>
#include <aoc/map.hpp>
#include <aoc/coord.hpp>

class tracker
{
public:
    std::map<coord_util::coord, char> map;
    tracker(){}
    void track(size_t val)
    {
        if ( val == '\n' )
        {
            pos_.x = 0;
            ++pos_.y;
        }
        else
        {
            map[pos_] = static_cast<map_util::value_type>(val);
            ++pos_.x;
        }
    }
    computer::take_output_cb tracker_hook()
    {
        return boost::bind(&tracker::track, this, boost::placeholders::_1);
    }
private:
    coord_util::coord pos_;
};
std::ostream& operator<< (std::ostream& os, const tracker& tracker)
{
    if ( !os || tracker.map.empty()) return os;
    coord_util::coord map_boundary = tracker.map.rbegin()->first + coord_util::coord{ 1, 1 };
    coord_util::coord_incrementer incr = { map_boundary.x };
    std::string eol;
    for ( coord_util::coord c; coord_util::within_limit(c, map_boundary); incr(c) )
    {
        if ( c.x == 0 ) os << eol;
        eol = "\n";
        os << tracker.map.at(c);
    }
    return os;
}

void print_as_char(size_t val)
{
    std::cout << static_cast<char>(val);
}

static const std::string mr = "A,B,A,C,B,C,A,C,B,C\n";
static const std::string a = "L,8,R,10,L,10\n";
static const std::string b = "R,10,L,8,L,8,L,10\n";
static const std::string c = "L,4,L,6,L,8,L,8\n";
static const std::string v = "n\n";

static const std::string all_moves = mr + a + b + c + v;

class robot
{
public:
    robot(const std::string& source) :
        martin_(),
        comp_(input_hook(),
              print_as_char),
        exe_( { comp_.compile(source) } )
    {}
    void run()
    {
        comp_.run(exe_);
        std::cout << martin_ << std::endl;
    }
    size_t sum_align_params()
    {
        coord_util::coord bound = martin_.map.rbegin()->first;
        size_t result = 0;
        for ( auto&& elem : martin_.map )
        {
            if ( elem.second != '#' ) continue;
            if ( elem.first.x == 0       || martin_.map.at(coord_util::coord{elem.first.x - 1, elem.first.y }) != '#' ) continue;
            if ( elem.first.x == bound.x || martin_.map.at(coord_util::coord{elem.first.x + 1, elem.first.y }) != '#' ) continue;
            if ( elem.first.y == 0       || martin_.map.at(coord_util::coord{elem.first.x, elem.first.y - 1 }) != '#' ) continue;
            if ( elem.first.y == bound.y || martin_.map.at(coord_util::coord{elem.first.x, elem.first.y + 1 }) != '#' ) continue;
            result += ( elem.first.x * elem.first.y );
        }
        return result;
    }
    computer::size_type input_move()
    {
        auto tmp = move_pos_++;
        std::cout << "sending: " << all_moves.at(tmp) << std::endl;
        if ( move_pos_ == all_moves.size() ) comp_.set_output_cb(computer::send_to_stdout);
        return static_cast<computer::size_type>(all_moves.at(tmp));
    }
    computer::get_input_cb input_hook()
    {
        return boost::bind(&robot::input_move, this);
    }
private:
    tracker martin_;
    computer comp_;
    computer::executable exe_;
    size_t move_pos_;
};

int main()
{
    std::ifstream inf(PROJEUL_AOC_PATH "/17_input.txt");
    std::string source((std::istream_iterator<char>(inf)), std::istream_iterator<char>());

#if 0
    robot robby(source);
    robby.run();
    size_t result = robby.sum_align_params();
    std::cout << "sum_align_params: " << result << std::endl;
#endif

    source[0] = '2'; // hack the code
    robot ghost(source);
    ghost.run();
    return 0;
}
