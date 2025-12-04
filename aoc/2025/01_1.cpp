
#include <aoc/path_def.hpp>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

/**
 * Initial test data
 * 3   4
 * 4   3
 * 2   5
 * 1   3
 * 3   9
 * 3   3
 *
 * part 1:
 * Count the number of times the dial is left pointing at 0 after any rotation in the sequence
 *
 *
 */

std::string test_string =
    "L68\n"
    "L30\n"
    "R48\n"
    "L5\n"
    "R60\n"
    "L55\n"
    "L1\n"
    "L99\n"
    "R14\n"
    "L82\n";

struct rotation
{
    char dir;
    int dist;
};

using rotations_type = std::vector<rotation>;

rotations_type read_input(std::istream& is)
{
    rotations_type result;
    std::string line;
    while (std::getline(is, line))
    {
        rotation rot;
        std::sscanf(line.c_str(), "%c%d", &rot.dir, &rot.dist);
        result.push_back(std::move(rot));
    }
    return result;
}

struct dial
{
    int val_;
    const int lbound_;
    const int rbound_;
    int pass_;

    dial() : val_(50), lbound_(0), rbound_(100), pass_(0) {}
    int rotate(const rotation& rot)
    {
        switch (rot.dir)
        {
        case 'L':
            return rotate_left(rot.dist);
        case 'R':
            return rotate_right(rot.dist);
        default:
            throw std::runtime_error("unrecognised direction");
        }
    }
    int rotate_left(int dist)
    {
        val_ -= dist;
        while (val_ < lbound_)
        {
            val_ = rbound_ - abs(val_);
        }
        if (val_ == 0)
            ++pass_;
        return val_;
    }
    int rotate_right(int dist)
    {
        val_ += dist;
        val_ %= rbound_;
        if (val_ == 0)
            ++pass_;
        return val_;
    }
};

int main()
{
    std::string input_path(PROJEUL_AOC_PATH "/01_input.txt");
    std::ifstream input(input_path);
    if (!input)
        throw std::runtime_error(std::string("Error reading input file: ").append(input_path));

    std::cout << "hello" << std::endl;

    //std::stringstream test_input;
    //test_input << test_string;
    //auto test_data = read_input(test_input);

    auto data = read_input(input);
    dial d;
    for (auto&& rotation : data)
    {
        d.rotate(rotation);
    }

    std::cout << "pass: " << d.pass_ << std::endl;

    return 0;
}
