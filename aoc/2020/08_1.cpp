/*
 * https://adventofcode.com/2020/day/6
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

#include <aoc/path_def.hpp>

enum op
{
    jmp,
    acc,
    nop
};
struct instruction
{
    enum op operation;
    ptrdiff_t arg;
};
std::ostream& operator<< (std::ostream& os, enum op operation)
{
    switch(operation)
    {
    case jmp : os << "jmp"; break;
    case acc : os << "acc"; break;
    case nop : os << "nop"; break;
    default  : throw 42;
    }
    return os;
}
std::istream& operator>> (std::istream& is, instruction& ins)
{
    std::string as_str;
    is >> as_str;
    if ( as_str.empty() ) return is;
    switch(as_str[0])
    {
    case 'j' : ins.operation = jmp; break;
    case 'a' : ins.operation = acc; break;
    case 'n' : ins.operation = nop; break;
    case '\n': std::cout << "huh" << std::endl; return is;
    default  : throw 42;
    }
    is >> ins.arg;
    return is;
}
std::ostream& operator<< (std::ostream& os, const instruction& ins)
{
    if ( !os ) return os;
    os << "op: " << ins.operation << ", arg: " << ins.arg;
    return os;
}

typedef std::vector<std::pair<instruction, bool> > instructions_type;
instructions_type parse_instructions(std::istream& is)
{
    instructions_type result;
    for ( instruction ins; is >> ins; )
    {
        result.emplace_back( std::pair{ std::move(ins), false } );
    }
    return result;
}
ptrdiff_t process(instructions_type& instructions)
{
    ptrdiff_t result = 0;
    if ( instructions.empty() ) return result;
    size_t idx = 0;
    size_t count = 0;
    while ( true )
    {
        std::cout << count++ << std::endl;
        if ( instructions[idx].second ) return result;
        instructions[idx].second = true;
        switch(instructions[idx].first.operation)
        {
        case jmp : idx    += instructions[idx].first.arg;        break;
        case acc : result += instructions[idx].first.arg; ++idx; break;
        case nop : ++idx;                                        break;
        default  : throw 42;
        }
    }
}

int main()
{
#if 0
    std::vector<std::string> data = {
        "nop +0\n"
        "acc +1\n"
        "jmp +4\n"
        "acc +3\n"
        "jmp -3\n"
        "acc -99\n"
        "acc +1\n"
        "jmp -4\n"
        "acc +6"
    };
    for ( auto&& datum : data )
    {
        std::istringstream iss(datum);
        auto instructions = parse_instructions(iss);
        auto res = process(instructions);
        std::cout << "res: " << res << std::endl;
    }
    return 0;
#endif
    std::ifstream inf(PROJEUL_AOC_PATH "/08_input.txt");
    std::vector<std::pair<instruction, bool> > instructions;
    for ( instruction ins; inf >> ins; )
    {
        instructions.emplace_back( std::pair{ std::move(ins), false } );
    }
    auto result = process(instructions);
    std::cout << "result: " << result << std::endl;
    return 0;
}
