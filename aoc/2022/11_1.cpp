#include <iostream>
#include <fstream>
#include <vector>
#include <deque>
#include <functional>

#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/multiprecision/cpp_int.hpp>

#include <aoc/path_def.hpp>

#define AOC_2022_11_PART_1 0


using worry_level_type = boost::multiprecision::cpp_int;
//using worry_level_type = int;

struct monkey
{
    int id; // id
    std::deque<worry_level_type> items; // list of items
    std::function<worry_level_type(worry_level_type)> operation; // operation affects worry level during inspection
    std::function<bool(worry_level_type)> test; // determines which monkey to throw to
    int true_id; // id of monkey to throw to if test is true
    int false_id; // id of monkey to throw to if test is false
    worry_level_type inspected; // number of times monkey inspects items
    static worry_level_type normaliser;
    monkey() : id(0), items(), true_id(0), false_id(0), inspected(0) {}
};

worry_level_type monkey::normaliser = 1;

std::istream& operator>>(std::istream& input, monkey& monkey)
{
    std::string line;
    // parse monkey.id
    std::getline(input, line);
    sscanf(line.c_str(), "Monkey %d:", &monkey.id);
    // parse monkey.items
    std::getline(input, line);
    std::string items_string(std::next(std::find(line.begin(), line.end(), ':'), 2), line.end());
    std::vector<std::string> item_strings;
    boost::algorithm::split(item_strings, items_string, boost::is_any_of(", "), boost::token_compress_on);
    for ( auto&& item_string : item_strings )
    {
        int item = 0;
        sscanf(item_string.c_str(), "%d", &item);
        monkey.items.push_back(item);
    }
    // parse monkey.operation (basic)
    std::getline(input, line);
    char op;
    char op_by[4];
    sscanf(line.c_str(), "  Operation: new = old %c %3s", &op, op_by);
    int op_by_val = 0;
    if ( strcmp(op_by, "old") != 0 ) { op_by_val = boost::lexical_cast<int>(op_by); }
    monkey.operation = [op, op_by_val](worry_level_type worry_level)
    {
        worry_level_type local_by_val = op_by_val;
        if ( op_by_val == 0 ) { local_by_val = worry_level; }
        worry_level_type result;
        if ( op == '+' )
        {
            result = worry_level + local_by_val;
        }
        else
        {
            result = worry_level * local_by_val;
        }
        return result;
    };
    // parse monkey.test
    std::getline(input, line);
    int div_by = 0;
    sscanf(line.c_str(), "  Test: divisible by %d", &div_by);
    monkey.test = [div_by](worry_level_type worry_level)
    {
        return worry_level % div_by == 0;
    };
    monkey::normaliser *= div_by;
    // parse monkey.true_id
    std::getline(input, line);
    sscanf(line.c_str(), "    If true: throw to monkey %d", &monkey.true_id);
    // parse monkey.false_id
    std::getline(input, line);
    sscanf(line.c_str(), "    If false: throw to monkey %d", &monkey.false_id);
    // eat empty
    std::getline(input, line);
    return input;
}

using monkeys_type = std::vector<monkey>;

void monkey_throw(monkeys_type& monkeys, monkey& from)
{
    if ( from.items.size() == 0 ) throw std::runtime_error("monkey no items!");
    auto item = from.items.front();
    auto to_id = from.test(item) ? from.true_id : from.false_id;
    if ( to_id >= static_cast<int>(monkeys.size()) ) throw std::runtime_error("unexpected to_id");
    if ( to_id == from.id ) throw std::runtime_error("can't throw to self");
    from.items.pop_front();
    monkeys[to_id].items.push_back(item);
}

void do_turn(monkeys_type& monkeys, monkey& monkey)
{
    while ( monkey.items.size() > 0 )
    {
        // inspect
        auto& item = monkey.items.front();
        item = monkey.operation(item);
        monkey.inspected++;
#if AOC_2022_11_PART_1
        // relief (part 1 only)
        item /= 3;
#else
        item %= monkey::normaliser;
#endif
        // throw
        monkey_throw(monkeys, monkey);
    }
}

void do_round(monkeys_type& monkeys)
{
    for ( auto&& monkey : monkeys )
    {
        do_turn(monkeys, monkey);
    }
}

void do_rounds(monkeys_type& monkeys, int rounds)
{
    for ( int i = 0; i < rounds; i++ )
    {
        std::cout << "doing round " << i+1 << std::endl;
        do_round(monkeys);
    }
}

monkeys_type read_monkeys(std::istream& input)
{
    monkeys_type result;
    do
    {
        monkey read_me;
        input >> read_me;
        result.push_back(read_me);
    }
    while(input && !input.eof());
    return result;
}


int main()
{
    std::ifstream input(PROJEUL_AOC_PATH "/11_input.txt");
    if ( !input ) throw std::runtime_error("Failed to open input file");

    auto monkeys = read_monkeys(input);
#if AOC_2022_11_PART_1
    // part 1
    do_rounds(monkeys, 20);
#else
    // part 2
    do_rounds(monkeys, 10000);
#endif
    auto most_inspected = monkeys_type(2);
    std::partial_sort_copy(monkeys.begin(), monkeys.end(),
                           most_inspected.begin(), most_inspected.end(),
                           [](const monkey& lhs, const monkey& rhs)
                           {
                               return lhs.inspected > rhs.inspected;
                           });
    auto result = most_inspected[0].inspected * most_inspected[1].inspected;
    std::cout << "Result: " << result << std::endl;

    return 0;
}
