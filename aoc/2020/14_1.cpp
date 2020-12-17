/*
 * https://adventofcode.com/2020/day/13
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <vector>
#include <algorithm>

#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/regex.hpp>
#include <boost/dynamic_bitset.hpp>

#include <aoc/path_def.hpp>

enum inst_obj
{
    mask,
    mem
};
enum inst_obj inst_obj_from_string(const std::string& inst_obj)
{
    switch(inst_obj[1])
    {
    case 'a' : return mask;
    case 'e' : return mem;
    default  : throw std::runtime_error("unexpected inst_obj string");
    }
}
struct instruction
{
    enum inst_obj obj;
    size_t addr;
    size_t val;
    std::string mask_val;
    instruction() : obj(mask), addr(0), val(0), mask_val()
    {}
};
instruction parse_instruction(const std::string inst_string)
{
    instruction result;
    static const boost::regex pattern("(mem|mask)\\[?([0-9]*)\\]? = ([01X]*|[0-9]*)$");
    // capture[0] -> match!
    // capture[1] -> mem vs mask
    // capture[2] -> mem address
    // capture[3] -> value
    boost::smatch groups;
    if ( boost::regex_search(inst_string, groups, pattern) )
    {
        result.obj = inst_obj_from_string(groups[1]);
        switch(result.obj)
        {
        case mask :
        {
            result.mask_val = groups[3];
            std::reverse(result.mask_val.begin(), result.mask_val.end());
            break;
        }
        case mem  :
        {
            result.addr = boost::lexical_cast<size_t>(groups[2]);
            result.val = boost::lexical_cast<size_t>(groups[3]);
            break;
        }
        default   : throw std::runtime_error("unexpected result.obj");
        }
    }
    return result;
}
class program
{
public:
    program(std::istream& is)
    {
        parse_input(is);
    }
    void parse_input(std::istream& is)
    {
        for ( std::string line; std::getline(is, line); )
        {
            if ( line.empty() ) continue;
            instructions_.emplace_back(parse_instruction(line));
        }
    }
    void run()
    {
        for ( auto&& instruction : instructions_ )
        {
            run_instruction(instruction);
        }
    }
    void run_instruction(const instruction& instruction)
    {
        switch(instruction.obj)
        {
        case mask : mask_ = instruction.mask_val; break;
        case mem  : set(instruction.addr, instruction.val); break;
        default   : throw std::runtime_error("unexpected instruction.obj");
        }
    }
    void set(size_t addr, size_t val)
    {
        boost::dynamic_bitset<> masked(36, val);
        for( size_t i = 0; i < mask_.size(); ++i )
        {
            if ( mask_[i] == 'X' ) continue;
            masked.set(i, mask_[i] == '1' ? true : false);
        }
        mem_[addr] = masked.to_ulong();
    }
    size_t sum_values()
    {
        size_t result = 0;
        for ( auto&& addr : mem_ )
        {
            result += addr.second;
        }
        return result;
    }
private:
    std::vector<instruction> instructions_;
    std::string mask_;
    std::map<size_t, size_t> mem_;
};

int main()
{
#if 1
    std::vector<std::string> data = {
        "mask = XXXXXXXXXXXXXXXXXXXXXXXXXXXXX1XXXX0X\n"
        "mem[8] = 11\n"
        "mem[7] = 101\n"
        "mem[8] = 0"
    };
    for ( auto&& datum : data )
    {
        std::istringstream iss(datum);
        program prog(iss);
        prog.run();
        auto result = prog.sum_values();
        std::cout << "result: " << result << std::endl;
    }
#endif
#if 1
    std::ifstream inf(PROJEUL_AOC_PATH "/14_input.txt");
    program prog(inf);
    prog.run();
    auto result = prog.sum_values();
    std::cout << "result: " << result << std::endl;
#endif
    return 0;
}
