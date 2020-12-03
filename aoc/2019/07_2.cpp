/**
 *
 * Most of the amplifiers are connected as they were before; amplifier A's output is connected
 * to amplifier B's input, and so on. However, the output from amplifier E is now connected
 * into amplifier A's input. This creates the feedback loop: the signal will be sent through
 * the amplifiers many times.
 *
 * In feedback loop mode, the amplifiers need totally different phase settings: integers from
 * 5 to 9, again each used exactly once. These settings will cause the Amplifier Controller
 * Software to repeatedly take input and produce output many times before halting. Provide each
 * amplifier its phase setting at its first input instruction; all further input/output
 * instructions are for signals.
 *
 * Don't restart the Amplifier Controller Software on any amplifier during this process.
 * Each one should continue receiving and sending signals until it halts.
 *
 * All signals sent or received in this process will be between pairs of amplifiers except
 * the very first signal and the very last signal. To start the process, a 0 signal is sent
 * to amplifier A's input exactly once.
 *
 * Eventually, the software on the amplifiers will halt after they have processed the final loop.
 * When this happens, the last output signal from amplifier E is sent to the thrusters.
 * Your job is to find the largest output signal that can be sent to the thrusters using the new
 * phase settings and feedback loop arrangement.
 *
 * Here are some example programs:
 *
 * Max thruster signal 139629729 (from phase setting sequence 9,8,7,6,5):
 * 3,26,1001,26,-4,26,3,27,1002,27,2,27,1,27,26,27,4,27,1001,28,-1,28,1005,28,6,99,0,0,5
 *
 * Max thruster signal 18216 (from phase setting sequence 9,7,8,5,6):
 * 3,52,1001,52,-5,52,3,53,1,52,56,54,1007,54,5,55,1005,55,26,1001,54,
 * -5,54,1105,1,12,1,53,54,53,1008,54,0,55,1001,55,1,55,2,53,55,53,4,
 * 53,1001,56,-1,56,1005,56,6,99,0,0,0,0,10
 *
 * Try every combination of the new phase settings on the amplifier feedback loop.
 * What is the highest signal that can be sent to the thrusters?
 *
 */


#include <iostream>
#include <vector>
#include <functional>
#include <algorithm>
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>

#include "../computer.hpp"

const std::string super_source =
"3,8,1001,8,10,8,105,1,0,0,21,34,47,72,93,110,191,272,"
"353,434,99999,3,9,102,3,9,9,1001,9,3,9,4,9,99,3,9,102,"
"4,9,9,1001,9,4,9,4,9,99,3,9,101,3,9,9,1002,9,3,9,1001,"
"9,2,9,1002,9,2,9,101,4,9,9,4,9,99,3,9,1002,9,3,9,101,5,"
"9,9,102,4,9,9,1001,9,4,9,4,9,99,3,9,101,3,9,9,102,4,9,9,"
"1001,9,3,9,4,9,99,3,9,101,2,9,9,4,9,3,9,1001,9,2,9,4,9,"
"3,9,101,2,9,9,4,9,3,9,1002,9,2,9,4,9,3,9,102,2,9,9,4,9,"
"3,9,1002,9,2,9,4,9,3,9,102,2,9,9,4,9,3,9,101,1,9,9,4,9,"
"3,9,1002,9,2,9,4,9,3,9,1002,9,2,9,4,9,99,3,9,102,2,9,9,"
"4,9,3,9,1002,9,2,9,4,9,3,9,102,2,9,9,4,9,3,9,1002,9,2,9,"
"4,9,3,9,1001,9,1,9,4,9,3,9,1001,9,2,9,4,9,3,9,102,2,9,9,"
"4,9,3,9,101,1,9,9,4,9,3,9,1001,9,1,9,4,9,3,9,101,2,9,9,"
"4,9,99,3,9,1001,9,1,9,4,9,3,9,1001,9,2,9,4,9,3,9,101,2,"
"9,9,4,9,3,9,101,2,9,9,4,9,3,9,1001,9,1,9,4,9,3,9,1001,9,"
"1,9,4,9,3,9,1001,9,1,9,4,9,3,9,102,2,9,9,4,9,3,9,101,2,"
"9,9,4,9,3,9,1001,9,2,9,4,9,99,3,9,1002,9,2,9,4,9,3,9,1001,"
"9,2,9,4,9,3,9,102,2,9,9,4,9,3,9,1002,9,2,9,4,9,3,9,102,2,"
"9,9,4,9,3,9,101,2,9,9,4,9,3,9,1002,9,2,9,4,9,3,9,1001,9,"
"2,9,4,9,3,9,102,2,9,9,4,9,3,9,1002,9,2,9,4,9,99,3,9,101,"
"1,9,9,4,9,3,9,101,1,9,9,4,9,3,9,101,2,9,9,4,9,3,9,102,2,"
"9,9,4,9,3,9,1001,9,2,9,4,9,3,9,101,1,9,9,4,9,3,9,102,2,9,"
"9,4,9,3,9,1001,9,1,9,4,9,3,9,101,1,9,9,4,9,3,9,1002,9,2,"
"9,4,9,99";



