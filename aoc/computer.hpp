/**
 *
 *
 */


#include <iosfwd>
#include <vector>
#include <string>
#include <functional>


class computer
{
public:
    typedef std::vector<int> program;
    typedef std::string source;
    typedef std::function<int()> get_input_cb;
    typedef std::function<void(int)> take_output_cb;
    struct executable
    {
        program prog;
        int ptr = 0;
        bool paused = false;
        bool finished() const { return ptr >= (int)prog.size(); }
    };

    computer();
    computer(get_input_cb input_cb,
             take_output_cb output_cb);

    bool run(executable& exe) const;

    static program compile(const source& src);

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

    std::vector<int> get_arg_indices(const program& prog, int ptr, int num_args) const;

    static int get_from_stdin();
    static void send_to_stdout(int n);
    int do_input(program& prog, int ptr) const;
    int do_output(program& prog, int ptr) const;
    int do_sum(program& prog, int ptr) const;
    int do_mult(program& prog, int ptr) const;
    int do_stop(program& prog, int) const;
    int jump_if_true(program& prog, int ptr) const;
    int jump_if_false(program& prog, int ptr) const;
    int less_than(program& prog, int ptr) const;
    int equals(program& prog, int ptr) const;
    int run_instruction(program& prog, int ptr) const;

    get_input_cb input_cb_;
    take_output_cb output_cb_;
};

std::ostream& operator<<(std::ostream& os, const computer::program& prog);
