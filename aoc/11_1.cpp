/**
 * On the way to Jupiter, you're pulled over by the Space Police.
 *
 * "Attention, unmarked spacecraft! You are in violation of Space Law! All spacecraft must have a clearly visible
 * registration identifier! You have 24 hours to comply or be sent to Space Jail!"
 *
 * Not wanting to be sent to Space Jail, you radio back to the Elves on Earth for help. Although it takes almost
 * three hours for their reply signal to reach you, they send instructions for how to power up the emergency hull
 * painting robot and even provide a small Intcode program (your puzzle input) that will cause it to paint your ship
 * appropriately.
 *
 * There's just one problem: you don't have an emergency hull painting robot.
 *
 * You'll need to build a new emergency hull painting robot. The robot needs to be able to move around on the grid
 * of square panels on the side of your ship, detect the color of its current panel, and paint its current panel
 * black or white. (All of the panels are currently black.)
 *
 * The Intcode program will serve as the brain of the robot. The program uses input instructions to access the
 * robot's camera: provide 0 if the robot is over a black panel or 1 if the robot is over a white panel. Then,
 * the program will output two values:
 *
 * First, it will output a value indicating the color to paint the panel the robot is over: 0 means to paint the
 * panel black, and 1 means to paint the panel white.
 * Second, it will output a value indicating the direction the robot should turn: 0 means it should turn left 90
 * degrees, and 1 means it should turn right 90 degrees.
 * After the robot turns, it should always move forward exactly one panel. The robot starts facing up.
 *
 * The robot will continue running for a while like this and halt when it is finished drawing. Do not restart
 * the Intcode computer inside the robot during this process.
 *
 * For example, suppose the robot is about to start running. Drawing black panels as ., white panels as #,
 * and the robot pointing the direction it is facing (< ^ > v), the initial state and region near the robot
 * looks like this:
 *
 * .....
 * .....
 * ..^..
 * .....
 * .....
 * The panel under the robot (not visible here because a ^ is shown instead) is also black, and so any input
 * instructions at this point should be provided 0. Suppose the robot eventually outputs 1 (paint white) and
 * then 0 (turn left). After taking these actions and moving forward one panel, the region now looks like this:
 *
 * .....
 * .....
 * .<#..
 * .....
 * .....
 * Input instructions should still be provided 0. Next, the robot might output 0 (paint black) and then 0 (turn left):
 *
 * .....
 * .....
 * ..#..
 * .v...
 * .....
 * After more outputs (1,0, 1,0):
 *
 * .....
 * .....
 * ..^..
 * .##..
 * .....
 * The robot is now back where it started, but because it is now on a white panel, input instructions should be
 * provided 1. After several more outputs (0,1, 1,0, 1,0), the area looks like this:
 *
 * .....
 * ..<#.
 * ...#.
 * .##..
 * .....
 * Before you deploy the robot, you should probably have an estimate of the area it will cover: specifically, you
 * need to know the number of panels it paints at least once, regardless of color. In the example above, the robot
 * painted 6 panels at least once. (It painted its starting panel twice, but that panel is still only counted once;
 * it also never painted the panel it ended on.)
 *
 * Build a new emergency hull painting robot and run the Intcode program on it. How many panels does it paint at
 * least once?
 *
 **/

#include <iostream>
#include <vector>

#include <aoc/computer.hpp>
#include <aoc/coord.hpp>
#include <aoc/map.hpp>
#include <set>
#include <map>


using coord_util::coord;


class robot_brain
{
public:
    robot_brain(const computer::program& prog) :
        comp_(std::bind(&robot_brain::take_picture, this),
              std::bind(&robot_brain::receive_command, this, std::placeholders::_1)),
        exe_({ prog }),
        curr_pos_( {0, 0} ),
        blocks_(),
        curr_dir_(direction::up),
        painted_(),
        painting_(false)
    {
        blocks_[curr_pos_] = 1;
    }
    size_t paint_panels()
    {
        comp_.run(exe_);
        normalise();
        to_ostream(std::cout) << "\n";
        return painted_.size();
    }

