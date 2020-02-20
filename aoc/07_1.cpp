/**
 *
 * Here are some example programs:
 *
 * Max thruster signal 43210 (from phase setting sequence 4,3,2,1,0):
 *
 * 3,15,3,16,1002,16,10,16,1,16,15,15,4,15,99,0,0
 * Max thruster signal 54321 (from phase setting sequence 0,1,2,3,4):
 *
 * 3,23,3,24,1002,24,10,24,1002,23,-1,23,
 * 101,5,23,23,1,24,23,23,4,23,99,0,0
 * Max thruster signal 65210 (from phase setting sequence 1,0,4,3,2):
 *
 * 3,31,3,32,1002,32,10,32,1001,31,-2,31,1007,31,0,33,
 * 1002,33,7,33,1,33,31,31,1,32,31,31,4,31,99,0,0,0
 *
 * Try every combination of phase settings on the amplifiers. What is the highest signal that can be sent to the thrusters?
 *
 */


#include <iostream>
#include <vector>
#include <functional>
#include <algorithm>
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>

const std::string super_source =
"3,225,1,225,6,6,1100,1,238,225,104,0,2,218,57,224,101,"
"-3828,224,224,4,224,102,8,223,223,1001,224,2,224,1,223,"
"224,223,1102,26,25,224,1001,224,-650,224,4,224,1002,223,"
"8,223,101,7,224,224,1,223,224,223,1102,44,37,225,1102,51,"
"26,225,1102,70,94,225,1002,188,7,224,1001,224,-70,224,4,"
"224,1002,223,8,223,1001,224,1,224,1,223,224,223,1101,86,"
"70,225,1101,80,25,224,101,-105,224,224,4,224,102,8,223,"
"223,101,1,224,224,1,224,223,223,101,6,91,224,1001,224,"
"-92,224,4,224,102,8,223,223,101,6,224,224,1,224,223,223,"
"1102,61,60,225,1001,139,81,224,101,-142,224,224,4,224,102,"
"8,223,223,101,1,224,224,1,223,224,223,102,40,65,224,1001,"
"224,-2800,224,4,224,1002,223,8,223,1001,224,3,224,1,224,"
"223,223,1102,72,10,225,1101,71,21,225,1,62,192,224,1001,"
"224,-47,224,4,224,1002,223,8,223,101,7,224,224,1,224,223,"
"223,1101,76,87,225,4,223,99,0,0,0,677,0,0,0,0,0,0,0,0,0,0,"
"0,1105,0,99999,1105,227,247,1105,1,99999,1005,227,99999,"
"1005,0,256,1105,1,99999,1106,227,99999,1106,0,265,1105,1,"
"99999,1006,0,99999,1006,227,274,1105,1,99999,1105,1,280,"
"1105,1,99999,1,225,225,225,1101,294,0,0,105,1,0,1105,1,"
"99999,1106,0,300,1105,1,99999,1,225,225,225,1101,314,0,0,"
"106,0,0,1105,1,99999,108,226,677,224,102,2,223,223,1005,"
"224,329,1001,223,1,223,1107,677,226,224,102,2,223,223,1006,"
"224,344,1001,223,1,223,7,226,677,224,1002,223,2,223,1005,"
"224,359,101,1,223,223,1007,226,226,224,102,2,223,223,1005,"
"224,374,101,1,223,223,108,677,677,224,102,2,223,223,1006,"
"224,389,1001,223,1,223,107,677,226,224,102,2,223,223,1006,"
"224,404,101,1,223,223,1108,677,226,224,102,2,223,223,1006,"
"224,419,1001,223,1,223,1107,677,677,224,1002,223,2,223,1006,"
"224,434,101,1,223,223,1007,677,677,224,102,2,223,223,1006,"
"224,449,1001,223,1,223,1108,226,677,224,1002,223,2,223,1006,"
"224,464,101,1,223,223,7,677,226,224,102,2,223,223,1006,224,"
"479,101,1,223,223,1008,226,226,224,102,2,223,223,1006,224,"
"494,101,1,223,223,1008,226,677,224,1002,223,2,223,1005,224,"
"509,1001,223,1,223,1007,677,226,224,102,2,223,223,1005,224,"
"524,1001,223,1,223,8,226,226,224,102,2,223,223,1006,224,539,"
"101,1,223,223,1108,226,226,224,1002,223,2,223,1006,224,554,"
"101,1,223,223,107,226,226,224,1002,223,2,223,1005,224,569,"
"1001,223,1,223,7,226,226,224,102,2,223,223,1005,224,584,101,"
"1,223,223,1008,677,677,224,1002,223,2,223,1006,224,599,1001,"
"223,1,223,8,226,677,224,1002,223,2,223,1006,224,614,1001,223,"
"1,223,108,226,226,224,1002,223,2,223,1006,224,629,101,1,223,"
"223,107,677,677,224,102,2,223,223,1005,224,644,1001,223,1,223,"
"8,677,226,224,1002,223,2,223,1005,224,659,1001,223,1,223,1107,"
"226,677,224,102,2,223,223,1005,224,674,1001,223,1,223,4,223,99,226";

