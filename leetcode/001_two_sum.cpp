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
        std::cout << "input: " << nums << ", goal: " << target << std::endl;
        std::vector<int> result;
        std::unordered_map<int, int> nums_hash;
        int idx = -1;
        std::find_if(nums.begin(),
                     nums.end(),
                     [&](const int& val)
                     {
                         auto found = nums_hash.find(target-val);
                         if ( found != std::end(nums_hash) )
                         {
                             result = { found->second, ++idx };
                             return true;
                         }
                         nums_hash.insert({ val, ++idx });
                         return false;
                     });
        return result;
    }
};

int main()
{
    auto nums = std::unordered_map<int, std::vector<int> >{ { 9, { 2, 7, 11, 15 } }, { 6, { 3, 3 } } };
    for ( auto&& inputs : nums )
    {
        std::cout << "input: " << inputs.second << ", goal: " << inputs.first << std::endl;
        auto result = solution().two_sum(inputs.second, inputs.first);
        std::cout << "result: " << result << std::endl;
    }
}
