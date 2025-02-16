

#include <cstdio>
#include <iostream>
#include <sstream>
#include <vector>

#include "../coord.hpp"
#include "../path_def.hpp"

std::string test_input =
    "Button A: X+94, Y+34\n"
    "Button B: X+22, Y+67\n"
    "Prize: X=8400, Y=5400\n"
    "\n"
    "Button A: X+26, Y+66\n"
    "Button B: X+67, Y+21\n"
    "Prize: X=12748, Y=12176\n"
    "\n"
    "Button A: X+17, Y+86\n"
    "Button B: X+84, Y+37\n"
    "Prize: X=7870, Y=6450\n"
    "\n"
    "Button A: X+69, Y+23\n"
    "Button B: X+27, Y+71\n"
    "Prize: X=18641, Y=10279\n";

using coord = coord_util::basic_coord<int>;

struct machine_params
{
    machine_params() {}
    machine_params(coord a, coord b, coord p) : A(a), B(b), prize(p) {}
    coord A;
    coord B;
    coord prize;
};

std::ostream& operator<<(std::ostream& os, const machine_params& p)
{
    return os << "{ A: " << p.A << ", B: " << p.B << ", prize: " << p.prize << " }";
}

using machine_params_list = std::vector<machine_params>;

std::ostream& operator<<(std::ostream& os, const machine_params_list& ps)
{
    os << "[";
    std::string sep = " ";
    for (auto&& p : ps)
    {
        os << sep << p;
        sep = ",\n";
    }
    return os << " ]";
}

machine_params_list read_input(std::istream& is)
{
    machine_params_list result;
    std::string line;
    while (std::getline(is, line))
    {
        result.emplace_back();
        std::vector<coord*> vals = { &result.back().A, &result.back().B, &result.back().prize };
        for (auto&& val : vals)
        {
            auto res = sscanf(line.c_str(), "%*[^:]: X%*1[+=]%d, Y%*1[+=]%d", &val->x, &val->y);
            if (res != 2)
                throw std::runtime_error(std::string("Failed to parse coord from: ") + line);
            std::getline(is, line);
        }
    }
    return result;
}

int token_cost(const machine_params& p)
{
    int result = 0;

    auto b3 = p.B + p.B + p.B;

    // magic

    return result;
}

int main()
{
    size_t result = 0;
    std::stringstream is(test_input);
    auto input = read_input(is);
    std::cout << "input:\n" << input << std::endl;
    std::cout << "Part 1 result: " << result << std::endl;

    return 0;
}
