
#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <iterator>

int trapped_water(std::vector<int> const& land)
{
    int result = 0;
    if ( land.size() == 0 ) return result;
    auto watershed = std::max_element(land.begin(), land.end());
    int curr_max = land.front();
    auto op = [&](const int& i){
        if ( curr_max < i ) curr_max = i;
        result += (curr_max - i);
    };
    std::for_each(land.begin(), watershed, op);
    curr_max = land.back();
    std::for_each(land.rbegin(), std::make_reverse_iterator(watershed), op);
    return result;
}
int trapped_water2(std::vector<int> const& land)
{
    int result = 0;
    if ( land.size() == 0 ) return result;
    auto watershed = std::max_element(land.begin(), land.end());
    std::vector<int> waterheights(land.size(), 0);
    std::partial_sum(land.begin(), watershed, waterheights.begin(), [](const int& lhs, const int& rhs){ return std::max(lhs, rhs); });
    std::partial_sum(land.rbegin(), std::make_reverse_iterator(watershed), waterheights.rbegin(), [](const int& lhs, const int& rhs){ return std::max(lhs, rhs); });
    return std::inner_product(waterheights.begin(), waterheights.end(), land.begin(), 0, std::plus{}, std::minus{});
}
int trapped_water3(std::vector<int> const& land)
{
    int result = 0;
    if ( land.size() == 0 ) return result;
    auto watershed = std::max_element(land.begin(), land.end());
    std::vector<int> waterheights(land.size(), 0);
    std::inclusive_scan(land.begin(), watershed, waterheights.begin(), [](const int& lhs, const int& rhs){ return std::max(lhs, rhs); });
    std::inclusive_scan(land.rbegin(), std::make_reverse_iterator(watershed), waterheights.rbegin(), [](const int& lhs, const int& rhs){ return std::max(lhs, rhs); });
    return std::transform_reduce(waterheights.begin(), waterheights.end(), land.begin(), 0, std::plus{}, std::minus{});
}

int main()
{
    std::vector<int> landscape = { 0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1 };
    std::cout << "result: " << trapped_water(landscape) << std::endl;
    std::cout << "result2: " << trapped_water2(landscape) << std::endl;
    std::cout << "result3: " << trapped_water3(landscape) << std::endl;
    return 0;
}