class amplifier
{
public:
    amplifier(int stages, const std::string& src) :
        stages_(stages),
        stage_(0),
        runner_(std::bind(&amplifier::input_sender, this),
                std::bind(&amplifier::value_saver, this, std::placeholders::_1)),
        exe_stages_(stages, { { runner_.compile(src) } } ),
        phases_({ 1, 2, 3, 4, 5 })
    {
        // prime the first stage
        exe_stages_[0].input_ready = true;
    }

    int run(const std::vector<int>& guess)
    {
        phases_ = guess;
        while ( ! all_done() )
        {
            for ( stage_ = 0; stage_ < stages_; ++stage_ )
            {
                std::cout << "stage " << stage_ << "\n";
                runner_.run(exe_stages_[stage_].exe);
            }
        }
        return exe_stages_[stages_ - 1].value;
    }

private:

    void signal_next(int val)
    {
        int cal = ( stage_ + 1 ) % stages_;
        exe_stages_[cal].value = val;
        exe_stages_[cal].input_ready = true;
        exe_stages_[cal].exe.paused = false;
        std::cout << "stage " << stage_ << " signaling stage " << cal << " : " << val << "\n";
    }
    void value_saver(int n)
    {
        std::cout << "  output: " << n << "\n";
        exe_stages_[stage_].value = n;
        signal_next(n);
    }
    int input_sender()
    {
        if ( exe_stages_[stage_].phase_mode )
        {
            std::cout << "  phase : " << phases_[stage_] << "\n";
            exe_stages_[stage_].phase_mode = false;
            return phases_[stage_];
        }
        if ( exe_stages_[stage_].input_ready )
        {
            std::cout << "  input : " << exe_stages_[stage_].value << "\n";
            exe_stages_[stage_].input_ready = false;
            return exe_stages_[stage_].value;
        }
        std::cout << "pausing stage " << stage_ << ", waiting on input..." << "\n";
        exe_stages_[stage_].exe.paused = true;
        const int dummy = 0;
        return dummy;
    }

    bool all_done()
    {
        for ( auto&& stage : exe_stages_ )
        {
            if ( !stage.exe.finished() ) return false;
        }
        return true;
    }

    int stages_;
    int stage_;
    computer runner_;
    struct exe_stage
    {
        computer::executable exe;
        bool phase_mode = true;
        bool input_ready = false;
        int phase = 0;
        int value = 0;
    };
    std::vector<exe_stage> exe_stages_;
    std::vector<int> phases_;
};

int main()
{

#if 0
    std::string ts = "3,21,1008,21,8,20,1005,20,22,107,8,21,20,1006,20,31,"
                     "1106,0,36,98,0,0,1002,21,125,20,4,20,1105,1,46,104,999,"
                     "1105,1,46,1101,1000,1,20,4,20,1105,1,46,98,99";
    computer::executable exe = { computer::compile(ts) };
    computer runner([](){return 7;}, [](int v){std::cout << "output: " << v << "\n";});
    auto result = runner.run(exe);

#endif

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

    std::cout << "result: " << winner << "\n";


    return 0;
}