    std::ostream& to_ostream(std::ostream& os) const
    {
        coord limit = coord_bound();
        coord_util::coord_incrementer incr = { limit.x };
        size_t last_y = 0;
        for ( coord i = { 0, 0 }; within_limit(i, limit); incr(i) )
        {
            if ( i.y != last_y )
            {
                os << "\n";
                last_y = i.y;
            }
            auto covered = blocks_.find(i);
            if ( covered == blocks_.end() )
            {
                os << ' ';
            }
            else
            {
                os << ( covered->second == 1 ? '#' : ' ' );
            }
        }
        return os;
    }
    void dry_run()
    {
        take_picture();
        receive_command(1);
        receive_command(0);

        take_picture();
        receive_command(0);
        receive_command(0);

        take_picture();
        receive_command(1);
        receive_command(0);

        take_picture();
        receive_command(1);
        receive_command(0);

        take_picture();
        receive_command(0);
        receive_command(1);

        take_picture();
        receive_command(1);
        receive_command(0);

        take_picture();
        receive_command(1);
        receive_command(0);
    }
private:
    enum direction
    {
        left = '<',
        right = '>',
        up = '^',
        down = 'v'
    };
    coord coord_bound() const
    {
        coord result;
        for ( auto&& block : blocks_ )
        {
            if ( block.first.x > result.x ) result.x = block.first.x;
            if ( block.first.y > result.y ) result.y = block.first.y;
        }
        result += { 1, 1 };
        return result;
    }
    void normalise()
    {
        // normalise coord first
        coord limit = { std::numeric_limits<int>::max(), std::numeric_limits<int>::max() };
        auto it = blocks_.upper_bound(limit);
        if ( it != blocks_.end() )
        {
            coord normaliser = { 0 - it->first.x, 0 - it->first.y };
            std::map<coord, size_t> normd;
            std::transform(blocks_.begin(), blocks_.end(), std::inserter(normd, normd.begin()),
            [&normaliser](const decltype(normd)::value_type& v)
            {
                return decltype(normd)::value_type{ { v.first.x + normaliser.x, v.first.y + normaliser.y }, v.second };
            });
            std::swap(normd, blocks_);
        }
    }
    std::ostream& list_blocks(std::ostream& os)
    {
        os << "listing blocks: \n";
        for ( auto&& block : blocks_ )
        {
            os << block.first << ", " << block.second << "\n";
        }
        return os;
    }
    void move_via(computer::size_type inst)
    {
        set_direction(inst);
        move();
    }
    void move()
    {
        switch(curr_dir_)
        {
        case up : curr_pos_ = { curr_pos_.x, curr_pos_.y - 1 }; break;
        case left : curr_pos_ = { curr_pos_.x - 1, curr_pos_.y }; break;
        case down : curr_pos_ = { curr_pos_.x, curr_pos_.y + 1 }; break;
        case right : curr_pos_ = { curr_pos_.x + 1, curr_pos_.y }; break;
        default: throw std::runtime_error("unknown direction");
        } // end switch
    }
    void set_direction(computer::size_type inst)
    {
        switch(inst)
        {
        case 0 :
        {
            switch(curr_dir_)
            {
            case up : curr_dir_ = left; break;
            case left : curr_dir_ = down; break;
            case down : curr_dir_ = right; break;
            case right : curr_dir_ = up; break;
            default: throw std::runtime_error("unknown direction");
            } // end switch
            break;
        }
        case 1 :
        {
            switch(curr_dir_)
            {
            case up : curr_dir_ = right; break;
            case right : curr_dir_ = down; break;
            case down : curr_dir_ = left; break;
            case left : curr_dir_ = up; break;
            default: throw std::runtime_error("unknown direction");
            } // end switch
            break;
        }
        default:
        {
            throw std::runtime_error("unknown direction instruction: <vomit>");
        }
        } // end switch
    }
    void paint_block(computer::size_type colour)
    {
        if ( blocks_[curr_pos_] != colour )
        {
            painted_.insert(curr_pos_);
            blocks_[curr_pos_] = colour;
        }
    }
    computer::size_type take_picture()
    {
        return blocks_[curr_pos_];
    }
    void receive_command(computer::size_type val)
    {
        painting_ = ! painting_;
        if ( painting_ ) paint_block(val);
        else move_via(val);
    }
    computer comp_;
    computer::executable exe_;
    coord_util::coord curr_pos_;
    std::map<coord, computer::size_type> blocks_;
    direction curr_dir_;
    std::set<coord> painted_;
    bool painting_;
    map_util::map_type blocks2_;

};


