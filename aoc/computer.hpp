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

    typedef size_t size_type;
    typedef std::vector<size_type> program;
    typedef std::string source;
    typedef std::function<size_type()> get_input_cb;
    typedef std::function<void(size_type)> take_output_cb;
    struct executable
    {
        program prog;
        size_type ptr = 0;
        bool paused = false;
        size_type relative_base = 0;
        bool finished() const { return ptr >= prog.size(); }
        void inc(size_type i = 1) { set(ptr + i); }
        void set(size_type v) { if ( !paused ) ptr = v; }
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
        arb = 9,
        stop = 99
    };

    std::vector<program::size_type> get_arg_indices(executable& exe, int num_args) const;

    static size_type get_from_stdin();
    static void send_to_stdout(size_type n);
    void do_input(executable& exe) const;
    void do_sum(executable& exe) const;
    void do_output(executable& exe) const;
    void do_mult(executable& exe) const;
    void do_stop(executable& exe) const;
    void jump_if_true(executable& exe) const;
    void jump_if_false(executable& exe) const;
    void less_than(executable& exe) const;
    void equals(executable& exe) const;
    void adj_rel_base(executable& exe) const;
    void run_instruction(executable& exe) const;

    get_input_cb input_cb_;
    take_output_cb output_cb_;
};

std::ostream& operator<<(std::ostream& os, const computer::program& prog);
