/*
 * https://adventofcode.com/2020/day/9
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <deque>
#include <algorithm>
#include <aoc/path_def.hpp>

class lister
{
public:
    lister(std::istream& is, size_t preamble_size)
    {
        for ( size_t i = 0; i < preamble_size; ++i )
        {
            preamble_.push_back(get_next(is));
        }
        bool uhoh = false;
        while ( ! uhoh )
        {
            size_t next = get_next(is);
            if ( validate(next) )
            {
                insert_preamble(next);
                continue;
            }
            std::cout << "value: " << next << " isn't valid for preamble:\n { ";
            uhoh = true;
        }
    }
    bool validate(size_t value)
    {
        // find mid, sum will always be from num in either part
        std::deque<size_t> presort(preamble_.size());
        std::partial_sort_copy(preamble_.begin(), preamble_.end(), presort.begin(), presort.end());
        size_t value_mid = value / 2;
        auto premid = std::upper_bound(presort.begin(), presort.end(), value_mid);
        auto preend = std::lower_bound(premid, presort.end(), value);
        for ( auto smit = presort.begin(); smit != premid; ++smit )
        {
            auto complement = value - *smit;
            if ( std::binary_search(premid, preend, complement) ) return true;
        }
        return false;
    }
    void insert_preamble(size_t next)
    {
        preamble_.pop_front();
        preamble_.push_back(next);
    }
    size_t get_next(std::istream& is)
    {
        size_t result;
        is >> result;
        return result;
    }
private:
    std::deque<size_t> preamble_;
};


int main()
{
#if 1
    std::vector<std::string> data = {
        "35\n"
        "20\n"
        "15\n"
        "25\n"
        "47\n"
        "40\n"
        "62\n"
        "55\n"
        "65\n"
        "95\n"
        "102\n"
        "117\n"
        "150\n"
        "182\n"
        "127\n"
        "219\n"
        "299\n"
        "277\n"
        "309\n"
        "576"
    };
    for ( auto&& datum : data )
    {
        std::istringstream iss(datum);
        lister listy(iss, 5);
    }
#endif
#if 1
    std::ifstream inf(PROJEUL_AOC_PATH "/09_input.txt");
    lister listy(inf, 25);
#endif
    return 0;

}
