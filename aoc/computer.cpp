/**
 *
 *
 */

#include "computer.hpp"

#include <iostream>
#include <vector>
#include <functional>
#include <algorithm>
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>

computer::computer() :
    input_cb_(get_from_stdin),
    output_cb_(send_to_stdout)
{
}
computer::computer(get_input_cb input_cb,
                   take_output_cb output_cb) :
    input_cb_(input_cb),
    output_cb_(output_cb)
{
}
bool computer::run(executable& exe) const
{
    while ( !exe.paused && !exe.finished() )
    {
        int next = run_instruction(exe.prog, exe.ptr);
        if ( !exe.paused ) exe.ptr = next;
    }
    return exe.finished();
}

computer::program computer::compile(const source& src)
{
    program prog;
    std::vector<std::string> tokens;
    boost::algorithm::split(tokens, src, boost::is_any_of(", "));

    try
    {
        std::transform(tokens.begin(), tokens.end(), std::back_inserter(prog), boost::lexical_cast<int, std::string> );
    }
    catch ( const std::exception& ex )
    {
        std::cout << "failed to compile: " << ex.what() << "\n";
        std::cout << "last compiled operands: ";
        for ( size_t i = prog.size() - 5; i < prog.size(); ++i )
        {
            std::cout << prog[i] << ", ";
        }
        std::cout << ";\n";
    }
    return prog;
}

std::vector<int> computer::get_arg_indices(const program& prog, int ptr, int num_args) const
{
    std::vector<int> argices(num_args, ptr);
    for( int param_modes = prog[ptr]/100, pos = 1;
        pos < (int)argices.size(); ++pos, param_modes /= 10 )
    {
        argices[pos] = param_modes % 10 ? ptr+pos : prog[ptr+pos];
    }
    return argices;
}

int computer::get_from_stdin()
{
    std::cout << "next intput: ";
    std::string in_val;
    std::cin >> in_val;
    try
    {
        return boost::lexical_cast<int>(in_val);
    }
    catch(const std::exception& e)
    {
        std::cout << "Failed to parse input value: " << in_val << '\n';
        return 0;
    }
}
void computer::send_to_stdout(int n)
{
    std::cout << "output: " << n << "\n";
}

int computer::do_input(program& prog, int ptr) const
{
    const int num_args = 2;
    prog[prog[ptr+1]] = input_cb_();
    return ptr + num_args;
}

int computer::do_output(program& prog, int ptr) const
{
    const int num_args = 2;
    auto args = get_arg_indices(prog, ptr, num_args);
    //if ( lop > 0 ) throw std::runtime_error("unexpected output: " + boost::lexical_cast<std::string>(lop));
    output_cb_(prog[args[1]]);
    return ptr + num_args;
}

int computer::do_sum(program& prog, int ptr) const
{
    const int num_args = 4;
    auto args = get_arg_indices(prog, ptr, num_args);
    prog[args[3]] = prog[args[1]] + prog[args[2]];
    return ptr + num_args;
}

int computer::do_mult(program& prog, int ptr) const
{
    const int num_args = 4;
    auto args = get_arg_indices(prog, ptr, num_args);
    prog[args[3]] = prog[args[1]] * prog[args[2]];
    return ptr + num_args;
}

int computer::do_stop(program& prog, int) const
{
    return prog.size();
}

int computer::jump_if_true(program& prog, int ptr) const
{
    const int num_args = 3;
    auto args = get_arg_indices(prog, ptr, num_args);
    if ( prog[args[1]] != 0 ) return prog[args[2]];
    return ptr + num_args;
}

int computer::jump_if_false(program& prog, int ptr) const
{
    const int num_args = 3;
    auto args = get_arg_indices(prog, ptr, num_args);
    if ( prog[args[1]] == 0 ) return prog[args[2]];
    return ptr + num_args;
}

int computer::less_than(program& prog, int ptr) const
{
    const int num_args = 4;
    auto args = get_arg_indices(prog, ptr, num_args);
    prog[args[3]] = prog[args[1]] < prog[args[2]] ? 1 : 0;
    return ptr + num_args;
}

int computer::equals(program& prog, int ptr) const
{
    const int num_args = 4;
    auto args = get_arg_indices(prog, ptr, num_args);
    prog[args[3]] = prog[args[1]] == prog[args[2]] ? 1 : 0;
    return ptr + num_args;
}

int computer::run_instruction(program& prog, int ptr) const
{
    computer::op op = static_cast<computer::op>(prog[ptr] % 100);
    if ( op == op::sum ) return do_sum(prog, ptr);
    else if ( op == op::mult ) return do_mult(prog, ptr);
    else if ( op == op::stop ) return do_stop(prog, ptr);
    else if ( op == op::in ) return do_input(prog, ptr);
    else if ( op == op::out ) return do_output(prog, ptr);
    else if ( op == op::jit ) return jump_if_true(prog, ptr);
    else if ( op == op::jif ) return jump_if_false(prog, ptr);
    else if ( op == op::lt ) return less_than(prog, ptr);
    else if ( op == op::eq ) return equals(prog, ptr);

    throw std::runtime_error("unknown instruction: " + boost::lexical_cast<std::string>(static_cast<int>(op)));
}

std::ostream& operator<<(std::ostream& os, const computer::program& prog)
{
    std::string sep = "";
    for ( auto&& token : prog )
    {
        os << sep << token;
        sep = ",";
    }
    return os;
}