using program = std::vector<int>;
program to_program(const std::string& in)
{
    program result;
    std::vector<std::string> tokens;
    boost::algorithm::split(tokens, in, boost::is_any_of(", "));
    std::transform(tokens.begin(), tokens.end(), std::back_inserter(result), boost::lexical_cast<int, std::string> );
    return result;

}

std::ostream& operator<<(std::ostream& os, const program& prog)
{
    std::string sep = "";
    for ( auto&& token : prog )
    {
        os << sep << token;
        sep = ",";
    }
    return os;
}
namespace op
{
    enum type
    {
        sum = 1,
        mult = 2,
        in = 3,
        out = 4,
        jit = 5,
        jif = 6,
        lt = 7,
        eq = 8,
        stop = 99
    };
}

std::vector<int> get_argices(const program& prog, int ptr, int num_args)
{
    std::vector<int> argices(num_args, ptr);
    for( int param_modes = prog[ptr]/100, pos = 1;
         pos < (int)argices.size(); ++pos, param_modes /= 10 )
    {
        argices[pos] = param_modes % 10 ? ptr+pos : prog[ptr+pos];
    }
    return argices;
}

int do_input(program& prog, int ptr)
{
    const int num_args = 2;
    prog[prog[ptr+1]] = 5;
    return ptr + num_args;
}

int do_output(program& prog, int ptr)
{
    const int num_args = 2;
    auto args = get_argices(prog, ptr, num_args);
    //if ( lop > 0 ) throw std::runtime_error("unexpected output: " + boost::lexical_cast<std::string>(lop));
    std::cout << prog[args[1]] << "\n";
    return ptr + num_args;
}

int do_sum(program& prog, int ptr)
{
    const int num_args = 4;
    auto args = get_argices(prog, ptr, num_args);
    prog[args[3]] = prog[args[1]] + prog[args[2]];
    return ptr + num_args;
}

int do_mult(program& prog, int ptr)
{
    const int num_args = 4;
    auto args = get_argices(prog, ptr, num_args);
    prog[args[3]] = prog[args[1]] * prog[args[2]];
    return ptr + num_args;
}

int do_stop(program& prog, int)
{
    return prog.size();
}

int jump_if_true(program& prog, int ptr)
{
    const int num_args = 3;
    auto args = get_argices(prog, ptr, num_args);
    if ( prog[args[1]] != 0 ) return prog[args[2]];
    return ptr + num_args;
}

int jump_if_false(program& prog, int ptr)
{
    const int num_args = 3;
    auto args = get_argices(prog, ptr, num_args);
    if ( prog[args[1]] == 0 ) return prog[args[2]];
    return ptr + num_args;
}

int less_than(program& prog, int ptr)
{
    const int num_args = 4;
    auto args = get_argices(prog, ptr, num_args);
    prog[args[3]] = prog[args[1]] < prog[args[2]] ? 1 : 0;
    return ptr + num_args;
}

int equals(program& prog, int ptr)
{
    const int num_args = 4;
    auto args = get_argices(prog, ptr, num_args);
    prog[args[3]] = prog[args[1]] == prog[args[2]] ? 1 : 0;
    return ptr + num_args;
}

int run_instruction(program& prog, int ptr)
{
    int op = prog[ptr] % 100;
    if ( op == op::sum ) return do_sum(prog, ptr);
    else if ( op == op::mult ) return do_mult(prog, ptr);
    else if ( op == op::stop ) return do_stop(prog, ptr);
    else if ( op == op::in ) return do_input(prog, ptr);
    else if ( op == op::out ) return do_output(prog, ptr);
    else if ( op == op::jit ) return jump_if_true(prog, ptr);
    else if ( op == op::jif ) return jump_if_false(prog, ptr);
    else if ( op == op::lt ) return less_than(prog, ptr);
    else if ( op == op::eq ) return equals(prog, ptr);

    throw std::runtime_error("unknown instruction: " + boost::lexical_cast<std::string>(op));
}
void run(program& prog)
{
    for ( int op_idx = 0;
          op_idx < (int)prog.size();
          op_idx = run_instruction(prog, op_idx) );
}

int main()
{
    std::vector<std::pair<program, program> > data = {
        { to_program("3,21,1008,21,8,20,1005,20,22,107,8,21,20,1006,20,31,1106,0,36,98,0,0,1002,21,"
                     "125,20,4,20,1105,1,46,104,999,1105,1,46,1101,1000,1,20,4,20,1105,1,46,98,99"), to_program("2,0,0,0,99") }
    };

    for ( auto&& datum : data )
    {
        std::cout << "Run [ " << datum.first << " ], ";
        run(datum.first);
    }

    auto super_prog = to_program(super_source);
    std::cout << "running: " << "\n";
    run(super_prog);

    std::cout << super_prog[0] << "\n";

    return 0;
}
