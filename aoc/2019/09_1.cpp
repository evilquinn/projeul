/**
 *
 *
 */


#include <iostream>
#include <fstream>
#include <vector>
#include <functional>
#include <algorithm>
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>

#include "../computer.hpp"

#include "../path_def.hpp"



int main()
{

#if 1

/**
 * Here are some example programs that use these features:
 *
 * 109,1,204,-1,1001,100,1,100,1008,100,16,101,1006,101,0,99 takes no input and produces a copy of itself as output.
 *
 * 1102,34915192,34915192,7,4,7,99,0 should output a 16-digit number.
 *
 * 104,1125899906842624,99 should output the large number in the middle.
 *
 **/

    std::vector<std::string> data = {
//        "109,1,204,-1,1001,100,1,100,1008,100,16,101,1006,101,0,99",
//        "1102,34915192,34915192,7,4,7,99,0",
//        "104,1125899906842624,99",
        "109,45,203,-17,99"
    };

    for ( auto&& datum : data )
    {
        computer::executable exe = { computer::compile(datum) };
        computer runner;
        auto result = runner.run(exe);
        std::cout << "result: " << result << "\n";
    }

#endif

    std::ifstream ifs(PROJEUL_AOC_PATH "/09_input.txt");
    std::string super_data;
    ifs >> super_data;
    computer::executable exe = { computer::compile(super_data) };
    computer runner;
    runner.run(exe);

#if 0
    std::vector<std::pair<std::string, std::vector<int> > > data = {
        // Max thruster signal 139629729 (from phase setting sequence 9,8,7,6,5):
        { "3,26,1001,26,-4,26,3,27,1002,27,2,27,1,27,26,27,4,27,1001,28,-1,28,1005,28,6,99,0,0,5", { 9, 8, 7, 6, 5 } },
        // Max thruster signal 18216 (from phase setting sequence 9,7,8,5,6):
        { "3,52,1001,52,-5,52,3,53,1,52,56,54,1007,54,5,55,1005,55,26,1001,54,-5,54,1105,1,12,1,"
          "53,54,53,1008,54,0,55,1001,55,1,55,2,53,55,53,4,53,1001,56,-1,56,1005,56,6,99,0,0,0,0,10", { 9, 7, 8, 5, 6 } },
    };

    for ( auto&& datum : data )
    {
        std::cout << "Run [ " << datum.first << " ]\n";
        amplifier ampy(5, datum.first);
        int result = ampy.run(datum.second);
        std::cout << "result: " << result << "\n";
    }

    std::vector<std::pair<std::string, std::vector<int> > > data = {
// Max thruster signal 43210 (from phase setting sequence 4,3,2,1,0):
        { "3,15,3,16,1002,16,10,16,1,16,15,15,4,15,99,0,0", { 4, 3, 2, 1, 0 } },
// Max thruster signal 54321 (from phase setting sequence 0,1,2,3,4):
        { "3,23,3,24,1002,24,10,24,1002,23,-1,23,101,5,23,23,1,24,23,23,4,23,99,0,0", { 0, 1, 2, 3, 4 } },
// Max thruster signal 65210 (from phase setting sequence 1,0,4,3,2):
        { "3,31,3,32,1002,32,10,32,1001,31,-2,31,1007,31,0,33,1002,33,7,33,1,33,31,31,1,32,31,31,4,31,99,0,0,0", { 1, 0, 4, 3, 2 } }
    };

    for ( auto&& datum : data )
    {
        std::cout << "Run [ " << datum.first << " ]\n";
        amplifier ampy(5, datum.first);
        int result = ampy.run(datum.second);
        std::cout << "result: " << result << "\n";
    }


#endif

#if 0
    std::vector<int> super_guess = { 5, 6, 7, 8, 9 };
    std::vector<int> winner_guess;
    int winner = 0;

    do
    {
        amplifier amp2(super_guess.size(), super_source);
        auto result = amp2.run(super_guess);
        if ( result > winner )
        {
            winner = result;
            winner_guess = super_guess;
        }

    } while ( std::next_permutation(super_guess.begin(), super_guess.end() ) );

    std::cout << "result: " << winner << ", " << winner_guess << "\n";
#endif


    return 0;
}
