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

int sum_prev_three(int n)
{
    int a = 0;
    int b = 1;
    int c = 1;
    while ( n-- > 1 )
    {
        int t = a;
        a = b;
        b += t;
        t = b;
        b = c;
        c += t;
    }
    return c;
}

class jolter
{
public:
    jolter(std::istream& is)
    {
        parse_adapter_stream(is);
        for ( size_t i = 1; i < 11; ++i )
        {
            std::cout << "sum_prev_three(" << i << "): " << sum_prev_three(i) << "\n";
        }
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
    size_t calc_options()
    {
        // count how many times there's a sequence of 3 adapters sep'd by 1
        size_t one = 0;
        size_t two = 0;
        size_t three = 0;
        size_t count = 1;
        for ( size_t i = 0; i < diffs_.size(); ++i )
        {
            if ( diffs_[i] == 3 )
            {
                if ( one > 1)
                {
                    count *= sum_prev_three(one);
                }
                one = 0;
                continue;
            }
            if ( diffs_[i] == 1 )
            {
                ++one;
            }
        }
        return count;
    }
private:
    std::vector<size_t> adapters_;
    std::vector<int> diffs_;
};


int main()
{
#if 0
    std::vector<std::string> data = {
        "1\n2\n3\n4\n5\n6\n7\n8\n9",
        "16\n10\n15\n5\n1\n11\n7\n19\n6\n12\n4",
        "28\n33\n18\n42\n31\n14\n46\n20\n48\n47\n24\n23\n49\n45\n19\n"
        "38\n39\n11\n1\n32\n25\n35\n8\n17\n7\n9\n4\n2\n34\n10\n3"
    };
    for ( auto&& datum : data )
    {
        std::istringstream iss(datum);
        jolter j(iss);
        auto ans = j.calc_sum_diffs();
        auto opt = j.calc_options();
        std::cout << "answer: " << ans << ", options: " << opt << std::endl;
    }
#endif
#if 1
    std::ifstream inf(PROJEUL_AOC_PATH "/10_input.txt");
    jolter jilt(inf);
    auto result = jilt.calc_sum_diffs();
    auto opt = jilt.calc_options();
    std::cout << "result: " << result << ", options: " << opt << std::endl;
#endif
    return 0;

}
