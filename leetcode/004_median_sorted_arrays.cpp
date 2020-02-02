/*
 * There are two sorted arrays nums1 and nums2 of size m and n respectively.
 *
 * Find the median of the two sorted arrays. The overall run time complexity should be O(log (m+n)).
 *
 * You may assume nums1 and nums2 cannot be both empty.
 *
 * Example 1:
 *
 * nums1 = [1, 3]
 * nums2 = [2]
 *
 * The median is 2.0
 *
 * Example 2:
 *
 * nums1 = [1, 2]
 * nums2 = [3, 4]
 *
 * The median is (2 + 3)/2 = 2.5
 *
 */
#include <iostream>
#include <vector>
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
    static double median_sorted_arrays(std::vector<int>& nums1, std::vector<int>& nums2)
    {
        std::vector<int>* shorter = &nums1;
        std::vector<int>* longer = &nums2;
        if ( nums2.size() < nums1.size() )
        {
            shorter = &nums2;
            longer = &nums1;
        }
        longer->insert(longer->end(), shorter->begin(), shorter->end());
        auto midpoint = std::next(longer->begin(), longer->size()/2);
        bool even_length = ( longer->size() % 2 ) == 0;
        std::nth_element(longer->begin(), midpoint, longer->end());
        double result = *midpoint;
        if ( even_length )
        {
            result = ( result + *std::max_element(longer->begin(), midpoint) ) / 2.0;
        }
        return result;
    }
};

int main()
{
    std::vector<std::pair<std::vector<int>, std::vector<int> > > data =
    {
        { { 1, 2 }, { 3, 4 } },
        { { 1, 2, 5, 9, 9, 9, 10 }, { 0, 3, 3, 4, 5, 6, 10 } }
    };
    for ( auto&& datum : data )
    {
        std::cout << "input: " << datum.first << ", " << datum.second;
        auto result = solution::median_sorted_arrays(datum.first, datum.second);
        std::cout << ", result: " << result << std::endl;
    }
}
