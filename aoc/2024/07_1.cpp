
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/multiprecision/cpp_int.hpp>
#include <fstream>
#include <functional>
#include <iostream>
#include <queue>
#include <sstream>
#include <vector>
#include "../path_def.hpp"

std::string test_string =
    "190: 10 19\n"
    "3267: 81 40 27\n"
    "83: 17 5\n"
    "156: 15 6\n"
    "7290: 6 8 6 15\n"
    "161011: 16 10 13\n"
    "192: 17 8 14\n"
    "21037: 9 7 18 13\n"
    "292: 11 6 16 20\n";

typedef long long operand_type;
typedef long long result_type;
typedef std::vector<operand_type> operands_type;
typedef std::pair<result_type, operands_type> equation_type;
typedef std::vector<equation_type> equations_type;
std::ostream& operator<<(std::ostream& os, const operands_type& operands)
{
    os << "[";
    std::string sep = " ";
    for (auto&& operand : operands)
    {
        os << sep << operand;
        sep = ", ";
    }
    return os << " ]";
}
std::ostream& operator<<(std::ostream& os, const equation_type& equation)
{
    return os << "{ " << equation.first << ": " << equation.second << " }";
}
std::ostream& operator<<(std::ostream& os, const equations_type& equations)
{
    os << "{";
    std::string sep = " ";
    for (auto&& equation : equations)
    {
        os << sep << equation;
        sep = ", ";
    }
    return os << " }";
}

equations_type read_equations(std::istream& is)
{
    equations_type result;
    std::string line;
    while (std::getline(is, line))
    {
        equation_type equation;
        std::vector<std::string> toks;
        boost::split(toks,
                     line,
                     boost::is_any_of(": "),
                     boost::algorithm::token_compress_on);
        if (toks.size() < 3)
            throw std::runtime_error("unexpected equation");
        equation.first = boost::lexical_cast<result_type>(toks[0]);
        for (auto operand = std::next(toks.begin()); operand != toks.end();
             ++operand)
        {
            equation.second.push_back(
                boost::lexical_cast<operand_type>(*operand));
        }
        result.push_back(std::move(equation));
    }
    return result;
}

struct concatter
{
    result_type operator()(const result_type& lhs, const result_type& rhs) const
    {
        // bleugh, performance later
        std::stringstream cat;
        cat << lhs << rhs;
        return boost::lexical_cast<result_type>(cat.str());
    }
};
typedef std::function<result_type(const result_type&, const result_type&)>
    operation_type;
const std::vector<operation_type> operations = {
    std::plus<result_type>{},
    std::multiplies<result_type>{},
    concatter{}
};
bool is_solvable(const equation_type& equation)
{
    struct save_state
    {
        result_type acc;
        size_t next_i;
    };
    std::queue<save_state> work;
    work.emplace(equation.second[0], 1);
    while (work.size() > 0)
    {
        auto next = work.front();
        work.pop();
        for (auto&& operation : operations)
        {
            auto cand = operation(next.acc, equation.second[next.next_i]);
            if (next.next_i == equation.second.size() - 1)
            {
                if (cand == equation.first)
                {
                    return true;  // found at least one solution
                }
            }
            else if (cand <= equation.first)
            {
                // queue more work
                work.emplace(cand, next.next_i + 1);
            }
        }
    }
    return false;
}

result_type total_calibration(const equations_type& equations)
{
    result_type result = 0;
    for (auto&& equation : equations)
    {
        if (is_solvable(equation))
        {
            result += equation.first;
        }
    }
    return result;
}

int main()
{
    std::string input_path(PROJEUL_AOC_PATH "/07_input.txt");
    std::ifstream input_stream(input_path);
    if (!input_stream)
        throw std::runtime_error(
            std::string("Error reading input file: ").append(input_path));
    auto equations = read_equations(input_stream);

    std::stringstream test_input(test_string);
    auto test_equations = read_equations(test_input);

    auto result = total_calibration(equations);
    std::cout << "Part 1 result: " << result << std::endl;

    return 0;
}
