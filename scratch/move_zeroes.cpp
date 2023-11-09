
#include <iostream>
#include <span>
#include <algorithm>
#include <iterator>

template<typename T>
std::ostream& operator<< (std::ostream& os, std::span<T> data)
{
    os << "{ ";
    std::string sep = "";
    for( size_t i = 0; i < data.size(); ++i )
    {
        os << sep << data.data()[i];
        sep = ", ";
    }
    return os << " }";
}

void move_zeros_to_left(int A[], size_t n)
{
    (void)A;
    (void)n;

    std::span<int> a{A, n};
    std::stable_partition(std::begin(a), std::end(a), [](const int& v){ return v == 0; });
}

int main()
{
    int v[] = {1, 10, 20, 0, 59, 63, 0, 88, 0};
    size_t n = sizeof(v) / sizeof(v[0]);

    std::cout << "Before: " << std::span{v, n} << std::endl;
    move_zeros_to_left(v, n);
    std::cout << "After : " << std::span{v, n} << std::endl;

    return 0;
}
