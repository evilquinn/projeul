

#include <cstdio>
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>

#include <boost/multiprecision/cpp_int.hpp>

#include "../coord.hpp"
#include "../path_def.hpp"

std::string test_string =
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

using longint = boost::multiprecision::cpp_int;
using coord = coord_util::basic_coord<longint>;

struct machine_params
{
    machine_params() {}
    machine_params(coord a, coord b, coord p) : a(a), b(b), p(p) {}
    coord a;
    coord b;
    coord p;
};

std::ostream& operator<<(std::ostream& os, const machine_params& p)
{
    return os << "{ a: " << p.a << ", b: " << p.b << ", p: " << p.p << " }";
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
        std::vector<coord*> vals = { &result.back().a, &result.back().b, &result.back().p };
        for (auto&& val : vals)
        {
            int x, y;
            auto res = sscanf(line.c_str(), "%*[^:]: X%*1[+=]%d, Y%*1[+=]%d", &x, &y);
            if (res != 2)
                throw std::runtime_error(std::string("Failed to parse coord from: ") + line);
            val->x = x;
            val->y = y;
            std::getline(is, line);
            if(!is || line.size() == 0 )
            {
                val->x += 10000000000000;
                val->y += 10000000000000;
            }
        }
    }
    return result;
}

longint token_cost(const machine_params& p)
{
    // 2-equations-2-unknowns, refactor then substitute
    // AXi + BXj == PX
    // AYi + BYj == PY
    // refactor by x:
    // i = (PX - BXj)/AX
    // substitute into y:
    // AY(PX - BXj)/AX + BYj = PY
    // (AY*PX - AY*BXj)/AX + BYj = PY
    // AY*PX - AY*BXj + AX*BYj = AX*PY
    // AX*BYj - AY*BXj = AX*PY - AY*PX
    // (AX*BY - AY*BX)j = (AX*PY - AY*PX)
    // j = (AX*PY - AY*PX)/(AX*BY - AY*BX) *** j in terms of known values, go! ***
    // i = (PX - BXj) / AX                 *** i in terms of known values, go! ***
    // phew!

    auto j = (p.a.x * p.p.y - p.a.y * p.p.x) / (p.a.x * p.b.y - p.a.y * p.b.x);
    auto i = (p.p.x - p.b.x * j) / p.a.x;

    // and check
    if ((p.a.x * i + p.b.x * j != p.p.x) || ((p.a.y * i + p.b.y * j != p.p.y)))
    {
        return 0;
    }

    return 3 * i + j;
}

longint cost_all_prizes(const machine_params_list& ps)
{
    longint result = 0;
    for(auto&& p : ps)
    {
        result += token_cost(p);
    }
    return result;
}

int main()
{
    std::string input_path(PROJEUL_AOC_PATH "/13_input.txt");
    std::ifstream input_file(input_path);
    if (!input_file)
        throw std::runtime_error(
            std::string("Error reading input file: ").append(input_path));
    auto input = read_input(input_file);

    std::stringstream tis(test_string);
    auto test_input = read_input(tis);
    std::cout << "Part 1 result: " << cost_all_prizes(input) << std::endl;

    return 0;
}
