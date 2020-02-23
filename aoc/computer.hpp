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
        int relative_base = 0;
        bool finished() const { return ptr >= (int)prog.size(); }
        void inc(int i = 1) { set(ptr + i); }
        void set(int v) { if ( !paused ) ptr = v; }
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
//        arb = 9,
        stop = 99
    };

    std::vector<int> get_arg_indices(const executable& exe, int num_args) const;

    static int get_from_stdin();
    static void send_to_stdout(int n);
    void do_input(executable& exe) const;
    void do_sum(executable& exe) const;
    void do_output(executable& exe) const;
    void do_mult(executable& exe) const;
    void do_stop(executable& exe) const;
    void jump_if_true(executable& exe) const;
    void jump_if_false(executable& exe) const;
    void less_than(executable& exe) const;
    void equals(executable& exe) const;
    void run_instruction(executable& exe) const;

    get_input_cb input_cb_;
    take_output_cb output_cb_;
};

std::ostream& operator<<(std::ostream& os, const computer::program& prog);
