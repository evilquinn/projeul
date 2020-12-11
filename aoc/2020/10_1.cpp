/*
 * https://adventofcode.com/2020/day/10
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <cmath>

#include <aoc/path_def.hpp>

class jolter
{
public:
    jolter(std::istream& is)
    {
        parse_adapter_stream(is);
    }
    void parse_adapter_stream(std::istream& is)
    {
        adapters_.push_back(0);
        while ( is )
        {
            size_t cand = 0;
            is >> cand;
            if ( cand > 0 ) adapters_.push_back(cand);
        }
        std::sort(adapters_.begin(), adapters_.end());
        adapters_.push_back(adapters_.back() + 3);

        for ( size_t i = 1; i < adapters_.size(); ++i )
        {
            diffs_.push_back(adapters_[i] - adapters_[i-1]);
        }
    }
    size_t calc_sum_diffs()
    {
        size_t num_ones = 0;
        size_t num_threes = 0;
        for ( size_t i = 0; i < diffs_.size(); ++i )
        {
            if ( diffs_[i] == 1 ) ++num_ones;
            else if ( diffs_[i] == 3 ) ++num_threes;
            else std::cout << "huh? diff of: " << diffs_[i] << "\n";
        }
        return num_threes * num_ones;
    }
private:
    std::vector<size_t> adapters_;
    std::vector<int> diffs_;
};


int main()
{
#if 0
    std::vector<std::string> data = {
    };
    for ( auto&& datum : data )
    {
    }
#endif
#if 1
    std::ifstream inf(PROJEUL_AOC_PATH "/10_input.txt");
    jolter jilt(inf);
    auto result = jilt.calc_sum_diffs();
    std::cout << "result: " << result << std::endl;
#endif
    return 0;

}
