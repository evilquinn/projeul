/**
 *
 * The Elves have sent you some Amplifier Controller Software (your puzzle input),
 * a program that should run on your existing Intcode computer. Each amplifier will
 * need to run a copy of the program.
 *
 * When a copy of the program starts running on an amplifier, it will first use an
 * input instruction to ask the amplifier for its current phase setting (an integer from 0 to 4).
 *
 * Each phase setting is used exactly once, but the Elves can't remember which amplifier needs which phase setting.
 *
 * The program will then call another input instruction to get the amplifier's input signal,
 * compute the correct output signal, and supply it back to the amplifier with an output instruction.
 * (If the amplifier has not yet received an input signal, it waits until one arrives.)
 *
 * Here are some example programs:
 *
 * Max thruster signal 43210 (from phase setting sequence 4,3,2,1,0):
 * 3,15,3,16,1002,16,10,16,1,16,15,15,4,15,99,0,0
 *
 * Max thruster signal 54321 (from phase setting sequence 0,1,2,3,4):
 * 3,23,3,24,1002,24,10,24,1002,23,-1,23,
 * 101,5,23,23,1,24,23,23,4,23,99,0,0
 *
 * Max thruster signal 65210 (from phase setting sequence 1,0,4,3,2):
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

class computer
{
public:
    typedef std::vector<int> program;
    typedef std::string source;
    typedef std::function<int()> get_input_cb;
    typedef std::function<void(int)> take_output_cb;

    computer() :
        input_cb_(get_from_stdin),
        output_cb_(send_to_stdout)
    {
    }
    computer(get_input_cb input_cb,
             take_output_cb output_cb) :
        input_cb_(input_cb),
        output_cb_(output_cb)
    {
    }
    int run(const source& src)
    {
        return run(compile(src));
    }
    int run(program prog)
    {
        for ( size_t op_idx = 0;
              op_idx < prog.size();
              op_idx = run_instruction(prog, op_idx) );
        return ( !prog.empty() ? prog[0] : 0 );
    }

    program compile(const source& src)
    {
        program result;
        std::vector<std::string> tokens;
        boost::algorithm::split(tokens, src, boost::is_any_of(", "));

        try
        {
            std::transform(tokens.begin(), tokens.end(), std::back_inserter(result), boost::lexical_cast<int, std::string> );
        }
        catch ( const std::exception& ex )
        {
            std::cout << "failed to compile: " << ex.what() << "\n";
            std::cout << "last compiled operands: ";
            for ( size_t i = result.size() - 5; i < result.size(); ++i )
            {
                std::cout << result[i] << ", ";
            }
            std::cout << ";\n";
        }

        return result;
    }

private:
    enum class op
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

    std::vector<int> get_arg_indices(const program& prog, int ptr, int num_args)
    {
        std::vector<int> argices(num_args, ptr);
        for( int param_modes = prog[ptr]/100, pos = 1;
            pos < (int)argices.size(); ++pos, param_modes /= 10 )
        {
            argices[pos] = param_modes % 10 ? ptr+pos : prog[ptr+pos];
        }
        return argices;
    }

    static int get_from_stdin()
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
    static void send_to_stdout(int n)
    {
        std::cout << "output: " << n << "\n";
    }

    int do_input(program& prog, int ptr)
    {
        const int num_args = 2;
        prog[prog[ptr+1]] = input_cb_();
        return ptr + num_args;
    }

    int do_output(program& prog, int ptr)
    {
        const int num_args = 2;
        auto args = get_arg_indices(prog, ptr, num_args);
        //if ( lop > 0 ) throw std::runtime_error("unexpected output: " + boost::lexical_cast<std::string>(lop));
        output_cb_(prog[args[1]]);
        return ptr + num_args;
    }

    int do_sum(program& prog, int ptr)
    {
        const int num_args = 4;
        auto args = get_arg_indices(prog, ptr, num_args);
        prog[args[3]] = prog[args[1]] + prog[args[2]];
        return ptr + num_args;
    }

    int do_mult(program& prog, int ptr)
    {
        const int num_args = 4;
        auto args = get_arg_indices(prog, ptr, num_args);
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
        auto args = get_arg_indices(prog, ptr, num_args);
        if ( prog[args[1]] != 0 ) return prog[args[2]];
        return ptr + num_args;
    }

    int jump_if_false(program& prog, int ptr)
    {
        const int num_args = 3;
        auto args = get_arg_indices(prog, ptr, num_args);
        if ( prog[args[1]] == 0 ) return prog[args[2]];
        return ptr + num_args;
    }

    int less_than(program& prog, int ptr)
    {
        const int num_args = 4;
        auto args = get_arg_indices(prog, ptr, num_args);
        prog[args[3]] = prog[args[1]] < prog[args[2]] ? 1 : 0;
        return ptr + num_args;
    }

    int equals(program& prog, int ptr)
    {
        const int num_args = 4;
        auto args = get_arg_indices(prog, ptr, num_args);
        prog[args[3]] = prog[args[1]] == prog[args[2]] ? 1 : 0;
        return ptr + num_args;
    }

    int run_instruction(program& prog, int ptr)
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

    get_input_cb input_cb_;
    take_output_cb output_cb_;
};

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

class amplifier
{
public:
    amplifier(int stages, const std::string& src) :
        stages_(stages),
        value_(0),
        guess_({ 1, 2, 3, 4, 5 }),
        guess_idx_(0),
        send_guess_(false),
        runner_(std::bind(&amplifier::input_sender, this),
                std::bind(&amplifier::value_saver, this, std::placeholders::_1)),
        prog_(runner_.compile(src))
    {}

    int run_once()
    {
        return run_once(guess_);
    }
    int run_once(const std::vector<int>& guess)
    {
        reset();
        guess_ = guess;
        std::cout << "guess: " << guess_ << "\n";
        for ( int stage = 0; stage < stages_; ++stage )
        {
            std::cout << "stage " << stage << "\n";
            runner_.run(prog_);
        }
        return value_;
    }

private:

    void reset()
    {
        value_ = 0;
        guess_idx_ = 0;
        send_guess_ = false;
    }

    void value_saver(int n)
    {
        std::cout << "  output: " << n << "\n";
        value_ = n;
    }
    int input_sender()
    {
        send_guess_ = !send_guess_;
        int val = send_guess_ ? guess_[guess_idx_++] : value_;
        std::cout << "  input : " << val << "\n";
        return val;
    }

    int stages_;
    int value_;
    std::vector<int> guess_;
    int guess_idx_;
    bool send_guess_;
    computer runner_;
    computer::program prog_;
};

int main()
{

#if 0
    std::vector<std::pair<std::string, std::vector<int> > > data = {
// Max thruster signal 43210 (from phase setting sequence 4,3,2,1,0):
        { "3,15,3,16,1002,16,10,16,1,16,15,15,4,15,99,0,0", { 4, 3, 2, 1, 0 } },
// Max thruster signal 54321 (from phase setting sequence 0,1,2,3,4):
        { "3,23,3,24,1002,24,10,24,1002,23,-1,23,101,5,23,23,1,24,23,23,4,23,99,0,0", { 0, 1, 2, 3, 4 } },
// Max thruster signal 65210 (from phase setting sequence 1,0,4,3,2):
        { "3,31,3,32,1002,32,10,32,1001,31,-2,31,1007,31,0,33,1002,33,7,33,1,33,31,31,1,32,31,31,4,31,99,0,0,0", { 1, 0, 4, 3, 2 } }
    };

    computer me;
    for ( auto&& datum : data )
    {
        std::cout << "Run [ " << datum.first << " ]\n";
        amplifier ampy(5, datum.first);
        int result = ampy.run_once(datum.second);
        std::cout << "result: " << result << "\n";
    }

#endif

    std::vector<int> super_guess = { 0, 1, 2, 3, 4 };
    std::vector<int> winner_guess;
    int winner = 0;

    amplifier amp2(super_guess.size(), super_source);
    do
    {
        int result = amp2.run_once(super_guess);
        if ( result > winner )
        {
            winner = result;
            winner_guess = super_guess;
        }

    } while ( std::next_permutation(super_guess.begin(), super_guess.end() ) );

    std::cout << "result: " << winner << ", " << winner_guess << "\n";

    return 0;
}
