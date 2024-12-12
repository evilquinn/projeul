
#include <algorithm>
#include <boost/lexical_cast.hpp>
#include <fstream>
#include <iostream>
#include <list>
#include <map>
#include <string_view>

std::string test_string = "125 17";

std::string control = "0";

std::string input_string = "5 62914 65 972 0 805922 6521 1639064";

typedef std::list<size_t> stones_type;
typedef std::map<size_t, size_t> cache_type;
std::ostream& operator<<(std::ostream& os, const stones_type& stones)
{
    std::string sep;
    for (auto&& stone : stones)
    {
        os << sep << stone;
        sep = " ";
    }
    return os;
}

int num_digits(size_t n)
{
    if (n < 10)
        return 1;
    if (n < 100)
        return 2;
    if (n < 1000)
        return 3;
    if (n < 10000)
        return 4;
    if (n < 100000)
        return 5;
    if (n < 1000000)
        return 6;
    if (n < 10000000)
        return 7;
    if (n < 100000000)
        return 8;
    if (n < 1000000000)
        return 9;
    if (n < 10000000000)
        return 10;
    if (n < 100000000000)
        return 11;
    if (n < 1000000000000)
        return 12;
    if (n < 10000000000000)
        return 13;
    if (n < 100000000000000)
        return 14;
    if (n < 1000000000000000)
        return 15;
    if (n < 10000000000000000)
        return 16;
    if (n < 100000000000000000)
        return 17;
    if (n < 1000000000000000000)
        return 18;
    if (n < 10000000000000000000U)
        return 19;
    throw std::runtime_error("Number too big for num_digits");
}

size_t diver(int digits)
{
    if (digits == 2)
        return 10;
    if (digits == 4)
        return 100;
    if (digits == 6)
        return 1000;
    if (digits == 8)
        return 10000;
    if (digits == 10)
        return 100000;
    if (digits == 12)
        return 1000000;
    if (digits == 14)
        return 10000000;
    if (digits == 16)
        return 100000000;
    if (digits == 18)
        return 1000000000;
    if (digits == 20)
        return 10000000000;
    throw std::runtime_error("Num digits too big for diver");
}

stones_type read_stones(std::string const& input)
{
    stones_type result;
    auto tok_begin = input.begin();
    auto tok_end   = std::find(tok_begin, input.end(), ' ');
    while (tok_begin != input.end())
    {
        result.insert(
            result.end(),
            boost::lexical_cast<int>(std::string_view{ tok_begin, tok_end }));
        tok_begin = tok_end == input.end() ? tok_end : std::next(tok_end);
        tok_end   = std::find(tok_begin, input.end(), ' ');
    }
    return result;
}

void blink(stones_type& stones)
{
    for (auto it = stones.begin(); it != stones.end(); ++it)
    {
        if (*it == 0)
            *it = 1;
        else
        {
            auto ds = num_digits(*it);
            if (ds % 2 == 0)
            {
                auto divby = diver(ds);
                auto lhs   = *it / divby;
                stones.insert(it, lhs);
                *it %= divby;
            }
            else
            {
                *it *= 2024;
            }
        }
    }
}

void blink(cache_type& stones)
{
    cache_type temp_cache;
    for (auto&& stone_cache : stones)
    {
        if (stone_cache.second == 0)
            continue;
        if (stone_cache.first == 0)
        {
            temp_cache[1] += stone_cache.second;
            stone_cache.second = 0;
        }
        else
        {
            auto ds = num_digits(stone_cache.first);
            if (ds % 2 == 0)
            {
                auto divby = diver(ds);
                auto lhs   = stone_cache.first / divby;
                auto rhs   = stone_cache.first % divby;
                temp_cache[lhs] += stone_cache.second;
                temp_cache[rhs] += stone_cache.second;
                stone_cache.second = 0;
            }
            else
            {
                temp_cache[stone_cache.first * 2024] += stone_cache.second;
                stone_cache.second = 0;
            }
        }
    }
    for (auto&& stone : temp_cache)
    {
        stones[stone.first] += stone.second;
    }
}

size_t count_stones(const stones_type& stones, size_t blinks)
{
    cache_type stones_cache;
    for (auto&& stone : stones)
    {
        ++stones_cache[stone];
    }
    for (size_t i = 0; i < blinks; ++i)
    {
        blink(stones_cache);
    }
    size_t result = 0;
    for (auto&& stone : stones_cache)
    {
        result += stone.second;
    }
    return result;
}

int main()
{
    auto test_stones = read_stones(test_string);

    auto stones = read_stones(input_string);

    size_t result = count_stones(stones, 25);
    std::cout << "Part 1 result: " << result << std::endl;

    size_t result2 = count_stones(stones, 75);
    std::cout << "Part 2 result: " << result2 << std::endl;
    return 0;
}
