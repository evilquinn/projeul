/*
 * Given an array of integers, return indices of the two numbers such that they add up to a specific target.
 *
 * You may assume that each input would have exactly one solution, and you may not use the same element twice.
 *
 * Example:
 *
 * Given nums = [2, 7, 11, 15], target = 9,
 *
 * Because nums[0] + nums[1] = 2 + 7 = 9,
 * return [0, 1].
 */
#include <iostream>
#include <vector>
#include <unordered_map>
#include <utility>
#include <algorithm>

std::ostream& operator<< (std::ostream& os, const std::vector<int>& elements)
{
    std::string sep = "[";
    for ( const auto& element : elements )
    {
        os << sep << element;
        sep = ", ";
    }
    if ( elements.empty() )
    {
        os << sep;
    }
    return os << "]";
}

class solution {
public:
    std::vector<int> two_sum(std::vector<int>& nums, int target)
    {
        std::vector<int> result;
        std::unordered_map<int, int> nums_hash;
        int idx = 0;
        std::transform(nums.begin(),
                       nums.end(),
                       std::inserter(nums_hash, nums_hash.begin()),
                       [&idx](const int& val)
                       {
                           return std::make_pair(val, idx++);
                       });
        std::find_if(nums_hash.begin(),
                     nums_hash.end(),
                     [&](const std::pair<int, int>& val)
                     {
                         const auto complement = target - ( val.first );
                         const auto found = nums_hash.find(complement);
                         if ( found != std::end(nums_hash) )
                         {
                             result.emplace_back(val.second);
                             result.emplace_back(found->second);
                             return true;
                         }
                         return false;
                     });
        return result;
    }
};

int main()
{
    auto nums = std::vector<int>{ 2, 7, 11, 15 };
    auto result = solution().two_sum(nums, 9);
    std::cout << result << std::endl;
    std::cout << nums << std::endl;
}
