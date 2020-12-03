/**
 * 1,0,0,0,99 becomes 2,0,0,0,99 (1 + 1 = 2).
 * 2,3,0,3,99 becomes 2,3,0,6,99 (3 * 2 = 6).
 * 2,4,4,5,99,0 becomes 2,4,4,5,99,9801 (99 * 99 = 9801).
 * 1,1,1,4,99,5,6,0,99 becomes 30,1,1,4,2,5,6,0,99.
 *
 * Once you have a working computer, the first step is to restore the gravity assist program
 * (your puzzle input) to the "1202 program alarm" state it had just before the last computer
 * caught fire. To do this, before running the program, replace position 1 with the value 12 and
 * replace position 2 with the value 2. What value is left at position 0 after the program halts?
 */


#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>

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
void run(program& prog)
{
    for ( int op_idx = 0; op_idx < (int)prog.size() && prog[op_idx] != 99; op_idx += 4 )
    {
        prog[prog[op_idx+3]] = prog[op_idx] == 1 ?
                                   prog[prog[op_idx+1]] + prog[prog[op_idx+2]] :
                                   prog[prog[op_idx+1]] * prog[prog[op_idx+2]] ;
    }
}

int check(program prog, int noun, int verb)
{
    prog[1] = noun;
    prog[2] = verb;
    run(prog);
    return prog[0];
}

int main()
{
    std::vector<std::pair<program, program> > data = {
        { to_program("1,0,0,0,99"), to_program("2,0,0,0,99") },
        { to_program("2,3,0,3,99"), to_program("2,3,0,6,99") },
        { to_program("2,4,4,5,99,0"), to_program("2,4,4,5,99,9801") },
        { to_program("1,1,1,4,99,5,6,0,99"), to_program("30,1,1,4,2,5,6,0,99") },
    };

    for ( auto&& datum : data )
    {
        std::cout << "Run [ " << datum.first << " ], ";
        run(datum.first);
        std::cout << "Out [ " << datum.first << " ] : "
                  << ( datum.first == datum.second ? "OK" : "FAIL" ) << std::endl;
    }

    const int magic = 19690720;
    const auto super_prog = to_program("1,0,0,3,1,1,2,3,1,3,4,3,1,5,0,3,2,1,10,19,2,9,19,23,1,9,23,27,2,27,9,31,1,"
                                         "31,5,35,2,35,9,39,1,39,10,43,2,43,13,47,1,47,6,51,2,51,10,55,1,9,55,59,2,6,"
                                         "59,63,1,63,6,67,1,67,10,71,1,71,10,75,2,9,75,79,1,5,79,83,2,9,83,87,1,87,9,"
                                         "91,2,91,13,95,1,95,9,99,1,99,6,103,2,103,6,107,1,107,5,111,1,13,111,115,2,"
                                         "115,6,119,1,119,5,123,1,2,123,127,1,6,127,0,99,2,14,0,0");
    for ( int i = 0; i < 100; ++i )
    {
        for ( int j = 0; j < 100; ++j )
        {
            auto result = check(super_prog, i, j);
            if ( result == magic )
            {
                std::cout << "noun: " << i << ", verb: " << j << "\n";
                std::cout << "result: " << ( 100 * i ) + j << "\n";
                break;
            }
        }
    }

    std::cout << super_prog[0] << "\n";

    return 0;
}
