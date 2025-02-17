

#include <cstdio>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

#include "../coord.hpp"
#include "../path_def.hpp"

std::string test_string =
    "p=0,4 v=3,-3\n"
    "p=6,3 v=-1,-3\n"
    "p=10,3 v=-1,2\n"
    "p=2,0 v=2,-1\n"
    "p=0,0 v=1,3\n"
    "p=3,0 v=-2,-2\n"
    "p=7,6 v=-1,-3\n"
    "p=3,0 v=-1,-2\n"
    "p=9,3 v=2,3\n"
    "p=7,3 v=-1,2\n"
    "p=2,4 v=2,-3\n"
    "p=9,5 v=-3,-3\n";

using coord = coord_util::basic_coord<long>;

struct robot_type
{
    robot_type() {}
    robot_type(coord p, coord v) : pos(p), vel(v) {}
    coord pos;
    coord vel;
};

std::ostream& operator<<(std::ostream& os, const robot_type& r)
{
    return os << "{ pos: " << r.pos << ", vel: " << r.vel << " }";
}

using robot_list_type = std::vector<robot_type>;

std::ostream& operator<<(std::ostream& os, const robot_list_type& rs)
{
    os << "[";
    std::string sep = " ";
    for (auto&& r : rs)
    {
        os << sep << r;
        sep = ",\n";
    }
    return os << " ]";
}

robot_list_type read_input(std::istream& is)
{
    robot_list_type result;
    std::string line;
    while (std::getline(is, line))
    {
        result.emplace_back();
        auto& inserted = result.back();

        auto res = sscanf(
            line.c_str(), "p=%ld,%ld v=%ld,%ld", &inserted.pos.x, &inserted.pos.y, &inserted.vel.x, &inserted.vel.y);
        if (res != 4)
            throw std::runtime_error(std::string("Failed to parse coord from: ") + line);
    }
    return result;
}

void do_move(const coord& map_size, robot_type& rob)
{
    rob.pos += rob.vel;
    if (rob.pos.x < 0)
    {
        rob.pos.x += map_size.x;
    }
    else
    {
        rob.pos.x %= map_size.x;
    }
    if (rob.pos.y < 0)
    {
        rob.pos.y += map_size.y;
    }
    else
    {
        rob.pos.y %= map_size.y;
    }
}

void draw_robots(std::ostream& os, const coord& map_size, const robot_list_type& robots)
{
    std::vector<char> buffer(map_size.x * map_size.y, '.');
    for (auto&& robot : robots)
    {
        auto& cur = buffer[map_size.x * robot.pos.y + robot.pos.x];
        if (cur == '.')
        {
            cur = '1';
        }
        else
        {
            ++cur;
        }
    }
    for (size_t i = 0; i < buffer.size(); ++i)
    {
        if (i > 0 && i % map_size.x == 0)
        {
            os << "\n";
        }
        os << buffer[i];
    }
    os << std::endl;
}

void do_moves(const coord& map, robot_list_type& robots, size_t moves)
{
    static std::ofstream robout("./robout.txt");

    for (size_t i = 0; i < moves; ++i)
    {
        for (auto&& robot : robots)
        {
            do_move(map, robot);
        }
        robout << "elapsed: " << i + 1 << "s" << std::endl;
        draw_robots(robout, map, robots);
    }
}

size_t calc_safety(const coord& map, const robot_list_type& robots)
{
    auto midx = map.x / 2;
    auto midy = map.y / 2;

    size_t tl = 0;
    size_t tr = 0;
    size_t bl = 0;
    size_t br = 0;

    for (auto&& robot : robots)
    {
        if (robot.pos.x < midx)
        {
            if (robot.pos.y < midy)
            {
                ++tl;
            }
            else if (robot.pos.y > midy)
            {
                ++tr;
            }
        }
        else if (robot.pos.x > midx)
        {
            if (robot.pos.y < midy)
            {
                ++bl;
            }
            else if (robot.pos.y > midy)
            {
                ++br;
            }
        }
    }
    auto result = tl * tr * bl * br;
    if (result == 0)
        throw std::runtime_error("ZERO");
    return result;
}

int main()
{
    std::string input_path(PROJEUL_AOC_PATH "/14_input.txt");
    std::ifstream input_file(input_path);
    if (!input_file)
        throw std::runtime_error(std::string("Error reading input file: ").append(input_path));
    //    auto input = read_input(input_file);

    std::stringstream tis(test_string);
    auto test_input = read_input(tis);
    const coord test_map_size{ 11, 7 };

    auto input = read_input(input_file);
    const coord map_size{ 101, 103 };
    do_moves(map_size, input, 10000);
    auto result = calc_safety(map_size, input);

    std::cout << "Part 1 result: " << result << std::endl;

    return 0;
}
