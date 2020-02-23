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
        run_instruction(exe);
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

std::vector<int> computer::get_arg_indices(const executable& exe, int num_args) const
{
    std::vector<int> argices(num_args, exe.ptr);
    for( int param_modes = exe.prog[exe.ptr]/100, pos = 1;
        pos < (int)argices.size(); ++pos, param_modes /= 10 )
    {
        argices[pos] = param_modes % 10 ? exe.ptr+pos : exe.prog[exe.ptr+pos];
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

void computer::do_input(executable& exe) const
{
    const int num_args = 2;
    exe.prog[exe.prog[exe.ptr+1]] = input_cb_();
    exe.inc(num_args);
}

void computer::do_output(executable& exe) const
{
    const int num_args = 2;
    auto args = get_arg_indices(exe, num_args);
    //if ( lop > 0 ) throw std::runtime_error("unexpected output: " + boost::lexical_cast<std::string>(lop));
    output_cb_(exe.prog[args[1]]);
    exe.inc(num_args);
}

void computer::do_sum(executable& exe) const
{
    const int num_args = 4;
    auto args = get_arg_indices(exe, num_args);
    exe.prog[args[3]] = exe.prog[args[1]] + exe.prog[args[2]];
    exe.inc(num_args);
}

void computer::do_mult(executable& exe) const
{
    const int num_args = 4;
    auto args = get_arg_indices(exe, num_args);
    exe.prog[args[3]] = exe.prog[args[1]] * exe.prog[args[2]];
    exe.inc(num_args);
}

void computer::do_stop(executable& exe) const
{
    exe.set(exe.prog.size());
}

void computer::jump_if_true(executable& exe) const
{
    const int num_args = 3;
    auto args = get_arg_indices(exe, num_args);
    if ( exe.prog[args[1]] != 0 )
    {
        exe.set(exe.prog[args[2]]);
    }
    else
    {
        exe.inc(num_args);
    }
}

void computer::jump_if_false(executable& exe) const
{
    const int num_args = 3;
    auto args = get_arg_indices(exe, num_args);
    if ( exe.prog[args[1]] == 0 )
    {
        exe.set(exe.prog[args[2]]);
    }
    else
    {
        exe.inc(num_args);
    }
}

void computer::less_than(executable& exe) const
{
    const int num_args = 4;
    auto args = get_arg_indices(exe, num_args);
    exe.prog[args[3]] = exe.prog[args[1]] < exe.prog[args[2]] ? 1 : 0;
    exe.inc(num_args);
}

void computer::equals(executable& exe) const
{
    const int num_args = 4;
    auto args = get_arg_indices(exe, num_args);
    exe.prog[args[3]] = exe.prog[args[1]] == exe.prog[args[2]] ? 1 : 0;
    exe.inc(num_args);
}

void computer::run_instruction(executable& exe) const
{
    computer::op op = static_cast<computer::op>(exe.prog[exe.ptr] % 100);
    switch(op)
    {
    case op::sum : return do_sum(exe);
    case op::mult : return do_mult(exe);
    case op::stop : return do_stop(exe);
    case op::in : return do_input(exe);
    case op::out : return do_output(exe);
    case op::jit : return jump_if_true(exe);
    case op::jif : return jump_if_false(exe);
    case op::lt : return less_than(exe);
    case op::eq : return equals(exe);
    default: throw std::runtime_error("unknown instruction: " + boost::lexical_cast<std::string>(static_cast<int>(op)));
    } // end switch
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
