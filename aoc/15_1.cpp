/**
 * https://adventofcode.com/2019/day/15
 *
 **/

#include <iostream>
#include <fstream>
#include <sstream>
#include <iterator>
#include <vector>
#include <memory>

#include <aoc/computer.hpp>
#include <aoc/coord.hpp>
#include <aoc/map.hpp>
#include <set>
#include <map>

#include "path_def.hpp"


using coord_util::coord;

namespace
{

static const int stop = 0;
static const int north = 1;
static const int south = 2;
static const int west = 3;
static const int east = 4;

int reverse_dir(int direction)
{
    switch(direction)
    {
    case north : return south;
    case south : return north;
    case west  : return east;
    case east  : return west;
    default    : throw  std::runtime_error(std::string("unexpected direction: "));
    }
}

enum move_status
{
    origin = -1,
    wall   = 0,
    moved  = 1,
    goal   = 2
};

struct node
{
    size_t value = 0;
    node* parent = nullptr;
    int pointing = north;
    std::unordered_map<int, std::unique_ptr<node> > paths = { };
    node* move_forward()
    {
        paths[pointing] = std::make_unique<node>( node{ value+1, this, pointing == south ? south : north } );
        return paths[pointing].get();
    }
    int rotate()
    {
        ++pointing;
        if ( parent && pointing == reverse_dir(parent->pointing) )
        {
            ++pointing;
        }
        return pointing;
    }
};

class node_walker
{
public:
    node_walker() :
        root_(std::make_unique<node>()),
        curr_(root_.get()),
        retreating_(false),
        goal_value_(0)
    {}
    int next_direction(computer::size_type last_status)
    {
        switch(last_status)
        {
        case wall :
        {
            if ( retreating_ ) throw std::runtime_error("unexpected wall while retreating...");

            // rotate, return;
            curr_->rotate();
            if ( curr_->pointing > east )
            {
                // exhausted path, retreat
                if ( ! curr_->parent )
                {
                    // we're done
                    return stop;
                }
                retreating_ = true;
                return reverse_dir(curr_->parent->pointing);
            }
            return curr_->pointing;
        }
        case goal :
        {
            // return final answer;
            if ( goal_value_ == 0 )
            {
                goal_value_ = curr_->value + 1;
            }
            [[fallthrough]];
        }
        case moved :
        {
            if ( retreating_ )
            {
                // made it back to parent, where next?
                // rotate, return;
                curr_ = curr_->parent;
                curr_->rotate();
                if ( curr_->pointing > east )
                {
                    // exhausted path, keep retreating
                    if ( ! curr_->parent )
                    {
                        // retreated all the way back, we're done
                        return stop;
                    }
                    return reverse_dir(curr_->parent->pointing);
                }
                retreating_ = false;
                return curr_->pointing;
            }
            // update paths, iters, return dir of new node;
            curr_ = curr_->move_forward();
            return curr_->pointing;
        }
        case origin :
        {
            // just go
            return curr_->pointing;
        }
        default :
        {
            throw std::runtime_error(std::string("unexpected status: "));
        }
        }
    }
    computer::size_type goal_value() const
    {
        return goal_value_;
    }
private:
    std::unique_ptr<node> root_;
    node*                 curr_;
    bool                  retreating_;
    computer::size_type   goal_value_;
};

}


class robot_remote
{
public:
    robot_remote(const std::string& source) :
        comp_(std::bind(&robot_remote::movement_command, this),
              std::bind(&robot_remote::report_status, this, std::placeholders::_1)),
        exe_( { computer::compile(source) } ),
        path_finder_(),
        last_status_(origin)
    {}
    void run()
    {
        comp_.run(exe_);
    }
    computer::size_type find_distance_to_goal()
    {
        run();
        return path_finder_.goal_value();
    }
private:
    computer::size_type movement_command()
    {
        computer::size_type next_dir = path_finder_.next_direction(last_status_);
        std::cout << "next command: " << next_dir << "\n";
        return next_dir;
    }
    void report_status(computer::size_type value)
    {
        std::cout << "status: " << value << "\n";
        last_status_ = value;
    }

    computer comp_;
    computer::executable exe_;

    node_walker path_finder_;
    computer::size_type last_status_;
};

int main()
{
    std::vector<std::string> data = {
        ""
    };

    std::ifstream ifs(PROJEUL_AOC_PATH "/15_input.txt");
    std::string source = std::string(std::istream_iterator<char>(ifs), std::istream_iterator<char>());
    robot_remote rob(source);
    size_t result = rob.find_distance_to_goal();
    std::cout << "result: " << result << "\n";

    return 0;
}
