#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <boost/lexical_cast.hpp>
#include "../path_def.hpp"

size_t find_product_for_recurs(const std::vector<size_t>& data, size_t offset, size_t num_cands, size_t sum_target)
{
    size_t result = 0;
    if ( num_cands == 2 )
    {
        for ( auto it = std::next(data.begin(), offset); it != data.end(); ++it )
        {
            if ( *it > sum_target / num_cands )
            {
                break;
            }
            size_t cand = sum_target - *it;
            if ( std::binary_search(std::next(it), data.end(), cand) )
            {
                result = *it * cand;
                //std::cout << "cands: " << num_cands << ", target: " << sum_target << ", answer: " << result << std::endl;
                break;
            }
        }
    }
    else if ( num_cands > 2 )
    {
        for ( size_t i = offset; i < data.size(); ++i )
        {
            if ( data[i] > sum_target / num_cands )
            {
                break;
            }
            size_t next_target = sum_target - data[i];
            size_t cand_result = find_product_for_recurs(data, i + 1, num_cands - 1, next_target);
            if ( cand_result != 0 )
            {
                result = data[i] * cand_result;
                //std::cout << "answer: " << result << std::endl;
                break;
            }
        }
    }
    return result;
}

size_t find_product_for(const std::vector<size_t>& data, size_t num_cands, size_t sum_target)
{
    return find_product_for_recurs(data, 0, num_cands, sum_target);
}

int main()
{
    std::ifstream inf(PROJEUL_AOC_PATH "/01_input.txt");
    std::vector<size_t> data;
    for (std::string line; std::getline(inf, line); )
    {
        data.push_back(boost::lexical_cast<size_t>(line));
    }
    std::sort(data.begin(), data.end());

    size_t result = find_product_for(data, 2, 2020);
    std::cout << "result: " << result << std::endl;
    result = find_product_for(data, 3, 2020);
    std::cout << "result: " << result << std::endl;
    return 0;
}
