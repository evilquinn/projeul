
#include <iostream>
#include <fstream>
#include <deque>
#include <map>

#include <aoc/path_def.hpp>

using stack_type = std::deque<char>;
using stacks_type = std::map<int, stack_type>;

void line_to_stacks(std::string const& line, stacks_type& stacks)
{
    for ( int pos = 1; unsigned(pos) < line.size(); pos += 4 )
    {
        if ( line[pos] != ' ' ) stacks[(pos/4)+1].push_front(line[pos]);
    }
}

stacks_type parse_stacks(std::istream& input)
{
    stacks_type stacks;
    std::string line;
    while(std::getline(input, line))
    {
        if(line == "") break;
        if(int(line.size()) < 2 || line[1] == '1') continue;
        line_to_stacks(line, stacks);
    }
    return stacks;
}

void apply_move_9000(std::string const& line, stacks_type& stacks)
{
    int move = 0, from = 0, to = 0;
    std::sscanf(line.c_str(), "move %d from %d to %d", &move, &from, &to);
    for ( int i = 0; i < move; ++i )
    {
        if ( stacks[from].size() == 0 ) throw std::runtime_error("Can't move from empty stack");
        stacks[to].push_back(stacks[from].back());
        stacks[from].pop_back();
    }
}

stacks_type apply_moves_9000(std::istream& input, stacks_type stacks)
{
    std::string line;
    while(std::getline(input, line))
    {
        if(line == "") break;
        apply_move_9000(line, stacks);
    }
    return stacks;
}

void apply_move_9001(std::string const& line, stacks_type& stacks)
{
    int move = 0, from = 0, to = 0;
    std::sscanf(line.c_str(), "move %d from %d to %d", &move, &from, &to);
    if ( stacks[from].size() < unsigned(move) ) throw std::runtime_error("Not enough crates in stack to move");
    auto start_move = std::prev(stacks[from].end(), move);
    auto end_move = stacks[from].end();
    stacks[to].insert(stacks[to].end(), start_move, end_move);
    stacks[from].erase(start_move, end_move);
}

stacks_type apply_moves_9001(std::istream& input, stacks_type stacks)
{
    std::string line;
    while(std::getline(input, line))
    {
        if(line == "") break;
        apply_move_9001(line, stacks);
    }
    return stacks;
}

std::string get_tops(stacks_type const& stacks)
{
    std::string tops;
    for ( auto&& stack : stacks )
    {
        if ( stack.second.size() == 0 ) throw std::runtime_error("Can't get back from empty stack");
        tops.push_back(stack.second.back());
    }
    return tops;
}

int main()
{
    std::ifstream input(PROJEUL_AOC_PATH "/05_input.txt");
    if ( !input ) throw std::runtime_error("Failed to open input file");

    auto p1 = get_tops(apply_moves_9000(input, parse_stacks(input)));
    std::cout << "Part 1 result: " << p1 << std::endl;

    input.clear();
    input.seekg(0);
    auto p2 = get_tops(apply_moves_9001(input, parse_stacks(input)));
    std::cout << "Part 2 result: " << p2 << std::endl;

    return 0;
}