int main()
{

    std::vector<std::string> data = {
        "3,8,1005,8,314,1106,0,11,0,0,0,104,1,104,0,3,8,1002,8,"
        "-1,10,1001,10,1,10,4,10,108,1,8,10,4,10,1002,8,1,28,2,"
        "2,16,10,1,1108,7,10,1006,0,10,1,5,14,10,3,8,102,-1,8,"
        "10,101,1,10,10,4,10,108,1,8,10,4,10,102,1,8,65,1006,0,"
        "59,2,109,1,10,1006,0,51,2,1003,12,10,3,8,102,-1,8,10,"
        "1001,10,1,10,4,10,108,1,8,10,4,10,1001,8,0,101,1006,0,"
        "34,1,1106,0,10,1,1101,17,10,3,8,102,-1,8,10,101,1,10,"
        "10,4,10,1008,8,0,10,4,10,1001,8,0,135,3,8,1002,8,-1,10,"
        "101,1,10,10,4,10,108,0,8,10,4,10,1001,8,0,156,3,8,1002,"
        "8,-1,10,101,1,10,10,4,10,108,0,8,10,4,10,1001,8,0,178,"
        "1,108,19,10,3,8,102,-1,8,10,101,1,10,10,4,10,108,0,8,10,"
        "4,10,1002,8,1,204,1,1006,17,10,3,8,102,-1,8,10,101,1,10,"
        "10,4,10,108,1,8,10,4,10,102,1,8,230,1006,0,67,1,103,11,"
        "10,1,1009,19,10,1,109,10,10,3,8,102,-1,8,10,101,1,10,10,"
        "4,10,1008,8,0,10,4,10,101,0,8,268,3,8,102,-1,8,10,101,1,"
        "10,10,4,10,1008,8,1,10,4,10,1002,8,1,290,2,108,13,10,101,"
        "1,9,9,1007,9,989,10,1005,10,15,99,109,636,104,0,104,1,"
        "21101,48210224024,0,1,21101,0,331,0,1105,1,435,21101,0,"
        "937264165644,1,21101,0,342,0,1105,1,435,3,10,104,0,104,"
        "1,3,10,104,0,104,0,3,10,104,0,104,1,3,10,104,0,104,1,3,"
        "10,104,0,104,0,3,10,104,0,104,1,21101,235354025051,0,1,"
        "21101,389,0,0,1105,1,435,21102,29166169280,1,1,21102,400,"
        "1,0,1105,1,435,3,10,104,0,104,0,3,10,104,0,104,0,21102,"
        "709475849060,1,1,21102,1,423,0,1106,0,435,21102,868498428684,"
        "1,1,21101,434,0,0,1105,1,435,99,109,2,21201,-1,0,1,21101,"
        "0,40,2,21102,1,466,3,21101,456,0,0,1105,1,499,109,-2,2105,"
        "1,0,0,1,0,0,1,109,2,3,10,204,-1,1001,461,462,477,4,0,1001,"
        "461,1,461,108,4,461,10,1006,10,493,1101,0,0,461,109,-2,2106,"
        "0,0,0,109,4,2102,1,-1,498,1207,-3,0,10,1006,10,516,21102,1,"
        "0,-3,21201,-3,0,1,21201,-2,0,2,21102,1,1,3,21102,535,1,0,"
        "1106,0,540,109,-4,2106,0,0,109,5,1207,-3,1,10,1006,10,563,"
        "2207,-4,-2,10,1006,10,563,21202,-4,1,-4,1106,0,631,21201,-4,"
        "0,1,21201,-3,-1,2,21202,-2,2,3,21101,582,0,0,1105,1,540,22102,"
        "1,1,-4,21102,1,1,-1,2207,-4,-2,10,1006,10,601,21101,0,0,-1,"
        "22202,-2,-1,-2,2107,0,-3,10,1006,10,623,22102,1,-1,1,21101,"
        "623,0,0,105,1,498,21202,-2,-1,-2,22201,-4,-2,-4,109,-5,2105,1,0"
 };

    for ( auto&& datum : data )
    {
        robot_brain rb(computer::compile(datum));
        auto result = rb.paint_panels();
        std::cout << "result: " << result << "\n";
    }

    return 0;
}
