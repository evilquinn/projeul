
#include <iostream>
#include <vector>
#include <algorithm>

int find_least_common_number(std::vector<int>& arr1, std::vector<int>& arr2, std::vector<int>& arr3)
{
    std::vector<int> buf;
    std::set_intersection(arr1.begin(), arr1.end(), arr2.begin(), arr2.end(), std::back_inserter(buf));
    if ( buf.empty() ) return -1;
    using std::swap;
    swap(arr1, buf);
    buf.clear();
    std::set_intersection(arr1.begin(), arr1.end(), arr3.begin(), arr3.end(), std::back_inserter(buf));
    if ( buf.empty() ) return -1;
    return buf.front();
}

int main()
{
    std::vector<int> v1 = {6, 7, 10, 25, 30, 63, 64};
    std::vector<int> v2 = {1, 4, 5, 6, 7, 8, 50};
    std::vector<int> v3 = {1, 6, 10, 14};
    int result = find_least_common_number(v1, v2, v3);
    std::cout << "Least Common Number: " << result << std::endl;
}
