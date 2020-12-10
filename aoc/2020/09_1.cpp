/*
 * https://adventofcode.com/2020/day/9
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <deque>
#include <algorithm>
#include <aoc/path_def.hpp>

#include <boost/multiprecision/cpp_int.hpp>

class lister
{
public:
    lister(std::istream& is, size_t preamble_size) : list_(), presort(preamble_size)
    {
        size_t idx = preamble_size;
        while ( is.good() )
        {
            list_.push_back(get_next(is));
        }
        prebegin_ = list_.begin();
        preend_ = prebegin_ + preamble_size;
        bool uhoh = false;
        while ( ! uhoh )
        {
            if ( validate(list_[idx]) )
            {
                ++prebegin_;
                ++preend_;
                ++idx;
                continue;
            }
            std::cout << "value: " << list_[idx] << " isn't valid for preamble:\n { ";
            uhoh = true;
        }
        //auto cand = find_nums_for(4, list_[idx]);
        for ( size_t i = 2; i < 1000; ++i )
        {
            auto cand = find_nums_for(i, list_[idx]);
            if ( cand > 0 )
            {
                std::cout << "found: " << cand << "\n";
                break;
            }
        }
    }
    bool validate(size_t value)
    {
        // find mid, sum will always be from num in either part
        std::partial_sort_copy(prebegin_, preend_, presort.begin(), presort.end());
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
    size_t get_next(std::istream& is)
    {
        size_t result;
        is >> result;
        return result;
    }

    boost::multiprecision::cpp_int find_nums_for(size_t num_cands, size_t sum_target)
    {
        boost::multiprecision::cpp_int cand = 0;
        for ( size_t i = 0; i < num_cands; ++i )
        {
            cand += list_[i];
        }
        size_t cont_begin = num_cands;
        for ( size_t i = num_cands; i < list_.size(); ++i )
        {
            if ( cand == sum_target )
            {
                cont_begin = i-num_cands;
                break;
            }
            cand -= list_[i-num_cands];
            cand += list_[i];
        }
        if ( cand != sum_target ) return 0;
        boost::multiprecision::cpp_int smallest = std::numeric_limits<size_t>::max();
        boost::multiprecision::cpp_int biggest = 0;
        for ( size_t j = cont_begin; j < cont_begin + num_cands; ++j )
        {
            std::cout << j << " : " << list_[j] << ", ";
            if ( list_[j] < smallest ) smallest = list_[j];
            if ( list_[j] > biggest ) biggest = list_[j];
        }
        std::cout << " : " << smallest << ", " << biggest << "\n";
        return smallest + biggest;
    }
private:
    std::vector<size_t> list_;
    std::vector<size_t> presort;
    std::vector<size_t>::iterator prebegin_;
    std::vector<size_t>::iterator preend_;
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
