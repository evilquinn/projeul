/*
 * https://adventofcode.com/2020/day/6
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <boost/dynamic_bitset.hpp>
#include <boost/optional.hpp>

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

typedef std::vector<instruction> instructions_type;
instructions_type parse_instructions(std::istream& is)
{
    instructions_type result;
    for ( instruction ins; is >> ins; )
    {
        result.emplace_back(std::move(ins));
    }
    return result;
}

class processor
{
public:
    processor(instructions_type ins) :
        instructions_(ins),
        used_(instructions_.size(), false),
        idx_(0),
        accumulator_(0)
    {}
    bool process()
    {
        while ( idx_ < instructions_.size() && process_one() )
        {
        }
        return idx_ == instructions_.size();
    }
    ptrdiff_t accumulator() const
    {
        return accumulator_;
    }
    bool process_one()
    {
        //std::cout << ins_list_.size() << ", " << idx_ << ", " << instructions_[idx_] << std::endl;
        if ( idx_ == instructions_.size() ) return true;
        if ( idx_ > instructions_.size() ) throw std::runtime_error("idx_ > instructions_.size()");
        if ( used_[idx_] ) { return false; }
        used_[idx_] = true;
        ins_list_.push_back(idx_);
        switch(instructions_[idx_].operation)
        {
        case jmp : idx_ += instructions_[idx_].arg; break;
        case acc : accumulator_ += instructions_[idx_].arg; ++idx_; break;
        case nop : ++idx_; break;
        default  : throw std::runtime_error("unexpected instruction operation");
        }
        return true;
    }
    void reset()
    {
        accumulator_ = 0;
        idx_ = 0;
        used_.reset();
        ins_list_.clear();
    }
    bool special_hack()
    {
        if ( process() )
        {
            std::cout << "we won! accumed: " << accumulator_ << "\n";
            return true;
        }

        std::vector<size_t> fix_cands;
        for ( auto&& ins : ins_list_ )
        {
            if ( instructions_[ins].operation != acc ) fix_cands.push_back(ins);
        }
        for ( auto&& cand : fix_cands )
        {
            reset();
            if ( instructions_[cand].operation == nop ) instructions_[cand].operation = jmp;
            else instructions_[cand].operation = nop;
            if ( process() )
            {
                std::cout << "we won! accumed: " << accumulator_ << "\n";
                return true;
            }
            if ( instructions_[cand].operation == nop ) instructions_[cand].operation = jmp;
            else instructions_[cand].operation = nop;
        }
        return false;
    }
private:
    instructions_type instructions_;
    std::vector<size_t> ins_list_;
    boost::dynamic_bitset<> used_;
    size_t idx_;
    ptrdiff_t accumulator_;
};

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
    }
    return 0;
#endif
    std::ifstream inf(PROJEUL_AOC_PATH "/08_input.txt");
    instructions_type instructions;
    for ( instruction ins; inf >> ins; )
    {
        instructions.emplace_back(std::move(ins));
    }
    processor poker(std::move(instructions));
    auto completed = poker.special_hack();
    auto accumed = poker.accumulator();
    std::cout << "accumed: " << accumed << ", completed: " << completed << std::endl;
    return 0;
}
